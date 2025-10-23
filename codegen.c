#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"
#include "semantic.h"

FILE* output;
int tempReg = 0;
int tempFloatReg = 0;  /* for $f0-$f7 temporaries */
int strLabelCount = 0;  /* counter for unique string labels */
int concatEmitted = 0;  /* emit concat helper only once */
char* strLiterals[200];
int strLitCount = 0;
int floatLabelCount = 0; /* counter for float literal labels */
float floatLiterals[200]; /* store float literals */
int floatLitCount = 0;

/* Add string literal to the pool if missing, return its label index */
int addStrLiteralIfMissing(const char* s) {
    for (int i = 0; i < strLitCount; i++) {
        if (strcmp(strLiterals[i], s) == 0) return i;
    }
    strLiterals[strLitCount++] = strdup(s);
    return strLitCount - 1;
}

/* Walk the AST and collect all string and float literals before codegen */
void collectStringLiterals(ASTNode* node) {
    if (!node) return;
    switch (node->type) {
        case NODE_STR:
            addStrLiteralIfMissing(node->data.str);
            break;
        case NODE_FLOAT:
            floatLiterals[floatLitCount++] = node->data.fnum;
            break;
        case NODE_BINOP:
            collectStringLiterals(node->data.binop.left);
            collectStringLiterals(node->data.binop.right);
            break;
        case NODE_ASSIGN:
            collectStringLiterals(node->data.assign.value);
            break;
        case NODE_PRINT:
            collectStringLiterals(node->data.expr);
            break;
        case NODE_STMT_LIST:
            collectStringLiterals(node->data.stmtlist.stmt);
            collectStringLiterals(node->data.stmtlist.next);
            break;
        case NODE_ARRAY_ASSIGN:
            collectStringLiterals(node->data.arrayAssign.index);
            collectStringLiterals(node->data.arrayAssign.value);
            break;
        case NODE_ARRAY_ACCESS:
            collectStringLiterals(node->data.arrayAccess.index);
            break;
        case NODE_FUNC_DECL:
            collectStringLiterals(node->data.funcDecl.body);
            break;
        case NODE_FUNC_CALL:
            collectStringLiterals(node->data.funcCall.args);
            break;
        case NODE_RETURN:
            collectStringLiterals(node->data.returnStmt.value);
            break;
        default:
            break;
    }
}

int getNextTemp() {
    int reg = tempReg++;
    if (tempReg > 7) tempReg = 0;  // Reuse $t0-$t7
    return reg;
}

int getNextFloatTemp() {
    int reg = tempFloatReg;
    tempFloatReg += 2;  // MIPS float regs work in pairs: $f0-$f1, $f2-$f3, etc.
    if (tempFloatReg > 14) tempFloatReg = 0;  // Reuse $f0-$f15
    return reg;
}

/* Helper: detect if an AST expression is a string or string variable */
/* Use the semantic exprType (more accurate) instead of ad-hoc heuristics */
int exprIsString(ASTNode* node) {
    if (!node) return 0;
    int t = exprType(node);
    return t == TYPE_STRING;
}

