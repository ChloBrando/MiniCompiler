# C-Minus Compiler

A complete, fully functional compiler that transforms C-like source code into executable MIPS assembly. Built from scratch for CST-405 Compiler Theory and Design, this compiler implements all phases of compilation with proper scope management, function calls, arrays, and control flow.

## 🎯 Overview

This is **not** a toy compiler—it's a production-quality implementation featuring:
- ✅ **Complete compilation pipeline**: Lexer → Parser → AST → Semantic Analysis → TAC → Optimization → MIPS Codegen
- ✅ **Function implementation**: Parameters, return values, proper calling conventions
- ✅ **Scoped symbol table**: Hierarchical scope management with shadowing support
- ✅ **Array support**: Array declarations, indexing, and array parameters (pass by reference)
- ✅ **Control flow**: While loops, if/else statements with proper label generation
- ✅ **Type system**: Integer and float types with semantic checking
- ✅ **Optimizations**: Constant folding and copy propagation
- ✅ **Performance metrics**: Detailed timing for each compilation phase

## 📚 Language Features

The C-Minus language supports:

### Data Types
- **Integers**: `int x;`
- **Floats**: `float pi;`
- **Arrays**: `int numbers[10];`
- **Strings**: `"hello world"` (for print statements)

### Variables & Assignment
- **Global variables**: Declared outside functions
- **Local variables**: Declared inside functions
- **Array indexing**: `arr[i]`
- **Assignment**: `x = expression;`

### Operators
- **Arithmetic**: `+`, `-`, `*`, `/`
- **Comparison**: `<`, `>`, `<=`, `>=`, `==`, `!=`
- **Precedence**: Follows standard mathematical precedence (PEMDAS)

### Functions
- **Function declarations**: `# functionName(params) { body }`
- **Parameters**: Scalar and array parameters
- **Return statements**: `return expression;`
- **Function calls**: `result = functionName(arg1, arg2);`

### Control Flow
- **If statements**: `if (condition) { ... }`
- **If-else**: `if (condition) { ... } else { ... }`
- **While loops**: `while (condition) { ... }`

### Built-in Functions
- **print()**: Outputs integer values to console


## 📖 Language Syntax & Grammar

### Complete Program Structure

```c
// Global variable declarations
int globalVar;
float globalFloat;
int array[10];

// Function declaration
# functionName(int param1, float param2, int arr[]) {
    // Local variable declarations
    int localVar;
    
    // Statements
    localVar = param1 + 5;
    
    if (localVar > 10) {
        print(localVar);
    } else {
        print(0);
    }
    
    while (localVar < 100) {
        localVar = localVar * 2;
    }
    
    return localVar;
}

// Main function (program entry point)
# main() {
    int result;
    result = functionName(5, 3.14, array);
    print(result);
}
```

### Grammar Rules

#### 1. **Variable Declarations**
```c
// Integer variables
int variableName;
int x;

// Float variables
float pi;
float temperature;

// Arrays (fixed size)
int numbers[5];
int matrix[100];
```

#### 2. **Function Declarations**
```c
// Function with no parameters
# functionName() {
    // body
}

// Function with parameters
# sum(int a, int b) {
    int result;
    result = a + b;
    return result;
}

// Function with array parameter
# sumArray(int arr[], int size) {
    int sum;
    int i;
    sum = 0;
    i = 0;
    
    while (i < size) {
        sum = sum + arr[i];
        i = i + 1;
    }
    
    return sum;
}
```

**Important Notes:**
- Function declarations start with `#` symbol
- Functions use `{ }` braces for the body
- All local variables must be declared at the **beginning** of the function
- The `main()` function is the entry point

#### 3. **Expressions**
```c
// Arithmetic (follows standard precedence)
x = 2 + 3 * 4;        // = 14 (multiplication first)
y = (2 + 3) * 4;      // = 20 (parentheses override)
z = 10 - 5 - 2;       // = 3 (left-to-right)

// Comparisons
if (x < 10) { }       // Less than
if (x > 10) { }       // Greater than
if (x <= 10) { }      // Less than or equal
if (x >= 10) { }      // Greater than or equal
if (x == 10) { }      // Equal to
if (x != 10) { }      // Not equal to

// Array access
value = arr[0];       // Access first element
arr[i] = 42;          // Assign to array element
```

#### 4. **Control Flow**

**If Statement:**
```c
if (condition) {
    // statements
}
```

**If-Else Statement:**
```c
if (condition) {
    // true branch
} else {
    // false branch
}
```

**While Loop:**
```c
while (condition) {
    // loop body
}
```

