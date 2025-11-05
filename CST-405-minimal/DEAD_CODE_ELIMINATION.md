# Dead Code Elimination: Theory, Implementation, and Benefits

## Overview

Dead code elimination is a compiler optimization technique that identifies and removes code that has no effect on the program's output. This includes unreachable code, unused variables, and computations whose results are never used. This optimization significantly improves program efficiency by reducing memory usage, execution time, and binary size.

## Types of Dead Code

### 1. **Unreachable Code**
Code that can never be executed due to control flow constraints.

### 2. **Unused Variables**
Variables that are declared but never read or used.

### 3. **Dead Assignments**
Assignments to variables whose values are never subsequently used.

### 4. **Dead Expressions**
Computations whose results are discarded or overwritten before use.

## Detailed Examples and Analysis

### Example 1: Unreachable Code After Return

#### Source Code:
```c
int calculateValue(int x) {
    if (x > 10) {
        return x * 2;
        print("This will never execute");  // Dead code
        int y = x + 5;                     // Dead code
    }
    return x;
}
```

#### Unoptimized TAC (Three-Address Code):
```
FUNCTION calculateValue:
    PARAM x
    t1 = x > 10
    IFFALSE t1 GOTO else_1
    t2 = x * 2
    RETURN t2
    PRINT "This will never execute"      // Dead code
    t3 = x + 5                          // Dead code
    ASSIGN y, t3                        // Dead code
else_1:
    RETURN x
END_FUNCTION
```

#### Optimized TAC (After Dead Code Elimination):
```
FUNCTION calculateValue:
    PARAM x
    t1 = x > 10
    IFFALSE t1 GOTO else_1
    t2 = x * 2
    RETURN t2
else_1:
    RETURN x
END_FUNCTION
```

**Resource Benefits:**
- **Memory**: Reduced by 3 TAC instructions (≈12-24 bytes per instruction)
- **Execution Time**: Eliminates unnecessary instruction fetches
- **Binary Size**: Smaller compiled code

### Example 2: Unused Variables and Dead Assignments

#### Source Code:
```c
int main() {
    int a = 5;          // Used
    int b = 10;         // Dead - never read
    int c = 15;         // Dead assignment - overwritten
    
    c = a + 3;          // Live assignment
    print(c);
    
    int d = a * 2;      // Dead - computed but never used
    
    return 0;
}
```

#### Unoptimized TAC:
```
DECL a
DECL b
DECL c
DECL d
ASSIGN a, 5           // Live
ASSIGN b, 10          // Dead - b never used
ASSIGN c, 15          // Dead - c overwritten before use
ADD t1, a, 3          // Live
ASSIGN c, t1          // Live
PRINT c               // Live
MUL t2, a, 2          // Dead computation
ASSIGN d, t2          // Dead assignment
RETURN 0              // Live
```

#### Optimized TAC (After Dead Code Elimination):
```
DECL a
DECL c
ASSIGN a, 5
ADD t1, a, 3
ASSIGN c, t1
PRINT c
RETURN 0
```

**Resource Benefits:**
- **Variables**: Reduced from 4 to 2 (50% reduction in stack space)
- **Instructions**: Reduced from 9 to 6 (33% reduction)
- **Registers**: Fewer temporary variables needed

### Example 3: Conditional Dead Code

#### Source Code:
```c
int processData(int flag) {
    int result = 0;
    
    if (flag == 0) {
        result = 100;
        return result;
    }
    
    // This code is live - reachable when flag != 0
    result = flag * 2;
    int temp = result + 10;   // Dead if not used later
    
    if (flag > 5) {
        return result;
    } else {
        return result + 1;
    }
    
    // Unreachable code after all return paths
    print("Never reached");
    return -1;
}
```

#### Unoptimized TAC:
```
FUNCTION processData:
    PARAM flag
    DECL result
    DECL temp
    ASSIGN result, 0
    
    EQ t1, flag, 0
    IFFALSE t1 GOTO else_1
    ASSIGN result, 100
    RETURN result
    
else_1:
    MUL t2, flag, 2
    ASSIGN result, t2
    ADD t3, result, 10
    ASSIGN temp, t3           // Dead - temp never used
    
    GT t4, flag, 5
    IFFALSE t4 GOTO else_2
    RETURN result
    GOTO end_if
    
else_2:
    ADD t5, result, 1
    RETURN t5
    
end_if:
    PRINT "Never reached"     // Dead - unreachable
    RETURN -1                 // Dead - unreachable
END_FUNCTION
```

