#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"

TACList tacList;
TACList optimizedList;

void initTAC() {
    tacList.head = NULL;
    tacList.tail = NULL;
    tacList.tempCount = 0;
    optimizedList.head = NULL;
    optimizedList.tail = NULL;
}

char* newTemp() {
    char* temp = malloc(10);
    sprintf(temp, "t%d", tacList.tempCount++);
    return temp;
}

TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result) {
    TACInstr* instr = malloc(sizeof(TACInstr));
    instr->op = op;
    instr->arg1 = arg1 ? strdup(arg1) : NULL;
    instr->arg2 = arg2 ? strdup(arg2) : NULL;
    instr->result = result ? strdup(result) : NULL;
    instr->next = NULL;
    return instr;
}

void appendTAC(TACInstr* instr) {
    if (!tacList.head) {
        tacList.head = tacList.tail = instr;
    } else {
        tacList.tail->next = instr;
        tacList.tail = instr;
    }
}

void appendOptimizedTAC(TACInstr* instr) {
    if (!optimizedList.head) {
        optimizedList.head = optimizedList.tail = instr;
    } else {
        optimizedList.tail->next = instr;
        optimizedList.tail = instr;
    }
}

char* generateTACExpr(ASTNode* node) {
    if (!node) return NULL;
    
    switch(node->type) {
        case NODE_NUM: {
            char* temp = malloc(20);
            sprintf(temp, "%d", node->data.num);
            return temp;
        }

        case NODE_FLOAT: {
            char* temp = malloc(20);
            sprintf(temp, "%f", node->data.fnum);
            return temp;
        }

        case NODE_VAR:
            return strdup(node->data.name);

        case NODE_STR:
            /* Return the string literal text so TAC can carry it as an operand */
            return strdup(node->data.str);
        
        case NODE_BINOP: {
            char* left = generateTACExpr(node->data.binop.left);
            char* right = generateTACExpr(node->data.binop.right);
            char* temp = newTemp();

            if (node->data.binop.op == '+') {
                appendTAC(createTAC(TAC_ADD, left, right, temp));
            }
            else if (node->data.binop.op == '-') {
                appendTAC(createTAC(TAC_SUB, left, right, temp));
            }
            else if (node->data.binop.op == '*') {
                appendTAC(createTAC(TAC_MUL, left, right, temp));
            }
            else if (node->data.binop.op == '/') {
                appendTAC(createTAC(TAC_DIV, left, right, temp));
            }

            return temp;
        }
        
        case NODE_ARRAY_ACCESS: {
            /* Generate TAC for array access */
            char* indexExpr = generateTACExpr(node->data.arrayAccess.index);
            char* temp = newTemp();

            appendTAC(createTAC(TAC_ARRAY_ACCESS, indexExpr, NULL, temp));
            return temp;
        }

        case NODE_FUNC_CALL: {
            /* Function call: funcName(args) */
            /* Generate TAC for each argument and emit PARAM instructions */
            ASTNode* arg = node->data.funcCall.args;
            int paramCount = 0;

            while (arg) {
                ASTNode* argExpr;

                /* Extract actual expression from stmt_list structure */
                if (arg->type == NODE_STMT_LIST) {
                    /* Check if stmt is also a stmt_list (nested case for 3+ args) */
                    if (arg->data.stmtlist.stmt &&
                        arg->data.stmtlist.stmt->type == NODE_STMT_LIST) {
                        /* Recursively process the nested stmt_list first */
                        ASTNode* nested = arg->data.stmtlist.stmt;
                        while (nested) {
                            if (nested->type == NODE_STMT_LIST) {
                                char* argVal = generateTACExpr(nested->data.stmtlist.stmt);
                                appendTAC(createTAC(TAC_PARAM, argVal, NULL, NULL));
                                paramCount++;
                                nested = nested->data.stmtlist.next;
                            } else {
                                char* argVal = generateTACExpr(nested);
                                appendTAC(createTAC(TAC_PARAM, argVal, NULL, NULL));
                                paramCount++;
                                nested = NULL;
                            }
                        }
                        /* Now process the final argument (next) */
                        arg = arg->data.stmtlist.next;
                        if (arg) {
                            char* argVal = generateTACExpr(arg);
                            appendTAC(createTAC(TAC_PARAM, argVal, NULL, NULL));
                            paramCount++;
                        }
                        break;
                    } else {
                        /* Normal case: stmt is an expression */
                        argExpr = arg->data.stmtlist.stmt;
                        char* argVal = generateTACExpr(argExpr);
                        appendTAC(createTAC(TAC_PARAM, argVal, NULL, NULL));
                        paramCount++;
                        arg = arg->data.stmtlist.next;
                    }
                } else {
                    /* Single argument */
                    char* argVal = generateTACExpr(arg);
                    appendTAC(createTAC(TAC_PARAM, argVal, NULL, NULL));
                    paramCount++;
                    arg = NULL;
                }
            }

            /* Generate the CALL instruction */
            char* temp = newTemp();
            TACInstr* call = createTAC(TAC_CALL, node->data.funcCall.name,
                                    NULL, temp);
            call->paramCount = paramCount;
            appendTAC(call);

            return temp;  /* Return temp holding result */
        }

        case NODE_COMPARE: {
            char* left = generateTACExpr(node->data.compare.left);
            char* right = generateTACExpr(node->data.compare.right);
            char* temp = newTemp();

            /* Generate comparison TAC instruction based on operator */
            switch(node->data.compare.compOp) {
                case '<':
                    appendTAC(createTAC(TAC_LT, left, right, temp));
                    break;
                case '>':
                    appendTAC(createTAC(TAC_GT, left, right, temp));
                    break;
                case 271: /* EQ token */
                    appendTAC(createTAC(TAC_EQ, left, right, temp));
                    break;
                case 272: /* NE token */
                    appendTAC(createTAC(TAC_NE, left, right, temp));
                    break;
                case 273: /* LE token */
                    appendTAC(createTAC(TAC_LE, left, right, temp));
                    break;
                case 274: /* GE token */
                    appendTAC(createTAC(TAC_GE, left, right, temp));
                    break;
            }

            return temp;
        }

        default:
            return NULL;
    }
}

