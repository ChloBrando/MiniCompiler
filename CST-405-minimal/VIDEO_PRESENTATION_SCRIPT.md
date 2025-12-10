# 5-Minute Video Presentation Script: Loop Implementation in C-Minus Compiler

**Total Time: 5 minutes**  
**Presenter: [Your Name]**  
**Course: CST-405 Compiler Construction**

---

## [0:00 - 0:30] Introduction (30 seconds)

**[Show title slide: "Loop Implementation in C-Minus Compiler"]**

"Hello! Today I'll be demonstrating how we implemented while loops in our C-minus compiler. Loops are a fundamental control structure in programming, and implementing them requires coordinated work across all phases of compilation: from lexical analysis, through parsing and semantic checking, all the way to MIPS assembly code generation. Let's dive in!"

**[Show simple while loop example on screen]**
```c
int i;
# main() {
    i = 0;
    while (i < 5) {
        print(i);
        i = i + 1;
    }
}
```

---

## [0:30 - 1:00] Phase 1: Lexical & Syntax Analysis (30 seconds)

**[Screen: Show scanner.l and parser.y side by side]**

"First, in the lexical analysis phase, we added the 'while' keyword to our scanner. The scanner recognizes 'while' and returns a WHILE token."

**[Highlight in scanner.l]**
```flex
"while"     { return WHILE; }
```

"Next, in the parser, we define the grammar rule for while statements. A while loop consists of the keyword, parentheses around a condition expression, and a statement body."

**[Highlight in parser.y]**
```yacc
while_stmt:
    WHILE '(' expr ')' stmt {
        $$ = createWhileNode($3, $5);
    }
    ;
```

"The parser calls createWhileNode to build an Abstract Syntax Tree node representing the loop."

---

## [1:00 - 2:00] Phase 2: AST & Semantic Analysis (60 seconds)

**[Screen: Show AST structure definition]**

"The AST node for a while loop contains two key components: the condition and the body."

**[Show code]**
```c
struct {
    struct ASTNode* condition;  /* Loop condition */
    struct ASTNode* body;       /* Loop body */
} whileLoop;
```

**[Show visual AST diagram on screen]**

"Here's what the AST looks like for our example. The WHILE node has a condition comparing i < 5, and a body containing two statements: the print and the increment."

```
WHILE
├── Condition: COMPARE (<)
│   ├── VAR: i
│   └── NUM: 5
└── Body: STMT_LIST
    ├── PRINT(i)
    └── ASSIGN: i = i + 1
```

**[Switch to semantic analysis]**

"In semantic analysis, we validate that the loop condition evaluates to a comparable type - either int or float. We also recursively check that all statements in the loop body are semantically correct and that all variables are declared."

**[Show code snippet]**
```c
int condType = exprType(node->data.whileLoop.condition);
if (condType != TYPE_INT && condType != TYPE_FLOAT) {
    fprintf(stderr, "Error: Condition must be numeric\n");
}
```

---

## [2:00 - 3:30] Phase 3: Code Generation (90 seconds)

**[Screen: Show control flow diagram]**

"Now comes the most interesting part - generating MIPS assembly code. A while loop requires a specific control flow structure with labels and jump instructions."

**[Show control flow diagram]**
```
while_start:
    → Evaluate condition
    → If false, jump to while_end
    → Execute body
    → Jump back to while_start
while_end:
    → Continue with rest of program
```

**[Show actual code generation function]**

"The code generator creates unique labels for each loop using a static counter. This ensures nested loops don't have label conflicts."

```c
static int whileLabelCounter = 0;
int currentLabel = whileLabelCounter++;
```

**[Show generated assembly on screen - walk through it]**

"Let's look at the actual MIPS assembly generated for our example:"

```mips
while_start_0:
    lw $t0, i              # Load i
    li $t1, 5              # Load constant 5
    slt $t2, $t0, $t1      # t2 = (i < 5)
    beq $t2, $zero, while_end_0  # Exit if false
    
    # Loop body
    lw $t0, i
    move $a0, $t0
    li $v0, 1
    syscall                # Print i
    
    lw $t0, i
    addi $t0, $t0, 1
    sw $t0, i              # i = i + 1
    
    j while_start_0        # Jump back to start
    
while_end_0:
    # Continue after loop
```