#### Optimized TAC:
```
FUNCTION processData:
    PARAM flag
    DECL result
    ASSIGN result, 0
    
    EQ t1, flag, 0
    IFFALSE t1 GOTO else_1
    ASSIGN result, 100
    RETURN result
    
else_1:
    MUL t2, flag, 2
    ASSIGN result, t2
    
    GT t4, flag, 5
    IFFALSE t4 GOTO else_2
    RETURN result
    
else_2:
    ADD t5, result, 1
    RETURN t5
END_FUNCTION
```

**Resource Benefits:**
- **Variables**: Eliminated `temp` variable
- **Instructions**: Removed 4 dead instructions
- **Control Flow**: Simplified by removing unreachable paths

## Implementation Algorithms

### Algorithm 1: Live Variable Analysis

```c
typedef struct LiveVarInfo {
    char* varName;
    bool isLive;
    int lastUse;        // Line number of last use
    int definition;     // Line number of definition
} LiveVarInfo;

typedef struct BasicBlock {
    int id;
    TACInstruction* instructions;
    int numInstructions;
    
    // Live variable sets
    BitSet* liveIn;     // Variables live at block entry
    BitSet* liveOut;    // Variables live at block exit
    BitSet* def;        // Variables defined in block
    BitSet* use;        // Variables used before definition in block
    
    struct BasicBlock** successors;
    int numSuccessors;
} BasicBlock;

// Compute live variables using backward data flow analysis
void computeLiveVariables(BasicBlock* blocks, int numBlocks, int numVars) {
    bool changed = true;
    
    // Initialize sets
    for (int i = 0; i < numBlocks; i++) {
        blocks[i].liveIn = createBitSet(numVars);
        blocks[i].liveOut = createBitSet(numVars);
        blocks[i].def = createBitSet(numVars);
        blocks[i].use = createBitSet(numVars);
        
        // Compute DEF and USE sets for this block
        computeDefUse(&blocks[i], numVars);
    }
    
    // Iterate until convergence
    while (changed) {
        changed = false;
        
        // Process blocks in reverse order
        for (int i = numBlocks - 1; i >= 0; i--) {
            BasicBlock* block = &blocks[i];
            
            // OUT[B] = ∪ IN[S] for all successors S of B
            BitSet* newOut = createBitSet(numVars);
            for (int s = 0; s < block->numSuccessors; s++) {
                unionBitSets(newOut, block->successors[s]->liveIn);
            }
            
            // IN[B] = USE[B] ∪ (OUT[B] - DEF[B])
            BitSet* newIn = createBitSet(numVars);
            copyBitSet(newIn, newOut);
            subtractBitSets(newIn, block->def);  // OUT[B] - DEF[B]
            unionBitSets(newIn, block->use);     // USE[B] ∪ (OUT[B] - DEF[B])
            
            // Check for changes
            if (!equalBitSets(block->liveOut, newOut) || 
                !equalBitSets(block->liveIn, newIn)) {
                changed = true;
                
                freeBitSet(block->liveOut);
                freeBitSet(block->liveIn);
                block->liveOut = newOut;
                block->liveIn = newIn;
            } else {
                freeBitSet(newOut);
                freeBitSet(newIn);
            }
        }
    }
}

// Compute DEF and USE sets for a basic block
void computeDefUse(BasicBlock* block, int numVars) {
    for (int i = 0; i < block->numInstructions; i++) {
        TACInstruction* instr = &block->instructions[i];
        
        switch (instr->op) {
            case TAC_ASSIGN:
            case TAC_ADD:
            case TAC_SUB:
            case TAC_MUL:
            case TAC_DIV:
                // Variable is used (if not already defined in this block)
                if (instr->arg1 && instr->arg1->type == OPERAND_VARIABLE) {
                    int varId = getVariableId(instr->arg1->name);
                    if (!getBit(block->def, varId)) {
                        setBit(block->use, varId);
                    }
                }
                if (instr->arg2 && instr->arg2->type == OPERAND_VARIABLE) {
                    int varId = getVariableId(instr->arg2->name);
                    if (!getBit(block->def, varId)) {
                        setBit(block->use, varId);
                    }
                }
                
                // Variable is defined
                if (instr->result && instr->result->type == OPERAND_VARIABLE) {
                    int varId = getVariableId(instr->result->name);
                    setBit(block->def, varId);
                }
                break;
                
            case TAC_PRINT:
                // Variable is used
                if (instr->arg1 && instr->arg1->type == OPERAND_VARIABLE) {
                    int varId = getVariableId(instr->arg1->name);
                    if (!getBit(block->def, varId)) {
                        setBit(block->use, varId);
                    }
                }
                break;
                
            default:
                break;
        }
    }
}
```

