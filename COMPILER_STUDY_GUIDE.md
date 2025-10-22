# 📚 COMPLETE COMPILER STUDY GUIDE
## Everything You Need to Know for Your Quiz

---

## 📖 TABLE OF CONTENTS

1. [Compiler Overview](#compiler-overview)
2. [Phase 1: Lexical Analysis (Scanner)](#phase-1-lexical-analysis-scanner)
3. [Phase 2: Syntax Analysis (Parser)](#phase-2-syntax-analysis-parser)
4. [Phase 3: Semantic Analysis](#phase-3-semantic-analysis)
5. [Phase 4: Intermediate Representation (TAC)](#phase-4-intermediate-representation-tac)
6. [Phase 5: Code Generation (MIPS)](#phase-5-code-generation-mips)
7. [Symbol Table & Scope Management](#symbol-table--scope-management)
8. [MIPS Assembly Basics](#mips-assembly-basics)
9. [Function Calling Convention](#function-calling-convention)
10. [Common Quiz Questions](#common-quiz-questions)

---

# COMPILER OVERVIEW

## What is a Compiler?

A **compiler** is a program that translates source code (high-level language) into target code (machine/assembly language).

### The Compilation Pipeline

```
Source Code
    ↓
[SCANNER] → Tokens
    ↓
[PARSER] → Abstract Syntax Tree (AST)
    ↓
[SEMANTIC ANALYZER] → Validated AST
    ↓
[TAC GENERATOR] → Three-Address Code
    ↓
[OPTIMIZER] → Optimized TAC
    ↓
[CODE GENERATOR] → MIPS Assembly
    ↓
Target Code (Assembly)
```

### Why Multiple Phases?

- **Separation of concerns** - Each phase has one job
- **Easier to debug** - Can inspect output at each stage
- **Reusability** - Change target architecture without changing parser
- **Optimization opportunities** - Can optimize at different levels

---

# PHASE 1: LEXICAL ANALYSIS (SCANNER)

## Purpose

Convert raw source code text into **tokens** (meaningful units).

## What is a Token?

A token is a categorized chunk of text.

### Token Categories

| Category | Examples | Description |
|----------|----------|-------------|
| **Keywords** | `int`, `if`, `while`, `return` | Reserved words |
| **Identifiers** | `x`, `myVar`, `count` | Variable/function names |
| **Literals** | `42`, `"hello"`, `3.14` | Constant values |
| **Operators** | `+`, `-`, `*`, `/`, `=` | Operations |
| **Punctuation** | `(`, `)`, `{`, `}`, `;` | Syntax markers |

## How It Works

### Example: Scanning `int x = 5;`

```
Input: "int x = 5;"

Scanning process:
"int"  → TOKEN_INT     (keyword)
" "    → SKIP          (whitespace)
"x"    → IDENTIFIER    (identifier)
" "    → SKIP
"="    → ASSIGN        (operator)
" "    → SKIP
"5"    → NUMBER(5)     (literal)
";"    → SEMICOLON     (punctuation)
```

## Implementation: Flex

### scanner.l Structure

```lex
%{
    /* C code: includes, definitions */
%}

/* Regular expression definitions */
DIGIT   [0-9]
LETTER  [a-zA-Z]

%%
/* Pattern matching rules */
{DIGIT}+        { return NUM; }
{LETTER}+       { return ID; }
"int"           { return INT; }
"="             { return '='; }

%%
/* C code: helper functions */
```

### Key Concepts

1. **Regular Expressions** - Patterns to match tokens
2. **Longest Match** - Always take the longest possible token
3. **Lexeme** - The actual text of the token (e.g., "hello")
4. **Token Type** - The category (e.g., STRING_LITERAL)

### Common Patterns

```lex
[0-9]+              /* Integer */
[a-zA-Z_][a-zA-Z0-9_]*  /* Identifier */
\"[^\"]*\"          /* String literal */
\/\/.*              /* Comment */
```

---

# PHASE 2: SYNTAX ANALYSIS (PARSER)

## Purpose

Build an **Abstract Syntax Tree (AST)** from tokens by checking grammar rules.

## What is an AST?

A tree representation of the program's structure.

### Example: `x = 5 + 3;`

```
        ASSIGN
        /    \
       x      +
             / \
            5   3
```

## Grammar Rules (BNF)

### Context-Free Grammar

```bnf
<program>   ::= <stmt_list>
<stmt_list> ::= <stmt> | <stmt_list> <stmt>
<stmt>      ::= <decl> | <assign> | <print>
<decl>      ::= "int" ID ";"
<assign>    ::= ID "=" <expr> ";"
<expr>      ::= <term> | <expr> "+" <term>
<term>      ::= NUM | ID
```

## Implementation: Bison

### parser.y Structure

```yacc
%{
    /* C code */
%}

%token INT ID NUM

%%
/* Grammar rules with actions */
stmt: INT ID ';' {
    $$ = createDecl($2);
}

expr: expr '+' expr {
    $$ = createBinOp('+', $1, $3);
}
%%
```

### Key Concepts

1. **Terminal Symbols** - Tokens from scanner (INT, ID, NUM)
2. **Non-terminal Symbols** - Grammar rules (stmt, expr)
3. **Production Rules** - How to build non-terminals
4. **Actions** - C code to build AST nodes

### Shift-Reduce Parsing

**Shift**: Push token onto stack
**Reduce**: Replace symbols with non-terminal

Example: Parsing `5 + 3`

```
Stack       Input       Action
----        -----       ------
$           5 + 3 $     Shift 5
$ 5         + 3 $       Reduce (5 → expr)
$ expr      + 3 $       Shift +
$ expr +    3 $         Shift 3
$ expr + 3  $           Reduce (3 → expr)
$ expr + expr $         Reduce (expr + expr → expr)
$ expr      $           Accept
```

### Operator Precedence

```yacc
%left '+' '-'      /* Left associative, low precedence */
%left '*' '/'      /* Left associative, higher precedence */
%right '='         /* Right associative */
```

**Left associative**: `a + b + c` = `(a + b) + c`
**Right associative**: `a = b = c` = `a = (b = c)`

---

# PHASE 3: SEMANTIC ANALYSIS

## Purpose

Check **meaning** and **correctness** beyond syntax.

## Semantic Checks

### 1. Type Checking

**Goal**: Ensure operations are valid for types

```c
int x = 5;        // ✅ OK
int y = "hello";  // ❌ Type mismatch
int z = x + y;    // ✅ Both int (if y were int)
string s = x + "hi"; // ❌ Can't add int + string
```

### 2. Declaration Checking

**Goal**: Variables must be declared before use

```c
int x = 5;
print(x);    // ✅ OK: x is declared
print(y);    // ❌ Error: y not declared
```

### 3. Scope Checking

**Goal**: Variables only visible in their scope

```c
int x = 5;        // Global x

# foo() {
    int x = 10;   // Local x (different from global)
    print(x);     // Prints 10 (local)
}

print(x);         // Prints 5 (global)
```

## Type System

### Our Type Definitions

```c
typedef enum {
    TYPE_INT,         // Integer
    TYPE_STRING,      // String
    TYPE_ARRAY_INT,   // Array of integers
    TYPE_VOID         // No value (for functions)
} Type;
```

### Type Inference

```c
int exprType(ASTNode* node) {
    switch(node->type) {
        case NODE_NUM:
            return TYPE_INT;        // Literal is int
        case NODE_STR:
            return TYPE_STRING;     // Literal is string
        case NODE_VAR:
            return lookupType(node->data.name);  // Look up in symbol table
        case NODE_BINOP:
            int left = exprType(node->left);
            int right = exprType(node->right);
            if (left == right) return left;
            else error("Type mismatch");
    }
}
```

---

# PHASE 4: INTERMEDIATE REPRESENTATION (TAC)

## Purpose

Convert AST to **Three-Address Code** - simpler representation.

## What is TAC?

Each instruction has **at most 3 operands**:

```
result = operand1 operator operand2
```

### Example Conversion

**Source code:**
```c
int x = 5 + 3 * 2;
```

**AST:**
```
  ASSIGN
  /    \
 x      +
       / \
      5   *
         / \
        3   2
```

**TAC:**
```
t0 = 3 * 2      // Temporary t0 holds 6
t1 = 5 + t0     // Temporary t1 holds 11
x = t1          // Assign 11 to x
```

## TAC Instructions

| Instruction | Format | Example |
|-------------|--------|---------|
| **Assignment** | `x = y` | `a = 5` |
| **Binary Op** | `x = y op z` | `t0 = a + b` |
| **Array Access** | `x = arr[i]` | `t0 = arr[2]` |
| **Array Assign** | `arr[i] = x` | `arr[2] = 5` |
| **Function Call** | `x = call f, n` | `t0 = call add, 2` |
| **Parameter** | `param x` | `param a` |
| **Return** | `return x` | `return t0` |
| **Label** | `label:` | `func:` |

## TAC for Functions

### Function Declaration

**Source:**
```c
# add(int x, int y) {
    int sum = x + y;
    return sum;
}
```

**TAC:**
```
FUNC_BEGIN add
LABEL add:
PARAM x
PARAM y
DECL sum
sum = x + y
RETURN sum
FUNC_END add
```

### Function Call

**Source:**
```c
int result = add(5, 3);
```

**TAC:**
```
PARAM 5
PARAM 3
t0 = CALL add, 2
result = t0
```

## TAC Optimizations

### 1. Constant Folding

**Before:**
```
t0 = 5 + 3
t1 = t0 * 2
```

**After:**
```
t1 = 16
```

### 2. Copy Propagation

**Before:**
```
a = 5
b = a
c = b + 1
```

**After:**
```
a = 5
b = 5
c = 6
```

### 3. Dead Code Elimination

**Before:**
```
return 5;
x = 10;        // Never executed!
print(x);      // Never executed!
```

**After:**
```
return 5;
```

### 4. Tail Call Optimization

**Before:**
```
t0 = CALL foo, 2
RETURN t0
```

**After:**
```
GOTO foo       // Jump instead of call
```

---

# PHASE 5: CODE GENERATION (MIPS)

## Purpose

Convert TAC to **MIPS assembly** code.

## MIPS Registers

| Register | Name | Purpose | Preserved? |
|----------|------|---------|------------|
| `$zero` | Always 0 | Constant zero | N/A |
| `$v0-$v1` | Value | Return values | No |
| `$a0-$a3` | Argument | Function arguments | No |
| `$t0-$t7` | Temporary | Scratch registers | **No** |
| `$s0-$s7` | Saved | Preserved across calls | **Yes** |
| `$sp` | Stack pointer | Top of stack | Yes |
| `$fp` | Frame pointer | Stack frame base | Yes |
| `$ra` | Return address | Where to return | Yes |

## MIPS Instructions

### Arithmetic

```assembly
add $t0, $t1, $t2    # $t0 = $t1 + $t2
sub $t0, $t1, $t2    # $t0 = $t1 - $t2
mul $t0, $t1, $t2    # $t0 = $t1 * $t2
div $t1, $t2         # lo = $t1 / $t2, hi = $t1 % $t2
```

### Load/Store

```assembly
lw $t0, 4($sp)       # Load word: $t0 = mem[$sp + 4]
sw $t0, 4($sp)       # Store word: mem[$sp + 4] = $t0
li $t0, 42           # Load immediate: $t0 = 42
la $t0, label        # Load address: $t0 = address of label
```

### Control Flow

```assembly
beq $t0, $t1, label  # Branch if equal
bne $t0, $t1, label  # Branch if not equal
j label              # Jump unconditionally
jal label            # Jump and link (save return address)
jr $ra               # Jump to register (return)
```

## Code Generation Examples

### Variable Declaration

**TAC:** `DECL x`

**MIPS:**
```assembly
# Declared x at offset 0
```
(Space already allocated, just a comment)

### Assignment

**TAC:** `x = 5`

**MIPS:**
```assembly
li $t0, 5          # Load 5 into temp
sw $t0, 0($sp)     # Store at x's offset
```

### Binary Operation

**TAC:** `t0 = a + b`

**MIPS:**
```assembly
lw $t0, 0($sp)     # Load a
lw $t1, 4($sp)     # Load b
add $t2, $t0, $t1  # Add them
```

### Array Access

**TAC:** `t0 = arr[2]`

**MIPS:**
```assembly
li $t0, 2          # Index
sll $t0, $t0, 2    # Multiply by 4 (word size)
addi $t1, $sp, 0   # Base address
add $t1, $t1, $t0  # Calculate element address
lw $t2, 0($t1)     # Load value
```

---

# SYMBOL TABLE & SCOPE MANAGEMENT

## Purpose

Track **all declared variables** and their properties.

## Symbol Table Structure

### Symbol Entry

```c
typedef struct {
    char* name;          // Variable name
    int offset;          // Stack offset
    int type;            // 0=int, 1=string
    int isArray;         // 1 if array
    int arraySize;       // Size if array
    int isFunction;      // 1 if function
    int paramCount;      // Number of parameters
} Symbol;
```

### Scope Stack

```c
typedef struct Scope {
    Symbol vars[MAX_VARS];
    int count;
    int nextOffset;
    struct Scope* parent;   // Link to outer scope
} Scope;
```

## Scope Management

### Visual Example

```c
int x = 5;        // Global scope

# foo(int y) {    // Enter function scope
    int z = 10;   // Local variable
}                 // Exit function scope
```

**Scope Stack:**

```
┌─────────────────┐
│ Function foo    │  ← Current scope
│ vars: y, z      │
│ parent ────────┼─┐
└─────────────────┘ │
                    ↓
┌─────────────────┐
│ Global scope    │
│ vars: x, foo    │
│ parent: NULL    │
└─────────────────┘
```

### Key Operations

**enterScope()** - Create new scope when entering function
```c
void enterScope() {
    Scope* newScope = malloc(sizeof(Scope));
    newScope->parent = currentScope;
    currentScope = newScope;
}
```

**exitScope()** - Pop scope when leaving function
```c
void exitScope() {
    Scope* oldScope = currentScope;
    currentScope = currentScope->parent;
    free(oldScope);
}
```

**lookupSymbol()** - Search current and parent scopes
```c
Symbol* lookupSymbol(char* name) {
    Scope* scope = currentScope;
    while (scope != NULL) {
        for (int i = 0; i < scope->count; i++) {
            if (strcmp(scope->vars[i].name, name) == 0)
                return &scope->vars[i];
        }
        scope = scope->parent;  // Try parent
    }
    return NULL;  // Not found
}
```

## Variable Shadowing

```c
int x = 5;        // Global x

# foo() {
    int x = 10;   // Local x (SHADOWS global)
    print(x);     // Prints 10
}

print(x);         // Prints 5
```

**Why this works**: `lookupSymbol()` searches current scope first!

---

# MIPS ASSEMBLY BASICS

## Memory Layout

```
High Addresses
┌──────────────┐
│    Stack     │  ← Grows DOWN (toward lower addresses)
│      ↓       │
├──────────────┤
│              │
├──────────────┤
│    Heap      │  ← Grows UP (toward higher addresses)
│      ↑       │
├──────────────┤
│    Data      │  ← Global variables, string literals
├──────────────┤
│    Text      │  ← Program code (instructions)
└──────────────┘
Low Addresses
```

## Stack Frame

### What is a Stack Frame?

Each function gets its own workspace on the stack.

### Stack Frame Layout

```
Higher Addresses
┌─────────────────┐
│ Caller's frame  │
├─────────────────┤ ← $fp (frame pointer)
│ Return address  │  +4 from $fp
│ Old $fp         │  +0 from $fp
│ Local var 1     │  -4 from $fp
│ Local var 2     │  -8 from $fp
│ ...             │
└─────────────────┘ ← $sp (stack pointer)
Lower Addresses
```

## Syscalls (OS Services)

| Service | Code ($v0) | Arguments | Result |
|---------|------------|-----------|--------|
| Print int | 1 | $a0 = integer | None |
| Print string | 4 | $a0 = address | None |
| Read int | 5 | None | $v0 = integer |
| Exit | 10 | None | Program ends |
| Print char | 11 | $a0 = char | None |
| Allocate heap | 9 | $a0 = bytes | $v0 = address |

### Example: Print "Hello"

```assembly
.data
msg: .asciiz "Hello"

.text
la $a0, msg       # Load address of string
li $v0, 4         # Syscall 4 = print string
syscall           # Execute
```

---

# FUNCTION CALLING CONVENTION

## Overview

How functions pass arguments and return values.

## MIPS Calling Convention

### Registers

- **$a0-$a3**: First 4 arguments
- **$v0-$v1**: Return values
- **$ra**: Return address
- **$sp**: Stack pointer
- **$fp**: Frame pointer

## Complete Function Call Sequence

### Example: Calling `add(5, 3)`

**1. CALLER: Prepare arguments**
```assembly
li $a0, 5         # First argument
li $a1, 3         # Second argument
```

**2. CALLER: Call function**
```assembly
jal add           # Jump to add, save return address in $ra
```

**3. CALLEE: Function Prologue (setup)**
```assembly
add:
    # Save registers
    addi $sp, $sp, -32    # Allocate stack frame
    sw $ra, 28($sp)       # Save return address
    sw $fp, 24($sp)       # Save old frame pointer
    move $fp, $sp         # Set new frame pointer

    # Save parameters (optional)
    sw $a0, 0($sp)        # Store param x
    sw $a1, 4($sp)        # Store param y
```

**4. CALLEE: Function Body**
```assembly
    # Do the work
    lw $t0, 0($sp)        # Load x
    lw $t1, 4($sp)        # Load y
    add $t2, $t0, $t1     # Compute x + y
    move $v0, $t2         # Put result in $v0
```

**5. CALLEE: Function Epilogue (cleanup)**
```assembly
    # Restore registers
    lw $fp, 24($sp)       # Restore frame pointer
    lw $ra, 28($sp)       # Restore return address
    addi $sp, $sp, 32     # Deallocate stack frame
    jr $ra                # Return to caller
```

**6. CALLER: Get Result**
```assembly
    move $t0, $v0         # Get return value from $v0
```

## Caller-Saved vs Callee-Saved

### Caller-Saved ($t0-$t7, $a0-$a3, $v0-$v1)

**Caller must save** if needed across function call

```assembly
# Before call
sw $t0, 0($sp)    # Save $t0
jal func
lw $t0, 0($sp)    # Restore $t0
```

### Callee-Saved ($s0-$s7, $fp, $ra)

**Callee must save** if it uses them

```assembly
func:
    sw $s0, 0($sp)    # Save $s0
    # ... use $s0 ...
    lw $s0, 0($sp)    # Restore $s0
    jr $ra
```

---

# COMMON QUIZ QUESTIONS

## 1. Name the phases of a compiler

**Answer:**
1. Lexical Analysis (Scanner)
2. Syntax Analysis (Parser)
3. Semantic Analysis
4. Intermediate Code Generation (TAC)
5. Optimization
6. Code Generation

## 2. What's the difference between syntax and semantics?

**Syntax**: Structure/grammar
- "Is this a valid sentence in the language?"
- Example: `int x =;` is **syntactically invalid**

**Semantics**: Meaning
- "Does this make logical sense?"
- Example: `int x = "hello";` is syntactically valid but **semantically invalid**

## 3. What is an AST?

**Answer:** Abstract Syntax Tree - a tree representation of the program's structure where:
- **Nodes** = operations/statements
- **Leaves** = values/variables
- **Edges** = relationships

## 4. What is three-address code?

**Answer:** Intermediate representation where each instruction has at most 3 operands:
`result = operand1 operator operand2`

Example: `t0 = a + b`

## 5. What is the purpose of a symbol table?

**Answer:** Track all declared identifiers (variables, functions) and their:
- Type
- Scope
- Memory location (offset)
- Other properties (array size, parameter count)

## 6. Explain variable shadowing

**Answer:** When a local variable has the same name as a variable in an outer scope, the local variable "shadows" (hides) the outer one within its scope.

## 7. What is MIPS $ra register for?

**Answer:** Return Address register - stores the address to return to after a function call. Set by `jal` instruction, used by `jr $ra`.

## 8. What's the difference between $t and $s registers?

**Answer:**
- **$t0-$t7**: Temporary (caller-saved) - caller must save
- **$s0-$s7**: Saved (callee-saved) - callee must save

## 9. How is an array element accessed in MIPS?

**Answer:**
```assembly
# arr[i] access
lw $t0, offset_i($sp)     # Load index
sll $t0, $t0, 2           # Multiply by 4 (word size)
addi $t1, $sp, offset_arr # Get array base
add $t1, $t1, $t0         # Add offset
lw $t2, 0($t1)            # Load element
```

## 10. What happens during function prologue?

**Answer:** Function setup:
1. Allocate stack frame
2. Save return address ($ra)
3. Save frame pointer ($fp)
4. Set new frame pointer
5. Save parameters to stack

## 11. What is constant folding?

**Answer:** Optimization that evaluates constant expressions at compile time.

Example: `x = 5 + 3` → `x = 8`

## 12. What is dead code elimination?

**Answer:** Removing code that will never execute.

Example: Code after `return` statement

## 13. What is tail call optimization?

**Answer:** When a function's last action is calling another function and returning its result, replace CALL+RETURN with a jump to save stack space.

## 14. Explain the difference between $sp and $fp

**Answer:**
- **$sp (stack pointer)**: Points to the current top of the stack (changes as stack grows/shrinks)
- **$fp (frame pointer)**: Points to the base of the current stack frame (stays constant within function)

## 15. What is a scope?

**Answer:** The region of code where a variable is visible and accessible. Variables are only accessible within their scope and any nested scopes.

---

# QUICK REFERENCE TABLES

## Token Types

| Type | Example | Regex Pattern |
|------|---------|---------------|
| Integer | `42` | `[0-9]+` |
| Identifier | `myVar` | `[a-zA-Z_][a-zA-Z0-9_]*` |
| String | `"hello"` | `\"[^\"]*\"` |
| Operator | `+`, `-` | Literal characters |

## AST Node Types

| Node Type | Represents | Children |
|-----------|------------|----------|
| `NODE_NUM` | Number literal | None (leaf) |
| `NODE_VAR` | Variable reference | None (leaf) |
| `NODE_BINOP` | Binary operation | left, right |
| `NODE_ASSIGN` | Assignment | variable, value |
| `NODE_FUNC_CALL` | Function call | arguments |
| `NODE_RETURN` | Return statement | value |

## TAC Operations

| Operation | Syntax | Meaning |
|-----------|--------|---------|
| Assignment | `x = y` | Copy value |
| Binary op | `x = y + z` | Arithmetic |
| Call | `x = call f, n` | Function call |
| Param | `param x` | Pass argument |
| Return | `return x` | Return value |

## MIPS Instruction Format

```
operation  destination, source1, source2
    ↓           ↓          ↓        ↓
   add        $t0,      $t1,     $t2
```

---

# STUDY TIPS

## For Quiz Preparation

1. **Draw diagrams** - ASTs, scope stacks, stack frames
2. **Trace examples** - Follow code through each phase
3. **Practice conversions** - Source → Tokens → AST → TAC → MIPS
4. **Memorize register purposes** - $a, $v, $t, $s, $sp, $fp, $ra
5. **Understand calling convention** - Prologue, body, epilogue sequence

## Common Pitfalls

- Forgetting to save $ra before calling another function
- Confusing caller-saved vs callee-saved registers
- Not accounting for word size (4 bytes) in array indexing
- Mixing up $sp and $fp
- Forgetting to deallocate stack frame before returning

## Practice Questions to Try

1. Convert `x = (a + b) * (c - d);` to TAC
2. Draw AST for `if (x > 5) { y = x * 2; }`
3. Write MIPS code for function that adds two numbers
4. Trace scope stack through nested function calls
5. Identify which registers need to be saved in a function

---

**Good luck on your quiz! 🎓**

*This guide covers everything in your compiler implementation.*