**Example - Factorial:**
```c
int n;
int result;

# factorial(int num) {
    int fact;
    fact = 1;
    
    while (num > 0) {
        fact = fact * num;
        num = num - 1;
    }
    
    return fact;
}

# main() {
    n = 5;
    result = factorial(n);
    print(result);  // Output: 120
}
```

#### 5. **Return Statements**
```c
return;              // Return from void function
return expression;   // Return value from function
```

#### 6. **Print Statement**
```c
print(42);           // Print constant
print(variable);     // Print variable
print(x + y);        // Print expression result
```

### Common Syntax Errors to Avoid

❌ **Wrong:**
```c
int x = 10;          // No initialization in declaration
void myFunc() { }    // No 'void' keyword
for (i=0; i<10; i++) // No 'for' loops (use 'while')
```

✅ **Correct:**
```c
int x;
x = 10;

# myFunc() { }

int i;
i = 0;
while (i < 10) {
    // body
    i = i + 1;
}
```

## 🚀 Installation & Setup

### Prerequisites

Install required tools:

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install flex bison gcc make
sudo apt install spim  # MIPS simulator
```

**macOS:**
```bash
brew install flex bison gcc make
brew install spim
```

**Arch Linux:**
```bash
sudo pacman -S flex bison gcc make
sudo pacman -S spim
```

### Building the Compiler

1. **Clone the repository:**
```bash
git clone https://github.com/ChloBrando/MiniCompiler.git
cd MiniCompiler/CST-405-minimal
```

2. **Build the compiler:**
```bash
make
```

3. **Verify installation:**
```bash
./minicompiler --version
```

### Clean Build

To remove all generated files:
```bash
make clean
```

## � Usage

### Basic Compilation

```bash
./minicompiler source.c output.s
```

**Parameters:**
- `source.c`: Your C-Minus source code file
- `output.s`: Output MIPS assembly file

### Example Workflow

1. **Create a source file** (`test.c`):
```c
int x;
int y;
int result;

# main() {
    x = 10;
    y = 20;
    result = x + y;
    print(result);
}
```

2. **Compile it:**
```bash
./minicompiler test.c test.s
```

3. **View the output:**
```bash
cat test.s
```

4. **Run with SPIM:**
```bash
spim -file test.s
```

### Compiler Output

The compiler provides detailed educational output for each phase:

```
╔════════════════════════════════════════════════════════════╗
║          MINIMAL C COMPILER - EDUCATIONAL VERSION         ║
╚════════════════════════════════════════════════════════════╝

┌──────────────────────────────────────────────────────────┐
│ PHASE 1: LEXICAL & SYNTAX ANALYSIS                       │
├──────────────────────────────────────────────────────────┤
│ • Reading source file: test.c
│ • Tokenizing input (scanner.l)
│ • Parsing grammar rules (parser.y)
│ • Building Abstract Syntax Tree
└──────────────────────────────────────────────────────────┘
✓ Parse successful - program is syntactically correct!
  ⏱  Phase 1 time: 0.169 ms

┌──────────────────────────────────────────────────────────┐
│ PHASE 2: ABSTRACT SYNTAX TREE (AST)                      │
├──────────────────────────────────────────────────────────┤
│ Tree structure representing the program hierarchy:        │
└──────────────────────────────────────────────────────────┘
[AST visualization...]

[... continues through all 5 phases ...]

╔════════════════════════════════════════════════════════════╗
║                  COMPILATION SUCCESSFUL!                   ║
╠════════════════════════════════════════════════════════════╣
║ PERFORMANCE METRICS                                        ║
╠════════════════════════════════════════════════════════════╣
║ Total Compilation Time:    1.433 ms                       ║
╚════════════════════════════════════════════════════════════╝
```

### Running MIPS Code

**Option 1: SPIM (command line)**
```bash
spim -file output.s
```

**Option 2: QtSPIM (GUI)**
```bash
qtspim
# Then: File → Load → Select output.s → Run
```

**Option 3: MARS**
```bash
java -jar Mars.jar output.s
```

## 📁 Project Structure


## 📁 Project Structure

```
CST-405-minimal/
├── Source Files
│   ├── scanner.l              # Lexical analyzer (Flex)
│   ├── parser.y               # Syntax analyzer (Bison)
│   ├── ast.h / ast.c          # Abstract Syntax Tree
│   ├── symtab.h / symtab.c    # Symbol table (scoped)
│   ├── semantic.h / semantic.c # Semantic analysis
│   ├── tac.h / tac.c          # Three-address code (TAC)
│   ├── codegen.h / codegen.c  # MIPS code generator
│   └── main.c                 # Compiler driver
│
├── Build System
│   └── Makefile               # Build configuration
│
├── Test Programs
│   ├── test.c                 # Basic test
│   ├── comprehensive_demo.c   # Full feature demo
│   ├── test_order_mixed.c     # Operator precedence test
│   └── comprehensiveTest.c    # Integration test
│
├── Shell Scripts
│   ├── compile_and_run.sh     # Compile & execute helper
│   ├── test_features.sh       # Feature test suite
│   ├── test_all_demos.sh      # Run all demos
│   └── benchmark_suite.sh     # Performance benchmarks
│
└── Documentation
    ├── README.md              # This file
    ├── lab30.md               # Feature showcase
    ├── ARRAY_PARAMETERS_IMPLEMENTATION.md
    └── TEST_SUITE_SUMMARY.md
