/* MINIMAL C COMPILER - EDUCATIONAL VERSION
 * Demonstrates all phases of compilation with a simple language
 * Supports: int variables, addition, assignment, print
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ast.h"
#include "codegen.h"
#include "tac.h"
#include "semantic.h"
#include "symtab.h"

extern int yyparse();
extern FILE* yyin;
extern ASTNode* root;

int main(int argc, char* argv[]) {
    clock_t start_time, end_time, phase_start;
    double total_time, phase_time;
    
    // Start overall compilation timer
    start_time = clock();
    
    if (argc != 3) {
        printf("Usage: %s <input.c> <output.s>\n", argv[0]);
        printf("Example: ./minicompiler test.c output.s\n");
        return 1;
    }
    
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", argv[1]);
        return 1;
    }
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║          MINIMAL C COMPILER - EDUCATIONAL VERSION         ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    /* PHASE 1: Lexical and Syntax Analysis */
    phase_start = clock();
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│ PHASE 1: LEXICAL & SYNTAX ANALYSIS                       │\n");
    printf("├──────────────────────────────────────────────────────────┤\n");
    printf("│ • Reading source file: %s\n", argv[1]);
    printf("│ • Tokenizing input (scanner.l)\n");
    printf("│ • Parsing grammar rules (parser.y)\n");
    printf("│ • Building Abstract Syntax Tree\n");
    printf("└──────────────────────────────────────────────────────────┘\n");
    
    if (yyparse() == 0) {
        phase_time = ((double)(clock() - phase_start)) / CLOCKS_PER_SEC * 1000;
        printf("✓ Parse successful - program is syntactically correct!\n");
        printf("  ⏱  Phase 1 time: %.3f ms\n\n", phase_time);
        
        /* PHASE 2: AST Display */
        phase_start = clock();
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 2: ABSTRACT SYNTAX TREE (AST)                      │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Tree structure representing the program hierarchy:        │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        printAST(root, 0);
        phase_time = ((double)(clock() - phase_start)) / CLOCKS_PER_SEC * 1000;
        printf("\n  ⏱  Phase 2 time: %.3f ms\n\n", phase_time);
        
        /* Initialize symbol table before semantic analysis */
        initSymTab();

        /* PHASE 2.5: Semantic analysis / type checking */
        phase_start = clock();
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 2.5: SEMANTIC ANALYSIS (TYPE CHECKING)             │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        if (semanticCheck(root) != 0) {
            printf("✗ Semantic errors detected, aborting.\n");
            return 1;
        }
        phase_time = ((double)(clock() - phase_start)) / CLOCKS_PER_SEC * 1000;
        printf("  ⏱  Phase 2.5 time: %.3f ms\n", phase_time);

        /* PHASE 3: Intermediate Code */
        phase_start = clock();
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 3: INTERMEDIATE CODE GENERATION                    │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Three-Address Code (TAC) - simplified instructions:       │\n");
        printf("│ • Each instruction has at most 3 operands                │\n");
        printf("│ • Temporary variables (t0, t1, ...) for expressions      │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        initTAC();
        generateTAC(root);
        printTAC();
        phase_time = ((double)(clock() - phase_start)) / CLOCKS_PER_SEC * 1000;
        printf("\n  ⏱  Phase 3 time: %.3f ms\n\n", phase_time);
        
        /* PHASE 4: Optimization */
        phase_start = clock();
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 4: CODE OPTIMIZATION                               │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Applying optimizations:                                  │\n");
        printf("│ • Constant folding (evaluate compile-time expressions)   │\n");
        printf("│ • Copy propagation (replace variables with values)       │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        optimizeTAC();
        printOptimizedTAC();
        phase_time = ((double)(clock() - phase_start)) / CLOCKS_PER_SEC * 1000;
        printf("\n  ⏱  Phase 4 time: %.3f ms\n\n", phase_time);
        
        /* PHASE 5: Code Generation */
        phase_start = clock();
        printf("┌──────────────────────────────────────────────────────────┐\n");
        printf("│ PHASE 5: MIPS CODE GENERATION                            │\n");
        printf("├──────────────────────────────────────────────────────────┤\n");
        printf("│ Translating to MIPS assembly:                            │\n");
        printf("│ • Variables stored on stack                              │\n");
        printf("│ • Using $t0-$t7 for temporary values                     │\n");
        printf("│ • System calls for print operations                      │\n");
        printf("└──────────────────────────────────────────────────────────┘\n");
        generateMIPS(root, argv[2]);
        phase_time = ((double)(clock() - phase_start)) / CLOCKS_PER_SEC * 1000;
        printf("✓ MIPS assembly code generated to: %s\n", argv[2]);
        printf("  ⏱  Phase 5 time: %.3f ms\n\n", phase_time);
        
        // Calculate total compilation time
        end_time = clock();
        total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000;
        
        printf("╔════════════════════════════════════════════════════════════╗\n");
        printf("║                  COMPILATION SUCCESSFUL!                   ║\n");
        printf("║         Run the output file in a MIPS simulator           ║\n");
        printf("╠════════════════════════════════════════════════════════════╣\n");
        printf("║ PERFORMANCE METRICS                                        ║\n");
        printf("╠════════════════════════════════════════════════════════════╣\n");
        printf("║ Total Compilation Time: %8.3f ms                       ║\n", total_time);
        printf("╚════════════════════════════════════════════════════════════╝\n");
    } else {
        printf("✗ Parse failed - check your syntax!\n");
        printf("Common errors:\n");
        printf("  • Missing semicolon after statements\n");
        printf("  • Undeclared variables\n");
        printf("  • Invalid syntax for print statements\n");
        return 1;
    }
    
    fclose(yyin);
    return 0;
}