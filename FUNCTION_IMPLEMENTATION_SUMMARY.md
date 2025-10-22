# Complete Function Implementation Guide

## Purpose and Overview

This document provides a comprehensive explanation of how function support was added to the Mini compiler. Functions are a fundamental building block of structured programming, allowing code reuse, modularity, and abstraction. This implementation extends the Mini language to support:

1. **Function declarations** with parameters
2. **Function calls** with arguments
3. **Return statements** for returning values from functions
4. **Parameter passing** through the call stack

This implementation focuses on the **front-end compilation phases**: lexical analysis (scanning), syntax analysis (parsing), and Abstract Syntax Tree (AST) construction. The semantic analysis and code generation phases will need future enhancements to fully execute functions.

---

## Compiler Architecture Context

A compiler processes source code through multiple phases:

1. **Lexical Analysis (Scanner)** - Breaks source code into tokens
2. **Syntax Analysis (Parser)** - Verifies grammar rules and builds AST
3. **Semantic Analysis** - Type checking and symbol table management
4. **Intermediate Code Generation** - Generates Three-Address Code (TAC)
5. **Optimization** - Improves intermediate code
6. **Code Generation** - Produces target machine code (MIPS assembly)

This function implementation primarily affects **phases 1 and 2**, with foundational work needed for phases 3-6.

---

## File Modifications: Detailed Breakdown

### 1. `ast.h` - Abstract Syntax Tree Header

**Purpose**: Defines the data structures representing the program's hierarchical syntax.

#### What Was Changed:

**Added Four New Node Types to the `NodeType` enum:**

```c
NODE_FUNC_DECL,   /* Function declaration */
NODE_PARAM,       /* Function parameter */
NODE_FUNC_CALL,   /* Function call */
NODE_RETURN       /* Return statement */
```

**Why These Types Are Needed:**

- **`NODE_FUNC_DECL`**: Represents a complete function definition including its name, parameters, and body (the statements inside the function). This is the root node for any function in the program.
  
- **`NODE_PARAM`**: Represents a single function parameter. Since functions can have multiple parameters, these form a linked list. Each parameter node stores the parameter's name and points to the next parameter (if any).
  
- **`NODE_FUNC_CALL`**: Represents a function invocation (e.g., `add(5, 3)`). Contains the function name and a list of argument expressions. This node type appears in the AST wherever a function is called.
  
- **`NODE_RETURN`**: Represents a return statement, which exits the function and optionally returns a value. The node stores the expression being returned (or NULL for void returns).

#### Added Data Structures to the Union:

The `ASTNode` struct uses a union to store different types of data depending on the node type. We added:

```c
/* Function declaration structure (NODE_FUNC_DECL) */
struct {
    char* name;                     /* Function name */
    struct ASTNode* params;         /* Parameter list */
    struct ASTNode* body;           /* Function body (stmt_list) */
} funcDecl;
```

**Why This Structure**: A function has three essential components:
- **name**: The identifier (e.g., "add", "main")
- **params**: Pointer to the first parameter node in a linked list
- **body**: Pointer to the statement list comprising the function's code

```c
/* Parameter structure (NODE_PARAM) */
struct {
    char* name;                     /* Parameter name */
    struct ASTNode* next;           /* Next parameter */
} param;
```

**Why This Structure**: Parameters form a linked list. Each node stores:
- **name**: The parameter identifier (e.g., "x", "y")
- **next**: Pointer to the next parameter (NULL if this is the last)

```c
/* Function call structure (NODE_FUNC_CALL) */
struct {
    char* name;                     /* Function name */
    struct ASTNode* args;           /* Argument list */
} funcCall;
```

**Why This Structure**: When calling a function, we need:
- **name**: Which function to call
- **args**: The expressions being passed as arguments (stored as a statement list)

```c
/* Return statement structure (NODE_RETURN) */
struct {
    struct ASTNode* value;          /* Return value expression */
} returnStmt;
```

**Why This Structure**: Return statements need to store:
- **value**: The expression to return (e.g., `sum`, `x + y`, or NULL for `return;`)

#### Added Function Declarations:

```c
ASTNode* createFuncDecl(char* name, ASTNode* params, ASTNode* body);
ASTNode* createParam(char* name);
ASTNode* addParam(ASTNode* list, char* name);
ASTNode* createFuncCall(char* name, ASTNode* args);
ASTNode* createReturn(ASTNode* value);
```

**Purpose**: These are the factory functions called by the parser to construct AST nodes. The parser doesn't directly allocate memory or set structure fields; instead, it calls these functions which handle all the details.

---

### 2. `ast.c` - AST Implementation

**Purpose**: Implements the AST node creation functions and the tree printing logic.

#### Implemented Functions:

**`createFuncDecl(char* name, ASTNode* params, ASTNode* body)`**

```c
ASTNode* createFuncDecl(char* name, ASTNode* params, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNC_DECL;
    node->data.funcDecl.name = strdup(name);
    node->data.funcDecl.params = params;
    node->data.funcDecl.body = body;
    return node;
}
```

**What It Does**: Allocates memory for a function declaration node, sets its type, copies the function name (using `strdup` to create a heap-allocated copy), and stores pointers to the parameter list and function body.

**Why `strdup`**: The parser passes string data from the lexer which may be in a temporary buffer. `strdup` creates a permanent copy on the heap that persists for the lifetime of the AST.

---

**`createParam(char* name)`**

```c
ASTNode* createParam(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PARAM;
    node->data.param.name = strdup(name);
    node->data.param.next = NULL;
    return node;
}
```

**What It Does**: Creates a single parameter node. Initially, `next` is NULL because this parameter doesn't know about subsequent parameters yet.

---

**`addParam(ASTNode* list, char* name)`**

```c
ASTNode* addParam(ASTNode* list, char* name) {
    ASTNode* newParam = createParam(name);
    if (!list) return newParam;
    
    ASTNode* current = list;
    while (current->data.param.next != NULL) {
        current = current->data.param.next;
    }
    current->data.param.next = newParam;
    return list;
}
```

**What It Does**: This is crucial for building parameter lists. When the parser encounters multiple parameters (e.g., `int x, int y, int z`), it:
1. Creates the first parameter with `createParam`
2. For each additional parameter, calls `addParam` which:
   - Creates the new parameter node
   - Traverses to the end of the existing list
   - Appends the new parameter
   - Returns the head of the list (unchanged)

**Why This Approach**: The parser builds the list incrementally as it encounters each parameter. This function maintains the proper linked list structure.

---

**`createFuncCall(char* name, ASTNode* args)`**

```c
ASTNode* createFuncCall(char* name, ASTNode* args) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNC_CALL;
    node->data.funcCall.name = strdup(name);
    node->data.funcCall.args = args;
    return node;
}
```

**What It Does**: Creates a function call node. The `args` parameter points to a list of expression nodes (reusing the `STMT_LIST` structure for convenience).

---

**`createReturn(ASTNode* value)`**

```c
ASTNode* createReturn(ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_RETURN;
    node->data.returnStmt.value = value;
    return node;
}
```

**What It Does**: Creates a return statement node. The `value` parameter can be an expression (for `return sum;`) or NULL (for `return;`).

---

#### Updated `printAST()` Function:

Added cases to the switch statement to handle printing the new node types:

```c
case NODE_FUNC_DECL:
    printf("FUNC_DECL: %s\n", node->data.funcDecl.name);
    if (node->data.funcDecl.params) {
        printf("%*sParameters:\n", (level+1)*2, "");
        printAST(node->data.funcDecl.params, level+2);
    }
    printf("%*sBody:\n", (level+1)*2, "");
    printAST(node->data.funcDecl.body, level+2);
    break;
```

**Purpose**: Provides human-readable visualization of function nodes in the AST. The indentation (`level*2`) shows the tree hierarchy.

**Also Fixed**: Added missing `NODE_STR_DECL` case that was causing a compiler warning.

---

### 3. `scanner.l` - Lexical Analyzer (Critical Changes)

**Purpose**: The scanner converts raw source code into tokens. Token recognition order is **critically important** in Flex.

#### Change 1: Moved Keyword Definitions BEFORE ID Pattern