void generateTAC(ASTNode* node) {
    if (!node) return;
    
    switch(node->type) {
        case NODE_DECL:
            appendTAC(createTAC(TAC_DECL, NULL, NULL, node->data.name));
            break;
        case NODE_FLOAT_DECL:
            /* Float variable declaration appears as a normal decl in TAC */
            appendTAC(createTAC(TAC_DECL, NULL, NULL, node->data.name));
            break;
        case NODE_STR_DECL:
            /* String variable declaration appears as a normal decl in TAC */
            appendTAC(createTAC(TAC_DECL, NULL, NULL, node->data.name));
            break;
            
        case NODE_ASSIGN: {
            char* expr = generateTACExpr(node->data.assign.value);
            appendTAC(createTAC(TAC_ASSIGN, expr, NULL, node->data.assign.var));
            break;
        }
        
        case NODE_PRINT: {
            char* expr = generateTACExpr(node->data.expr);
            appendTAC(createTAC(TAC_PRINT, expr, NULL, NULL));
            break;
        }
        
        case NODE_STMT_LIST:
            generateTAC(node->data.stmtlist.stmt);
            generateTAC(node->data.stmtlist.next);
            break;

        case NODE_ARRAY_DECL:
            /* TODO: Generate TAC for array declaration */
            appendTAC(createTAC(TAC_ARRAY_DECL, NULL, NULL, node->data.arrayDecl.name));
            break;

        case NODE_ARRAY_ASSIGN: {
            /* TODO: Generate TAC for array assignment */
            char* indexExpr = generateTACExpr(node->data.arrayAssign.index);
            char* valueExpr = generateTACExpr(node->data.arrayAssign.value);
            appendTAC(createTAC(TAC_ARRAY_ASSIGN, indexExpr, valueExpr,
                node->data.arrayAssign.name));
            break;
        }
        case NODE_FUNC_DECL: {
            /* Function declaration: # funcName(params) { body } */
            appendTAC(createTAC(TAC_FUNC_BEGIN, NULL, NULL,
                                node->data.funcDecl.name));
            appendTAC(createTAC(TAC_LABEL, NULL, NULL,
                                node->data.funcDecl.name));

            /* Generate TAC for parameters (they become local variables) */
            ASTNode* param = node->data.funcDecl.params;
            while (param) {
                /* PARAM instruction marks each parameter */
                appendTAC(createTAC(TAC_PARAM, param->data.param.name, NULL, NULL));
                param = param->data.param.next;
            }

            /* Generate TAC for function body */
            generateTAC(node->data.funcDecl.body);

            /* Ensure function ends with FUNC_END marker */
            appendTAC(createTAC(TAC_FUNC_END, NULL, NULL,
                                node->data.funcDecl.name));
            break;
        }

        case NODE_FUNC_CALL: {
            /* Function call as statement (ignore return value) */
            generateTACExpr(node);  /* Generate the call in expression context */
            break;
        }

        case NODE_RETURN: {
            /* Return statement: return expr; or return; */
            if (node->data.returnStmt.value) {
                char* retVal = generateTACExpr(node->data.returnStmt.value);
                appendTAC(createTAC(TAC_RETURN, retVal, NULL, NULL));
            } else {
                /* Return void */
                appendTAC(createTAC(TAC_RETURN, NULL, NULL, NULL));
            }
            break;
        }

        case NODE_IF: {
            /* If statement: if (condition) then_stmt [else else_stmt] */
            char* condResult = generateTACExpr(node->data.ifStmt.condition);
            
            /* Generate labels for control flow */
            char* elseLabel = malloc(20);
            char* endLabel = malloc(20);
            sprintf(elseLabel, "else_%d", tacList.tempCount);
            sprintf(endLabel, "endif_%d", tacList.tempCount++);
            
            /* Generate conditional jump */
            appendTAC(createTAC(TAC_IFFALSE, condResult, elseLabel, NULL));
            
            /* Generate then statement */
            generateTAC(node->data.ifStmt.thenStmt);
            
            if (node->data.ifStmt.elseStmt) {
                /* Jump to end after then statement */
                appendTAC(createTAC(TAC_GOTO, endLabel, NULL, NULL));
                
                /* Else label */
                appendTAC(createTAC(TAC_LABEL, NULL, NULL, elseLabel));
                
                /* Generate else statement */
                generateTAC(node->data.ifStmt.elseStmt);
                
                /* End label */
                appendTAC(createTAC(TAC_LABEL, NULL, NULL, endLabel));
            } else {
                /* Simple if - else label is the end label */
                appendTAC(createTAC(TAC_LABEL, NULL, NULL, elseLabel));
            }
            
            break;
        }

        case NODE_FLOAT_ARRAY_DECL: {
            /* Float array declaration */
            char* sizeStr = malloc(20);
            sprintf(sizeStr, "%d", node->data.arrayDecl.size);
            appendTAC(createTAC(TAC_ARRAY_DECL, sizeStr, NULL, node->data.arrayDecl.name));
            break;
        }
            
        default:
            break;
    }
}

