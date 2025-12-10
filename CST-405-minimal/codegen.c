#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "symtab.h"
#include "semantic.h"
#include "parser.tab.h"

/* Helper function to flatten argument list */
static void collectArgs(ASTNode* node, ASTNode** argArray, int* count, int maxArgs) {
    if (!node || *count >= maxArgs) return;

    if (node->type == NODE_STMT_LIST) {
        /* Recursively collect from left (stmt) first */
        collectArgs(node->data.stmtlist.stmt, argArray, count, maxArgs);
        /* Then collect from right (next) */
        collectArgs(node->data.stmtlist.next, argArray, count, maxArgs);
    } else {
        /* This is an actual argument expression */
        argArray[(*count)++] = node;
    }
}

/* Helper function to calculate local variable storage size for a function body */
static int calculateLocalVarSize(ASTNode* node) {
    if (!node) return 0;

    int size = 0;

    switch (node->type) {
        case NODE_DECL:
            /* Regular variable: 4 bytes */
            size = 4;
            break;
        case NODE_ARRAY_DECL:
            /* Array: size * 4 bytes */
            size = node->data.arrayDecl.size * 4;
            break;
        case NODE_STMT_LIST:
            /* Recursively calculate for both stmt and next */
            size = calculateLocalVarSize(node->data.stmtlist.stmt) +
                   calculateLocalVarSize(node->data.stmtlist.next);
            break;
        case NODE_IF:
            /* Check both then and else branches for local declarations */
            size = calculateLocalVarSize(node->data.ifStmt.thenStmt);
            if (node->data.ifStmt.elseStmt) {
                size += calculateLocalVarSize(node->data.ifStmt.elseStmt);
            }
            break;
        case NODE_WHILE:
            /* Check loop body for local declarations */
            size = calculateLocalVarSize(node->data.whileLoop.body);
            break;
        default:
            /* Other nodes don't declare local variables */
            break;
    }

    return size;
}