```

## 🔧 Compiler Architecture

### Complete Compilation Pipeline

```
Source Code (.c)
      ↓
┌─────────────────┐
│ PHASE 1:        │
│ LEXICAL         │ → Tokenization (scanner.l)
│ ANALYSIS        │   Input: "int x;"
└─────────────────┘   Output: INT ID(x) SEMICOLON
      ↓
┌─────────────────┐
│ PHASE 2:        │
│ SYNTAX          │ → Parse Tree Construction (parser.y)
│ ANALYSIS        │   Verifies grammar rules
└─────────────────┘   Builds Abstract Syntax Tree
      ↓
┌─────────────────┐
│ PHASE 2.5:      │
│ SEMANTIC        │ → Type checking (semantic.c)
│ ANALYSIS        │   Symbol table management
└─────────────────┘   Scope verification
      ↓
┌─────────────────┐
│ PHASE 3:        │
│ INTERMEDIATE    │ → Three-Address Code (tac.c)
│ CODE GEN        │   Platform-independent IR
└─────────────────┘   Example: t0 = a + b
      ↓
┌─────────────────┐
│ PHASE 4:        │
│ OPTIMIZATION    │ → Constant folding
│                 │   Copy propagation
└─────────────────┘   Dead code elimination
      ↓
┌─────────────────┐
│ PHASE 5:        │
│ CODE            │ → MIPS Assembly (codegen.c)
│ GENERATION      │   Stack management
└─────────────────┘   Register allocation
      ↓
MIPS Assembly (.s)
```

### Key Components

#### 1. **Lexical Analyzer (scanner.l)**
- Tokenizes input source code
- Recognizes keywords, identifiers, numbers, operators
- Handles comments and whitespace
- Returns tokens to parser

#### 2. **Parser (parser.y)**
- Implements C-Minus grammar
- Builds Abstract Syntax Tree
- Handles operator precedence
- Reports syntax errors with context

#### 3. **Symbol Table (symtab.c)**
- **Hierarchical scopes**: Global and function-local
- **Variable tracking**: Names, types, offsets
- **Scope chain**: Parent pointers for lookup
- **Shadowing support**: Local variables can hide globals

#### 4. **Semantic Analyzer (semantic.c)**
- Type checking for expressions
- Variable declaration verification
- Function signature validation
- Scope rule enforcement

#### 5. **TAC Generator (tac.c)**
- Converts AST to three-address code
- Simplified intermediate representation
- Temporary variable management
- Platform-independent

#### 6. **Optimizer (tac.c)**
- **Constant folding**: `2 + 3` → `5`
- **Copy propagation**: Replace variables with known values
- **Dead code elimination**: Remove unused code

#### 7. **Code Generator (codegen.c)**
- MIPS assembly generation
- **Stack frame management**: Proper function prologue/epilogue
- **Register allocation**: Uses `$t0-$t7` for temporaries
- **Calling conventions**: `$a0-$a3` for arguments, `$v0` for return
- **System calls**: `print()` uses MIPS syscall interface

## 🧪 Example Programs

### Example 1: Simple Arithmetic

```c
int a;
int b;
int sum;

# main() {
    a = 5;
    b = 10;
    sum = a + b;
    print(sum);
}
```

**Output:** `15`

### Example 2: Function with Parameters

```c
int result;

# add(int x, int y) {
    int sum;
    sum = x + y;
    return sum;
}

# main() {
    result = add(10, 20);
    print(result);
}
```

**Output:** `30`

### Example 3: Factorial with While Loop

```c
int n;
int result;

# factorial(int num) {
    int fact;
    fact = 1;
    
    while (num > 0) {
        fact = fact * num;
        num = num - 1;
    }
    
    return fact;
}

# main() {
    n = 5;
    result = factorial(n);
    print(result);
}
```

**Output:** `120`

### Example 4: Array Processing

```c
int numbers[5];
int total;

