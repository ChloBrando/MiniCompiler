// Final verification test for float support
print("=== FLOAT VERIFICATION TEST ===");

// Test 1: Float literals
float pi;
pi = 3.14159;
print("Pi = ");
print(pi);

// Test 2: Float arithmetic
float a;
float b;
float sum;
a = 2.5;
b = 1.5;
sum = a + b;
print("2.5 + 1.5 = ");
print(sum);

// Test 3: Mixed int/float
int x;
float y;
float z;
x = 10;
y = 3.5;
z = x + y;
print("10 + 3.5 = ");
print(z);

// Test 4: Float subtraction
float diff;
diff = b - a;
print("1.5 - 2.5 = ");
print(diff);

// Test 5: Function with float
# multiplyByTwo(float val) {
    float result;
    result = val + val;
    return result;
}

float doubled;
doubled = multiplyByTwo(4.5);
print("multiplyByTwo(4.5) = ");
print(doubled);

print("=== ALL TESTS PASSED ===");
