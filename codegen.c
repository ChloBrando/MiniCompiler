#include <stdio.h>
#include <stdlib.h>
#include "codegen.h"
#include "symtab.h"

FILE* output;
int tempReg = 0;

int getNextTemp() {
    int reg = tempReg++;
    if (tempReg > 7) tempReg = 0;  // Reuse $t0-$t7
    return reg;
}

void genExpr(ASTNode* node) {
    if (!node) return;
    
    switch(node->type) {
        case NODE_NUM:
            fprintf(output, "    li $t%d, %d\n", getNextTemp(), node->data.num);
            break;
            
        case NODE_VAR: {
            int offset = getVarOffset(node->data.name);
            if (offset == -1) {
                fprintf(stderr, "Error: Variable %s not declared\n", node->data.name);
                exit(1);
            }
            fprintf(output, "    lw $t%d, %d($sp)\n", getNextTemp(), offset);
            break;
        }
        
        case NODE_BINOP: {
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
            
        default:
            break;
    }
}

void genStmt(ASTNode* node) {
    if (!node) return;
    
    switch(node->type) {
        case NODE_DECL: {
            int offset = addVar(node->data.name);
            if (offset == -1) {
                fprintf(stderr, "Error: Variable %s already declared\n", node->data.name);
                exit(1);
            }
            fprintf(output, "    # Declared %s at offset %d\n", node->data.name, offset);
            break;
        }
        
        case NODE_ASSIGN: {
            int offset = getVarOffset(node->data.assign.var);
            if (offset == -1) {
                fprintf(stderr, "Error: Variable %s not declared\n", node->data.assign.var);
                exit(1);
            }
            genExpr(node->data.assign.value);
            fprintf(output, "    sw $t%d, %d($sp)\n", tempReg - 1, offset);
            tempReg = 0;
            break;
        }
        
        case NODE_PRINT:
            genExpr(node->data.expr);
            fprintf(output, "    # Print integer\n");
            fprintf(output, "    move $a0, $t%d\n", tempReg - 1);
            fprintf(output, "    li $v0, 1\n");
            fprintf(output, "    syscall\n");
            fprintf(output, "    # Print newline\n");
            fprintf(output, "    li $v0, 11\n");
            fprintf(output, "    li $a0, 10\n");
            fprintf(output, "    syscall\n");
            tempReg = 0;
            break;
            
        case NODE_STMT_LIST:
            genStmt(node->data.stmtlist.stmt);
            genStmt(node->data.stmtlist.next);
            break;

        case NODE_ARRAY_DECL: {
            /* Generate code for array declaration */
            int offset = addArrayVar(node->data.arrayDecl.name, node->data.arrayDecl.size);
            if (offset == -1) {
                fprintf(stderr, "Error: Array %s already declared\n",
                    node->data.arrayDecl.name);
                exit(1);
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
        
        default:
            break;
    }
}

void generateMIPS(ASTNode* root, const char* filename) {
    output = fopen(filename, "w");
    if (!output) {
        fprintf(stderr, "Cannot open output file %s\n", filename);
        exit(1);
    }
    
    // Initialize symbol table
    initSymTab();
    
    // MIPS program header
    fprintf(output, ".data\n");
    fprintf(output, "\n.text\n");
    fprintf(output, ".globl main\n");
    fprintf(output, "main:\n");
    
    // Allocate stack space (max 100 variables * 4 bytes)
    fprintf(output, "    # Allocate stack space\n");
    fprintf(output, "    addi $sp, $sp, -400\n\n");
    
    // Generate code for statements
    genStmt(root);
    
    // Program exit
    fprintf(output, "\n    # Exit program\n");
    fprintf(output, "    addi $sp, $sp, 400\n");
    fprintf(output, "    li $v0, 10\n");
    fprintf(output, "    syscall\n");
    
    fclose(output);
}