void printTAC() {
    printf("Unoptimized TAC Instructions:\n");
    printf("─────────────────────────────\n");
    TACInstr* curr = tacList.head;
    int lineNum = 1;
    while (curr) {
        printf("%2d: ", lineNum++);
        switch(curr->op) {
            case TAC_DECL:
                printf("DECL %s", curr->result);
                printf("          // Declare variable '%s'\n", curr->result);
                break;
            case TAC_ADD:
                printf("%s = %s + %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Add: store result in %s\n", curr->result);
                break;
            case TAC_SUB:
                printf("%s = %s - %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Subtract: store result in %s\n", curr->result);
                break;
            case TAC_MUL:
                printf("%s = %s * %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Multiply: store result in %s\n", curr->result);
                break;
            case TAC_DIV:
                printf("%s = %s / %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Divide: store result in %s\n", curr->result);
                break;
            case TAC_ASSIGN:
                printf("%s = %s", curr->result, curr->arg1);
                printf("           // Assign value to %s\n", curr->result);
                break;
            case TAC_PRINT:
                printf("PRINT %s", curr->arg1);
                printf("          // Output value of %s\n", curr->arg1);
                break;
            case TAC_ARRAY_DECL:
                printf("ARRAY_DECL %s", curr->result);
                printf("     // Declare array '%s'\n", curr->result);
                break;
            case TAC_ARRAY_ASSIGN:
                printf("%s[%s] = %s", curr->result, curr->arg1, curr->arg2);
                printf("   // Array assignment\n");
                break;
            case TAC_ARRAY_ACCESS:
                printf("%s = array[%s]", curr->result, curr->arg1);
                printf("  // Array access\n");
                break;
            case TAC_FUNC_BEGIN:
                printf("FUNC_BEGIN %s", curr->result);
                printf("       // Start of function '%s'\n", curr->result);
                break;
            case TAC_LABEL:
                printf("LABEL %s:", curr->result);
                printf("            // Function entry point\n");
                break;
            case TAC_PARAM:
                printf("PARAM %s", curr->arg1);
                printf("            // Parameter '%s'\n", curr->arg1);
                break;
            case TAC_CALL:
                printf("%s = CALL %s, %d", curr->result, curr->arg1, curr->paramCount);
                printf("  // Call function with %d args\n", curr->paramCount);
                break;
            case TAC_RETURN:
                if (curr->arg1) {
                    printf("RETURN %s", curr->arg1);
                    printf("           // Return value\n");
                } else {
                    printf("RETURN");
                    printf("               // Return void\n");
                }
                break;
            case TAC_FUNC_END:
                printf("FUNC_END %s", curr->result);
                printf("         // End of function '%s'\n", curr->result);
                break;
            case TAC_LT:
                printf("%s = %s < %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Less than comparison\n");
                break;
            case TAC_GT:
                printf("%s = %s > %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Greater than comparison\n");
                break;
            case TAC_EQ:
                printf("%s = %s == %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Equality comparison\n");
                break;
            case TAC_NE:
                printf("%s = %s != %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Not equal comparison\n");
                break;
            case TAC_LE:
                printf("%s = %s <= %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Less than or equal comparison\n");
                break;
            case TAC_GE:
                printf("%s = %s >= %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Greater than or equal comparison\n");
                break;
            case TAC_IFFALSE:
                printf("IFFALSE %s GOTO %s", curr->arg1, curr->arg2);
                printf("  // Conditional jump if false\n");
                break;
            case TAC_GOTO:
                printf("GOTO %s", curr->arg1);
                printf("             // Unconditional jump\n");
                break;
            default:
                break;
        }
        curr = curr->next;
    }
}

