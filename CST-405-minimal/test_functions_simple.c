// Test file for function declarations and calls
// Two functions with same parameters and similar local variable names

# addNumbers(int x, float y) {
    float result;
    float temp;
    temp = 2.5;
    result = x + y + temp;
    return result;
}

# multiplyNumbers(int x, float y) {
    float result;
    float temp;
    temp = 1.5;
    result = x * y * temp;
    return result;
}

float main_result;
float second_result;

main_result = addNumbers(10, 3.14);
print(main_result);

second_result = multiplyNumbers(5, 2.0);
print(second_result);