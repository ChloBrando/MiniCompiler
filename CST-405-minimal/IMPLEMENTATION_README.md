## Mini Compiler — Implementation + Teaching README (Detailed, with code snippets)

Goal: produce a single document that lets you understand, demonstrate, and explain exactly how arrays and strings were implemented in this Mini compiler. This README includes actual code snippets from the project so you can point at the lines while recording a video for your professor.

At a glance: the compilation flow is

- lexer (scanner.l) → parser (parser.y) → AST (ast.h/c) → semantic/type-check (semantic.c) → TAC (tac.c) → optimize (optimize.c) → codegen (codegen.c) → MIPS (.s)

Before we dive into specifics, here's what I will do for you in this document:

1) Show the exact lexer & parser rules that accept arrays and string literals.  
2) Show the AST node shapes used for arrays and strings.  
3) Show the symbol-table code that reserves stack space for arrays and marks string variables.  
4) Show the semantic checks (what we added and why).  
5) Show how TAC carries array and string operations.  
6) Show the code generator sequences that turn AST/TAC into MIPS (real snippets).  
7) Explain runtime details (string pooling in `.data`, concat helper, array offsets).  
8) Provide a short demo script and recording notes.

Run these commands (from `Mini` folder) to compile and run the tests we'll discuss:

```bash
make test
spim test.s
```

Now dive in.

---

## 1) Lexer and parser rules (exact code snippets)

Parser: `parser.y` contains the grammar pieces that parse declarations, array access, and string literals. Key excerpts:

```yacc
/* declaration: int x; | int x[NUM]; | string x; */
decl:
    INT ID ';' { $$ = createDecl($2); free($2); }
  | INT ID '[' NUM ']' ';' { $$ = createArrayDecl($2, $4); free($2); }
  | STRING ID ';' { $$ = createStrDecl($2); free($2); }
  ;

/* string literal in expressions */
expr:
    STRING_LITERAL { $$ = createStringLit($1); free($1); }
    | ID '[' expr ']' { $$ = createArrayAccess($1, $3); free($1); }
    | expr '+' expr { $$ = createBinOp('+', $1, $3); }
    | NUM { $$ = createNum($1); }
    | ID { $$ = createVar($1); free($1); }
;
```

Lexer: `scanner.l` turns "quoted text" into `STRING_LITERAL`. The exact rule we use is:

```flex
"\""[^\"]*"\"" {
    /* match a double-quoted string, copy without quotes */
    int len = yyleng;
    if (len >= 2) {
        char *s = malloc(len-1);
        strncpy(s, yytext+1, len-2);
        s[len-2] = '\0';
        yylval.str = s;
        return STRING_LITERAL;
    }
}
```

Notes:
- The lexer currently does not decode C-style escape sequences — it copies characters between the quotes directly. That is a simple, safe approach for student examples but can be extended (see "improvements").

---

## 2) AST representation (exact snippet)

`ast.h` defines the nodes used to represent arrays and strings. Important parts:

```c
typedef enum {
    NODE_NUM,
    NODE_STR,        /* String literal: node->data.str */
    NODE_STR_DECL,   /* String variable declaration: node->data.name */
    NODE_VAR,
    NODE_BINOP,
    NODE_DECL,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_STMT_LIST,
    NODE_ARRAY_DECL,     /* array declaration: node->data.arrayDecl.name and .size */
    NODE_ARRAY_ASSIGN,   /* name, index (AST), value (AST) */
    NODE_ARRAY_ACCESS    /* name, index (AST) */
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        int num;           /* NODE_NUM */
        char* str;         /* NODE_STR */
        char* name;        /* NODE_VAR, NODE_DECL, NODE_STR_DECL */
        struct { char op; struct ASTNode* left; struct ASTNode* right; } binop;
        struct { char* name; struct ASTNode* index; struct ASTNode* value; } arrayAssign;
        struct { char* name; int size; } arrayDecl;
        /* ... */
    } data;
} ASTNode;
```

This union-based node lets us store different shapes of data compactly and lets the parser build trees that the semantic and codegen stages traverse.

---

## 3) Symbol table: exactly how we reserve space

