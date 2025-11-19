// Test File 1: Functions Only (No Control Flow)
// This test file includes:
// - Multiple function definitions with various parameters
// - Complex arithmetic expressions
// - Functions calling other functions
// - Nested function calls
// - Array declarations and operations
// - Input/output operations
// - Return statements

// Function: Calculate sum of two numbers
# add(int a, int b) {
    return a + b;
}

// Function: Calculate difference of two numbers
# subtract(int x, int y) {
    return x - y;
}

// Function: Calculate product of two numbers
# multiply(int a, int b) {
    return a * b;
}

// Function: Calculate quotient of two numbers
# divide(int numerator, int denominator) {
    return numerator / denominator;
}

// Function: Complex expression combining multiple operations
# complexExpression(int a, int b, int c) {
    int temp;
    temp = a * b + c - a / b;
    return temp;
}

// Function: Calls other functions - demonstrates function composition
# addAndMultiply(int x, int y, int z) {
    int sum;
    sum = add(x, y);
    return multiply(sum, z);
}

// Function: Nested function calls with complex expression
# nestedCalls(int a, int b, int c, int d) {
    return add(multiply(a, b), subtract(c, d));
}

// Function: Calculate average using function calls
# average(int num1, int num2, int num3) {
    int total;
    int result;
    total = add(add(num1, num2), num3);
    result = divide(total, 3);
    return result;
}

// Function: Calculate polynomial: ax^2 + bx + c
// Note: x^2 implemented as x * x since no exponentiation operator
# polynomial(int a, int x, int b, int c) {
    int xSquared;
    int term1;
    int term2;
    int result;

    xSquared = multiply(x, x);
    term1 = multiply(a, xSquared);
    term2 = multiply(b, x);
    result = add(add(term1, term2), c);

    return result;
}

// Function: Multiple arithmetic operations in sequence
# chainOperations(int value) {
    int result;
    result = value;
    result = add(result, 10);
    result = multiply(result, 2);
    result = subtract(result, 5);
    result = divide(result, 3);
    return result;
}

// Function: Deeply nested function calls
# deepNesting(int a, int b, int c) {
    return multiply(add(subtract(a, b), c), divide(add(a, c), subtract(c, b)));
}

// Function: Test complex expression with all operators
# allOperators(int w, int x, int y, int z) {
    int part1;
    int part2;
    int result;

    part1 = w * x + y - z;
    part2 = w / x - y + z;
    result = part1 * part2;

    return result;
}

// Function: Void function that performs output
# printCalculation(int a, int b) {
    int sum;
    int product;

    sum = add(a, b);
    product = multiply(a, b);

    print(sum);
    print(product);
}

// Main function: Demonstrates all features
# main() {
    int x;
    int y;
    int z;
    int result;
    int numbers[5];
    int arraySum;
    int arrayAvg;
    int poly;
    int deep;
    int chain;

    print("Function Tests Start");
    print("Enter three numbers:");
    x = 5;
    y = 10;
    z = 15;

    // Test basic arithmetic function calls
    print(add(x, y));
    print(subtract(x, y));
    print(multiply(x, y));
    print(divide(x, y));

    // Test complex expression function
    result = complexExpression(x, y, z);
    print(result);

    // Test function composition
    result = addAndMultiply(x, y, z);
    print(result);

    // Test nested function calls
    result = nestedCalls(x, y, z, x);
    print(result);

    // Test average calculation
    result = average(x, y, z);
    print(result);

    // Initialize array with complex expressions
    numbers[0] = add(x, y);
    numbers[1] = multiply(x, 2);
    numbers[2] = subtract(y, 3);
    numbers[3] = divide(z, 2);
    numbers[4] = add(x, z);

    // Test array access
    print(numbers[0]);
    print(numbers[1]);
    print(numbers[2]);
    print(numbers[3]);
    print(numbers[4]);

    // Test polynomial: 2x^2 + 3x + 5
    poly = polynomial(2, x, 3, 5);
    print(poly);

    // Test chain operations
    chain = chainOperations(x);
    print(chain);

    // Test deeply nested calls
    deep = deepNesting(x, y, z);
    print(deep);

    // Test all operators in complex expression
    result = allOperators(x, y, z, 10);
    print(result);

    // Test void functions
    printCalculation(x, y);

    // Test multiple nested calls in single statement
    print(add(multiply(x, y), divide(subtract(z, x), add(y, 2))));

    // Test expressions with literal values and function calls
    result = add(multiply(x, 5), subtract(y, 10)) + divide(z, 2);
    print(result);
}

// Call main function
main();
