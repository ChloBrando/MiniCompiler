// Test 1: Simple Function (No Parameters)
# getNumber() {
    return 42;
}

int x;
x = getNumber();
print(x);

// Test 2: Function with Parameters
# double(int n) {
    return n + n;
}

int result;
result = double(21);
print(result);

// Test 3: Multiple Parameters
# addTwo(int a, int b) {
    return a + b;
}

print(addTwo(10, 32));

// Test 4: Nested Function Calls
# addThree(int a, int b, int c) {
    int temp;
    temp = addTwo(a, b);
    return addTwo(temp, c);
}

print(addThree(1, 2, 3));

// Test 5: Scope Testing
int global_x;
global_x = 5;

# func(int x) {
    int y;
    y = x + 10;
    return y;
}

print(func(global_x));
print(global_x);