`symtab.c` implements the symbol table; here are the essential functions we relied on.

Add array variable (reserves contiguous stack slots):

```c
int addArrayVar(char* name, int size) {
    if (isVarDeclared(name)) return -1;
    symtab.vars[symtab.count].name = strdup(name);
    symtab.vars[symtab.count].offset = symtab.nextOffset;
    symtab.vars[symtab.count].isArray = 1;
    symtab.vars[symtab.count].arraySize = size;
    symtab.vars[symtab.count].type = 0; /* array of int */
    symtab.nextOffset += size * 4; /* 4 bytes per int */
    symtab.count++;
    return symtab.vars[symtab.count - 1].offset;
}
```

Add a string variable (store pointer-sized slot):

```c
int addStringVar(char* name) {
    if (isVarDeclared(name)) return -1;
    symtab.vars[symtab.count].name = strdup(name);
    symtab.vars[symtab.count].offset = symtab.nextOffset;
    symtab.vars[symtab.count].isArray = 0;
    symtab.vars[symtab.count].arraySize = 0;
    symtab.vars[symtab.count].type = 1; /* string type */
    symtab.nextOffset += 4; /* pointer size on this target */
    symtab.count++;
    return symtab.vars[symtab.count - 1].offset;
}
```

Lookup helpers used by semantic and codegen:

```c
int getVarOffset(char* name) { /* linear search returning .offset or -1 */ }
int isArrayVar(char* name) { /* returns symtab.vars[i].isArray */ }
int isStringVar(char* name) { /* returns symtab.vars[i].type == 1 */ }
```

Key idea: the symbol table is the single source of truth for variable offsets and types. Semantic stage populates it; codegen reads it.

---

## 4) Semantic checks (what we added and why)

`semantic.c` registers declarations and rejects invalid programs early. We implemented `exprType()` and `checkStmt()` so later stages can rely on consistent types.

Important parts (real code):

```c
/* compute type of expression */
int exprType(ASTNode* node) {
    switch (node->type) {
        case NODE_NUM: return TYPE_INT;
        case NODE_STR: return TYPE_STRING;
        case NODE_VAR:
            if (isStringVar(node->data.name)) return TYPE_STRING;
            if (isArrayVar(node->data.name)) return TYPE_ARRAY_INT;
            return TYPE_INT;
        case NODE_ARRAY_ACCESS:
            if (!isArrayVar(node->data.arrayAccess.name)) {
                fprintf(stderr, "Semantic Error: %s is not an array\n", node->data.arrayAccess.name);
                return -1;
            }
            if (exprType(node->data.arrayAccess.index) != TYPE_INT) { /* error */ }
            return TYPE_INT;
        case NODE_BINOP: {
            int lt = exprType(node->data.binop.left);
            int rt = exprType(node->data.binop.right);
            if (node->data.binop.op == '+') {
                if (lt == TYPE_INT && rt == TYPE_INT) return TYPE_INT;
                if ((lt == TYPE_STRING || lt == TYPE_ARRAY_INT) && (rt == TYPE_STRING || rt == TYPE_ARRAY_INT)) return TYPE_STRING;
                /* else error */
            }
            /* ... */
        }
    }
}
```

`checkStmt()` registers declarations by calling `addVar`, `addStringVar`, `addArrayVar` and validates assignments/prints.

Why this matters:
- By registering declarations here, the symbol table is fully populated before TAC/codegen runs. That enforces a clean separation of responsibilities: codegen never creates new symbol-table entries.

---

## 5) TAC: how arrays and strings appear (real examples)

`tac.c` linearizes AST into simple instructions. For arrays and strings we use these TAC forms:

- `TAC_ARRAY_DECL` — indicates array declaration (name stored in `result`)  
- `TAC_ARRAY_ASSIGN` — `result = array name`, `arg1 = indexExpr`, `arg2 = valueExpr`  
- `TAC_ARRAY_ACCESS` — `result` is the temp where loaded element value will be stored  
- `TAC_DECL` used for string var and normal var declarations; `TAC_PRINT` carries literal or temp to print

Example generation for an array assignment (simplified):

