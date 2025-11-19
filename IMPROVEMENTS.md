# Compiler Improvements - Error Reporting

## Changes Made

### 1. Enhanced Error Reporting in Parser
**File: parser.y**

- Added line number tracking (`extern int yylineno`)
- Added token text tracking (`extern char* yytext`)
- Improved `yyerror()` function with:
  - Visual box formatting for errors
  - Line number where error occurred
  - Current token that caused the error
  - Helpful suggestions for common mistakes

### 2. Line Number Tracking in Scanner
**File: scanner.l**

- Added `%option yylineno` to enable automatic line number tracking
- This allows the parser to report exactly which line has the error

## Error Messages Now Include:

```
╔════════════════════════════════════════════════════════════╗
║                     SYNTAX ERROR DETECTED                  ║
╚════════════════════════════════════════════════════════════╝

Error at line <LINE_NUMBER> near token: '<TOKEN>'
Error message: <DETAILED_MESSAGE>

Common causes:
  • Missing semicolon ';' after statement
  • Mismatched parentheses () or braces {}
  • Invalid function syntax (use: # funcName(params) { })
  • Array parameters not supported (use: int x, not int x[])
  • Missing return type or parameters in function
```

## Current Parser Limitations

Your Mini compiler currently does **NOT** support:

1. **Array parameters in functions**
   - ❌ NOT SUPPORTED: `# sumArray(int arr[], int size)`
   - ✅ SUPPORTED: `# sumArray(int size)` (must pass array differently)

2. **Void functions** (function declarations without parameters/returns)
   - ❌ NOT SUPPORTED: `void main(void)`
   - ✅ SUPPORTED: `# main()`

3. **Type specifiers on function declarations**
   - ❌ NOT SUPPORTED: `int add(int a, int b)`
   - ✅ SUPPORTED: `# add(int a, int b)`

## Supported Syntax

### Functions
```c
# functionName(int param1, float param2) {
    int result;
    result = param1 + param2;
    return result;
}
```

### Arrays
```c
int numbers[5];
numbers[0] = 10;
numbers[1] = 20;
print(numbers[0]);
```

### If Statements
```c
if (a > b) {
    print("a is greater");
} else {
    print("b is less or equal");
}
```

### Comments
```c
// Single line comments are supported
```

## Testing

Run your compiler with:
```bash
make run          # Compile and execute test.c
make test         # Compile and show MIPS assembly
make clean        # Clean all generated files
```

## Future Improvements

To support the full test file with array parameters, you would need to:

1. Extend the `param_list` grammar rule in parser.y:
```yacc
| INT ID '[' ']' {
    $$ = createArrayParam($2, "int");
    free($2);
}
```

2. Update the AST to handle array parameter nodes
3. Update code generation to pass array addresses properly