**Original (BROKEN) Order:**
```c
"int"           { return INT; }
"print"         { return PRINT; }
"string"        { return STRING; }

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.str = strdup(yytext);
    return ID; 
}

// ... later in file ...
"return"        { return RETURN; }
"void"          { return VOID; }
```

**New (CORRECT) Order:**
```c
"int"           { return INT; }
"print"         { return PRINT; }
"string"        { return STRING; }
"return"        { return RETURN; }  // MOVED UP!
"void"          { return VOID; }    // MOVED UP!

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.str = strdup(yytext);
    return ID; 
}
```

**WHY THIS IS CRITICAL - The Longest Match Rule:**

Flex (the scanner generator) uses the **"longest match" principle**: When multiple patterns could match the input, Flex chooses the one that matches the **longest** sequence of characters. However, when multiple patterns match the **same** length string, Flex uses the **first rule that appears in the file**.

**The Problem:**
- When the scanner sees "return" in the source code:
  - The pattern `"return"` matches exactly 6 characters
  - The pattern `[a-zA-Z_][a-zA-Z0-9_]*` ALSO matches "return" (6 characters)
  
**With the BROKEN order:**
1. Scanner encounters "return" in source
2. Both `[a-zA-Z_][a-zA-Z0-9_]*` and `"return"` match
3. Since they're the same length, Flex picks the **first one in the file**
4. The ID pattern appears first, so "return" is tokenized as `ID` with value "return"
5. Parser expects `RETURN` token but gets `ID` → **SYNTAX ERROR**

**With the CORRECT order:**
1. Scanner encounters "return"
2. Both `"return"` and `[a-zA-Z_][a-zA-Z0-9_]*` match
3. Since `"return"` appears first in the file, it wins
4. Scanner returns `RETURN` token
5. Parser receives the correct token → **SUCCESS**

**This is why the test programs failed initially** - the scanner was treating "return" as an identifier instead of a keyword!

#### Change 2: Added Comma Token

```c
","             { return ','; }
```

**Why Needed**: Function parameters and arguments are comma-separated. The parser needs to recognize commas as distinct tokens to properly parse parameter lists like `int x, int y, int z`.

#### Change 3: Changed Hash Symbol to Return FUNCTION Token

```c
"#"             { return FUNCTION; }
```

**Why This Change**: In the original code, `"#"` returned the character literal `'#'`. However, in `parser.y`, we declared the token as `FUNCTION` (not a character literal). The scanner must return the same token type that the parser expects. We use `#` as the visual syntax for function declarations (e.g., `# main() {...}`), but internally it's represented by the `FUNCTION` token.

---

### 4. `parser.y` - Syntax Analyzer (Grammar Rules)

**Purpose**: Defines the grammar of the language and builds the AST during parsing.

#### Change 1: Added Token Declaration

```c
%token INT PRINT VAR STRING FUNCTION RETURN VOID
%token <str> STRING_LITERAL
```

**What Changed**: Formatted the token declarations on separate lines for readability. The tokens `FUNCTION`, `RETURN`, and `VOID` were already declared but now are cleanly formatted.

#### Change 2: Added `arg_list` to Non-Terminal Types

```c
%type <node> program stmt_list stmt decl assign expr print_stmt func_decl param_list arg_list
```

**Why**: The `%type` directive tells Bison what semantic value type each grammar rule produces. Since `arg_list` is a grammar rule that produces AST nodes, we must declare it here with type `<node>`.

---

#### Change 3: Extended `stmt` Rule

**Original:**
```c
stmt:
    decl
    | assign
    | print_stmt
    | func_decl
    ;
```

**New:**
```c
stmt:
    decl
    | assign
    | print_stmt
    | func_decl
    | expr ';'                      /* Expression statement */
    | RETURN expr ';' { $$ = createReturn($2); }
    | RETURN ';'      { $$ = createReturn(NULL); }
    ;
```

**Why These Changes:**

1. **`expr ';'`** - Expression Statement
   - Allows standalone expressions as statements
   - Critical for function calls: `foo(5);` is valid syntax
   - The expression is evaluated, and its result is discarded
   - The parser stores the expression AST node as the statement