```c
char* indexExpr = generateTACExpr(node->data.arrayAssign.index);
char* valueExpr = generateTACExpr(node->data.arrayAssign.value);
appendTAC(createTAC(TAC_ARRAY_ASSIGN, indexExpr, valueExpr, node->data.arrayAssign.name));
```

For strings, `generateTACExpr()` returns the literal text for `NODE_STR` so the TAC instruction can carry it forward:

```c
case NODE_STR:
    return strdup(node->data.str); /* TAC operand is the literal text */
```

Optimization runs on TAC but focuses on numeric folding. String concats are left for codegen/runtime.

---

## 6) Code generation (MIPS): exact sequences we emit

Important design principles used in `codegen.c`:

- `generateMIPS()` collects string literals first so labels can be emitted in `.data` before any `la` uses. It then writes `.text` and `main` body.
- `codegen` never adds declarations to the symbol table; it only calls `getVarOffset()` to locate stack offsets reserved by `semanticCheck()`.

### String literal pooling & emission (exact code)

We collect string literals and emit them in `.data`.

```c
/* collectStringLiterals walks the AST and saves unique string literals */
void collectStringLiterals(ASTNode* node) {
    if (!node) return;
    switch (node->type) {
        case NODE_STR: addStrLiteralIfMissing(node->data.str); break;
        case NODE_BINOP: collectStringLiterals(node->data.binop.left); collectStringLiterals(node->data.binop.right); break;
        case NODE_ASSIGN: collectStringLiterals(node->data.assign.value); break;
        case NODE_PRINT: collectStringLiterals(node->data.expr); break;
        case NODE_STMT_LIST: collectStringLiterals(node->data.stmtlist.stmt); collectStringLiterals(node->data.stmtlist.next); break;
        case NODE_ARRAY_ASSIGN: collectStringLiterals(node->data.arrayAssign.index); collectStringLiterals(node->data.arrayAssign.value); break;
        default: break;
    }
}

/* generateMIPS emits .data with labels then .text */
fprintf(output, ".data\n");
for (int i = 0; i < strLitCount; i++) {
    fprintf(output, "str_literal_%d: .asciiz \"%s\"\n", i, strLiterals[i]);
}
fprintf(output, "\n.text\n.globl main\nmain:\n");
```

### Array access (exact code snippet)

When emitting code for an array access `arr[index]` we do:

```c
/* index is already generated into $t<indexReg> */
fprintf(output, "    sll $t%d, $t%d, 2    # index * 4\n", indexReg, indexReg);
fprintf(output, "    addi $t%d, $sp, %d   # base address\n", resultReg, baseOffset);
fprintf(output, "    add $t%d, $t%d, $t%d # element address\n", resultReg, resultReg, indexReg);
fprintf(output, "    lw $t%d, 0($t%d)     # load value\n", resultReg, resultReg);
```

Here `baseOffset` is the offset returned by `getVarOffset("arr")` and `sll` multiplies index by 4.

### Array assignment (exact):

```c
fprintf(output, "    sll $t%d, $t%d, 2    # index * 4\n", indexReg, indexReg);
fprintf(output, "    addi $t%d, $sp, %d   # base address\n", addressReg, baseOffset);
fprintf(output, "    add $t%d, $t%d, $t%d # element address\n", addressReg, addressReg, indexReg);
fprintf(output, "    sw $t%d, 0($t%d)     # store value\n", valueReg, addressReg);
```

### String concatenation and printing (exact code snippets)

Determining string vs int: `codegen` calls `exprType(node)` (the semantic function) through `exprIsString()`:

```c
int exprIsString(ASTNode* node) {
    if (!node) return 0;
    int t = exprType(node);
    return t == TYPE_STRING;
}
```

When `genExpr()` sees `NODE_STR`, it loads the address of the pooled literal:

```c
case NODE_STR: {
    int label = addStrLiteralIfMissing(node->data.str);
    fprintf(output, "    la $t%d, str_literal_%d\n", getNextTemp(), label);
    break;
}
```

When the code generator emits a `print` and `exprIsString()` is true, it loads a pointer into `$a0` and issues syscall 4:

```c
if (exprIsString(node->data.expr)) {
    if (node->data.expr->type == NODE_VAR) {
        int off = getVarOffset(node->data.expr->data.name);
        fprintf(output, "    lw $a0, %d($sp)\n", off);
    } else {
        fprintf(output, "    move $a0, $t%d\n", tempReg - 1);
    }
    fprintf(output, "    li $v0, 4\n    syscall\n");
}
```

Concatenation uses a helper `concat` emitted once at the end of the `.s` file. The helper (abridged) performs:

```asm
# compute lengths of s1 and s2
strlen_loop1:
    lb $t2, 0($t0)
    beq $t2, $zero, strlen_done1
    addi $t1, $t1, 1
    addi $t0, $t0, 1
    j strlen_loop1
strlen_done1:
    ... /* repeat for s2 */
# allocate sbrk(len1+len2+1)
    li $v0, 9
    syscall
    move $s0, $v0  # dest
# copy bytes from s1 then s2 and write 0
copy1_loop:
    lb $t8, 0($t6)
    beq $t8, $zero, copy1_done
    sb $t8, 0($t7)
    addi $t6, $t6, 1
    addi $t7, $t7, 1
    j copy1_loop
copy1_done:
    /* copy s2 similarly */
    sb $zero, 0($t7)
    move $v0, $s0
    jr $ra
```

The compiler emits `jal concat` with string pointers in `$a0` and `$a1`; the helper returns the new buffer in `$v0` which the caller stores in the destination variable's stack slot.

---

## 7) Putting it together: an end-to-end example

For this input (excerpt from `test.c`):

```c
string t, u;
t = "world";
u = t + " " + t;
print(u);
```

- Parser builds `NODE_STR_DECL` and `NODE_ASSIGN` nodes and `NODE_BINOP` for `+`.
- Semantic pass calls `addStringVar("t")` and `addStringVar("u")`, and verifies the `+` operands have `TYPE_STRING`.
- TAC carries the string literal operands and temp results.
- Codegen:
  - `collectStringLiterals()` registers `"world"` and `" "` and they are emitted in `.data` as `str_literal_0` and `str_literal_1`.
  - A generated sequence loads `t`'s pointer (or the literal address) into `$a0`, the literal into `$a1`, calls `concat` (returns pointer in `$v0`) and stores the returned pointer into `u`'s stack slot.

You can inspect the generated `test.s` to see the exact assembly printed by `generateMIPS()`.

---

## 8) Limitations, improvements, and what to say in your video

Limitations (be clear about these when you present):

- No bounds checking on arrays. Say: "we store arrays as contiguous stack slots, so we didn't add bounds checks to keep the compiler simple. That would be a small extension."  
- Concatenation allocates with `sbrk` and never frees. Say: "we intentionally keep it simple; this is acceptable for short tests, but a real runtime would manage memory or use a GC."  
- The lexer doesn't decode escape sequences. Say: "we strip the quotes and keep content literal; decoding escapes is an easy lexer extension."  

Recommended small follow-ups (if you want to show off extra work live):

1. Implement escape sequence decoding in the `scanner.l` rule that constructs `STRING_LITERAL` values.  
2. Move `concat` into a small `concat.c` runtime module and link it — cleaner generated assembly.  
3. Add optional array bounds checks in `codegen.c` by using `getArraySize()` before access.

Recording / presentation checklist (short script):

1. Show `parser.y` rules for declarations and string literal usage. Point out the `STRING_LITERAL` token.  
2. Show `ast.h` to explain `NODE_ARRAY_*` and `NODE_STR` shapes.  
3. Show `symtab.c` `addArrayVar` and `addStringVar` to show how stack layout is allocated.  
4. Show `semantic.c` `exprType()` and `checkStmt()` to explain how declarations are recorded and type rules enforced.  
5. Show a TAC snippet from `tac.c` that carries string literal operands.  
6. Show `codegen.c` `collectStringLiterals()` + `.data` emission and the `concat` helper snippet.  
7. Run `make test` and point at `test.s` to show actual emitted MIPS and run it in `spim` to demonstrate results.  

