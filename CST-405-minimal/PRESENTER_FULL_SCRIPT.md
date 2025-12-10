# Presenter Script — If-Statements and Comparison Operators
**Complete Speaker Script with Code References - 7 Minutes**

This script is designed to be read aloud. Each section tells you what to say and what to show on screen.

---

## Opening (30 seconds)

**[SHOW: ifandbooleans.c file open]**

**SAY:**
"Hello. Today I'm presenting my implementation of if-statements and comparison operators in my Mini compiler. My compiler can now handle if-then statements, if-then-else statements, nested if statements up to three levels deep, and all six comparison operators. It generates working MIPS assembly code that runs in the SPIM simulator."

**[SCROLL through ifandbooleans.c to show tests]**

"As you can see here, I have 25 comprehensive test cases, and 22 of them pass successfully. Let me walk you through exactly how this works, from source code to running MIPS assembly."

---

## Part A: How If-Statements Work - The Complete Pipeline (4 minutes)

### Step 1: Scanner - Breaking Input Into Tokens (45 seconds)

**[OPEN: scanner.l in your editor]**

**SAY:**
"Let me trace a simple if-statement through all five phases of my compiler. Here's my example:"

**[WRITE THIS ON WHITEBOARD OR SHOW IN COMMENT:]**
```c
if (x > 5) {
    print("x is big");
}
```

**SAY:**
"The first phase is the scanner, which breaks this into tokens. Let me show you the rules I added."

**[SCROLL TO: Line 26 in scanner.l]**

**SAY:**
"On line 26, I added the 'if' keyword, and line 27 has 'else':"

```c
"if"            { return IF; }      // Line 26
"else"          { return ELSE; }    // Line 27
```

**[SCROLL TO: Lines 64-69 in scanner.l]**

**SAY:**
"And here are lines 64 through 69, where I added all six comparison operators:"

```c
"=="            { return EQ; }      // Line 64 - equals
"!="            { return NE; }      // Line 65 - not equals
"<="            { return LE; }      // Line 66 - less or equal
">="            { return GE; }      // Line 67 - greater or equal
"<"             { return '<'; }     // Line 68 - less than
">"             { return '>'; }     // Line 69 - greater than
```

**SAY:**
"So when the scanner sees our if-statement, it produces these tokens: IF... open paren... ID for x... GT for greater-than... NUM for 5... close paren... and so on. These tokens go to the parser."

---

### Step 2: Parser - Building the Syntax Tree (1 minute)

**[OPEN: parser.y in your editor]**

**[SCROLL TO: Lines 95-96]**

**SAY:**
"The parser takes those tokens and builds a syntax tree. Here's the grammar rule I wrote, starting at line 95 of parser.y:"

```yacc
stmt:
    IF '(' expr ')' '{' stmt_list '}' {
        $$ = createIfStmt($3, $6, NULL);
    }
```

**SAY:**
"This rule says: match the keyword IF, then a parenthesized expression, then a block of statements in braces. The action calls createIfStmt to build an AST node."

**[SCROLL TO: Lines 100-101]**

**SAY:**
"And here's the if-else version on line 100:"

```yacc
    | IF '(' expr ')' '{' stmt_list '}' ELSE '{' stmt_list '}' {
        $$ = createIfStmt($3, $6, $10);
    }
```

**SAY:**
"The dollar-three is the condition expression, dollar-six is the then-branch, and dollar-ten is the optional else-branch."

**[YOU CAN DRAW THIS ON WHITEBOARD:]**

**SAY:**
"This creates an Abstract Syntax Tree that looks like this:"

```
IF_STMT node
├── condition: x > 5
│   ├── left: x
│   ├── operator: >
│   └── right: 5
└── then_branch: print("x is big")
```

---

### Step 3: Semantic Analysis - Checking Types (30 seconds)

**[OPEN: semantic.c]**

**[SCROLL TO: Line 240]**

**SAY:**
"The semantic phase walks the tree and checks that everything makes sense. Here's my code at line 240 of semantic.c:"

```c
case NODE_IF_STMT:
    checkExpr(node->data.ifStmt.condition);
    checkStmt(node->data.ifStmt.thenBranch);
    if (node->data.ifStmt.elseBranch) {
        checkStmt(node->data.ifStmt.elseBranch);
    }
    break;
```