### Algorithm 2: Dead Code Elimination Implementation

```c
// Mark and eliminate dead code
typedef struct DeadCodeInfo {
    bool* isDeadInstruction;    // Array marking dead instructions
    bool* isDeadVariable;       // Array marking dead variables
    int numInstructions;
    int numVariables;
} DeadCodeInfo;

DeadCodeInfo* analyzeDeadCode(TACList* tacList, BasicBlock* blocks, int numBlocks) {
    DeadCodeInfo* info = malloc(sizeof(DeadCodeInfo));
    info->numInstructions = countTACInstructions(tacList);
    info->numVariables = getNumVariables();
    
    info->isDeadInstruction = calloc(info->numInstructions, sizeof(bool));
    info->isDeadVariable = calloc(info->numVariables, sizeof(bool));
    
    // Step 1: Compute live variables
    computeLiveVariables(blocks, numBlocks, info->numVariables);
    
    // Step 2: Mark dead assignments
    markDeadAssignments(tacList, blocks, numBlocks, info);
    
    // Step 3: Mark unreachable code
    markUnreachableCode(tacList, blocks, numBlocks, info);
    
    // Step 4: Mark unused variables
    markUnusedVariables(info);
    
    return info;
}

void markDeadAssignments(TACList* tacList, BasicBlock* blocks, int numBlocks, 
                        DeadCodeInfo* info) {
    TACNode* current = tacList->head;
    int instrIndex = 0;
    
    for (int b = 0; b < numBlocks; b++) {
        BasicBlock* block = &blocks[b];
        
        for (int i = 0; i < block->numInstructions; i++, instrIndex++) {
            TACInstruction* instr = &block->instructions[i];
            
            if (instr->op == TAC_ASSIGN || instr->op == TAC_ADD || 
                instr->op == TAC_SUB || instr->op == TAC_MUL || 
                instr->op == TAC_DIV) {
                
                if (instr->result && instr->result->type == OPERAND_VARIABLE) {
                    int varId = getVariableId(instr->result->name);
                    
                    // Check if variable is live at this point
                    bool isLiveAfter = false;
                    
                    // Check if live in any successor instruction in same block
                    for (int j = i + 1; j < block->numInstructions; j++) {
                        if (isVariableUsed(&block->instructions[j], instr->result->name)) {
                            isLiveAfter = true;
                            break;
                        }
                        if (isVariableRedefined(&block->instructions[j], instr->result->name)) {
                            break; // Redefined before use
                        }
                    }
                    
                    // Check if live in successor blocks
                    if (!isLiveAfter) {
                        for (int s = 0; s < block->numSuccessors; s++) {
                            if (getBit(block->successors[s]->liveIn, varId)) {
                                isLiveAfter = true;
                                break;
                            }
                        }
                    }
                    
                    // Mark as dead if not live after
                    if (!isLiveAfter) {
                        info->isDeadInstruction[instrIndex] = true;
                        printf("Dead assignment: %s at instruction %d\n", 
                               instr->result->name, instrIndex);
                    }
                }
            }
        }
    }
}

void markUnreachableCode(TACList* tacList, BasicBlock* blocks, int numBlocks,
                        DeadCodeInfo* info) {
    bool* reachable = calloc(numBlocks, sizeof(bool));
    
    // Mark entry block as reachable
    reachable[0] = true;
    
    // Propagate reachability
    bool changed = true;
    while (changed) {
        changed = false;
        
        for (int i = 0; i < numBlocks; i++) {
            if (reachable[i]) {
                BasicBlock* block = &blocks[i];
                
                for (int s = 0; s < block->numSuccessors; s++) {
                    int succId = block->successors[s]->id;
                    if (!reachable[succId]) {
                        reachable[succId] = true;
                        changed = true;
                    }
                }
            }
        }
    }
    
    // Mark instructions in unreachable blocks as dead
    int instrIndex = 0;
    for (int b = 0; b < numBlocks; b++) {
        if (!reachable[b]) {
            BasicBlock* block = &blocks[b];
            for (int i = 0; i < block->numInstructions; i++, instrIndex++) {
                info->isDeadInstruction[instrIndex] = true;
                printf("Unreachable instruction at index %d in block %d\n", 
                       instrIndex, b);
            }
        } else {
            instrIndex += blocks[b].numInstructions;
        }
    }
    
    free(reachable);
}

// Eliminate dead code from TAC
TACList* eliminateDeadCode(TACList* originalTAC, DeadCodeInfo* info) {
    TACList* optimizedTAC = createTACList();
    TACNode* current = originalTAC->head;
    int instrIndex = 0;
    
    while (current) {
        if (!info->isDeadInstruction[instrIndex]) {
            // Copy live instruction to optimized TAC
            TACNode* newNode = createTACNode(current->op, 
                                           current->arg1, 
                                           current->arg2, 
                                           current->result);
            appendTACNode(optimizedTAC, newNode);
        } else {
            printf("Eliminated dead instruction: ");
            printTACInstruction(current);
        }
        
        current = current->next;
        instrIndex++;
    }
    
    return optimizedTAC;
}
```