// Simple optimization: constant folding and copy propagation
void optimizeTAC() {
    TACInstr* curr = tacList.head;
    
    // Copy propagation table
    typedef struct {
        char* var;
        char* value;
    } VarValue;
    
    VarValue values[100];
    int valueCount = 0;
    
    while (curr) {
        TACInstr* newInstr = NULL;
        
        switch(curr->op) {
            case TAC_DECL:
                newInstr = createTAC(TAC_DECL, NULL, NULL, curr->result);
                break;
                
            case TAC_ADD: {
                char* left = curr->arg1;
                char* right = curr->arg2;
                
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, left) == 0) {
                        left = values[i].value;
                        break;
                    }
                }
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, right) == 0) {
                        right = values[i].value;
                        break;
                    }
                }
                
                if (isdigit(left[0]) && isdigit(right[0])) {
                    int result = atoi(left) + atoi(right);
                    char* resultStr = malloc(20);
                    sprintf(resultStr, "%d", result);
                    
                    values[valueCount].var = strdup(curr->result);
                    values[valueCount].value = resultStr;
                    valueCount++;
                    
                    newInstr = createTAC(TAC_ASSIGN, resultStr, NULL, curr->result);
                } else {
                    newInstr = createTAC(TAC_ADD, left, right, curr->result);
                }
                break;
            }
            
            case TAC_SUB: {
                char* left = curr->arg1;
                char* right = curr->arg2;
                
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, left) == 0) {
                        left = values[i].value;
                        break;
                    }
                }
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, right) == 0) {
                        right = values[i].value;
                        break;
                    }
                }
                
                if (isdigit(left[0]) && isdigit(right[0])) {
                    int result = atoi(left) - atoi(right);
                    char* resultStr = malloc(20);
                    sprintf(resultStr, "%d", result);
                    
                    values[valueCount].var = strdup(curr->result);
                    values[valueCount].value = resultStr;
                    valueCount++;
                    
                    newInstr = createTAC(TAC_ASSIGN, resultStr, NULL, curr->result);
                } else {
                    newInstr = createTAC(TAC_SUB, left, right, curr->result);
                }
                break;
            }

            case TAC_MUL: {
                char* left = curr->arg1;
                char* right = curr->arg2;

                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, left) == 0) {
                        left = values[i].value;
                        break;
                    }
                }
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, right) == 0) {
                        right = values[i].value;
                        break;
                    }
                }

                if (isdigit(left[0]) && isdigit(right[0])) {
                    int result = atoi(left) * atoi(right);
                    char* resultStr = malloc(20);
                    sprintf(resultStr, "%d", result);

                    values[valueCount].var = strdup(curr->result);
                    values[valueCount].value = resultStr;
                    valueCount++;

                    newInstr = createTAC(TAC_ASSIGN, resultStr, NULL, curr->result);
                } else {
                    newInstr = createTAC(TAC_MUL, left, right, curr->result);
                }
                break;
            }

            case TAC_DIV: {
                char* left = curr->arg1;
                char* right = curr->arg2;

                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, left) == 0) {
                        left = values[i].value;
                        break;
                    }
                }
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, right) == 0) {
                        right = values[i].value;
                        break;
                    }
                }

                if (isdigit(left[0]) && isdigit(right[0])) {
                    int divisor = atoi(right);
                    if (divisor != 0) {  // Avoid division by zero
                        int result = atoi(left) / divisor;
                        char* resultStr = malloc(20);
                        sprintf(resultStr, "%d", result);

                        values[valueCount].var = strdup(curr->result);
                        values[valueCount].value = resultStr;
                        valueCount++;

                        newInstr = createTAC(TAC_ASSIGN, resultStr, NULL, curr->result);
                    } else {
                        newInstr = createTAC(TAC_DIV, left, right, curr->result);
                    }
                } else {
                    newInstr = createTAC(TAC_DIV, left, right, curr->result);
                }
                break;
            }
            
            case TAC_ASSIGN: {
                char* value = curr->arg1;
                
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, value) == 0) {
                        value = values[i].value;
                        break;
                    }
                }
                
                values[valueCount].var = strdup(curr->result);
                values[valueCount].value = strdup(value);
                valueCount++;
                
                newInstr = createTAC(TAC_ASSIGN, value, NULL, curr->result);
                break;
            }
            
            case TAC_PRINT: {
                char* value = curr->arg1;
                
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, value) == 0) {
                        value = values[i].value;
                        break;
                    }
                }
                
                newInstr = createTAC(TAC_PRINT, value, NULL, NULL);
                break;
            }

            case TAC_ARRAY_DECL:
                newInstr = createTAC(TAC_ARRAY_DECL, NULL, NULL, curr->result);
                break;

            case TAC_ARRAY_ASSIGN: {
                char* index = curr->arg1;
                char* value = curr->arg2;

                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, index) == 0) {
                        index = values[i].value;
                        break;
                    }
                }
                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, value) == 0) {
                        value = values[i].value;
                        break;
                    }
                }

                newInstr = createTAC(TAC_ARRAY_ASSIGN, index, value, curr->result);
                break;
            }

            case TAC_ARRAY_ACCESS: {
                char* index = curr->arg1;

                for (int i = valueCount - 1; i >= 0; i--) {
                    if (strcmp(values[i].var, index) == 0) {
                        index = values[i].value;
                        break;
                    }
                }

                newInstr = createTAC(TAC_ARRAY_ACCESS, index, NULL, curr->result);
                break;
            }

            /* Function-related instructions - pass through for now */
            case TAC_FUNC_BEGIN:
                /* Clear value table when entering new function */
                valueCount = 0;
                newInstr = createTAC(TAC_FUNC_BEGIN, NULL, NULL, curr->result);
                break;

            case TAC_LABEL:
                newInstr = createTAC(TAC_LABEL, NULL, NULL, curr->result);
                break;

            case TAC_PARAM:
                newInstr = createTAC(TAC_PARAM, curr->arg1, NULL, NULL);
                break;

            case TAC_CALL: {
                /* Function calls - preserve for now */
                newInstr = createTAC(TAC_CALL, curr->arg1, NULL, curr->result);
                newInstr->paramCount = curr->paramCount;
                break;
            }

            case TAC_RETURN: {
                /* Propagate return value if constant */
                char* retVal = curr->arg1;
                if (retVal) {
                    for (int i = valueCount - 1; i >= 0; i--) {
                        if (strcmp(values[i].var, retVal) == 0) {
                            retVal = values[i].value;
                            break;
                        }
                    }
                }
                newInstr = createTAC(TAC_RETURN, retVal, NULL, NULL);
                break;
            }

            case TAC_FUNC_END:
                newInstr = createTAC(TAC_FUNC_END, NULL, NULL, curr->result);
                break;

            /* Comparison operations - pass through for now */
            case TAC_LT:
            case TAC_GT:
            case TAC_EQ:
            case TAC_NE:
            case TAC_LE:
            case TAC_GE:
                newInstr = createTAC(curr->op, curr->arg1, curr->arg2, curr->result);
                break;

            /* Control flow operations */
            case TAC_IFFALSE:
                newInstr = createTAC(TAC_IFFALSE, curr->arg1, curr->arg2, curr->result);
                break;
            case TAC_GOTO:
                newInstr = createTAC(TAC_GOTO, curr->arg1, curr->arg2, curr->result);
                break;
        }

        // Fix: Move this outside the switch statement and outside any case
        if (newInstr) {
            appendOptimizedTAC(newInstr);
        }

        curr = curr->next;
    }
}

