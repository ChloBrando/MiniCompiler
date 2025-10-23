// Test multiplication and division

// Test 1: Simple multiplication
int x;
x = 5 * 3;
print(x);  // Should print 15

// Test 2: Simple division
int y;
y = 20 / 4;
print(y);  // Should print 5

// Test 3: Mixed operations
int z;
z = 10 + 2 * 3;  // Order of operations: 10 + 6 = 16
print(z);

// Test 4: More complex
int result;
result = 100 / 10 - 5;  // 10 - 5 = 5
print(result);

// Test 5: Function with multiplication
# multiply(int a, int b) {
    return a * b;
}

int prod;
prod = multiply(7, 8);
print(prod);  // Should print 56

// Test 6: Function with division
# divide(int a, int b) {
    return a / b;
}

int quot;
quot = divide(50, 5);
print(quot);  // Should print 10