void genExpr(ASTNode* node) {
    if (!node) return;

    int nodeType = exprType(node);

    switch(node->type) {
        case NODE_NUM:
            fprintf(output, "    li $t%d, %d\n", getNextTemp(), node->data.num);
            break;

        case NODE_FLOAT: {
            /* For float literals, find its index in the collected literals */
            int labelIdx = -1;
            for (int i = 0; i < floatLitCount; i++) {
                if (floatLiterals[i] == node->data.fnum) {
                    labelIdx = i;
                    break;
                }
            }
            if (labelIdx == -1) {
                /* Not found - add it now (shouldn't happen if collectStringLiterals was called) */
                labelIdx = floatLitCount;
                floatLiterals[floatLitCount++] = node->data.fnum;
            }
            fprintf(output, "    # Load float literal %f\n", node->data.fnum);
            fprintf(output, "    la $t0, float_literal_%d\n", labelIdx);
            fprintf(output, "    lwc1 $f%d, 0($t0)\n", getNextFloatTemp());
            break;
        }

        case NODE_STR: {
            /* Use the pool and load address of the string literal */
            int label = addStrLiteralIfMissing(node->data.str);
            fprintf(output, "    # load address of string literal\n");
            fprintf(output, "    la $t%d, str_literal_%d\n", getNextTemp(), label);
            /* also emit the data label (collected later by generateMIPS) */
            /* For simplicity, we will emit data labels immediately at top of file in generateMIPS */
            /* But here we only record label by emitting a comment - actual labels will be written in data sect */
            break;
        }
            
        case NODE_VAR: {
            int offset = getVarOffset(node->data.name);
            if (offset == -1) {
                fprintf(stderr, "Error: Variable %s not declared\n", node->data.name);
                exit(1);
            }
            if (isFloatVar(node->data.name)) {
                fprintf(output, "    lwc1 $f%d, %d($sp)\n", getNextFloatTemp(), offset);
            } else {
                fprintf(output, "    lw $t%d, %d($sp)\n", getNextTemp(), offset);
            }
            break;
        }
        
        case NODE_BINOP: {
            int resultType = exprType(node);

            /* If semantic type says this expression is a string, treat '+' as string concatenation */
            if (node->data.binop.op == '+' && exprIsString(node)) {
                /* generate left and right into temporaries */
                genExpr(node->data.binop.left);
                int leftReg = tempReg - 1;
                genExpr(node->data.binop.right);
                int rightReg = tempReg - 1;

                /* move operands into $a0/$a1 and call concat helper */
                fprintf(output, "    # String concatenation\n");
                fprintf(output, "    move $a0, $t%d\n", leftReg);
                fprintf(output, "    move $a1, $t%d\n", rightReg);
                fprintf(output, "    jal concat\n");
                /* move returned pointer ($v0) into a temp */
                int dest = getNextTemp();
                fprintf(output, "    move $t%d, $v0\n", dest);
                tempReg = dest + 1;
            } else if (resultType == TYPE_FLOAT) {
                /* Float arithmetic */
                int leftType = exprType(node->data.binop.left);
                int rightType = exprType(node->data.binop.right);

                genExpr(node->data.binop.left);
                int leftReg = (leftType == TYPE_FLOAT) ? (tempFloatReg - 2) : (tempReg - 1);

                genExpr(node->data.binop.right);
                int rightReg = (rightType == TYPE_FLOAT) ? (tempFloatReg - 2) : (tempReg - 1);

                /* Handle int->float conversion if needed */
                int leftFloatReg = leftReg;
                int rightFloatReg = rightReg;

                if (leftType == TYPE_INT) {
                    /* Convert int to float */
                    fprintf(output, "    # Convert int to float\n");
                    fprintf(output, "    mtc1 $t%d, $f%d\n", leftReg, getNextFloatTemp());
                    fprintf(output, "    cvt.s.w $f%d, $f%d\n", tempFloatReg-2, tempFloatReg-2);
                    leftFloatReg = tempFloatReg - 2;
                }

                if (rightType == TYPE_INT) {
                    /* Convert int to float */
                    fprintf(output, "    # Convert int to float\n");
                    fprintf(output, "    mtc1 $t%d, $f%d\n", rightReg, getNextFloatTemp());
                    fprintf(output, "    cvt.s.w $f%d, $f%d\n", tempFloatReg-2, tempFloatReg-2);
                    rightFloatReg = tempFloatReg - 2;
                }

                if (node->data.binop.op == '+') {
                    fprintf(output, "    # Float addition\n");
                    fprintf(output, "    add.s $f%d, $f%d, $f%d\n", leftFloatReg, leftFloatReg, rightFloatReg);
                    tempFloatReg = leftFloatReg + 2;
                } else if (node->data.binop.op == '-') {
                    fprintf(output, "    # Float subtraction\n");
                    fprintf(output, "    sub.s $f%d, $f%d, $f%d\n", leftFloatReg, leftFloatReg, rightFloatReg);
                    tempFloatReg = leftFloatReg + 2;
                }
            } else {
                /* Integer arithmetic */
                genExpr(node->data.binop.left);
                int leftReg = tempReg - 1;
                genExpr(node->data.binop.right);
                int rightReg = tempReg - 1;

                if (node->data.binop.op == '+') {
                    fprintf(output, "    # Addition\n");
                    fprintf(output, "    add $t%d, $t%d, $t%d\n", leftReg, leftReg, rightReg);
                    tempReg = leftReg + 1;  // Result in leftReg
                } else if (node->data.binop.op == '-') {
                    fprintf(output, "    # Subtraction\n");
                    fprintf(output, "    sub $t%d, $t%d, $t%d\n", leftReg, leftReg, rightReg);
                    tempReg = leftReg + 1;  // Result in leftReg
                } else if (node->data.binop.op == '*') {
                    fprintf(output, "    # Multiplication\n");
                    fprintf(output, "    mul $t%d, $t%d, $t%d\n", leftReg, leftReg, rightReg);
                    tempReg = leftReg + 1;  // Result in leftReg
                } else if (node->data.binop.op == '/') {
                    fprintf(output, "    # Division\n");
                    fprintf(output, "    div $t%d, $t%d, $t%d\n", leftReg, leftReg, rightReg);
                    tempReg = leftReg + 1;  // Result in leftReg
                }
            }
            break;
        }

        case NODE_ARRAY_ACCESS: {
            /* Generate code for array access */
            if (!isArrayVar(node->data.arrayAccess.name)) {
                fprintf(stderr, "Error: %s is not an array\n", node->data.arrayAccess.name);
                exit(1);
            }

            /* Generate code for index expression */
            genExpr(node->data.arrayAccess.index);
            int indexReg = tempReg - 1;

            /* Calculate array element address and load value */
            int baseOffset = getVarOffset(node->data.arrayAccess.name);
            int resultReg = getNextTemp();

            fprintf(output, "    # Array access: %s[index]\n", node->data.arrayAccess.name);
            fprintf(output, "    sll $t%d, $t%d, 2    # index * 4\n", indexReg, indexReg);
            fprintf(output, "    addi $t%d, $sp, %d   # base address\n", resultReg, baseOffset);
            fprintf(output, "    add $t%d, $t%d, $t%d # element address\n",
                resultReg, resultReg, indexReg);
            fprintf(output, "    lw $t%d, 0($t%d)     # load value\n",
                resultReg, resultReg);
            break;
        }

        case NODE_FUNC_CALL: {
            /* Function call: funcName(args) */
            fprintf(output, "    # Function call: %s\n", node->data.funcCall.name);

            /* Step 1: Evaluate arguments and place in $a0-$a3 */
            ASTNode* arg = node->data.funcCall.args;
            int argNum = 0;

            while (arg && argNum < 4) {
                ASTNode* argExpr;

                /* Extract actual expression from stmt_list structure */
                if (arg->type == NODE_STMT_LIST) {
                    /* Check if stmt is also a stmt_list (nested case for 3+ args) */
                    if (arg->data.stmtlist.stmt &&
                        arg->data.stmtlist.stmt->type == NODE_STMT_LIST) {
                        /* Recursively process the nested stmt_list first */
                        ASTNode* nested = arg->data.stmtlist.stmt;
                        while (nested && argNum < 4) {
                            if (nested->type == NODE_STMT_LIST) {
                                genExpr(nested->data.stmtlist.stmt);
                                int argReg = (tempReg > 0) ? tempReg - 1 : 0;
                                fprintf(output, "    move $a%d, $t%d    # Arg %d\n",
                                        argNum, argReg, argNum);
                                argNum++;
                                nested = nested->data.stmtlist.next;
                            } else {
                                genExpr(nested);
                                int argReg = (tempReg > 0) ? tempReg - 1 : 0;
                                fprintf(output, "    move $a%d, $t%d    # Arg %d\n",
                                        argNum, argReg, argNum);
                                argNum++;
                                nested = NULL;
                            }
                        }
                        /* Now process the final argument (next) */
                        arg = arg->data.stmtlist.next;
                        if (arg && argNum < 4) {
                            genExpr(arg);
                            int argReg = (tempReg > 0) ? tempReg - 1 : 0;
                            fprintf(output, "    move $a%d, $t%d    # Arg %d\n",
                                    argNum, argReg, argNum);
                            argNum++;
                        }
                        break;
                    } else {
                        /* Normal case: stmt is an expression */
                        argExpr = arg->data.stmtlist.stmt;
                        genExpr(argExpr);
                        int argReg = (tempReg > 0) ? tempReg - 1 : 0;
                        fprintf(output, "    move $a%d, $t%d    # Arg %d\n",
                                argNum, argReg, argNum);
                        argNum++;
                        arg = arg->data.stmtlist.next;
                    }
                } else {
                    /* Single argument */
                    genExpr(arg);
                    int argReg = (tempReg > 0) ? tempReg - 1 : 0;
                    fprintf(output, "    move $a%d, $t%d    # Arg %d\n",
                            argNum, argReg, argNum);
                    argNum++;
                    arg = NULL;
                }
            }

            /* Step 2: Call the function */
            fprintf(output, "    jal %s             # Call function\n",
                    node->data.funcCall.name);

            /* Step 3: Get result from $v0 and put in temp register */
            int resultReg = getNextTemp();
            fprintf(output, "    move $t%d, $v0      # Get return value\n", resultReg);

            break;
        }

        default:
            break;
    }
}

