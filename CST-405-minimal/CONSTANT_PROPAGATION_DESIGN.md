# Constant Propagation Optimization Implementation

## Overview

Constant propagation is a compiler optimization technique that replaces variables with their known constant values throughout the program. This optimization can significantly improve code efficiency by eliminating unnecessary variable lookups and enabling further optimizations like constant folding.

## Design Approaches and Implementation Strategies

### 1. **Basic Constant Propagation**

**Concept**: Replace variables that hold constant values with the actual constants.

#### Source Code Example:
```c
// Before constant propagation
int x = 5;
int y = x + 3;
print(y);

// After constant propagation  
int x = 5;
int y = 5 + 3;    // x replaced with 5
print(8);         // y replaced with 8 (after constant folding)
```

#### Implementation Approach A: Single-Pass Analysis

```c
// Simple constant propagation during TAC generation
typedef struct ConstantTable {
    char* varName;
    int isConstant;
    union {
        int intVal;
        float floatVal;
    } value;
    VarType type;
} ConstantTable;

ConstantTable constTable[MAX_VARS];
int constTableSize = 0;

// Add variable to constant table
void addConstant(const char* name, int intVal, VarType type) {
    for (int i = 0; i < constTableSize; i++) {
        if (strcmp(constTable[i].varName, name) == 0) {
            constTable[i].isConstant = 1;
            constTable[i].value.intVal = intVal;
            constTable[i].type = type;
            return;
        }
    }
    // Add new entry
    constTable[constTableSize].varName = strdup(name);
    constTable[constTableSize].isConstant = 1;
    constTable[constTableSize].value.intVal = intVal;
    constTable[constTableSize].type = type;
    constTableSize++;
}

// Check if variable is constant
int isVarConstant(const char* name, int* value) {
    for (int i = 0; i < constTableSize; i++) {
        if (strcmp(constTable[i].varName, name) == 0 && 
            constTable[i].isConstant) {
            *value = constTable[i].value.intVal;
            return 1;
        }
    }
    return 0;
}

// Invalidate variable (when it's modified)
void invalidateConstant(const char* name) {
    for (int i = 0; i < constTableSize; i++) {
        if (strcmp(constTable[i].varName, name) == 0) {
            constTable[i].isConstant = 0;
            break;
        }
    }
}
```

#### Implementation Approach B: Data Flow Analysis

```c
// More sophisticated approach using reaching definitions
typedef struct ReachingDef {
    char* varName;
    int defPoint;        // Where variable was defined
    int isConstant;
    int constantValue;
    struct ReachingDef* next;
} ReachingDef;

typedef struct BasicBlock {
    int id;
    TACInstruction* instructions;
    int numInstructions;
    ReachingDef* reachingIn;   // Constants reaching this block
    ReachingDef* reachingOut;  // Constants leaving this block
    struct BasicBlock** predecessors;
    struct BasicBlock** successors;
    int numPreds, numSuccs;
} BasicBlock;

// Compute reaching definitions for constant propagation
void computeReachingDefinitions(BasicBlock* blocks, int numBlocks) {
    bool changed = true;
    
    while (changed) {
        changed = false;
        
        for (int i = 0; i < numBlocks; i++) {
            BasicBlock* block = &blocks[i];
            
            // IN[B] = ∪ OUT[P] for all predecessors P of B
            ReachingDef* newIn = NULL;
            for (int p = 0; p < block->numPreds; p++) {
                newIn = unionReachingDefs(newIn, block->predecessors[p]->reachingOut);
            }
            
            // OUT[B] = (IN[B] - KILL[B]) ∪ GEN[B]
            ReachingDef* newOut = computeBlockOutput(block, newIn);
            
            if (!equalReachingDefs(block->reachingOut, newOut)) {
                changed = true;
                block->reachingIn = newIn;
                block->reachingOut = newOut;
            }
        }
    }
}
```

### 2. **Inter-procedural Constant Propagation**

#### Challenge: Function Calls and Parameter Passing

```c
// Source code with function calls
int getConstant() {
    return 42;
}

int main() {
    int x = getConstant();  // Can we propagate 42?
    int y = x + 1;
    print(y);
}
```

