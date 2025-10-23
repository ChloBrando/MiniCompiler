# 🚀 Quick Start Guide

## Running Your Compiler

```bash
# Compile a source file
./minicompiler input.c output.s

# Run in SPIM
spim -file output.s
```

## What Your Compiler Supports

✅ **Variables**: `int x;` `string s;`  
✅ **Arrays**: `int arr[10];`  
✅ **Arithmetic**: `x = a + b;` `y = x - 5;`  
✅ **Print**: `print(x);` `print("hello");`  
✅ **Functions**: `# funcName(int a, int b) { ... }`  
✅ **Return**: `return value;`  
✅ **Scope**: Local variables and parameters  
✅ **Comments**: `// single line comments`  

## Syntax Examples

### Variables
```c
int x;
x = 10;
print(x);
```

### Arrays
```c
int arr[5];
arr[0] = 10;
arr[1] = 20;
print(arr[0]);
```

### Functions
```c
# add(int a, int b) {
    int sum;
    sum = a + b;
    return sum;
}

int result;
result = add(5, 3);
print(result);  // Prints 8
```

### Nested Calls
```c
# double(int n) {
    return n + n;
}

# add(int a, int b) {
    return a + b;
}

print(add(double(5), 3));  // Prints 13
```

### Arrays + Functions
```c
int arr[3];
arr[0] = getFive();
arr[1] = double(4);
arr[2] = add(arr[0], arr[1]);
```

## Test Files

- `test_simple.c` - Basic function tests (recommended)
- `test.c` - Comprehensive tests

## Limitations

- Maximum 4 function parameters
- Only `int` and `string` types
- No conditionals (if/else) or loops
- Arrays are 1-dimensional only

## Need Help?

📖 See `COMPILER_STUDY_GUIDE.md` for complete details  
🎓 Everything you need for your quiz is in the study guide!

---

**Your compiler is fully functional and ready to use! 🎉**