# sumArray(int arr[], int size) {
    int sum;
    int i;
    
    sum = 0;
    i = 0;
    
    while (i < size) {
        sum = sum + arr[i];
        i = i + 1;
    }
    
    return sum;
}

# main() {
    numbers[0] = 10;
    numbers[1] = 20;
    numbers[2] = 30;
    numbers[3] = 40;
    numbers[4] = 50;
    
    total = sumArray(numbers, 5);
    print(total);
}
```

**Output:** `150`

### Example 5: Conditional Logic

```c
int x;
int max;

# findMax(int a, int b) {
    int result;
    
    if (a > b) {
        result = a;
    } else {
        result = b;
    }
    
    return result;
}

# main() {
    x = 10;
    max = findMax(x, 25);
    print(max);
}
```

**Output:** `25`

## 🧰 Testing & Validation

### Run Test Suite

```bash
# Run all feature tests
./test_features.sh

# Run all demo programs
./test_all_demos.sh

# Compile and run a specific test
./compile_and_run.sh test.c test.s

# Run performance benchmarks
./benchmark_suite.sh
```

### Manual Testing

```bash
# Compile
make

# Test compilation
./minicompiler test.c test.s

# Run in SPIM
spim -file test.s

# Check for errors
echo $?  # Should be 0 for success
```

## 🎓 Educational Features

### 1. **Visual Output**
Each compilation phase displays:
- Clear ASCII box formatting
- Phase descriptions and timing
- Intermediate representations
- Success/error indicators

### 2. **Performance Metrics**
- Individual phase timing (milliseconds)
- Total compilation time
- Helps understand compilation overhead

### 3. **Intermediate Representations**
Students can see:
- **AST**: Program structure hierarchy
- **TAC**: Three-address intermediate code
- **Optimized TAC**: After optimization passes
- **MIPS**: Final assembly code

### 4. **Educational Comments**
- Source code extensively documented
- Explains "why" not just "what"
- Real-world compiler design patterns

## � Debugging Tips

### Common Issues

**1. Compilation Fails**
```bash
# Check if Flex/Bison are installed
flex --version
bison --version

# Clean and rebuild
make clean
make
```

**2. Parser Errors**
- Check for missing semicolons
- Verify function syntax uses `#` symbol
- Ensure all variables declared before use
- Check bracket matching `{ }`

**3. SPIM Errors**
```bash
# Verbose SPIM output
spim -file output.s -exception_handler

# Check assembly syntax
cat output.s | grep "error"
```

**4. Unexpected Output**
- Verify operator precedence
- Check variable initialization
- Ensure correct function parameter passing

### Verbose Compiler Output

The compiler already provides detailed output. To redirect it:
```bash
./minicompiler test.c test.s > compilation.log 2>&1
```

## 📊 Performance Benchmarks

Typical compilation times (on modern hardware):

| Program Size | Lines | Compilation Time |
|-------------|-------|------------------|
| Simple      | 10    | ~1-2 ms         |
| Medium      | 50    | ~2-5 ms         |
| Complex     | 200   | ~10-20 ms       |

**Note**: Times include all 5 phases of compilation.

## � Key Accomplishments

This compiler implements three major features from scratch:

### 1. **Function System**
- Complete parameter passing
- Return value handling
- Stack frame management
- MIPS calling conventions
- Recursive function support

### 2. **Array Parameters**
- Pass-by-reference semantics
- Pointer decay implementation
- Efficient (4-byte pointer vs copying array)
- Compatible with C semantics

### 3. **Scoped Symbol Table**
- Hierarchical scope management
- Parent pointer chain for lookup
- Variable shadowing support
- Proper memory management

See `lab30.md` for detailed implementation analysis.

## 🤝 Contributing

This is an educational project developed for CST-405. Suggestions and improvements welcome!

## 📜 License

Educational use - Free to use and modify for learning purposes.

## 👤 Author

**Chloe Brandow**  
CST-405: Compiler Theory and Design  
Grand Canyon University

---

## 🔗 Additional Resources

- **MIPS Reference**: [MIPS Instruction Set](https://www.dsi.unive.it/~gasparetto/materials/MIPS_Instruction_Set.pdf)
- **SPIM Documentation**: [SPIM Simulator Guide](http://spimsimulator.sourceforge.net/)
- **Flex Manual**: [Flex Documentation](https://westes.github.io/flex/manual/)
- **Bison Manual**: [Bison Documentation](https://www.gnu.org/software/bison/manual/)

## 📞 Support

For questions or issues:
1. Check the documentation in `docs/`
2. Review example programs in test files
3. Examine `lab30.md` for implementation details
4. Consult the comprehensive grammar rules above