Commands to show during demo (copy/paste):

```bash
cd Mini
make test
less test.s   # inspect generated assembly
spim test.s   # run the program and show output
```

---

If you want, I can now:

- Add the `scanner.l` escape-sequence decoding and show before/after generated `test.s`.  
- Move `concat` into `concat.c` and update the `Makefile` so `codegen.c` no longer emits the helper inline.  
- Add a tiny script and recording checklist with timestamps and exact lines to point to while recording (I can prepare a one-page presenter script).

Tell me which of those you'd like next and I will implement it and re-run the build+tests.

---

## Runtime helper: concat — summary & integration

Short summary (one paragraph):

- `concat` is the runtime helper that performs string concatenation at program execution time. It takes two asciiz string pointers in `$a0` and `$a1`, computes lengths, allocates a new buffer with syscall 9 (sbrk), copies the bytes from the two inputs into the new buffer and returns the pointer in `$v0`.

Where it lives today:

- Current state: the compiler's `codegen.c` writes the full `concat` MIPS implementation directly into every generated `.s` file so the output is self-contained.

Why that matters:

- Having `concat` emitted inline makes the generated `test.s` self-contained and simple to run but duplicates the helper text across generated outputs.

Recommended integration options (pick one):

1) Keep inline (current default)
    - Pros: simplest; no build changes.  
    - Cons: duplicated helper in every generated `.s`.

2) Extract to `Mini/concat.s` and append to generated output (recommended)
    - Create `Mini/concat.s` with the `concat:` label and body (exact helper code is the same as the one currently emitted by `codegen.c`).
    - After generating `test.s` run:

```bash
cat Mini/concat.s >> test.s
spim test.s
```

    - To automate, add an append step to the `make test` target in your `Makefile` (example below).

3) Use assembler include (if supported)
    - In `generateMIPS()` you could emit a `.include "concat.s"` directive instead of inlining. This requires the assembler used by your environment to support `.include`.

Example Makefile snippet to append `concat.s` automatically (add to the `make test` rule):

```makefile
# After the compiler generates the assembly, append the helper and run spim
%.s: %.cm
     ./minicompiler $< $@
     cat Mini/concat.s >> $@

test: test.s
     spim test.s
```

Notes and caveats:

- The helper uses `sbrk` (syscall 9) and never frees memory — mention this in your video as an intentional simplification.  
- Whether the helper is placed before or after call sites in `test.s` does not matter: MIPS assembly and the simulator will resolve the `jal concat` label as long as the label exists somewhere in the final assembly file.  
- If you later implement a runtime library for your compiler, `concat.s` is a small, independent unit that fits naturally into that runtime.

If you'd like, I can now implement option (2): create `Mini/concat.s`, remove the inline emission from `codegen.c`, and patch the `Makefile` to append `concat.s` automatically and verify `make test` runs successfully. Say "do it" and I'll make the changes and run the build.

---

## FAQ & Video Notes (for your recording)

Q: Does the parser or lexer "reserve memory" when they see a declaration? What's the purpose of the free($2) call in parser actions?

A: Short answer: No — the parser does not reserve runtime stack memory. The `free($2)` call simply releases a temporary C-string buffer that the lexer allocated for the token. Here's the flow:

- The lexer (`scanner.l`) sees an identifier or a quoted string. It calls `strdup(yytext)` or `malloc(...)` and stores the pointer into `yylval.str`. That buffer is on the heap and its lifetime is until someone frees it.
- The parser (`parser.y`) receives the pointer as `$1` or `$2` in action code. The parser then typically calls an AST constructor like `createDecl($2)` or `createStringLit($1)` which copies or stores the necessary data in the AST. After that constructor returns, the parser calls `free($2)` to free the temporary buffer that the lexer created.

Important: freeing here is safe because the AST constructor either copies the string or takes ownership of it. Freeing prevents temporary heap buffers from accumulating while parsing a large program. This memory-management detail is internal to the compiler front-end and unrelated to runtime memory allocation for variables: actual runtime memory layout is created later by the semantic pass (`symtab`) which assigns stack offsets.