### Algorithm 3: Advanced Dead Code Elimination with Side Effects

```c
// Enhanced dead code elimination considering side effects
typedef struct SideEffectInfo {
    bool hasIO;           // Function calls, print statements
    bool hasMemoryAccess; // Array accesses, pointer operations
    bool hasVolatileAccess; // Volatile variable access
    bool throwsException; // Exception throwing operations
} SideEffectInfo;

bool hasSideEffects(TACInstruction* instr) {
    SideEffectInfo effects = analyzeSideEffects(instr);
    
    return effects.hasIO || effects.hasMemoryAccess || 
           effects.hasVolatileAccess || effects.throwsException;
}

SideEffectInfo analyzeSideEffects(TACInstruction* instr) {
    SideEffectInfo effects = {false, false, false, false};
    
    switch (instr->op) {
        case TAC_PRINT:
        case TAC_FUNC_CALL:
            effects.hasIO = true;
            break;
            
        case TAC_ARRAY_STORE:
        case TAC_ARRAY_LOAD:
            effects.hasMemoryAccess = true;
            break;
            
        case TAC_DIV:
            // Division by zero can throw exception
            effects.throwsException = true;
            break;
            
        case TAC_ASSIGN:
        case TAC_ADD:
        case TAC_SUB:
        case TAC_MUL:
            // Pure operations - no side effects
            break;
            
        default:
            // Conservative: assume side effects for unknown operations
            effects.hasIO = true;
            break;
    }
    
    return effects;
}

// Modified dead code elimination that preserves side effects
void markDeadCodeWithSideEffects(TACList* tacList, DeadCodeInfo* info) {
    TACNode* current = tacList->head;
    int instrIndex = 0;
    
    while (current) {
        if (info->isDeadInstruction[instrIndex]) {
            // Check if instruction has side effects
            if (hasSideEffects(&current->instruction)) {
                // Keep instruction for side effects, but may optimize result
                info->isDeadInstruction[instrIndex] = false;
                printf("Preserving dead instruction due to side effects: ");
                printTACInstruction(current);
            }
        }
        
        current = current->next;
        instrIndex++;
    }
}
```

## Resource Utilization Benefits

### 1. **Memory Usage Reduction**

#### Variable Elimination:
```c
// Before optimization: 4 variables × 4 bytes = 16 bytes
int a, b, c, d;
a = 5;
b = 10;    // Dead
c = 15;    // Dead
d = 20;    // Dead
print(a);

// After optimization: 1 variable × 4 bytes = 4 bytes (75% reduction)
int a;
a = 5;
print(a);
```

#### Instruction Memory:
- **Before**: 10 TAC instructions × 12 bytes average = 120 bytes
- **After**: 4 TAC instructions × 12 bytes average = 48 bytes
- **Savings**: 72 bytes (60% reduction)

### 2. **Execution Time Improvement**

#### CPU Cycles Saved:
```c
// Unoptimized execution profile:
// - Variable declarations: 4 cycles
// - Dead assignments: 3 × 2 cycles = 6 cycles  
// - Live operations: 2 × 2 cycles = 4 cycles
// - Total: 14 cycles

// Optimized execution profile:
// - Variable declarations: 1 cycle
// - Live operations: 2 × 2 cycles = 4 cycles
// - Total: 5 cycles

// Improvement: 64% reduction in execution time
```

### 3. **Cache Performance**

#### Instruction Cache:
- Smaller code footprint improves instruction cache hit rate
- Fewer cache misses reduce memory access latency
- Better spatial locality in instruction execution

#### Data Cache:
- Fewer variables reduce stack memory usage
- Better cache line utilization
- Reduced memory bandwidth requirements

### 4. **Register Allocation Benefits**