2. **`RETURN expr ';'`** - Return with Value
   - Syntax: `return sum;` or `return x + y;`
   - Matches the `RETURN` token, then an expression, then semicolon
   - Action: `$$ = createReturn($2);`
     - `$2` refers to the second symbol (`expr`), which is an AST node
     - Passes the expression to `createReturn()`
     - Assigns the result to `$$` (the semantic value of this `stmt`)

3. **`RETURN ';'`** - Void Return
   - Syntax: `return;`
   - No expression to return
   - Action: `$$ = createReturn(NULL);`
     - Passes NULL indicating no return value

---

#### Change 4: Extended `expr` Rule for Function Calls

**Added to the `expr` rule:**

```c
| ID '(' ')' { 
    /* Function call with no arguments */
    $$ = createFuncCall($1, NULL);
    free($1);
}
| ID '(' arg_list ')' { 
    /* Function call with arguments */
    $$ = createFuncCall($1, $3);
    free($1);
}
```

**Why These Changes:**

Functions are **expressions** in C-like languages, not statements. A function can return a value that's used in larger expressions:
- `x = add(5, 3);` - The function call is part of an assignment expression
- `print(multiply(2, 3));` - Function call is an argument to another function

**How It Works:**

1. **`ID '(' ')'`** - No Arguments
   - Matches: `factorial()`, `getInput()`
   - `$1` is the function name (string from lexer)
   - Creates a function call node with NULL arguments
   - `free($1)` because we used `strdup` in `createFuncCall`

2. **`ID '(' arg_list ')'`** - With Arguments
   - Matches: `add(x, y)`, `max(10, 20, 30)`
   - `$1` is the function name
   - `$3` is the argument list (AST node)
   - Creates a function call node with the argument list

---

#### Change 5: Added `arg_list` Grammar Rule

```c
/* ARGUMENT LIST - "expr" or "expr, expr, ..." */
arg_list:
    expr { 
        $$ = $1; 
    }
    | arg_list ',' expr { 
        $$ = createStmtList($1, $3);  /* Reuse stmt_list structure */
    }
    ;
```

**Purpose**: Parses comma-separated argument lists in function calls.

**How It Works:**

- **Base case**: `expr`
  - Single argument: `foo(42)` → just the expression node
  
- **Recursive case**: `arg_list ',' expr`
  - Multiple arguments: `add(x, y, z)`
  - Builds a linked structure using `createStmtList` (reuses the statement list structure)
  - First arg is `$1` (the existing arg_list)
  - New arg is `$3` (the latest expression)
  - The result is a linked list of expression nodes

**Why Reuse `createStmtList`**: Both statement lists and argument lists are sequences of AST nodes. Rather than creating a separate argument list structure, we reuse the existing `STMT_LIST` node type. This is a common compiler design pattern - reusing data structures where the semantics are similar.

---

## How It All Works Together: Parse Flow Example

Let's trace how this code is parsed:

```c
# add(int x, int y) {
    int sum;
    sum = x + y;
    return sum;
}
```

### Step 1: Lexical Analysis (Scanner)

Scanner breaks the input into tokens:
```
FUNCTION, ID("add"), '(', INT, ID("x"), ',', INT, ID("y"), ')', '{',
INT, ID("sum"), ';',
ID("sum"), '=', ID("x"), '+', ID("y"), ';',
RETURN, ID("sum"), ';',
'}'
```

### Step 2: Syntax Analysis (Parser)

Parser applies grammar rules:

1. **Matches `func_decl` rule:**
   ```
   FUNCTION ID '(' param_list ')' '{' stmt_list '}'
   ```

2. **Builds `param_list`:**
   - Matches `INT ID` → creates param("x")
   - Matches `',' INT ID` → calls addParam to append param("y")
   - Result: param("x") → param("y") → NULL

3. **Builds `stmt_list` (function body):**
   - Matches `decl`: `INT ID ';'` → creates declaration for "sum"
   - Matches `assign`: `ID '=' expr ';'` → creates assignment
   - Matches `RETURN expr ';'` → creates return node
   - Links them together with `createStmtList`

4. **Calls `createFuncDecl`:**
   - name: "add"
   - params: pointer to param list
   - body: pointer to statement list
   - Returns complete function declaration node

### Step 3: AST Result