**SAY:**
"It verifies that the condition is a valid expression, checks that the then-branch contains valid statements, and if there's an else-branch, checks that too. It also makes sure variables like x are declared before they're used."

---

### Step 4: TAC Generation - Control Flow with Labels (1 minute)

**[OPEN: tac.c]**

**[SCROLL TO: Line 395]**

**SAY:**
"Now comes the interesting part. The TAC phase - that's Three Address Code - converts the if-statement into assembly-like instructions with labels and jumps. Here's my implementation at line 395:"

```c
case NODE_IF_STMT: {
    int else_label = nextLabel++;
    int endif_label = nextLabel++;

    char* condResult = genExpr(node->data.ifStmt.condition);

    emitTAC3("IF_FALSE", condResult, "", labelToStr(else_label));

    genStmt(node->data.ifStmt.thenBranch);
    emitTAC3("GOTO", "", "", labelToStr(endif_label));

    emitLabel(else_label);
    if (node->data.ifStmt.elseBranch) {
        genStmt(node->data.ifStmt.elseBranch);
    }
    emitLabel(endif_label);
}
```

**SAY:**
"I create two unique labels - one for the else part and one for after the if-statement. I evaluate the condition into a temporary variable, then emit an IF_FALSE instruction that jumps to the else label if the condition is zero. After the then-branch, I jump to the end. This is how high-level if-else becomes low-level jumps."

**[SHOW THIS ON SCREEN OR WHITEBOARD:]**

**SAY:**
"For our example, the TAC looks like this:"

```
t0 = x > 5           // Evaluate condition
IF_FALSE t0 GOTO else_1
    PRINT "x is big"  // Then branch
    GOTO endif_2
else_1:              // Else branch (empty here)
endif_2:             // Continue
```

---

### Step 5: MIPS Code Generation - Real Assembly (1 minute 15 seconds)

**[OPEN: codegen.c]**

**[SCROLL TO: Line 575]**

**SAY:**
"The final phase generates actual MIPS assembly. First, let me show you how comparison operators work. Here's line 575 where I handle greater-than:"

```c
else if (strcmp(tac->op, ">") == 0) {
    fprintf(output, "    lw $t0, %s\n", getLocation(tac->arg1));
    fprintf(output, "    lw $t1, %s\n", getLocation(tac->arg2));
    fprintf(output, "    slt $t2, $t1, $t0\n");
    fprintf(output, "    sw $t2, %s\n", getLocation(tac->result));
}
```

**SAY:**
"MIPS doesn't have a greater-than instruction. It only has 'set less than' - that's slt. So I flip it: checking if 5 is less than x is the same as checking if x is greater than 5. If it's true, t2 gets 1. If false, t2 gets 0."

**[SCROLL TO: Line 652]**

**SAY:**
"And here's the conditional branch at line 652:"

```c
case TAC_IF_FALSE:
    fprintf(output, "    lw $t0, %s\n", getLocation(tac->arg1));
    fprintf(output, "    beq $t0, $zero, %s\n", tac->result);
    break;
```

**SAY:**
"This loads the condition result - remember, that's 0 or 1 - and uses beq, which means 'branch if equal.' If t0 equals zero, meaning the condition was false, it jumps to the else label."

**[OPEN: ifandbooleans.s]**

**[SCROLL TO: Around line 100 where you can see actual generated MIPS]**

**SAY:**
"Here's what my compiler actually generates for our example:"

```assembly
    lw $t0, -4($sp)        # Load x from stack
    li $t1, 5              # Load constant 5
    slt $t2, $t1, $t0      # Set t2 = 1 if 5 < x
    sw $t2, -8($sp)        # Store result

    lw $t0, -8($sp)        # Load condition
    beq $t0, $zero, else_1 # If 0, jump to else

    la $a0, str_0          # Load string address
    li $v0, 4              # Syscall 4 = print string
    syscall
    j endif_2              # Jump to end

else_1:
    # Else code would go here
endif_2:
    # Continue
```

**SAY:**
"And this is what actually runs in SPIM."

---

## Part B: What I Personally Implemented (1 minute)

**[CAN STAY ON CODE SCREEN]**