### Video talking points (structured)

Below is a short script you can follow when recording. It contains three parts the professor asked for.

a) Explain how the code works (high level)

- Show the pipeline slide: lexer → parser → AST → semantic → TAC → optimize → codegen → MIPS. Explain the single responsibility of each phase in one sentence.
- Open `scanner.l` and show the `STRING_LITERAL` rule. Explain: lexer turns characters into tokens and may allocate temporary buffers for token text.
- Open `parser.y` and show declaration and expression rules. Explain how grammar rules turn tokens into an AST using `createXxx` functions.
- Open `ast.h` and explain that the AST nodes are simple containers (unions) that keep the structure of the program.
- Open `semantic.c` and explain `semanticCheck()` and `exprType()`: this phase records declarations in the symbol table and enforces type rules, including array index types and string vs int semantics.
- Open `tac.c` briefly and explain that TAC is a simple intermediate representation that linearizes expressions and makes optimizations easier.
- Open `codegen.c` and show:
    - `collectStringLiterals()` + emitted `.data` labels
    - array address calculation (`sll` + `addi $sp, OFFSET`) for `arr[index]`
    - how `print()` uses `li $v0,4` for strings and `li $v0,1` for integers
    - `concat` helper and `jal concat` calling convention

b) Outline the individually assigned tasks that were completed (how to present your involvement)

Suggested phrasing (honest and clear):

"For this project I implemented the end-to-end support for strings and completed integration of arrays into the normal compilation pipeline. Specifically I:

- Added parser grammar support for `string` declarations and `STRING_LITERAL` usage.
- Ensured the lexer produces `STRING_LITERAL` tokens that the parser consumes.
- Added `NODE_STR` and `NODE_STR_DECL` AST nodes and updated AST constructors.
- Implemented semantic checks to register string and array declarations in the symbol table and enforce types (`semantic.c`).
- Updated TAC generation (`tac.c`) so string literals flow as operands and arrays produce `TAC_ARRAY_*` instructions.
- Implemented code generation (`codegen.c`) to emit `.data` for string literals, to treat string variables as pointer slots, and to implement array addressing and the `concat` runtime helper.

Note: Chloe initialized the GitHub repository and implemented the initial array support; I extended the pipeline to ensure strings are processed with the same structural pipeline and cleaned up integration points so declarations are handled in semantic analysis rather than in codegen."

c) Describe the logic/process behind leveraging the AST to generate intermediate code and assembly code for a given source language

Talking points with step-by-step logic:

1. AST is a faithful tree representation of the source program. Each AST node corresponds to a construct in the source language (literal, variable, binary op, array access, etc.). The parser builds this tree.

2. Semantic analysis walks the AST to check and record program-level information (which variables exist, what types they have, array sizes). It populates the symbol table which maps names to offsets and types. This step is necessary because code generation needs numeric offsets and type flags, but the parser only knows syntax.

3. TAC generation flattens the nested AST expressions into a linear, three-address format where each instruction has at most two operands and one result. Example: the expression `a + b + 3` becomes two TAC instructions: `t0 = a + b` then `t1 = t0 + 3`. TAC makes optimizations like constant folding and copy propagation easy to implement.

4. The optimizer runs on TAC and simplifies numeric expressions. It replaces `a + 0` with `a` or `2 + 3` with `5` and updates dependent temporaries. These transformations reduce codegen complexity and produce smaller assembly.

5. Code generation maps TAC/AST nodes to target instructions. This mapping uses information from the symbol table (stack offsets, array base addresses, whether a variable is a string). For arrays, codegen generates index multiplication and address computation to access elements. For strings, codegen emits `la` for literal addresses, syscalls for I/O, and calls the `concat` helper for concatenation.

6. The final output is an assembly file that the MIPS simulator runs. The entire process isolates concerns: syntax is separate from semantics and target-specific details, which makes maintaining and extending the compiler easier.

Closing note: If you'd like, I can prepare a 1‑page speaker script mapping each talking point to exact line numbers in the repository and the timestamps you should pause on during your video. I can also prepare a short list of 6–8 screenshots you can flip through during the recording.