**[Walk through key instructions]**

"The key instructions are:
1. Load the loop variable 'i'
2. Compare it with 5 using 'slt' - set less than
3. Branch to the end if condition is false using 'beq'
4. Execute the loop body - print and increment
5. Unconditionally jump back to the start with 'j'
6. The end label where we exit"

---

## [3:30 - 4:30] Live Demonstration (60 seconds)

**[Screen: Terminal with compiler]**

"Let's see this in action! I'll compile and run a more interesting example that calculates the sum from 1 to N."

**[Type and show code]**
```c
int n;
int sum;
int i;

# main() {
    n = 5;
    sum = 0;
    i = 1;
    while (i <= n) {
        sum = sum + i;
        i = i + 1;
    }
    print(sum);
}
```

**[Run compiler]**
```bash
$ ./minicompiler sum_demo.c sum_demo.s
```

**[Show compilation output - highlight phases]**

"Notice the compiler goes through all phases:
- Parsing successful
- AST built showing the WHILE node
- TAC generated with loop labels
- Optimizations applied
- MIPS assembly generated"

**[Run with SPIM]**
```bash
$ spim -file sum_demo.s
15
```

**[Show execution trace on screen]**

"Perfect! The output is 15, which is 1+2+3+4+5. Let me show you the execution trace:

- Iteration 1: i=1, sum=1
- Iteration 2: i=2, sum=3
- Iteration 3: i=3, sum=6
- Iteration 4: i=4, sum=10
- Iteration 5: i=5, sum=15
- Iteration 6: i=6, condition false, exit"

---

## [4:30 - 5:00] Advanced Features & Conclusion (30 seconds)

**[Screen: Show nested loop example]**

"Our implementation also supports nested loops. Each loop gets its own unique labels."

```c
int i, j;
# main() {
    i = 0;
    while (i < 3) {
        j = 0;
        while (j < 3) {
            print(i * 10 + j);
            j = j + 1;
        }
        i = i + 1;
    }
}
```

**[Show assembly with while_start_0 and while_start_1 labels]**

**[Final slide: Summary]**

"To summarize, we implemented while loops by:
1. Adding the 'while' keyword token in the scanner
2. Defining grammar rules in the parser
3. Creating AST nodes to represent loop structure
4. Validating conditions in semantic analysis
5. Generating MIPS assembly with proper labels and jumps

The result is a fully functional loop construct that integrates seamlessly with the rest of our compiler. Thank you!"

---

## Screen Recording Tips

1. **Preparation:**
   - Have all example files ready (`sum_demo.c`, `nested_loop.c`)
   - Clean terminal with large font
   - Pre-run commands to ensure they work
   - Have diagrams ready as images or slides

2. **Transitions:**
   - Use screen capture software (OBS Studio, Zoom, or QuickTime)
   - Have slides for diagrams
   - Terminal for live demos
   - Code editor showing source files

3. **Pacing:**
   - Speak clearly and not too fast
   - Pause briefly between sections
   - Point out key code sections
   - Let outputs display for 2-3 seconds

4. **Visual Elements:**
   - Use syntax highlighting
   - Zoom in on important code sections
   - Highlight lines as you explain them
   - Show before/after comparisons

---

## Backup Demo Commands

In case of technical issues, have these pre-recorded or ready:

```bash
# Compile simple counter
./minicompiler test_loop_simple.c test_loop_simple.s
spim -file test_loop_simple.s

# Compile sum example
./minicompiler test_loop_sum.c test_loop_sum.s
spim -file test_loop_sum.s

# Compile nested loop
./minicompiler test_loop_nested.c test_loop_nested.s
spim -file test_loop_nested.s

# Show assembly code
cat test_loop_sum.s | grep -A 20 "while_start"
```

---

## Key Points to Emphasize

✓ **Integration:** Loops work across all compiler phases  
✓ **Correctness:** Proper control flow with labels and jumps  
✓ **Flexibility:** Support for simple and nested loops  
✓ **Testing:** Working examples that execute correctly  
✓ **Performance:** Efficient MIPS code generation  

---

*End of Script*  
*Total Duration: 5:00*