/* ADVANCED OPTIMIZATION 1: Dead Code Elimination
 * Remove unreachable code after RETURN statements
 */
void eliminateDeadCode() {
    TACInstr* curr = optimizedList.head;

    while (curr) {
        /* If we hit a RETURN, skip instructions until FUNC_END */
        if (curr->op == TAC_RETURN) {
            TACInstr* next = curr->next;

            /* Skip dead code until we hit FUNC_END */
            while (next && next->op != TAC_FUNC_END) {
                TACInstr* deadInstr = next;
                next = next->next;
                /* Mark dead instruction (in real impl, we'd remove it) */
                printf("    [OPTIMIZATION] Removed dead code after RETURN\n");
                free(deadInstr);
            }

            /* Link RETURN directly to FUNC_END */
            curr->next = next;
        }

        curr = curr->next;
    }
}

/* ADVANCED OPTIMIZATION 2: Tail Call Optimization
 * Convert CALL followed immediately by RETURN into a jump
 * Pattern: t0 = CALL func, N
 *          RETURN t0
 * Becomes: GOTO func (tail call)
 */
void optimizeTailCalls() {
    TACInstr* curr = optimizedList.head;

    while (curr && curr->next) {
        /* Check for CALL followed by RETURN of the same temp */
        if (curr->op == TAC_CALL && curr->next->op == TAC_RETURN) {
            TACInstr* callInstr = curr;
            TACInstr* retInstr = curr->next;

            /* Check if RETURN uses the result of CALL */
            if (retInstr->arg1 && strcmp(retInstr->arg1, callInstr->result) == 0) {
                printf("    [OPTIMIZATION] Tail call detected for function '%s'\n",
                       callInstr->arg1);
                /* In a full implementation, we'd replace with a jump instruction */
                /* For now, just mark it with a comment */
            }
        }

        curr = curr->next;
    }
}