FILE* output;
int tempReg = 0;
int tempFloatReg = 0;  /* for $f0-$f7 temporaries */
int strLabelCount = 0;  /* counter for unique string labels */
int concatEmitted = 0;  /* emit concat helper only once */
int currentFrameSize = 128;  /* Frame size for current function being generated */
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
        case NODE_IF:
            collectStringLiterals(node->data.ifStmt.condition);
            collectStringLiterals(node->data.ifStmt.thenStmt);
            if (node->data.ifStmt.elseStmt) {
                collectStringLiterals(node->data.ifStmt.elseStmt);
            }
            break;
        case NODE_WHILE:
            collectStringLiterals(node->data.whileLoop.condition);
            collectStringLiterals(node->data.whileLoop.body);
            break;
        case NODE_COMPARE:
            collectStringLiterals(node->data.compare.left);
            collectStringLiterals(node->data.compare.right);
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
                int leftReg = (leftType == TYPE_FLOAT) ? (tempFloatReg - 2) : ((tempReg == 0) ? 7 : tempReg - 1);

                genExpr(node->data.binop.right);
                int rightReg = (rightType == TYPE_FLOAT) ? (tempFloatReg - 2) : ((tempReg == 0) ? 7 : tempReg - 1);

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
                if (leftReg < 0) leftReg = 0;  // Safety check
                genExpr(node->data.binop.right);
                int rightReg = tempReg - 1;
                if (rightReg < 0) rightReg = 0;  // Safety check

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
                    fprintf(output, "    div $t%d, $t%d      # Divide: result in LO\n", leftReg, rightReg);
                    fprintf(output, "    mflo $t%d           # Move quotient from LO\n", leftReg);
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

            /* Calculate array element address and load value */
            int baseOffset = getVarOffset(node->data.arrayAccess.name);
            int baseReg = getNextTemp();

            /* Generate code for index expression */
            genExpr(node->data.arrayAccess.index);
            int indexReg = (tempReg == 0) ? 7 : tempReg - 1;

            fprintf(output, "    # Array access: %s[index]\n", node->data.arrayAccess.name);

            /* For array parameters, the offset contains a POINTER to the array.
             * For local arrays, the offset IS the base address.
             * We detect array parameters by checking array size - parameters have size 0 */
            int arraySize = getArraySize(node->data.arrayAccess.name);
            if (arraySize == 0 || arraySize == -1) {
                /* Likely an array parameter - load the pointer */
                fprintf(output, "    lw $t%d, %d($sp)     # load array pointer (parameter)\n",
                        baseReg, baseOffset);
            } else {
                /* Local array - use stack pointer + offset directly */
                fprintf(output, "    addi $t%d, $sp, %d   # local array base address\n",
                        baseReg, baseOffset);
            }

            fprintf(output, "    sll $t%d, $t%d, 2    # index * 4\n", indexReg, indexReg);
            fprintf(output, "    add $t%d, $t%d, $t%d # element address\n",
                baseReg, baseReg, indexReg);
            fprintf(output, "    lw $t%d, 0($t%d)     # load value\n",
                baseReg, baseReg);

            /* Result is now in baseReg, ensure tempReg points one past it */
            tempReg = baseReg + 1;
            if (tempReg > 7) tempReg = 0;
            break;
        }

        case NODE_FUNC_CALL: {
            /* Function call: funcName(args) */
            fprintf(output, "    # Function call: %s\n", node->data.funcCall.name);

            /* Step 1: Collect arguments into array by flattening stmt_list structure */
            ASTNode* argArray[4] = {NULL, NULL, NULL, NULL};
            int argCount = 0;
            collectArgs(node->data.funcCall.args, argArray, &argCount, 4);

            /* Step 2: Generate code for each argument */
            for (int i = 0; i < argCount && i < 4; i++) {
                /* Check if this argument is an array variable - pass address instead of value */
                if (argArray[i]->type == NODE_VAR && isArrayVar(argArray[i]->data.name)) {
                    /* For array arguments, pass the pointer */
                    int offset = getVarOffset(argArray[i]->data.name);
                    int argReg = getNextTemp();
                    int arraySize = getArraySize(argArray[i]->data.name);

                    if (arraySize == 0 || arraySize == -1) {
                        /* Array parameter - load the pointer value */
                        fprintf(output, "    lw $t%d, %d($sp)     # Arg %d: load array pointer (param)\n",
                                argReg, offset, i);
                    } else {
                        /* Local array - compute its address */
                        fprintf(output, "    addi $t%d, $sp, %d    # Arg %d: local array address\n",
                                argReg, offset, i);
                    }
                    fprintf(output, "    move $a%d, $t%d\n", i, argReg);
                } else {
                    /* For non-array arguments, pass by value */
                    genExpr(argArray[i]);
                    int argReg = (tempReg > 0) ? tempReg - 1 : 0;
                    fprintf(output, "    move $a%d, $t%d    # Arg %d\n", i, argReg, i);
                }
            }

            /* Step 2: Call the function */
            /* Add func_ prefix to avoid MIPS instruction conflicts */
            /* Special case: main is called as _user_main */
            char funcLabel[256];
            if (strcmp(node->data.funcCall.name, "main") == 0) {
                snprintf(funcLabel, sizeof(funcLabel), "_user_main");
            } else {
                snprintf(funcLabel, sizeof(funcLabel), "func_%s", node->data.funcCall.name);
            }
            fprintf(output, "    jal %s             # Call function\n", funcLabel);

            /* Step 3: Get result from $v0 and put in temp register */
            int resultReg = getNextTemp();
            fprintf(output, "    move $t%d, $v0      # Get return value\n", resultReg);

            break;
        }

        case NODE_INPUT: {
            /* Input: read integer from user */
            fprintf(output, "    # Read integer from user\n");
            fprintf(output, "    li $v0, 5           # Syscall 5: read integer\n");
            fprintf(output, "    syscall\n");

            /* Move result to temp register */
            int resultReg = getNextTemp();
            fprintf(output, "    move $t%d, $v0      # Store input value\n", resultReg);

            break;
        }

        case NODE_COMPARE: {
            /* Comparison operations for if statements */
            int leftType = exprType(node->data.compare.left);
            int rightType = exprType(node->data.compare.right);

            genExpr(node->data.compare.left);
            int leftReg = (leftType == TYPE_FLOAT) ? (tempFloatReg - 2) : ((tempReg == 0) ? 7 : tempReg - 1);

            genExpr(node->data.compare.right);
            int rightReg = (rightType == TYPE_FLOAT) ? (tempFloatReg - 2) : ((tempReg == 0) ? 7 : tempReg - 1);
            
            int resultReg = getNextTemp();
            
            if (leftType == TYPE_FLOAT || rightType == TYPE_FLOAT) {
                /* Handle float comparisons */
                int leftFloatReg = leftReg;
                int rightFloatReg = rightReg;
                
                /* Convert integers to float if needed */
                if (leftType == TYPE_INT) {
                    fprintf(output, "    # Convert left operand to float\n");
                    fprintf(output, "    mtc1 $t%d, $f%d\n", leftReg, getNextFloatTemp());
                    fprintf(output, "    cvt.s.w $f%d, $f%d\n", tempFloatReg-2, tempFloatReg-2);
                    leftFloatReg = tempFloatReg - 2;
                }
                
                if (rightType == TYPE_INT) {
                    fprintf(output, "    # Convert right operand to float\n");
                    fprintf(output, "    mtc1 $t%d, $f%d\n", rightReg, getNextFloatTemp());
                    fprintf(output, "    cvt.s.w $f%d, $f%d\n", tempFloatReg-2, tempFloatReg-2);
                    rightFloatReg = tempFloatReg - 2;
                }
                
                /* Perform float comparison */
                switch (node->data.compare.compOp) {
                    case '<':
                        fprintf(output, "    # Float less than\n");
                        fprintf(output, "    c.lt.s $f%d, $f%d\n", leftFloatReg, rightFloatReg);
                        fprintf(output, "    bc1t float_true_%d\n", resultReg);
                        fprintf(output, "    li $t%d, 0\n", resultReg);
                        fprintf(output, "    j float_done_%d\n", resultReg);
                        fprintf(output, "float_true_%d:\n", resultReg);
                        fprintf(output, "    li $t%d, 1\n", resultReg);
                        fprintf(output, "float_done_%d:\n", resultReg);
                        break;
                    case LE:
                        fprintf(output, "    # Float less than or equal\n");
                        fprintf(output, "    c.le.s $f%d, $f%d\n", leftFloatReg, rightFloatReg);
                        fprintf(output, "    bc1t float_true_%d\n", resultReg);
                        fprintf(output, "    li $t%d, 0\n", resultReg);
                        fprintf(output, "    j float_done_%d\n", resultReg);
                        fprintf(output, "float_true_%d:\n", resultReg);
                        fprintf(output, "    li $t%d, 1\n", resultReg);
                        fprintf(output, "float_done_%d:\n", resultReg);
                        break;
                    case '>':
                        fprintf(output, "    # Float greater than\n");
                        fprintf(output, "    c.le.s $f%d, $f%d\n", leftFloatReg, rightFloatReg);
                        fprintf(output, "    bc1f float_true_%d\n", resultReg);
                        fprintf(output, "    li $t%d, 0\n", resultReg);
                        fprintf(output, "    j float_done_%d\n", resultReg);
                        fprintf(output, "float_true_%d:\n", resultReg);
                        fprintf(output, "    li $t%d, 1\n", resultReg);
                        fprintf(output, "float_done_%d:\n", resultReg);
                        break;
                    case GE:
                        fprintf(output, "    # Float greater than or equal\n");
                        fprintf(output, "    c.lt.s $f%d, $f%d\n", leftFloatReg, rightFloatReg);
                        fprintf(output, "    bc1f float_true_%d\n", resultReg);
                        fprintf(output, "    li $t%d, 0\n", resultReg);
                        fprintf(output, "    j float_done_%d\n", resultReg);
                        fprintf(output, "float_true_%d:\n", resultReg);
                        fprintf(output, "    li $t%d, 1\n", resultReg);
                        fprintf(output, "float_done_%d:\n", resultReg);
                        break;
                    case EQ:
                        fprintf(output, "    # Float equal\n");
                        fprintf(output, "    c.eq.s $f%d, $f%d\n", leftFloatReg, rightFloatReg);
                        fprintf(output, "    bc1t float_true_%d\n", resultReg);
                        fprintf(output, "    li $t%d, 0\n", resultReg);
                        fprintf(output, "    j float_done_%d\n", resultReg);
                        fprintf(output, "float_true_%d:\n", resultReg);
                        fprintf(output, "    li $t%d, 1\n", resultReg);
                        fprintf(output, "float_done_%d:\n", resultReg);
                        break;
                    case NE:
                        fprintf(output, "    # Float not equal\n");
                        fprintf(output, "    c.eq.s $f%d, $f%d\n", leftFloatReg, rightFloatReg);
                        fprintf(output, "    bc1f float_true_%d\n", resultReg);
                        fprintf(output, "    li $t%d, 0\n", resultReg);
                        fprintf(output, "    j float_done_%d\n", resultReg);
                        fprintf(output, "float_true_%d:\n", resultReg);
                        fprintf(output, "    li $t%d, 1\n", resultReg);
                        fprintf(output, "float_done_%d:\n", resultReg);
                        break;
                }
                tempFloatReg = 0;
            } else {
                /* Integer comparisons */
                switch (node->data.compare.compOp) {
                    case '<':
                        fprintf(output, "    # Integer less than\n");
                        fprintf(output, "    slt $t%d, $t%d, $t%d\n", resultReg, leftReg, rightReg);
                        break;
                    case LE:
                        fprintf(output, "    # Integer less than or equal\n");
                        fprintf(output, "    slt $t%d, $t%d, $t%d\n", resultReg, rightReg, leftReg);
                        fprintf(output, "    xori $t%d, $t%d, 1\n", resultReg, resultReg);
                        break;
                    case '>':
                        fprintf(output, "    # Integer greater than\n");
                        fprintf(output, "    slt $t%d, $t%d, $t%d\n", resultReg, rightReg, leftReg);
                        break;
                    case GE:
                        fprintf(output, "    # Integer greater than or equal\n");
                        fprintf(output, "    slt $t%d, $t%d, $t%d\n", resultReg, leftReg, rightReg);
                        fprintf(output, "    xori $t%d, $t%d, 1\n", resultReg, resultReg);
                        break;
                    case EQ:
                        fprintf(output, "    # Integer equal\n");
                        fprintf(output, "    xor $t%d, $t%d, $t%d\n", resultReg, leftReg, rightReg);
                        fprintf(output, "    sltiu $t%d, $t%d, 1\n", resultReg, resultReg);
                        break;
                    case NE:
                        fprintf(output, "    # Integer not equal\n");
                        fprintf(output, "    xor $t%d, $t%d, $t%d\n", resultReg, leftReg, rightReg);
                        fprintf(output, "    sltu $t%d, $zero, $t%d\n", resultReg, resultReg);
                        break;
                }
            }
            
            tempReg = resultReg + 1;
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

            /* Save the result register immediately after genExpr */
            int resultReg = (tempReg > 0) ? tempReg - 1 : 0;
            int resultFloatReg = (tempFloatReg > 0) ? tempFloatReg - 2 : 0;

            if (varType == TYPE_FLOAT) {
                if (exprTypeVal == TYPE_INT) {
                    /* Convert int to float before storing */
                    fprintf(output, "    # Convert int to float for assignment\n");
                    fprintf(output, "    mtc1 $t%d, $f%d\n", resultReg, getNextFloatTemp());
                    fprintf(output, "    cvt.s.w $f%d, $f%d\n", tempFloatReg-2, tempFloatReg-2);
                    fprintf(output, "    swc1 $f%d, %d($sp)\n", tempFloatReg - 2, offset);
                } else {
                    fprintf(output, "    swc1 $f%d, %d($sp)\n", resultFloatReg, offset);
                }
                tempFloatReg = 0;
            } else {
                fprintf(output, "    sw $t%d, %d($sp)\n", resultReg, offset);
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

            /* Calculate array element address */
            int baseOffset = getVarOffset(node->data.arrayAssign.name);
            int addressReg = getNextTemp();
            int baseReg = getNextTemp();

            /* Generate code for index expression */
            genExpr(node->data.arrayAssign.index);
            int indexReg = (tempReg == 0) ? 7 : tempReg - 1;

            /* Generate code for value expression */
            genExpr(node->data.arrayAssign.value);
            int valueReg = (tempReg == 0) ? 7 : tempReg - 1;

            fprintf(output, "    # Array assignment: %s[index] = value\n",
                node->data.arrayAssign.name);

            /* Check if array parameter (size 0) or local array */
            int arraySize = getArraySize(node->data.arrayAssign.name);
            if (arraySize == 0 || arraySize == -1) {
                /* Array parameter - load the pointer */
                fprintf(output, "    lw $t%d, %d($sp)     # load array pointer (parameter)\n",
                        baseReg, baseOffset);
            } else {
                /* Local array - use stack pointer + offset */
                fprintf(output, "    addi $t%d, $sp, %d   # local array base address\n",
                        baseReg, baseOffset);
            }

            fprintf(output, "    sll $t%d, $t%d, 2    # index * 4\n", indexReg, indexReg);
            fprintf(output, "    add $t%d, $t%d, $t%d # element address\n",
                addressReg, baseReg, indexReg);
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

            /* Prefix all user functions with func_ to avoid MIPS instruction conflicts */
            /* Special case: main becomes _user_main for readability */
            if (strcmp(node->data.funcDecl.name, "main") == 0) {
                fprintf(output, "_user_main:\n");
            } else {
                fprintf(output, "func_%s:\n", node->data.funcDecl.name);
            }

            /* Enter new scope for function */
            enterScope();

            /* Add parameters to scope */
            ASTNode* param = node->data.funcDecl.params;
            int paramNum = 0;
            while (param && paramNum < 4) {
                addParameter(param->data.param.name, param->data.param.type, param->data.param.isArray);
                param = param->data.param.next;
                paramNum++;
            }

            /* PROLOGUE: Set up stack frame */
            /* Use a generous fixed frame size to prevent stack corruption */
            /* This ensures $ra and $fp are never overwritten by local variables or parameters */
            currentFrameSize = 128;  /* 128 bytes should handle most functions */

            fprintf(output, "    # Function prologue\n");
            fprintf(output, "    addi $sp, $sp, -%d    # Allocate stack frame\n", currentFrameSize);
            fprintf(output, "    sw $ra, %d($sp)      # Save return address\n", currentFrameSize - 4);
            fprintf(output, "    sw $fp, %d($sp)      # Save frame pointer\n", currentFrameSize - 8);
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
            /* Add func_ prefix to epilogue label too */
            if (strcmp(node->data.funcDecl.name, "main") == 0) {
                fprintf(output, "_user_main_return:\n");
            } else {
                fprintf(output, "func_%s_return:\n", node->data.funcDecl.name);
            }
            fprintf(output, "    lw $fp, %d($sp)      # Restore frame pointer\n", currentFrameSize - 8);
            fprintf(output, "    lw $ra, %d($sp)      # Restore return address\n", currentFrameSize - 4);
            fprintf(output, "    addi $sp, $sp, %d    # Deallocate stack frame\n", currentFrameSize);
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
            fprintf(output, "    lw $fp, %d($sp)      # Restore frame pointer\n", currentFrameSize - 8);
            fprintf(output, "    lw $ra, %d($sp)      # Restore return address\n", currentFrameSize - 4);
            fprintf(output, "    addi $sp, $sp, %d    # Deallocate stack frame\n", currentFrameSize);
            fprintf(output, "    jr $ra               # Return to caller\n");

            break;
        }

        case NODE_FUNC_CALL: {
            /* Function call as statement (ignore return value) */
            genExpr(node);
            tempReg = 0;
            break;
        }

        case NODE_IF: {
            /* If statement: if (condition) then_stmt else else_stmt */
            static int labelCounter = 0;
            int currentLabel = labelCounter++;
            
            fprintf(output, "    # If statement\n");
            
            /* Generate condition */
            genExpr(node->data.ifStmt.condition);
            int condReg = tempReg - 1;
            
            /* Branch if condition is false */
            if (node->data.ifStmt.elseStmt) {
                /* Has else clause */
                fprintf(output, "    beq $t%d, $zero, else_label_%d\n", condReg, currentLabel);
                
                /* Generate then statement */
                genStmt(node->data.ifStmt.thenStmt);
                
                /* Jump over else clause */
                fprintf(output, "    j endif_label_%d\n", currentLabel);
                
                /* Else clause */
                fprintf(output, "else_label_%d:\n", currentLabel);
                genStmt(node->data.ifStmt.elseStmt);
                
                /* End of if */
                fprintf(output, "endif_label_%d:\n", currentLabel);
            } else {
                /* No else clause */
                fprintf(output, "    beq $t%d, $zero, endif_label_%d\n", condReg, currentLabel);
                
                /* Generate then statement */
                genStmt(node->data.ifStmt.thenStmt);
                
                /* End of if */
                fprintf(output, "endif_label_%d:\n", currentLabel);
            }
            
            tempReg = 0;
            break;
        }

        case NODE_WHILE: {
            /* While loop: while (condition) body */
            static int whileLabelCounter = 0;
            int currentLabel = whileLabelCounter++;

            fprintf(output, "    # While loop\n");

            /* Start of loop - check condition */
            fprintf(output, "while_start_%d:\n", currentLabel);

            /* Generate condition */
            genExpr(node->data.whileLoop.condition);
            int condReg = (tempReg == 0) ? 7 : tempReg - 1;

            /* Branch to end if condition is false */
            fprintf(output, "    beq $t%d, $zero, while_end_%d\n", condReg, currentLabel);

            /* Generate loop body */
            genStmt(node->data.whileLoop.body);

            /* Jump back to condition check */
            fprintf(output, "    j while_start_%d\n", currentLabel);

            /* End of loop */
            fprintf(output, "while_end_%d:\n", currentLabel);

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
    
    // Call the user's main function if it exists
    fprintf(output, "\n    # Call user main function\n");
    fprintf(output, "    jal _user_main\n");
    
    // Program exit
    fprintf(output, "\n    # Exit program\n");
    fprintf(output, "    addi $sp, $sp, 400\n");
    fprintf(output, "    li $v0, 10\n");
    fprintf(output, "    syscall\n");

    /* Infinite loop to catch any execution past exit */
    fprintf(output, "\n# Infinite loop to prevent bad instruction exceptions\n");
    fprintf(output, "__post_exit_stub:\n");
    fprintf(output, "    li $v0, 10\n");
    fprintf(output, "    syscall\n");
    fprintf(output, "    j __post_exit_stub    # Loop forever\n");

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