void genStmt(ASTNode* node) {
    if (!node) return;
    
    switch(node->type) {
        case NODE_DECL: {
            /* Add variable to symbol table during code generation */
            int offset = addVar(node->data.name);
            if (offset == -1) {
                /* Already declared - get existing offset */
                offset = getVarOffset(node->data.name);
            }
            fprintf(output, "    # Declared %s at offset %d\n", node->data.name, offset);
            break;
        }
        case NODE_FLOAT_DECL: {
            /* Add float variable to symbol table during code generation */
            int offset = addFloatVar(node->data.name);
            if (offset == -1) {
                /* Already declared - get existing offset */
                offset = getVarOffset(node->data.name);
            }
            fprintf(output, "    # Declared float %s at offset %d\n", node->data.name, offset);
            break;
        }
        case NODE_STR_DECL: {
            /* Add string variable to symbol table during code generation */
            int offset = addStringVar(node->data.name);
            if (offset == -1) {
                /* Already declared - get existing offset */
                offset = getVarOffset(node->data.name);
            }
            fprintf(output, "    # Declared string %s at offset %d\n", node->data.name, offset);
            break;
        }
        
        case NODE_ASSIGN: {
            int offset = getVarOffset(node->data.assign.var);
            if (offset == -1) {
                fprintf(stderr, "Error: Variable %s not declared\n", node->data.assign.var);
                exit(1);
            }
            int varType = isFloatVar(node->data.assign.var) ? TYPE_FLOAT :
                         (isStringVar(node->data.assign.var) ? TYPE_STRING : TYPE_INT);
            int exprTypeVal = exprType(node->data.assign.value);

            genExpr(node->data.assign.value);

            if (varType == TYPE_FLOAT) {
                if (exprTypeVal == TYPE_INT) {
                    /* Convert int to float before storing */
                    fprintf(output, "    # Convert int to float for assignment\n");
                    fprintf(output, "    mtc1 $t%d, $f%d\n", tempReg - 1, getNextFloatTemp());
                    fprintf(output, "    cvt.s.w $f%d, $f%d\n", tempFloatReg-2, tempFloatReg-2);
                    fprintf(output, "    swc1 $f%d, %d($sp)\n", tempFloatReg - 2, offset);
                } else {
                    fprintf(output, "    swc1 $f%d, %d($sp)\n", tempFloatReg - 2, offset);
                }
                tempFloatReg = 0;
            } else {
                fprintf(output, "    sw $t%d, %d($sp)\n", tempReg - 1, offset);
            }
            tempReg = 0;
            break;
        }
        
        case NODE_PRINT: {
            int printType = exprType(node->data.expr);
            genExpr(node->data.expr);
            /* Decide by semantic type */
            if (exprIsString(node->data.expr)) {
                /* If expression is string, ensure we have a pointer in $tX or load it */
                if (node->data.expr->type == NODE_VAR) {
                    int off = getVarOffset(node->data.expr->data.name);
                    if (off == -1) {
                        fprintf(stderr, "Error: Variable %s not declared\n", node->data.expr->data.name);
                        exit(1);
                    }
                    fprintf(output, "    # Print string variable %s\n", node->data.expr->data.name);
                    fprintf(output, "    lw $a0, %d($sp)\n", off);
                } else {
                    fprintf(output, "    # Print string expression\n");
                    fprintf(output, "    move $a0, $t%d\n", tempReg - 1);
                }
                fprintf(output, "    li $v0, 4\n");
                fprintf(output, "    syscall\n");
            } else if (printType == TYPE_FLOAT) {
                /* Float */
                fprintf(output, "    # Print float\n");
                fprintf(output, "    mov.s $f12, $f%d\n", tempFloatReg - 2);
                fprintf(output, "    li $v0, 2\n");
                fprintf(output, "    syscall\n");
                tempFloatReg = 0;
            } else {
                /* Integer */
                fprintf(output, "    # Print integer (expr)\n");
                fprintf(output, "    move $a0, $t%d\n", tempReg - 1);
                fprintf(output, "    li $v0, 1\n");
                fprintf(output, "    syscall\n");
            }
            /* Print newline */
            fprintf(output, "    li $v0, 11\n");
            fprintf(output, "    li $a0, 10\n");
            fprintf(output, "    syscall\n");
            tempReg = 0;
            break;
        }
            
        case NODE_STMT_LIST:
            genStmt(node->data.stmtlist.stmt);
            genStmt(node->data.stmtlist.next);
            break;

        case NODE_ARRAY_DECL: {
            /* Add array to symbol table during code generation */
            int offset = addArrayVar(node->data.arrayDecl.name, node->data.arrayDecl.size);
            if (offset == -1) {
                /* Already declared - get existing offset */
                offset = getVarOffset(node->data.arrayDecl.name);
            }
            fprintf(output, "    # Declared array %s[%d] at offset %d\n",
                node->data.arrayDecl.name, node->data.arrayDecl.size, offset);
            break;
        }
    
        case NODE_ARRAY_ASSIGN: {
            /* Generate code for array assignment */
            if (!isArrayVar(node->data.arrayAssign.name)) {
                fprintf(stderr, "Error: %s is not an array\n", node->data.arrayAssign.name);
                exit(1);
            }

            /* Generate code for index expression */
            genExpr(node->data.arrayAssign.index);
            int indexReg = tempReg - 1;

            /* Generate code for value expression */
            genExpr(node->data.arrayAssign.value);
            int valueReg = tempReg - 1;

            /* Calculate array element address */
            int baseOffset = getVarOffset(node->data.arrayAssign.name);
            int addressReg = getNextTemp();

            fprintf(output, "    # Array assignment: %s[index] = value\n",
                node->data.arrayAssign.name);
            fprintf(output, "    sll $t%d, $t%d, 2    # index * 4\n", indexReg, indexReg);
            fprintf(output, "    addi $t%d, $sp, %d   # base address\n", addressReg, baseOffset);
            fprintf(output, "    add $t%d, $t%d, $t%d # element address\n",
                addressReg, addressReg, indexReg);
            fprintf(output, "    sw $t%d, 0($t%d)     # store value\n",
                valueReg, addressReg);
            tempReg = 0;
            break;
        }

        case NODE_FUNC_DECL: {
            /* Function declaration: # funcName(params) { body } */

            /* Add function to global scope */
            addFunction(node->data.funcDecl.name, "int", NULL, 0);

            fprintf(output, "\n# Function: %s\n", node->data.funcDecl.name);
            fprintf(output, "%s:\n", node->data.funcDecl.name);

            /* Enter new scope for function */
            enterScope();

            /* Add parameters to scope */
            ASTNode* param = node->data.funcDecl.params;
            int paramNum = 0;
            while (param && paramNum < 4) {
                addParameter(param->data.param.name, param->data.param.type);
                param = param->data.param.next;
                paramNum++;
            }

            /* PROLOGUE: Set up stack frame */
            /* Calculate frame size: 8 bytes (ra + fp) + local variables */
            int frameSize = 32;  /* Start with 32 bytes for simplicity */

            fprintf(output, "    # Function prologue\n");
            fprintf(output, "    addi $sp, $sp, -%d    # Allocate stack frame\n", frameSize);
            fprintf(output, "    sw $ra, %d($sp)      # Save return address\n", frameSize - 4);
            fprintf(output, "    sw $fp, %d($sp)      # Save frame pointer\n", frameSize - 8);
            fprintf(output, "    move $fp, $sp        # Set new frame pointer\n");

            /* Parameters are in $a0-$a3 (or $f12-$f14 for floats), store them on stack */
            param = node->data.funcDecl.params;
            paramNum = 0;
            fprintf(output, "    # Store parameters\n");
            while (param && paramNum < 4) {
                int paramOffset = getVarOffset(param->data.param.name);
                if (paramOffset != -1) {
                    if (strcmp(param->data.param.type, "float") == 0) {
                        /* Float parameters come in $f12, $f13, $f14 for the first 3 */
                        /* For simplicity, we'll assume they're passed via int registers and converted */
                        fprintf(output, "    mtc1 $a%d, $f0       # Move param to float reg\n", paramNum);
                        fprintf(output, "    swc1 $f0, %d($sp)    # Store float param '%s'\n",
                                paramOffset, param->data.param.name);
                    } else {
                        fprintf(output, "    sw $a%d, %d($sp)     # Store param '%s'\n",
                                paramNum, paramOffset, param->data.param.name);
                    }
                }
                paramNum++;
                param = param->data.param.next;
            }

            /* Generate function body */
            fprintf(output, "    # Function body\n");
            genStmt(node->data.funcDecl.body);

            /* EPILOGUE: Default return (if no explicit return) */
            fprintf(output, "    # Function epilogue (default return)\n");
            fprintf(output, "%s_return:\n", node->data.funcDecl.name);
            fprintf(output, "    lw $fp, %d($sp)      # Restore frame pointer\n", frameSize - 8);
            fprintf(output, "    lw $ra, %d($sp)      # Restore return address\n", frameSize - 4);
            fprintf(output, "    addi $sp, $sp, %d    # Deallocate stack frame\n", frameSize);
            fprintf(output, "    jr $ra               # Return to caller\n");

            /* Exit function scope */
            exitScope();

            break;
        }

        case NODE_RETURN: {
            /* Return statement: return expr; or return; */
            fprintf(output, "    # Return statement\n");

            if (node->data.returnStmt.value) {
                /* Evaluate return expression */
                int retType = exprType(node->data.returnStmt.value);
                genExpr(node->data.returnStmt.value);

                /* Move result to $v0 or $f0 depending on type */
                if (retType == TYPE_FLOAT) {
                    fprintf(output, "    mov.s $f0, $f%d      # Set float return value\n",
                            (tempFloatReg > 0) ? tempFloatReg - 2 : 0);
                } else {
                    int regNum = (tempReg > 0) ? tempReg - 1 : 0;
                    fprintf(output, "    move $v0, $t%d       # Set return value\n", regNum);
                }
            }

            /* Jump to function epilogue (handled in NODE_FUNC_DECL) */
            /* For now, inline the epilogue here */
            int frameSize = 32;
            fprintf(output, "    lw $fp, %d($sp)      # Restore frame pointer\n", frameSize - 8);
            fprintf(output, "    lw $ra, %d($sp)      # Restore return address\n", frameSize - 4);
            fprintf(output, "    addi $sp, $sp, %d    # Deallocate stack frame\n", frameSize);
            fprintf(output, "    jr $ra               # Return to caller\n");

            break;
        }

        case NODE_FUNC_CALL: {
            /* Function call as statement (ignore return value) */
            genExpr(node);
            tempReg = 0;
            break;
        }

        default:
            break;
    }
}

