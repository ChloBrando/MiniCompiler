# Compiler Presentation Script - Function Implementation
**5-Minute Version with File References**

---

## Introduction (30 seconds)

"Hello everyone. Today we're presenting our Mini Compiler's new function implementation. Our compiler now supports functions with parameters, return values, and nested calls, generating working MIPS assembly code."

**[Show test_simple.c:19-23]**
```c
# add(int a, int b) {
    return a + b;
}
print(add(5, 3));  // Prints 8
```

---

## A) Function Implementation - How It Works (2.5 minutes)

### Complete Compilation Pipeline

"Let me walk through how a function moves through our compiler:"

**1. Scanner & Parser**

**[scanner.l:59-61]** - We added the function token:
```c
"#"             { return FUNCTION; }
"return"        { return RETURN; }
"//".*          { /* Skip single-line comments */ }
```

**[parser.y:169-175]** - Function declaration grammar:
```yacc
func_decl:
    FUNCTION ID '(' param_list ')' '{' stmt_list '}' {
        $$ = createFuncDecl($2, $4, $7);
        free($2);
    }
    ;
```

This creates an AST like:
```
FUNC_DECL: add
├── params: [a, b]
└── body: RETURN(a + b)
```

---

**2. Semantic Analysis - Scope Management**

**[symtab.h:24-29]** - Our scope structure:
```c
typedef struct Scope {
    Symbol vars[MAX_VARS];
    int count;
    int nextOffset;
    struct Scope* parent;  // Link to enclosing scope
} Scope;
```

**[semantic.c:146-175]** - Function checking:
```c
case NODE_FUNC_DECL: {
    // Add function to symbol table
    addFunction(node->data.funcDecl.name, "int", NULL, 0);

    // Enter new scope for function body
    enterScope();

    // Add parameters to the new scope
    ASTNode* param = node->data.funcDecl.params;
    while (param) {
        addParameter(param->data.param.name, "int");
        param = param->data.param.next;
    }

    // Check function body
    checkStmt(node->data.funcDecl.body);

    // Exit function scope
    exitScope();
}
```

This enables variable shadowing - parameters can hide global variables.

---

**3. TAC Generation**

**[tac.c:99-145]** - Generate intermediate code:
```
FUNC_BEGIN add
LABEL add:
PARAM a
PARAM b
t0 = a + b
RETURN t0
FUNC_END add
```

**Key Bug We Fixed [tac.c:105-112]:**

For 3+ arguments like `func(1, 2, 3)`, parser creates nested lists:
```c
if (arg->data.stmtlist.stmt &&
    arg->data.stmtlist.stmt->type == NODE_STMT_LIST) {
    // Recursively process the nested stmt_list first
    ASTNode* nested = arg->data.stmtlist.stmt;
    while (nested) {
        // Extract each argument properly
    }
}
```

---

**4. MIPS Code Generation**

**[codegen.c:329-385]** - Generate MIPS following calling convention:

```assembly
add:
    # Prologue - setup [lines 350-354]
    addi $sp, $sp, -32      # Allocate stack frame
    sw $ra, 28($sp)         # Save return address
    sw $fp, 24($sp)         # Save frame pointer
    move $fp, $sp           # Set new frame pointer

    # Store parameters [lines 360-368]
    sw $a0, 0($sp)          # Store param a
    sw $a1, 4($sp)          # Store param b

    # Body - compute a + b
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    add $t2, $t0, $t1
    move $v0, $t2           # Return value in $v0

    # Epilogue - cleanup [lines 377-380]
    lw $fp, 24($sp)
    lw $ra, 28($sp)
    addi $sp, $sp, 32
    jr $ra                  # Return
```

**Critical Fix [codegen.c:449-458]:** Code organization problem

Before: Execution fell through from `main:` into first function!

Solution:
```c
fprintf(output, "main:\n");
fprintf(output, "    addi $sp, $sp, -400\n");
fprintf(output, "    j main_code\n\n");  // Jump over functions!

genFunctionsOnly(root);     // Generate all functions

fprintf(output, "\nmain_code:\n");  // Main program starts here
genStatementsOnly(root);
```

---

## B) Individual Tasks (30 seconds)