**SAY:**
"Let me list exactly what I implemented for this project."

**[READ CLEARLY - YOU CAN COUNT ON FINGERS:]**

"**One: Scanner tokens.** I added the if and else keywords and all six comparison operators to scanner.l.

**Two: Parser grammar.** I wrote the grammar rules that recognize if-statements and if-else statements in parser.y.

**Three: AST node creation.** I implemented createIfStmt to build the syntax tree nodes.

**Four: Semantic checking.** I added validation in semantic.c to verify conditions and statement blocks.

**Five: TAC generation.** I implemented the label and jump strategy in tac.c - this was the trickiest part because I had to figure out how to convert if-else into labels.

**Six: MIPS code generation.** I wrote the code that generates conditional branches using beq and implemented all six comparison operators using the slt instruction.

**Seven: Testing.** I created a comprehensive test file with 25 different test cases covering basic ifs, if-else, nested ifs, all six operators, and edge cases. 22 out of 25 pass successfully."

---

## Part C: How I Increased Compiler Complexity (45 seconds)

**[STILL ON CODE OR YOU CAN SHOW DIAGRAM]**

**SAY:**
"Let me explain my strategy for adding this feature to the compiler."

"**First, I worked incrementally.** I didn't try to do everything at once. I started with a simple if-then statement with just a greater-than operator. Once that worked, I added else. Then I added the other comparison operators one by one. Then nested ifs. Each step was small and testable."

"**Second, I used modular architecture.** Notice each phase is in its own file. When scanner.l worked, I moved to parser.y. When that worked, I moved to TAC. This separation meant I could focus on one problem at a time."

"**Third, the key insight was labels.** Once I figured out the label pattern - generate a label, emit a jump, place the label later - that same pattern works for if-statements, nested ifs, and even future features like loops. The pattern is: label for else, label for end, jump if false, generate code, jump to end, place labels."

"**Fourth, understanding MIPS limitations.** MIPS only has slt for comparisons. So I had to figure out how to make five other operators from one instruction. Greater-than is less-than with swapped operands. Equal is subtract and check if zero. This required creative thinking but kept the code simple."

---

## Part D: Live Demonstration (1 minute 15 seconds)

**[SWITCH TO: Terminal window]**

**SAY:**
"Now let me show you it actually working."

**[TYPE AND RUN:]**
```bash
cat ifandbooleans.c | head -30
```

**[WHILE IT SCROLLS, SAY:]**
"Here's my test file. You can see test one is a basic if-then. Test two checks that false conditions don't execute. Test three tests the then-branch of if-else. Test four tests the else-branch. And so on."

**[TYPE AND RUN:]**
```bash
make clean && make
```

**SAY:**
"Compiling the compiler..."

**[WHEN DONE, TYPE:]**
```bash
./minicompiler ifandbooleans.c ifandbooleans.s
```

**SAY:**
"And compiling my test file... Compilation successful!"

**[TYPE:]**
```bash
tail -20 ifandbooleans.s
```

**SAY:**
"Here's some of the generated MIPS. You can see the lw instructions loading variables, the slt for comparison, the beq for conditional branching, labels like else underscore and endif underscore."

**[TYPE:]**
```bash
spim -file ifandbooleans.s | head -50
```

**[AS OUTPUT APPEARS, SAY:]**
"And here it is running in SPIM. Test 1 - success. Test 2 - false condition correctly skipped. Test 3 - took the then branch. Test 4 - took the else branch. Test 5 through 13 - all six comparison operators working. Test 14 through 16 - nested if statements working. Tests 17 through 22 - all passing."

**[SCROLL DOWN IF NEEDED]**

**SAY:**
"22 out of 25 tests pass. The three that fail are four-level deeply nested if statements - there's a minor bug in my label generation for very deep nesting that I'm debugging. But the core functionality - if-statements with all six comparison operators - is fully working and generating correct MIPS code."

---

## Conclusion (20 seconds)

**[CAN GO BACK TO CODE OR STAY ON TERMINAL]**

**SAY:**
"To summarize: I successfully implemented if-statements by adding tokens in the scanner, writing grammar rules in the parser, using labels and jumps for control flow in the TAC phase, and generating conditional branch instructions in MIPS. The key insight was understanding how high-level if-else becomes low-level machine instructions using labels and branches. This modular approach means adding more features like loops would follow the same pattern."

