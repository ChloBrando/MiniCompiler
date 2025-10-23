// ===== COMPREHENSIVE FLOAT TEST =====
// Tests: float variables, literals, arithmetic, mixed operations, functions

print("===== FLOAT TESTS =====");

// ===== TEST 1: Float declaration and assignment =====
print("Test 1: Float declaration and assignment");
float x;
x = 3.14;
print("x = ");
print(x);
print("Expected: 3.14");

// ===== TEST 2: Float arithmetic - addition =====
print("Test 2: Float addition");
float a;
float b;
float sum;
a = 2.5;
b = 3.7;
sum = a + b;
print("a = ");
print(a);
print("b = ");
print(b);
print("sum = ");
print(sum);
print("Expected: 6.2");

// ===== TEST 3: Float arithmetic - subtraction =====
print("Test 3: Float subtraction");
float c;
float d;
float diff;
c = 10.5;
d = 3.2;
diff = c - d;
print("c = ");
print(c);
print("d = ");
print(d);
print("diff = ");
print(diff);
print("Expected: 7.3");

// ===== TEST 4: Mixed int and float operations =====
print("Test 4: Mixed int and float");
int intVal;
float floatVal;
float result;
intVal = 5;
floatVal = 2.5;
result = floatVal + intVal;
print("intVal = ");
print(intVal);
print("floatVal = ");
print(floatVal);
print("result (float + int) = ");
print(result);
print("Expected: 7.5");

// ===== TEST 5: Int assigned to float (implicit conversion) =====
print("Test 5: Int to float conversion");
float converted;
int original;
original = 42;
converted = original;
print("original (int) = ");
print(original);
print("converted (float) = ");
print(converted);
print("Expected: 42.0");

// ===== TEST 6: Complex expression =====
print("Test 6: Complex expression");
float e;
float f;
float g;
float complex;
e = 1.5;
f = 2.0;
g = 3.5;
complex = e + f - g;
print("e = ");
print(e);
print("f = ");
print(f);
print("g = ");
print(g);
print("complex = e + f - g = ");
print(complex);
print("Expected: 0.0");

// ===== TEST 7: Function with float parameter =====
# doubleFloat(float val) {
    float doubled;
    doubled = val + val;
    return doubled;
}

print("Test 7: Function with float parameter");
float testVal;
float doubled;
testVal = 4.5;
doubled = doubleFloat(testVal);
print("testVal = ");
print(testVal);
print("doubled = ");
print(doubled);
print("Expected: 9.0");

// ===== TEST 8: Function with multiple float parameters =====
# addFloats(float x, float y) {
    float sum;
    sum = x + y;
    return sum;
}

print("Test 8: Function with multiple float params");
float result1;
result1 = addFloats(1.5, 2.5);
print("addFloats(1.5, 2.5) = ");
print(result1);
print("Expected: 4.0");

// ===== TEST 9: Mixed parameter types =====
# mixedAdd(int i, float f) {
    float result;
    result = i + f;
    return result;
}

print("Test 9: Mixed parameter types (int, float)");
float mixedResult;
mixedResult = mixedAdd(3, 2.7);
print("mixedAdd(3, 2.7) = ");
print(mixedResult);
print("Expected: 5.7");

// ===== TEST 10: Negative floats =====
print("Test 10: Negative floats");
float neg1;
float neg2;
float negSum;
neg1 = 5.5;
neg2 = 8.3;
negSum = neg1 - neg2;
print("neg1 = ");
print(neg1);
print("neg2 = ");
print(neg2);
print("negSum = neg1 - neg2 = ");
print(negSum);
print("Expected: -2.8");

print("===== ALL FLOAT TESTS COMPLETE =====");