```c
// Register pressure analysis

// Before optimization:
// Variables: a, b, c, d (4 registers needed)
// Temporaries: t1, t2, t3 (3 additional registers)
// Total register pressure: 7

// After optimization:
// Variables: a (1 register needed)
// Temporaries: t1 (1 additional register)
// Total register pressure: 2

// Benefit: 71% reduction in register pressure
// Enables better register allocation for remaining code
```

### 5. **Binary Size Reduction**

#### MIPS Assembly Comparison:

**Unoptimized MIPS (40 instructions):**
```mips
# Dead variable declarations
addi $sp, $sp, -16    # Allocate 4 variables
sw $zero, 0($sp)      # Initialize a
sw $zero, 4($sp)      # Initialize b (dead)
sw $zero, 8($sp)      # Initialize c (dead)  
sw $zero, 12($sp)     # Initialize d (dead)

# Dead assignments
li $t0, 10
sw $t0, 4($sp)        # Dead: b = 10
li $t1, 15
sw $t1, 8($sp)        # Dead: c = 15
li $t2, 20  
sw $t2, 12($sp)       # Dead: d = 20

# Live code
li $t0, 5
sw $t0, 0($sp)        # a = 5
lw $a0, 0($sp)
li $v0, 1
syscall               # print(a)
```

**Optimized MIPS (8 instructions):**
```mips
# Only live variable
addi $sp, $sp, -4     # Allocate 1 variable
li $t0, 5
sw $t0, 0($sp)        # a = 5
lw $a0, 0($sp)
li $v0, 1
syscall               # print(a)
```

**Size Reduction**: 80% fewer instructions (32 → 8 instructions)

## Performance Measurement

### Benchmarking Framework

```c
typedef struct OptimizationMetrics {
    int originalInstructions;
    int optimizedInstructions;
    int deadInstructionsEliminated;
    int deadVariablesEliminated;
    
    double memoryReduction;      // Percentage
    double executionTimeReduction; // Percentage
    double binarySizeReduction;   // Percentage
} OptimizationMetrics;

OptimizationMetrics measureDeadCodeElimination(TACList* original, 
                                              TACList* optimized) {
    OptimizationMetrics metrics = {0};
    
    metrics.originalInstructions = countTACInstructions(original);
    metrics.optimizedInstructions = countTACInstructions(optimized);
    metrics.deadInstructionsEliminated = 
        metrics.originalInstructions - metrics.optimizedInstructions;
    
    metrics.memoryReduction = 
        (double)metrics.deadInstructionsEliminated / 
        metrics.originalInstructions * 100.0;
    
    // Simulate execution to measure time reduction
    metrics.executionTimeReduction = 
        simulateExecutionTime(original, optimized);
    
    printf("Dead Code Elimination Results:\n");
    printf("Instructions eliminated: %d/%d (%.1f%%)\n",
           metrics.deadInstructionsEliminated,
           metrics.originalInstructions,
           metrics.memoryReduction);
    
    return metrics;
}
```

## Integration with Compiler Pipeline

```c
// In main compiler pipeline
void optimizeProgram(TACList* tacList) {
    printf("Phase 4.1: Dead Code Elimination\n");
    
    // Build control flow graph
    BasicBlock* blocks;
    int numBlocks = buildControlFlowGraph(tacList, &blocks);
    
    // Analyze and eliminate dead code
    DeadCodeInfo* deadInfo = analyzeDeadCode(tacList, blocks, numBlocks);
    TACList* optimizedTAC = eliminateDeadCode(tacList, deadInfo);
    
    // Measure improvement
    OptimizationMetrics metrics = measureDeadCodeElimination(tacList, optimizedTAC);
    
    // Replace original TAC with optimized version
    freeTACList(tacList);
    *tacList = *optimizedTAC;
    
    printf("Dead code elimination complete: %.1f%% size reduction\n",
           metrics.memoryReduction);
    
    // Cleanup
    free(deadInfo->isDeadInstruction);
    free(deadInfo->isDeadVariable);
    free(deadInfo);
    free(blocks);
}
```

## Conclusion

Dead code elimination provides significant benefits in terms of:

- **Memory Efficiency**: 50-80% reduction in memory usage for programs with significant dead code
- **Execution Speed**: 30-70% improvement in execution time by eliminating unnecessary operations  
- **Cache Performance**: Better instruction and data cache utilization
- **Register Allocation**: Reduced register pressure enables better optimization
- **Binary Size**: Smaller executables improve load times and distribution

The optimization is particularly effective in educational compilers where students may write inefficient code with unused variables and unreachable statements. The techniques shown can be implemented incrementally, starting with simple dead assignment elimination and progressing to full control flow analysis.