#### Implementation Approach: Function Summary Analysis

```c
typedef struct FunctionSummary {
    char* functionName;
    bool returnsConstant;
    int constantReturnValue;
    VarType returnType;
} FunctionSummary;

FunctionSummary funcSummaries[MAX_FUNCTIONS];
int numFuncSummaries = 0;

// Analyze function to determine if it returns a constant
void analyzeFunctionForConstants(ASTNode* funcNode) {
    if (funcNode->type != NODE_FUNC_DECL) return;
    
    // Simple case: function body is just "return constant"
    ASTNode* body = funcNode->data.funcDecl.body;
    if (body && body->type == NODE_RETURN && 
        body->data.returnStmt.value && 
        body->data.returnStmt.value->type == NODE_NUM) {
        
        // Record that this function returns a constant
        funcSummaries[numFuncSummaries].functionName = 
            strdup(funcNode->data.funcDecl.name);
        funcSummaries[numFuncSummaries].returnsConstant = true;
        funcSummaries[numFuncSummaries].constantReturnValue = 
            body->data.returnStmt.value->data.num;
        funcSummaries[numFuncSummaries].returnType = TYPE_INT;
        numFuncSummaries++;
    }
}

// Use function summary during constant propagation
int getFunctionConstantReturn(const char* funcName) {
    for (int i = 0; i < numFuncSummaries; i++) {
        if (strcmp(funcSummaries[i].functionName, funcName) == 0 && 
            funcSummaries[i].returnsConstant) {
            return funcSummaries[i].constantReturnValue;
        }
    }
    return INT_MIN; // Not a constant
}
```

### 3. **TAC-Level Constant Propagation**

#### Original TAC vs Optimized TAC

```c
// Original TAC sequence
// x = 5
// y = x + 3  
// z = y * 2
// print z

TAC_ASSIGN, x, NULL, 5
TAC_ADD, y, x, 3        // Can propagate x=5
TAC_MUL, z, y, 2        // Can propagate y=8  
TAC_PRINT, z, NULL, NULL // Can propagate z=16

// After constant propagation
TAC_ASSIGN, x, NULL, 5
TAC_ADD, y, 5, 3        // x replaced with 5
TAC_MUL, z, 8, 2        // y replaced with 8
TAC_PRINT, 16, NULL, NULL // z replaced with 16
```

#### Implementation: TAC Optimization Pass

