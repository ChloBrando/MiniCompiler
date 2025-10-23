// Simple test - basic types and operations

print("=== Simple Test ===");

// Basic variables
int x;
x = 10;
print(x);

float y;
y = 3.14;
print(y);

string s;
s = "Hello";
print(s);

// Array
int arr[2];
arr[0] = 5;
arr[1] = arr[0] + 3;
print(arr[1]);

// Function
# addNums(int a, int b) {
    return a + b;
}

# return5() {
    return 5;
}

int result;
result = addNums(4, 6);
print(result);

int five;
five = return5();
print(five);

print("=== Done ===");
