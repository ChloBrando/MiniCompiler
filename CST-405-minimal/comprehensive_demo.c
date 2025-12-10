/* Comprehensive Feature Demo
 * Shows the full power of this compiler
 */

int globalResult;
int arr[10];

# sum(int a, int b) {
    int result;
    result = a + b;
    return result;
}

# processArray(int data[], int size) {
    int i;
    int total;
    
    total = 0;
    i = 0;
    
    while (i < size) {
        total = total + data[i];
        i = i + 1;
    }
    
    return total;
}

# main() {
    int x;
    int y;
    float pi;
    int i;
    
    /* Test 1: Function calls */
    x = 5;
    y = 10;
    globalResult = sum(x, y);
    print(globalResult);
    
    /* Test 2: Float support */
    pi = 3.14;
    
    /* Test 3: Arrays */
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    
    /* Test 4: Array as parameter */
    globalResult = processArray(arr, 3);
    print(globalResult);
    
    /* Test 5: Control flow */
    i = 0;
    while (i < 3) {
        if (arr[i] > 15) {
            print(arr[i]);
        }
        i = i + 1;
    }
}