```c
typedef struct ConstantInfo {
    char* varName;
    bool isConstant;
    TACOperandType constType;
    union {
        int intValue;
        float floatValue;
    } value;
} ConstantInfo;

void optimizeTACConstantPropagation(TACList* tacList) {
    ConstantInfo constants[MAX_VARS];
    int numConstants = 0;
    
    TACNode* current = tacList->head;
    
    while (current) {
        switch (current->op) {
            case TAC_ASSIGN:
                if (current->arg1->type == OPERAND_CONSTANT) {
                    // Record constant assignment
                    updateConstantInfo(constants, &numConstants, 
                                     current->result->name, 
                                     current->arg1);
                } else if (current->arg1->type == OPERAND_VARIABLE) {
                    // Check if source is constant
                    ConstantInfo* srcConst = findConstant(constants, numConstants, 
                                                        current->arg1->name);
                    if (srcConst && srcConst->isConstant) {
                        // Propagate constant
                        current->arg1->type = OPERAND_CONSTANT;
                        current->arg1->value = srcConst->value;
                        
                        // Record result as constant too
                        updateConstantInfo(constants, &numConstants,
                                         current->result->name, current->arg1);
                    } else {
                        // Invalidate result as non-constant
                        invalidateConstant(constants, numConstants, 
                                         current->result->name);
                    }
                } else {
                    // Complex expression - invalidate result
                    invalidateConstant(constants, numConstants, 
                                     current->result->name);
                }
                break;
                
            case TAC_ADD:
            case TAC_SUB:
            case TAC_MUL:
            case TAC_DIV:
                // Check if both operands are constants
                ConstantInfo* leftConst = NULL;
                ConstantInfo* rightConst = NULL;
                
                if (current->arg1->type == OPERAND_VARIABLE) {
                    leftConst = findConstant(constants, numConstants, 
                                           current->arg1->name);
                    if (leftConst && leftConst->isConstant) {
                        // Replace variable with constant
                        current->arg1->type = OPERAND_CONSTANT;
                        current->arg1->value = leftConst->value;
                    }
                }
                
                if (current->arg2->type == OPERAND_VARIABLE) {
                    rightConst = findConstant(constants, numConstants, 
                                            current->arg2->name);
                    if (rightConst && rightConst->isConstant) {
                        // Replace variable with constant
                        current->arg2->type = OPERAND_CONSTANT;
                        current->arg2->value = rightConst->value;
                    }
                }
                
                // If both are now constants, the result could be constant folded
                if (current->arg1->type == OPERAND_CONSTANT && 
                    current->arg2->type == OPERAND_CONSTANT) {
                    
                    // Perform constant folding and record result
                    int resultValue = evaluateConstantOperation(
                        current->op, 
                        current->arg1->value.intValue, 
                        current->arg2->value.intValue);
                    
                    TACOperand constResult;
                    constResult.type = OPERAND_CONSTANT;
                    constResult.value.intValue = resultValue;
                    
                    updateConstantInfo(constants, &numConstants,
                                     current->result->name, &constResult);
                } else {
                    // Result is not constant
                    invalidateConstant(constants, numConstants, 
                                     current->result->name);
                }
                break;
                
            case TAC_IFFALSE:
                // Propagate constants in condition
                if (current->arg1->type == OPERAND_VARIABLE) {
                    ConstantInfo* condConst = findConstant(constants, numConstants, 
                                                         current->arg1->name);
                    if (condConst && condConst->isConstant) {
                        current->arg1->type = OPERAND_CONSTANT;
                        current->arg1->value = condConst->value;
                    }
                }
                break;
                
            case TAC_PRINT:
                // Propagate constants in print arguments
                if (current->arg1 && current->arg1->type == OPERAND_VARIABLE) {
                    ConstantInfo* printConst = findConstant(constants, numConstants, 
                                                          current->arg1->name);
                    if (printConst && printConst->isConstant) {
                        current->arg1->type = OPERAND_CONSTANT;
                        current->arg1->value = printConst->value;
                    }
                }
                break;
                
            default:
                break;
        }
        
        current = current->next;
    }
}
```

### 4. **Control Flow Aware Constant Propagation**

#### Challenge: Conditionals and Loops

```c
// Source code with control flow
int x = 5;
if (condition) {
    x = 10;        // x is no longer constant
}
print(x);          // Cannot propagate constant here
```

#### Implementation: Basic Block Analysis

```c
typedef struct {
    int blockId;
    ConstantInfo constants[MAX_VARS];
    int numConstants;
} BlockConstantInfo;

void propagateConstantsAcrossBlocks(BasicBlock* blocks, int numBlocks) {
    BlockConstantInfo blockInfo[numBlocks];
    
    // Initialize entry block
    initializeConstants(&blockInfo[0]);
    
    // Iterate until convergence
    bool changed = true;
    while (changed) {
        changed = false;
        
        for (int i = 0; i < numBlocks; i++) {
            BasicBlock* block = &blocks[i];
            
            // Merge constants from predecessors
            ConstantInfo mergedConstants[MAX_VARS];
            int numMerged = 0;
            
            for (int p = 0; p < block->numPreds; p++) {
                BasicBlock* pred = block->predecessors[p];
                mergeConstants(mergedConstants, &numMerged, 
                             &blockInfo[pred->id]);
            }
            
            // Propagate through block instructions
            ConstantInfo blockConstants[MAX_VARS];
            memcpy(blockConstants, mergedConstants, 
                   sizeof(ConstantInfo) * numMerged);
            int numBlockConstants = numMerged;
            
            for (int j = 0; j < block->numInstructions; j++) {
                processInstructionForConstants(&block->instructions[j],
                                             blockConstants, 
                                             &numBlockConstants);
            }
            
            // Check if block output changed
            if (!equalConstants(blockInfo[i].constants, 
                              blockConstants, numBlockConstants)) {
                changed = true;
                memcpy(blockInfo[i].constants, blockConstants,
                       sizeof(ConstantInfo) * numBlockConstants);
                blockInfo[i].numConstants = numBlockConstants;
            }
        }
    }
}

// Merge constants from multiple control flow paths
void mergeConstants(ConstantInfo* result, int* numResult, 
                   BlockConstantInfo* source) {
    for (int i = 0; i < source->numConstants; i++) {
        ConstantInfo* srcConst = &source->constants[i];
        
        // Find if this variable already exists in result
        int found = -1;
        for (int j = 0; j < *numResult; j++) {
            if (strcmp(result[j].varName, srcConst->varName) == 0) {
                found = j;
                break;
            }
        }
        
        if (found >= 0) {
            // Variable exists - check if values match
            if (result[found].isConstant && srcConst->isConstant &&
                result[found].value.intValue == srcConst->value.intValue) {
                // Same constant value - keep as constant
                continue;
            } else {
                // Different values or one not constant - mark as non-constant
                result[found].isConstant = false;
            }
        } else if (srcConst->isConstant) {
            // New constant variable
            result[*numResult] = *srcConst;
            result[*numResult].varName = strdup(srcConst->varName);
            (*numResult)++;
        }
    }
}
```

