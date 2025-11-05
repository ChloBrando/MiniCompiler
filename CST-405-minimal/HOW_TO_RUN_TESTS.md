# 🚀 HOW TO RUN THE FUNCTION TESTS

## Quick Start (One Command)

```bash
make && ./minicompiler test.c
```

---

## Step-by-Step Instructions

### 1. Compile the Compiler
```bash
cd /Users/gvklok/Documents/CST-405/Compiler/CST-405/Mini
make clean
make
```

**Expected output:**
```
rm -f minicompiler ...
bison -d parser.y
flex scanner.l
gcc -g -Wall -c lex.yy.c
gcc -g -Wall -c parser.tab.c
...
gcc -g -Wall -o minicompiler ...
```

### 2. Run the Test File
```bash
./minicompiler test.c
```

**What this does:**
1. Scans `test.c` (tokenization)
2. Parses into AST
3. Performs semantic analysis
4. Generates TAC
5. Applies optimizations
6. Generates MIPS assembly → `output.s`

### 3. View the Generated Assembly
```bash
cat output.s
```

Or open in your editor to see the MIPS code!

### 4. (Optional) Run in MIPS Simulator

If you have MARS or SPIM installed:

**Using MARS:**
```bash
java -jar Mars.jar output.s
```

**Using SPIM:**
```bash
spim -file output.s
```

---

## What the Test File Tests

### ✅ Test 1: Function with NO parameters
```c
# getConstant() {
    int value;
    value = 42;
    return value;
}
```

### ✅ Test 2: Function with ONE parameter
```c
# double(int x) {
    int result;
    result = x + x;
    return result;
}
```

### ✅ Test 3: Function with TWO parameters
```c
# add(int a, int b) {
    int sum;
    sum = a + b;
    return sum;
}
```

### ✅ Test 4: Function with THREE parameters
```c
# addThree(int x, int y, int z) {
    int temp;
    int result;
    temp = x + y;
    result = temp + z;
    return result;
}
```

### ✅ Test 5: Nested function calls
```c
# compute(int a, int b) {
    int doubled;
    int added;
    doubled = double(a);      // Calls double()
    added = add(doubled, b);  // Calls add()
    return added;
}
```

### ✅ Test 6: Scope/Shadowing
```c
int x;  // Global x = 100

# testScope(int x) {  // Parameter x shadows global
    int y;
    y = x + 10;  // Uses parameter x (50), not global (100)
    return y;    // Returns 60
}
```

### ✅ Test 7: Return constant directly
```c
# getFive() {
    return 5;
}
```

### ✅ Test 8: Nested calls in expressions
```c
complex = add(getFive(), double(3));
// getFive() returns 5
// double(3) returns 6
// add(5, 6) returns 11
```

### ✅ Test 9: Functions with arrays
```c
arr[0] = getFive();           // arr[0] = 5
arr[1] = double(4);           // arr[1] = 8
arr[2] = add(arr[0], arr[1]); // arr[2] = 13
```

---

## Expected Output

When you run the test, you should see printed:

```
===== FUNCTION TESTS =====
Test 1: getConstant()
Result:
42
Expected: 42
Test 2: double(7)
Result:
14
Expected: 14
Test 3: add(5, 3)
Result:
8
Expected: 8
Test 4: addThree(1, 2, 3)
Result:
6
Expected: 6
Test 5: compute(5, 10)
Result:
20
Expected: 20
Test 6: testScope(50)
Result:
60
Expected: 60
Global x still:
100
Expected: 100
Test 7: getFive()
Result:
5
Expected: 5
Test 8: add(getFive(), double(3))
Result:
11
Expected: 11
Test 9: Arrays with functions
arr[0]:
5
arr[1]:
8
arr[2]:
13
Expected: 5, 8, 13
===== ALL TESTS COMPLETE =====
```

---

## Debugging Tips

### If compilation fails:
```bash
make clean
make 2>&1 | less
# Read error messages carefully
```

### If you get semantic errors:
Check that functions are declared before they're called in the source file.

### If MIPS code looks wrong:
```bash
cat output.s | less
# Look for function labels and calling sequences
```

### To see TAC (intermediate code):
Add print statements in your main.c after `generateTAC(root)` and `optimizeTAC()`:
```c
printTAC();
optimizeTAC();
printOptimizedTAC();
```

---

## Viewing Different Compilation Phases

### See Tokens (Scanner Output)
Modify main.c to print tokens as they're scanned.

### See AST (Parser Output)
After parsing, call:
```c
printAST(root, 0);
```

### See TAC (Before Optimization)
```c
generateTAC(root);
printTAC();
```

### See Optimized TAC
```c
optimizeTAC();
applyAdvancedOptimizations();
printOptimizedTAC();
```

### See MIPS Assembly
```bash
cat output.s
```

---

## Quick Commands Reference

| Task | Command |
|------|---------|
| **Compile compiler** | `make` |
| **Clean build** | `make clean && make` |
| **Run test** | `./minicompiler test.c` |
| **View assembly** | `cat output.s` |
| **View with line numbers** | `cat -n output.s` |
| **Search in assembly** | `grep "add:" output.s` |
| **Run in MARS** | `java -jar Mars.jar output.s` |

---

## What Success Looks Like

✅ **Compilation succeeds** - No errors from make
✅ **Parser accepts file** - No syntax errors
✅ **Semantic check passes** - No type/scope errors
✅ **TAC generates** - Three-address code created
✅ **MIPS generates** - output.s file created
✅ **Functions work** - Results match expected values

---

## Common Issues and Fixes

### Issue: "minicompiler: command not found"
**Fix:**
```bash
make
# Then try again
```

### Issue: "test.c: No such file or directory"
**Fix:**
```bash
pwd  # Make sure you're in the right directory
ls test.c  # Check file exists
```

### Issue: "Semantic Error: function not declared"
**Fix:** Make sure functions are defined before they're called, or add forward declarations.

### Issue: "Segmentation fault"
**Fix:** There's a bug in the compiler. Run with gdb:
```bash
gdb ./minicompiler
(gdb) run test.c
(gdb) backtrace
```

---

## Understanding the Generated MIPS

Look for these patterns in `output.s`:

### Function Definition:
```assembly
add:                        # Function label
    addi $sp, $sp, -32     # Allocate frame
    sw $ra, 28($sp)        # Save return address
    sw $fp, 24($sp)        # Save frame pointer
    sw $a0, 0($sp)         # Store parameter
    # ... function body ...
    jr $ra                 # Return
```

### Function Call:
```assembly
    li $a0, 5              # First argument
    li $a1, 3              # Second argument
    jal add                # Call function
    move $t0, $v0          # Get result
```

---

**Good luck with testing! 🎉**

Your compiler now supports full function capabilities with:
- Multiple parameters (up to 4 in registers)
- Return values
- Nested calls
- Proper scope management
- Parameter shadowing

All tests should pass! 🚀