**Gabe:** Implemented complete function support including:
- Scanner/parser grammar **[scanner.l:59-61, parser.y:169-175]**
- Scope management **[symtab.c:45-72]**
- TAC generation **[tac.c:140-162]**
- MIPS code generation **[codegen.c:329-410]**
- Fixed nested function call bug **[tac.c:105-129, codegen.c:185-215]**

**Chloe:** Added mathematical operator support:
- Implemented `*` and `/` operators **[scanner.l:57-58, parser.y:139-146]**
- Float support with floating-point registers **[codegen.c:169-208]**
- Constant folding optimization **[tac.c:438-507]**
- MIPS arithmetic instructions **[codegen.c:224-231]**

---

## C) Team Integration Approach (1 minute)

### Development Strategy

**1. Modular Architecture**
```
Scanner → Parser → Semantic → TAC → CodeGen
(scanner.l) (parser.y) (semantic.c) (tac.c) (codegen.c)
```
Each file has clear inputs/outputs, enabling independent development.

**2. Incremental Integration**
```c
// Week 1: Basic functions (no parameters)
# getValue() { return 42; }  // test_simple.c:1-3

// Week 2: Parameters (1, then 2, then 3+)
# double(int x) { return x + x; }  // test_simple.c:5-8
# add(int a, int b) { return a + b; }  // test_simple.c:10-14

// Week 3: Nested calls
# addThree(int x, int y, int z) {  // test_simple.c:16-20
    int temp;
    temp = add(x, y);
    return add(temp, z);
}
```

**3. Testing at Each Stage**
- Created **test_simple.c** (6 test functions)
- Each test verifies different feature
- All tests must pass before merging

**4. Systematic Debugging**
- Check each phase output: `./minicompiler test.c output.s 2>&1 | less`
- TAC visible in compilation output
- MIPS in output.s
- Test in SPIM: `spim -file output.s`

---

## Live Demonstration (45 seconds)

**[DEMO - Show actual files]**

```bash
# Show the test file
$ cat test_simple.c
# getNumber() { return 42; }           # Line 1-3
# double(int n) { return n + n; }      # Line 5-8
# add(int a, int b) { return a + b; }  # Line 10-14
# addThree(int x, int y, int z) {      # Line 16-23
    int temp;
    temp = add(x, y);
    return add(temp, z);
}

print(getNumber());      # Test 1
print(double(21));       # Test 2
print(add(10, 32));      # Test 3
print(addThree(1, 2, 3));  # Test 4

# Compile
$ ./minicompiler test_simple.c output.s
✓ COMPILATION SUCCESSFUL!

# Show generated MIPS (snippet)
$ head -50 output.s
[Shows function definitions with proper stack frames]

# Run in SPIM
$ spim -file output.s
42    # Test 1: getNumber()
42    # Test 2: double(21)
42    # Test 3: add(10, 32)
6     # Test 4: addThree(1,2,3)
```

**All tests pass!** ✅

---

## Results Summary (15 seconds)

### What Works
✅ Functions with 0-4 parameters
✅ Return statements
✅ Nested function calls
✅ Variable shadowing
✅ Local variables
✅ Arithmetic: +, -, *, / **[codegen.c:216-231]**
✅ Floating-point operations **[codegen.c:169-208]**

### Test Suite: **6/6 tests passing** (test_simple.c)
### Code Stats:
- Functions: ~800 lines added across 6 files
- Test file: test_simple.c (43 lines)

---

## Conclusion (15 seconds)

"We successfully built a compiler with full function support by using modular design, incremental integration, and systematic testing. Our compiler generates working MIPS code that runs in SPIM."

**Key Files Modified:**
- scanner.l, parser.y, ast.h/c
- semantic.c, symtab.h/c
- tac.h/c, codegen.h/c

**Questions?**

---

## Quick Reference for Presenter

### Files to have open during presentation:
1. **test_simple.c** - Show this first
2. **scanner.l** - Line 59-61 (tokens)
3. **parser.y** - Line 169-175 (grammar)
4. **semantic.c** - Line 146-175 (scope management)
5. **tac.c** - Line 99-145 (TAC gen), 105-112 (bug fix)
6. **codegen.c** - Line 329-385 (function), 449-458 (code organization)
7. **output.s** - Generated MIPS to show

### Demo Commands:
```bash
cat test_simple.c
./minicompiler test_simple.c output.s
head -50 output.s
spim -file output.s
```

**Total Time: ~5 minutes**