### 5. **Advanced: Conditional Constant Propagation**

#### Concept: Propagate constants based on condition outcomes

```c
// Source code example
int x = 5;
if (x > 3) {        // Always true since x = 5
    int y = x + 2;  // y = 7 (can be propagated)
    print(y);
} else {
    // Dead code - never executed
    int z = x - 1;
}
```

#### Implementation: Conditional Analysis

```c
typedef struct ConditionalConstant {
    char* varName;
    bool isConstant;
    bool isConditionallyConstant;
    int constantValue;
    ASTNode* condition;  // Condition under which it's constant
} ConditionalConstant;

void analyzeConditionalConstants(ASTNode* ifNode, 
                               ConstantInfo* constants, 
                               int numConstants) {
    // Evaluate condition with current constants
    int conditionResult = evaluateConditionWithConstants(
        ifNode->data.ifStmt.condition, constants, numConstants);
    
    if (conditionResult == 1) {
        // Condition always true - analyze then branch only
        analyzeBlockForConstants(ifNode->data.ifStmt.thenStmt, 
                               constants, numConstants);
        // Mark else branch as dead code
        markDeadCode(ifNode->data.ifStmt.elseStmt);
        
    } else if (conditionResult == 0) {
        // Condition always false - analyze else branch only
        analyzeBlockForConstants(ifNode->data.ifStmt.elseStmt, 
                               constants, numConstants);
        // Mark then branch as dead code
        markDeadCode(ifNode->data.ifStmt.thenStmt);
        
    } else {
        // Condition unknown - analyze both branches
        ConstantInfo thenConstants[MAX_VARS];
        ConstantInfo elseConstants[MAX_VARS];
        int numThen = numConstants, numElse = numConstants;
        
        memcpy(thenConstants, constants, sizeof(ConstantInfo) * numConstants);
        memcpy(elseConstants, constants, sizeof(ConstantInfo) * numConstants);
        
        analyzeBlockForConstants(ifNode->data.ifStmt.thenStmt,
                               thenConstants, &numThen);
        analyzeBlockForConstants(ifNode->data.ifStmt.elseStmt,
                               elseConstants, &numElse);
        
        // Merge results
        mergeConstantInfo(constants, numConstants, 
                         thenConstants, numThen,
                         elseConstants, numElse);
    }
}

int evaluateConditionWithConstants(ASTNode* condition, 
                                 ConstantInfo* constants, 
                                 int numConstants) {
    if (condition->type == NODE_COMPARE) {
        int leftVal, rightVal;
        bool leftIsConst = false, rightIsConst = false;
        
        if (condition->data.compare.left->type == NODE_VAR) {
            ConstantInfo* leftConst = findConstant(constants, numConstants,
                                                 condition->data.compare.left->data.name);
            if (leftConst && leftConst->isConstant) {
                leftVal = leftConst->value.intValue;
                leftIsConst = true;
            }
        } else if (condition->data.compare.left->type == NODE_NUM) {
            leftVal = condition->data.compare.left->data.num;
            leftIsConst = true;
        }
        
        if (condition->data.compare.right->type == NODE_VAR) {
            ConstantInfo* rightConst = findConstant(constants, numConstants,
                                                  condition->data.compare.right->data.name);
            if (rightConst && rightConst->isConstant) {
                rightVal = rightConst->value.intValue;
                rightIsConst = true;
            }
        } else if (condition->data.compare.right->type == NODE_NUM) {
            rightVal = condition->data.compare.right->data.num;
            rightIsConst = true;
        }
        
        if (leftIsConst && rightIsConst) {
            // Evaluate comparison
            switch (condition->data.compare.compOp) {
                case '<':  return (leftVal < rightVal) ? 1 : 0;
                case LE:   return (leftVal <= rightVal) ? 1 : 0;
                case '>':  return (leftVal > rightVal) ? 1 : 0;
                case GE:   return (leftVal >= rightVal) ? 1 : 0;
                case EQ:   return (leftVal == rightVal) ? 1 : 0;
                case NE:   return (leftVal != rightVal) ? 1 : 0;
                default:   return -1; // Unknown
            }
        }
    }
    
    return -1; // Cannot evaluate
}
```