**SAY:**
"Are there any questions?"

---

## Quick Command Reference (Keep This Open in Another Window)

```bash
# Show test file
cat ifandbooleans.c | head -50

# Show more tests
cat ifandbooleans.c | tail -50

# Compile compiler
make clean && make

# Compile test file
./minicompiler ifandbooleans.c ifandbooleans.s

# Show generated MIPS
tail -30 ifandbooleans.s

# Run in SPIM
spim -file ifandbooleans.s | head -80
```

---

## File and Line Number Quick Reference

**Have these written down in case you need to jump to specific code:**

- **scanner.l line 26-27** → if/else keywords
- **scanner.l line 64-69** → comparison operators (==, !=, <=, >=, <, >)
- **parser.y line 95** → if-then grammar rule
- **parser.y line 100** → if-then-else grammar rule
- **semantic.c line 240** → if-statement semantic checking
- **tac.c line 395** → TAC generation with labels and jumps
- **codegen.c line 575** → greater-than comparison MIPS code
- **codegen.c line 652** → conditional branch (IF_FALSE) MIPS code

---

## Backup Q&A Answers (Read These If Asked)

**Q: "Why use labels instead of direct memory addresses?"**

**SAY:**
"Labels give me flexibility. When I'm generating TAC, I don't know the final memory addresses - those aren't determined until the MIPS code is assembled. Labels let me think about control flow abstractly. The TAC phase says 'jump to else_1' and the code generation phase figures out where else_1 actually is in memory. This separation of concerns makes the compiler easier to write and debug."

---

**Q: "How would you add while loops?"**

**SAY:**
"The same pattern would work perfectly. I'd put a label at the start of the loop, evaluate the condition, branch to an end label if false, execute the loop body, then jump back to the start label. It's literally the same label strategy I used for if-statements - the only difference is the jump at the end goes backward instead of forward. Once you understand labels and jumps, all control structures follow the same pattern."

---

**Q: "Why do 3 tests fail?"**

**SAY:**
"Those three tests have four-level deeply nested if-statements - so an if inside an if inside an if inside an if. There's a bug where my nextLabel counter doesn't increment properly in very deep nesting, so the generated code references undefined labels like endif_31. The fix is to make sure I'm tracking the label counter correctly across recursive calls. The bug doesn't affect the core if-statement logic - that works fine. It's just an edge case with label management in extreme nesting situations."

---

**Q: "How do you implement comparison operators MIPS doesn't have?"**

**SAY:**
"MIPS only gives us slt - set if less than. For greater-than, I swap the operands: x greater than y becomes y less than x. For equal, I subtract x minus y and check if the result is zero using beq. For not-equal, I use the same subtraction but branch if not equal to zero using bne. For less-than-or-equal, I use slt to get x less than y, then OR that with x equals y. Each operator requires a little creativity, but they all use slt as the foundation. It's like solving a puzzle where you only have one tool and have to make it do six different jobs."

---

**Q: "Did you implement boolean operators like AND and OR?"**

**SAY:**
"Not yet. I have the architecture designed - I know exactly how they'd work. The scanner would tokenize && and ||, the parser would build AND and OR nodes in the tree, TAC would emit multiple IF_FALSE jumps to implement short-circuit evaluation, and MIPS would use the 'and' and 'or' instructions. But I ran out of time, so currently I only have the six comparison operators working. Boolean operators are the next feature on my list - they'd follow the exact same pipeline I showed you today."

---

**END OF SCRIPT**

---

## Presentation Tips

1. **Practice the code navigation.** Know exactly where each line number is so you can jump to it quickly.

2. **Have both the code and terminal visible.** Split screen or two monitors if possible.

3. **Run the commands ahead of time** to make sure they work. Have the output ready so you know what to expect.

4. **Speak slowly and clearly** when saying line numbers and file names.

5. **Point at the screen** when you say "here" or "this line."

6. **If you freeze, look at the Quick Reference** section and pick up from the next command.

7. **The whole thing should take 6-7 minutes.** Practice with a timer.

8. **End with confidence** - you built a working compiler feature! That's impressive.