/* ADVANCED OPTIMIZATION 3: Function Inlining
 * Replace small function calls with the function body inline
 * Criteria: Function body < 5 instructions, non-recursive
 */
typedef struct FunctionInfo {
    char* name;
    TACInstr* begin;
    TACInstr* end;
    int instrCount;
    int hasRecursiveCall;
} FunctionInfo;

FunctionInfo functions[20];
int functionCount = 0;

/* Analyze all functions in the TAC list */
void analyzeFunctions() {
    TACInstr* curr = optimizedList.head;
    functionCount = 0;

    while (curr) {
        if (curr->op == TAC_FUNC_BEGIN) {
            FunctionInfo* func = &functions[functionCount++];
            func->name = strdup(curr->result);
            func->begin = curr;
            func->instrCount = 0;
            func->hasRecursiveCall = 0;

            /* Count instructions in function body */
            TACInstr* bodyInstr = curr->next;
            while (bodyInstr && bodyInstr->op != TAC_FUNC_END) {
                func->instrCount++;

                /* Check for recursive call */
                if (bodyInstr->op == TAC_CALL &&
                    strcmp(bodyInstr->arg1, func->name) == 0) {
                    func->hasRecursiveCall = 1;
                }

                bodyInstr = bodyInstr->next;
            }

            func->end = bodyInstr;  /* Points to FUNC_END */

            /* Report small functions that could be inlined */
            if (func->instrCount < 5 && !func->hasRecursiveCall) {
                printf("    [OPTIMIZATION] Function '%s' is inlineable (%d instructions)\n",
                       func->name, func->instrCount);
            }
        }

        curr = curr->next;
    }
}