### 6. **Integration with Existing Compiler Pipeline**

#### Compiler Integration Points

```c
// In main.c - add optimization pass
int main(int argc, char* argv[]) {
    // ... existing phases ...
    
    // Phase 4: Optimization
    printf("Phase 4: Constant Propagation Optimization\n");
    optimizeTACConstantPropagation(tacList);
    
    // Additional optimization passes
    performConstantFolding(tacList);
    eliminateDeadCode(tacList);
    
    // ... continue with code generation ...
}
```

#### TAC Modification Structure

```c
// Enhanced TAC operand to track constant status
typedef struct TACOperand {
    TACOperandType type;
    union {
        char* name;           // Variable name
        int intValue;         // Integer constant
        float floatValue;     // Float constant
    } value;
    
    // Optimization metadata
    bool wasConstantPropagated;  // Track if this was optimized
    char* originalName;          // Original variable name before propagation
} TACOperand;
```

### 7. **Testing and Validation**

#### Test Cases for Constant Propagation

```c
// Test 1: Basic propagation
// Input:
int a = 5;
int b = a + 3;
print(b);

// Expected output after optimization:
// TAC: ASSIGN a, 5
//      ADD b, 5, 3      <- 'a' propagated to 5
//      PRINT 8          <- 'b' propagated to 8

// Test 2: Control flow
// Input:
int x = 10;
if (x > 5) {
    int y = x * 2;
    print(y);
}

// Expected: x propagated to 10, condition evaluates to true,
//          y propagated to 20

// Test 3: Loop invalidation
// Input:
int i = 0;
while (i < 5) {
    print(i);
    i = i + 1;    // i is no longer constant after first iteration
}

// Expected: Initial i=0 propagated, but invalidated in loop
```

#### Validation Framework

```c
void validateConstantPropagation(TACList* original, TACList* optimized) {
    // Verify semantic equivalence
    assert(simulateExecution(original) == simulateExecution(optimized));
    
    // Count constant propagations performed
    int propagations = countConstantReplacements(original, optimized);
    printf("Constant propagations performed: %d\n", propagations);
    
    // Verify no incorrect propagations
    validateNoInvalidPropagations(optimized);
}
```

## Performance Considerations

### Time Complexity Analysis
- **Single-pass approach**: O(n) where n is number of TAC instructions
- **Data flow analysis**: O(n³) in worst case for complex control flow
- **Inter-procedural**: O(p×n²) where p is number of procedures

### Space Complexity
- **Constant table**: O(v) where v is number of variables
- **Reaching definitions**: O(n×v) for complete analysis

## Implementation Priority

1. **Phase 1**: Basic intra-procedural constant propagation for straight-line code
2. **Phase 2**: Add support for simple control flow (if statements)
3. **Phase 3**: Handle loops with proper invalidation
4. **Phase 4**: Inter-procedural analysis for function calls
5. **Phase 5**: Advanced conditional constant propagation

This approach provides a solid foundation for constant propagation optimization while maintaining the educational focus of the compiler project.