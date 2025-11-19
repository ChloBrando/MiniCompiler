// Test File: If Statements and Comparison Operators
// This test file includes:
// - Basic if-then statements
// - If-then-else statements
// - Nested if statements (multiple levels)
// - All comparison operators: <, >, <=, >=, ==, !=
// NOTE: Boolean operators (&&, ||, !) need to be implemented in scanner.l first

int x;
int y;
int z;

// Test 1: Basic if-then statement with greater than
print("=== Test 1: Basic if-then (>) ===");
x = 10;
if (x > 5) {
    print("Success: x is greater than 5");
}

// Test 2: Basic if-then statement that should NOT execute
print("=== Test 2: If-then false condition ===");
x = 3;
if (x > 5) {
    print("ERROR: This should not print");
}
print("Success: False condition correctly skipped");

// Test 3: If-then-else with true condition
print("=== Test 3: If-then-else (true branch) ===");
x = 10;
if (x > 5) {
    print("Success: Took the THEN branch");
} else {
    print("ERROR: Should not reach ELSE branch");
}

// Test 4: If-then-else with false condition
print("=== Test 4: If-then-else (else branch) ===");
y = 3;
if (y > 5) {
    print("ERROR: Should not reach THEN branch");
} else {
    print("Success: Took the ELSE branch");
}

// Test 5: Less than operator
print("=== Test 5: Less than (<) ===");
x = 5;
if (x < 10) {
    print("Success: x is less than 10");
}

// Test 6: Less than or equal operator (equal case)
print("=== Test 6: Less than or equal (<=) equal ===");
x = 10;
if (x <= 10) {
    print("Success: x <= 10 when x equals 10");
}

// Test 7: Less than or equal operator (less case)
print("=== Test 7: Less than or equal (<=) less ===");
x = 8;
if (x <= 10) {
    print("Success: x <= 10 when x is 8");
}

// Test 8: Greater than or equal operator (equal case)
print("=== Test 8: Greater than or equal (>=) equal ===");
x = 10;
if (x >= 10) {
    print("Success: x >= 10 when x equals 10");
}

// Test 9: Greater than or equal operator (greater case)
print("=== Test 9: Greater than or equal (>=) greater ===");
x = 15;
if (x >= 10) {
    print("Success: x >= 10 when x is 15");
}

// Test 10: Equal to operator (true)
print("=== Test 10: Equal to (==) true ===");
x = 10;
if (x == 10) {
    print("Success: x equals 10");
}

// Test 11: Equal to operator (false)
print("=== Test 11: Equal to (==) false ===");
x = 10;
if (x == 15) {
    print("ERROR: Should not execute");
} else {
    print("Success: x does not equal 15");
}

// Test 12: Not equal to operator (true)
print("=== Test 12: Not equal to (!=) true ===");
x = 10;
if (x != 15) {
    print("Success: x is not equal to 15");
}

// Test 13: Not equal to operator (false)
print("=== Test 13: Not equal to (!=) false ===");
x = 10;
if (x != 10) {
    print("ERROR: Should not execute");
} else {
    print("Success: !(x != 10) means x == 10");
}

// Test 14: Nested if statements (2 levels)
print("=== Test 14: Nested if (2 levels) ===");
x = 15;
y = 25;
if (x > 10) {
    print("Outer: x > 10 is TRUE");
    if (y > 20) {
        print("Inner: y > 20 is TRUE");
    }
}

// Test 15: Nested if statements (2 levels) with else
print("=== Test 15: Nested if with else ===");
x = 15;
y = 15;
if (x > 10) {
    print("Outer: x > 10 is TRUE");
    if (y > 20) {
        print("ERROR: Should not execute");
    } else {
        print("Inner else: y is NOT > 20");
    }
}

// Test 16: Nested if statements (3 levels)
print("=== Test 16: Nested if (3 levels) ===");
x = 15;
y = 25;
z = 35;
if (x > 10) {
    print("Level 1: x > 10");
    if (y > 20) {
        print("Level 2: y > 20");
        if (z > 30) {
            print("Level 3: z > 30");
        }
    }
}

// Test 17: Nested if-else (path 1)
print("=== Test 17: Nested if-else (path 1) ===");
x = 15;
y = 25;
if (x > 10) {
    if (y > 20) {
        print("Success: Path x>10 THEN y>20");
    } else {
        print("ERROR: Wrong path");
    }
} else {
    print("ERROR: Wrong path");
}

// Test 18: Nested if-else (path 2)
print("=== Test 18: Nested if-else (path 2) ===");
x = 8;
y = 15;
if (x > 10) {
    print("ERROR: Wrong path");
} else {
    if (y < 20) {
        print("Success: Path x<=10 THEN y<20");
    } else {
        print("ERROR: Wrong path");
    }
}

// Test 19: If with arithmetic in condition
print("=== Test 19: Arithmetic in condition ===");
x = 5;
y = 3;
if (x + y > 7) {
    print("Success: (5 + 3) > 7 is true");
}

// Test 20: If with variable comparison
print("=== Test 20: Variable-to-variable comparison ===");
x = 10;
y = 10;
if (x == y) {
    print("Success: x == y when both are 10");
}

// Test 21: Sequential if statements (independent)
print("=== Test 21: Sequential independent ifs ===");
x = 10;
if (x > 5) {
    print("First if: x > 5 TRUE");
}
if (x < 15) {
    print("Second if: x < 15 TRUE");
}
if (x == 10) {
    print("Third if: x == 10 TRUE");
}

// Test 22: If-else chain (mutually exclusive)
print("=== Test 22: If-else chain ===");
x = 15;
if (x < 10) {
    print("ERROR: x < 10");
} else {
    if (x < 20) {
        print("Success: 10 <= x < 20");
    } else {
        print("ERROR: x >= 20");
    }
}



// Test 24: Multiple else branches
print("=== Test 23: Multiple else branches ===");
x = 25;
if (x < 10) {
    print("ERROR: Range 1");
} else {
    if (x < 20) {
        print("ERROR: Range 2");
    } else {
        if (x < 30) {
            print("Success: Range 3 (20-30)");
        } else {
            print("ERROR: Range 4");
        }
    }
}

// Test 25: All comparison operators in sequence
print("=== Test 24: All six comparison operators ===");
x = 10;
y = 20;
if (x < y) {
    print("1. x < y TRUE");
}
if (x <= 10) {
    print("2. x <= 10 TRUE");
}
if (y > x) {
    print("3. y > x TRUE");
}
if (y >= 20) {
    print("4. y >= 20 TRUE");
}
if (x == 10) {
    print("5. x == 10 TRUE");
}
if (x != y) {
    print("6. x != y TRUE");
}

print("=== All 25 tests complete ===");
print("Note: Boolean operators (&&, ||, !) need scanner.l implementation");
