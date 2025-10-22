// ===== COMPREHENSIVE FUNCTION TEST =====
// Tests: functions, parameters, return, scope, nested calls

// ===== TEST 1: Function with NO parameters =====
# getConstant() {
    int value;
    value = 42;
    return value;
}

// ===== TEST 2: Function with ONE parameter =====
# double(int x) {
    int result;
    result = x + x;
    return result;
}

// ===== TEST 3: Function with TWO parameters =====
# addTwo(int a, int b) {
    int sum;
    sum = a + b;
    return sum;
}

// ===== TEST 4: Function with multiple parameters =====
# addThree(int x, int y, int z) {
    int temp;
    int result;
    temp = x + y;
    result = temp + z;
    return result;
}

// ===== TEST 5: Nested function calls =====
# compute(int a, int b) {
    int doubled;
    int added;
    doubled = double(a);      // Call double() inside compute()
    added = addTwo(doubled, b);  // Call addTwo() inside compute()
    return added;
}

// ===== TEST 6: Scope testing - variable shadowing =====
int x;  // Global x
x = 100;

# testScope(int x) {
    // Parameter x shadows global x
    int y;
    y = x + 10;  // Should use parameter x, not global
    return y;
}

// ===== TEST 7: Function returning constant =====
# getFive() {
    return 5;
}

// ===== MAIN TEST EXECUTION =====

print("===== FUNCTION TESTS =====");

// Test 1: No parameters
print("Test 1: getConstant()");
int const;
const = getConstant();
print("Result: ");
print(const);
print("Expected: 42");

// Test 2: One parameter
print("Test 2: double(7)");
int doubled;
doubled = double(7);
print("Result: ");
print(doubled);
print("Expected: 14");

// Test 3: Two parameters
print("Test 3: addTwo(5, 3)");
int sum;
sum = addTwo(5, 3);
print("Result: ");
print(sum);
print("Expected: 8");

// Test 4: Multiple parameters
print("Test 4: addThree(1, 2, 3)");
int sum3;
sum3 = addThree(1, 2, 3);
print("Result: ");
print(sum3);
print("Expected: 6");

// Test 5: Nested calls
print("Test 5: compute(5, 10)");
int result;
result = compute(5, 10);
print("Result: ");
print(result);
print("Expected: 20");

// Test 6: Scope test
print("Test 6: testScope(50)");
int scoped;
scoped = testScope(50);
print("Result: ");
print(scoped);
print("Expected: 60");
print("Global x still: ");
print(x);
print("Expected: 100");

// Test 7: Return constant
print("Test 7: getFive()");
int five;
five = getFive();
print("Result: ");
print(five);
print("Expected: 5");

// Test 8: Use function result in expression
print("Test 8: addTwo(getFive(), double(3))");
int complex;
complex = addTwo(getFive(), double(3));
print("Result: ");
print(complex);
print("Expected: 11");

// Test 9: Arrays with functions
print("Test 9: Arrays with functions");
int arr[3];
arr[0] = getFive();
arr[1] = double(4);
arr[2] = addTwo(arr[0], arr[1]);
print("arr[0]: ");
print(arr[0]);
print("arr[1]: ");
print(arr[1]);
print("arr[2]: ");
print(arr[2]);
print("Expected: 5, 8, 13");

print("===== ALL TESTS COMPLETE =====");