```
FUNC_DECL: add
  Parameters:
    PARAM: x
    PARAM: y
  Body:
    DECL: sum
    ASSIGN: sum
      BINOP: +
        VAR: x
        VAR: y
    RETURN
      VAR: sum
```

---

## Current Limitations and Future Work

### What Works Now:
✅ Functions are fully parsed
✅ AST correctly represents function structure
✅ Parameters and arguments are properly linked
✅ Return statements are recognized

### What Still Needs Implementation:

1. **Semantic Analysis Phase:**
   - **Function Symbol Table**: Must track declared functions, their signatures (parameter types), and return types
   - **Call Validation**: Verify that function calls match declared functions (name exists)
   - **Argument Count Checking**: Ensure the number of arguments matches the number of parameters
   - **Type Checking**: Verify argument types match parameter types
   - **Return Type Checking**: Ensure return statements match function's declared return type
   - **Scope Management**: Implement local variable scoping within functions

2. **Intermediate Code Generation (TAC):**
   - Generate TAC for function prologue (entry code)
   - Generate TAC for parameter passing
   - Generate TAC for function calls
   - Generate TAC for return statements
   - Generate TAC for function epilogue (exit code)

3. **Code Generation (MIPS Assembly):**
   - **Calling Convention**: Implement MIPS calling convention
     - Use `$a0-$a3` for first 4 arguments, stack for additional
     - Use `$v0-$v1` for return values
     - Save/restore `$ra` (return address)
     - Save/restore `$fp` (frame pointer)
   - **Stack Frame Management**:
     - Allocate space for local variables
     - Save caller-saved registers
     - Manage stack pointer (`$sp`)
   - **Function Call Sequence**:
     - Push arguments onto stack
     - `jal` (jump and link) instruction
     - Handle return values
   - **Function Return Sequence**:
     - Place return value in `$v0`
     - Restore stack frame
     - `jr $ra` (jump to return address)

---

## Testing and Verification

The implementation was verified with multiple test cases:

### Test Case 1: Simple Function
```c
# test() {
    int x;
    x = 5;
    print(x);
}
```
✅ Successfully parsed

### Test Case 2: Function with Parameters
```c
# add(int a, int b) {
    int sum;
    sum = a + b;
    return sum;
}
```
✅ Successfully parsed with parameter list

### Test Case 3: Function Calls
```c
# main() {
    int result;
    result = add(5, 3);
    print(result);
}
```
✅ Successfully parsed with function call in expression

### Test Case 4: Multiple Functions
```c
# multiply(int x, int y) { ... }
# factorial(int n) { ... }
# main() { ... }
```
✅ All functions parsed correctly

---

## Key Design Decisions and Rationale

### 1. Why Use `#` for Function Declarations?
- Provides clear visual distinction from variable declarations
- Single-character token is easy to scan
- Avoids conflicts with C keywords like `function` or `def`

### 2. Why Linked Lists for Parameters?
- Parameters are variable-length (0 to N)
- Linked lists grow dynamically without pre-allocation
- Easy traversal during semantic analysis and code generation
- Standard approach in compiler AST design

### 3. Why Reuse STMT_LIST for Arguments?
- Arguments and statements are both sequences of nodes
- Reduces code duplication
- Simpler memory management
- Common compiler design pattern

### 4. Why Allow Functions as Expressions?
- Matches C semantics
- Enables function composition: `f(g(x))`
- Allows functions in any expression context
- More flexible and powerful

---

## Conclusion

This implementation successfully extends the Mini compiler to support functions at the parsing level. All grammar rules are properly defined, AST nodes correctly represent function constructs, and the scanner/parser work together to recognize function syntax.

The foundation is now in place for implementing the remaining compilation phases (semantic analysis, intermediate code generation, and final code generation) to produce executable function code.

**Files Modified:**
- `ast.h` - Added 4 node types and 5 function declarations
- `ast.c` - Implemented 5 creation functions and updated printing
- `scanner.l` - Fixed keyword ordering (critical), added comma token
- `parser.y` - Extended grammar for function calls, returns, and arguments

**Total Lines Changed:** ~150 lines across 4 files

**Result:** Fully functional parser for function declarations, calls, and returns.