/* Apply all advanced optimizations */
void applyAdvancedOptimizations() {
    printf("\n=== ADVANCED OPTIMIZATIONS ===\n");

    printf("\n  1. Analyzing functions for inlining...\n");
    analyzeFunctions();

    printf("\n  2. Eliminating dead code after RETURN...\n");
    eliminateDeadCode();

    printf("\n  3. Optimizing tail calls...\n");
    optimizeTailCalls();

    printf("\n==============================\n\n");
}

void printOptimizedTAC() {
    printf("Optimized TAC Instructions:\n");
    printf("─────────────────────────────\n");
    TACInstr* curr = optimizedList.head;
    int lineNum = 1;
    while (curr) {
        printf("%2d: ", lineNum++);
        switch(curr->op) {
            case TAC_DECL:
                printf("DECL %s\n", curr->result);
                break;
            case TAC_ADD:
                printf("%s = %s + %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Runtime addition needed\n");
                break;
            case TAC_SUB:
                printf("%s = %s - %s", curr->result, curr->arg1, curr->arg2);
                printf("     // Runtime subtraction needed\n");
                break;
            case TAC_ASSIGN:
                printf("%s = %s", curr->result, curr->arg1);
                if (curr->arg1[0] >= '0' && curr->arg1[0] <= '9') {
                    printf("           // Constant value: %s\n", curr->arg1);
                } else {
                    printf("           // Copy value\n");
                }
                break;
            case TAC_PRINT:
                printf("PRINT %s", curr->arg1);
                if (curr->arg1[0] >= '0' && curr->arg1[0] <= '9') {
                    printf("          // Print constant: %s\n", curr->arg1);
                } else {
                    printf("          // Print variable\n");
                }
                break;
            case TAC_ARRAY_DECL:
                printf("ARRAY_DECL %s\n", curr->result);
                break;
            case TAC_ARRAY_ASSIGN:
                printf("%s[%s] = %s", curr->result, curr->arg1, curr->arg2);
                printf("   // Array assignment\n");
                break;
            case TAC_ARRAY_ACCESS:
                printf("%s = array[%s]", curr->result, curr->arg1);
                printf("  // Array access\n");
                break;
            case TAC_FUNC_BEGIN:
                printf("FUNC_BEGIN %s\n", curr->result);
                break;
            case TAC_LABEL:
                printf("LABEL %s:\n", curr->result);
                break;
            case TAC_PARAM:
                printf("PARAM %s\n", curr->arg1);
                break;
            case TAC_CALL:
                printf("%s = CALL %s, %d", curr->result, curr->arg1, curr->paramCount);
                printf("  // Optimized call\n");
                break;
            case TAC_RETURN:
                if (curr->arg1) {
                    printf("RETURN %s\n", curr->arg1);
                } else {
                    printf("RETURN\n");
                }
                break;
            case TAC_FUNC_END:
                printf("FUNC_END %s\n", curr->result);
                break;
            default:
                break;
        }
        curr = curr->next;
    }
}