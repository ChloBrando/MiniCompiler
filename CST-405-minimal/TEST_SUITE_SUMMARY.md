# Test Suite Summary: While Loops & Order of Operations

## Quick Overview

This test suite validates two critical compiler features:
1. **While Loops** - Iterative control structures
2. **Order of Operations** - Operator precedence and associativity

## Test Files Created

### While Loop Tests (4 tests)
- `test_while_basic.c` - Simple counter (0-5)
- `test_while_accumulator.c` - Factorial calculation (5! = 120)
- `test_while_nested.c` - Nested loops with unique labels
- `test_while_condition.c` - Different comparison operators

### Order of Operations Tests (5 tests)
- `test_order_basic.c` - Multiplication before addition (2+3*4=14)
- `test_order_division.c` - Division before subtraction (20-10/2=15)
- `test_order_mixed.c` - Multiple operators (10+2*5-8/4=18)
- `test_order_associativity.c` - Left-to-right evaluation (20-5-3=12)
- `test_order_comparison.c` - Arithmetic before comparison (5+3<10=1)

### Integration Test (1 test)
- `test_combined_while_order.c` - Both features working together

## Running Tests

```bash
cd CST-405-minimal
./test_features.sh
```

## Test Results

```
==========================================
TEST SUMMARY
==========================================
Total Tests:  10
Passed:       10
Failed:       0
==========================================
All tests passed! ✓
```

## Implementation Documentation

**Main Document:** `WHILE_AND_ORDER_IMPLEMENTATION.md`

Contains:
- Complete implementation details for both features
- All 5 compiler phases explained
- Detailed test results with calculations
- Integration examples
- Technical deep-dives
- MIPS assembly examples

## Key Implementation Points

### While Loops
- **Scanner:** Recognizes `while` keyword
- **Parser:** Grammar rule `while (expr) stmt`
- **AST:** NODE_WHILE with condition and body
- **Codegen:** Labels (while_start_N, while_end_N) with branches
- **Feature:** Static counter ensures unique labels for nested loops

### Order of Operations
- **Parser:** Precedence declarations with `%left`
- **Hierarchy:** `==`, `!=` < `<`, `>`, `<=`, `>=` < `+`, `-` < `*`, `/`
- **Associativity:** All operators are left-to-right
- **Feature:** Bison automatically builds correct parse tree

## Quick Test Examples

### While Loop
```c
int i;
# main() {
    i = 0;
    while (i < 6) {
        print(i);
        i = i + 1;
    }
}
```
Output: `0, 1, 2, 3, 4, 5`

### Order of Operations
```c
int result;
# main() {
    result = 2 + 3 * 4;
    print(result);
}
```
Output: `14` (not 20)

### Combined
```c
int i;
int sum;
# main() {
    i = 0;
    sum = 0;
    while (i < 5) {
        sum = sum + i * 2;
        print(sum);
        i = i + 1;
    }
}
```
Output: `0, 2, 6, 12, 20`

## Files Reference

| File | Purpose |
|------|---------|
| `test_features.sh` | Automated test runner |
| `WHILE_AND_ORDER_IMPLEMENTATION.md` | Complete implementation guide |
| `test_while_*.c` | While loop test programs |
| `test_order_*.c` | Order of operations test programs |
| `test_combined_*.c` | Integration test program |

## Success Criteria

✅ All 10 tests pass  
✅ Correct output for each test case  
✅ Proper MIPS assembly generation  
✅ Nested loops with unique labels  
✅ Correct operator precedence  
✅ Left-to-right associativity  
✅ Integration of both features  

---

**Status:** All tests passing ✓  
**Date:** December 7, 2025  
**Course:** CST-405 Compiler Construction