/* Helper: Generate only function declarations from AST */
void genFunctionsOnly(ASTNode* node) {
    if (!node) return;

    if (node->type == NODE_FUNC_DECL) {
        genStmt(node);
    } else if (node->type == NODE_STMT_LIST) {
        genFunctionsOnly(node->data.stmtlist.stmt);
        genFunctionsOnly(node->data.stmtlist.next);
    }
}

/* Helper: Generate only non-function statements from AST */
void genStatementsOnly(ASTNode* node) {
    if (!node) return;

    if (node->type == NODE_FUNC_DECL) {
        // Skip function declarations
        return;
    } else if (node->type == NODE_STMT_LIST) {
        genStatementsOnly(node->data.stmtlist.stmt);
        genStatementsOnly(node->data.stmtlist.next);
    } else {
        genStmt(node);
    }
}

void generateMIPS(ASTNode* root, const char* filename) {
    output = fopen(filename, "w");
    if (!output) {
        fprintf(stderr, "Cannot open output file %s\n", filename);
        exit(1);
    }
    
    // Symbol table should already be initialized by main and populated during semantic check

    // Collect string literals from the AST before emitting code so labels are known
    collectStringLiterals(root);

    // MIPS program header
    fprintf(output, ".data\n");
    /* Emit collected string literals */
    for (int i = 0; i < strLitCount; i++) {
        fprintf(output, "str_literal_%d: .asciiz \"%s\"\n", i, strLiterals[i]);
    }
    /* Emit collected float literals */
    for (int i = 0; i < floatLitCount; i++) {
        fprintf(output, "float_literal_%d: .float %f\n", i, floatLiterals[i]);
    }
    fprintf(output, "\n.text\n");
    fprintf(output, ".globl main\n");
    fprintf(output, "main:\n");
    
    // Allocate stack space (max 100 variables * 4 bytes)
    fprintf(output, "    # Allocate stack space\n");
    fprintf(output, "    addi $sp, $sp, -400\n");
    fprintf(output, "    j main_code        # Jump to main program\n\n");

    // First pass: Generate only function definitions
    genFunctionsOnly(root);

    // Label for actual main code
    fprintf(output, "\nmain_code:\n");

    // Second pass: Generate non-function statements
    genStatementsOnly(root);
    
    // Program exit
    fprintf(output, "\n    # Exit program\n");
    fprintf(output, "    addi $sp, $sp, 400\n");
    fprintf(output, "    li $v0, 10\n");
    fprintf(output, "    syscall\n");
    
    /* Emit concat helper if needed */
    if (strLitCount > 0 && !concatEmitted) {
        concatEmitted = 1;
        fprintf(output, "\n# concat helper - allocate and concatenate two asciiz strings\n");
        fprintf(output, "# Inputs: a0 = ptr1, a1 = ptr2; Returns: v0 = ptr to new buffer\n");
        fprintf(output, "concat:\n");
        /* save callee-saved registers we will use: ra, s0-s2 */
        fprintf(output, "    addi $sp, $sp, -32\n");
        fprintf(output, "    sw $ra, 28($sp)\n");
        fprintf(output, "    sw $s0, 24($sp)\n");
        fprintf(output, "    sw $s1, 20($sp)\n");
        fprintf(output, "    sw $s2, 16($sp)\n");

        /* Save original pointers in s1 and s2 */
        fprintf(output, "    move $s1, $a0\n");
        fprintf(output, "    move $s2, $a1\n");

        /* strlen(s1) -> t1 */
        fprintf(output, "    move $t0, $s1\n");
        fprintf(output, "    li $t1, 0\n");
        fprintf(output, "strlen_loop1:\n");
        fprintf(output, "    lb $t2, 0($t0)\n");
        fprintf(output, "    beq $t2, $zero, strlen_done1\n");
        fprintf(output, "    addi $t1, $t1, 1\n");
        fprintf(output, "    addi $t0, $t0, 1\n");
        fprintf(output, "    j strlen_loop1\n");
        fprintf(output, "strlen_done1:\n");

        /* strlen(s2) -> t2 */
        fprintf(output, "    move $t0, $s2\n");
        fprintf(output, "    li $t2, 0\n");
        fprintf(output, "strlen_loop2:\n");
        fprintf(output, "    lb $t3, 0($t0)\n");
        fprintf(output, "    beq $t3, $zero, strlen_done2\n");
        fprintf(output, "    addi $t2, $t2, 1\n");
        fprintf(output, "    addi $t0, $t0, 1\n");
        fprintf(output, "    j strlen_loop2\n");
        fprintf(output, "strlen_done2:\n");

        /* allocate t1 + t2 + 1 bytes using syscall 9 */
        fprintf(output, "    add $a0, $t1, $t2\n");
        fprintf(output, "    addi $a0, $a0, 1\n");
        fprintf(output, "    li $v0, 9\n");
        fprintf(output, "    syscall\n");
        fprintf(output, "    move $s0, $v0    # s0 = dest ptr\n");

        /* copy bytes from s1 into dest */
        fprintf(output, "    move $t6, $s1\n");
        fprintf(output, "    move $t7, $s0\n");
        fprintf(output, "copy1_loop:\n");
        fprintf(output, "    lb $t8, 0($t6)\n");
        fprintf(output, "    beq $t8, $zero, copy1_done\n");
        fprintf(output, "    sb $t8, 0($t7)\n");
        fprintf(output, "    addi $t6, $t6, 1\n");
        fprintf(output, "    addi $t7, $t7, 1\n");
        fprintf(output, "    j copy1_loop\n");
        fprintf(output, "copy1_done:\n");

        /* copy bytes from s2 into dest (continuing at t7) */
        fprintf(output, "    move $t6, $s2\n");
        fprintf(output, "copy2_loop:\n");
        fprintf(output, "    lb $t8, 0($t6)\n");
        fprintf(output, "    beq $t8, $zero, copy2_done\n");
        fprintf(output, "    sb $t8, 0($t7)\n");
        fprintf(output, "    addi $t6, $t6, 1\n");
        fprintf(output, "    addi $t7, $t7, 1\n");
        fprintf(output, "    j copy2_loop\n");
        fprintf(output, "copy2_done:\n");

        /* null terminator */
        fprintf(output, "    sb $zero, 0($t7)\n");

        /* return pointer in v0 */
        fprintf(output, "    move $v0, $s0\n");

        /* restore regs and return */
        fprintf(output, "    lw $s2, 16($sp)\n");
        fprintf(output, "    lw $s1, 20($sp)\n");
        fprintf(output, "    lw $s0, 24($sp)\n");
        fprintf(output, "    lw $ra, 28($sp)\n");
        fprintf(output, "    addi $sp, $sp, 32\n");
        fprintf(output, "    jr $ra\n\n");
    }
    fclose(output);
}