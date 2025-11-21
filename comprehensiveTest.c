int globalCounter;
int globalArray[20];
int globalResult;

# testArithmetic(int a, int b) {
    int sum;
    int diff;
    int prod;
    int quot;
    int complex;

    sum = a + b;
    diff = a - b;
    prod = a * b;
    quot = a / b;

    complex = 2 + 3 * 4;
    complex = (2 + 3) * 4;
    complex = a * b + a / b - a + b;

    return sum + diff + prod + quot;
}

# testRelational(int x, int y) {
    int result;

    result = 0;

    if (x < y) {
        result = result + 1;
    }

    if (x <= y) {
        result = result + 10;
    }

    if (x > y) {
        result = result + 100;
    }

    if (x >= y) {
        result = result + 1000;
    }

    if (x == y) {
        result = result + 10000;
    }

    if (x != y) {
        result = result + 100000;
    }

    return result;
}

# testIfElse(int value) {
    int result;

    if (value > 0) {
        result = 1;
    }

    if (value < 0) {
        result = 0 - 1;
    } else {
        result = 0;
    }

    if (value > 100) {
        if (value > 200) {
            result = 200;
        } else {
            result = 100;
        }
    } else {
        if (value > 50) {
            result = 50;
        } else {
            result = 0;
        }
    }

    return result;
}

# testWhileLoop(int n) {
    int sum;
    int i;

    sum = 0;
    i = 1;

    while (i <= n) {
        sum = sum + i;
        i = i + 1;
    }

    return sum;
}

# testNestedLoops(int rows, int cols) {
    int total;
    int i;
    int j;

    total = 0;
    i = 0;

    while (i < rows) {
        j = 0;
        while (j < cols) {
            total = total + 1;
            j = j + 1;
        }
        i = i + 1;
    }

    return total;
}

# testArrayOperations(int arr[], int size) {
    int i;

    i = 0;
    while (i < size) {
        arr[i] = i * 2;
        i = i + 1;
    }

    i = 0;
    while (i < size) {
        arr[i] = arr[i] + 1;
        i = i + 1;
    }

    return 0;
}

# sumArray(int arr[], int size) {
    int sum;
    int i;

    sum = 0;
    i = 0;

    while (i < size) {
        sum = sum + arr[i];
        i = i + 1;
    }

    return sum;
}

# factorial(int n) {
    int result;

    if (n <= 1) {
        result = 1;
    } else {
        result = n * factorial(n - 1);
    }

    return result;
}

# fibonacci(int n) {
    int result;

    if (n <= 1) {
        result = n;
    } else {
        result = fibonacci(n - 1) + fibonacci(n - 2);
    }

    return result;
}

# power(int base, int exp) {
    int result;

    if (exp == 0) {
        result = 1;
    } else {
        result = base * power(base, exp - 1);
    }

    return result;
}

# gcd(int a, int b) {
    int remainder;

    while (b != 0) {
        remainder = a - (a / b) * b;
        a = b;
        b = remainder;
    }

    return a;
}

# linearSearch(int arr[], int size, int target) {
    int i;
    int found;

    i = 0;
    found = 0 - 1;

    while (i < size) {
        if (arr[i] == target) {
            found = i;
            i = size;
        } else {
            i = i + 1;
        }
    }

    return found;
}

# bubbleSort(int arr[], int size) {
    int i;
    int j;
    int temp;

    i = 0;
    while (i < size - 1) {
        j = 0;
        while (j < size - i - 1) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            j = j + 1;
        }
        i = i + 1;
    }

    return 0;
}

# findMax(int arr[], int size) {
    int max;
    int i;

    max = arr[0];
    i = 1;

    while (i < size) {
        if (arr[i] > max) {
            max = arr[i];
        }
        i = i + 1;
    }

    return max;
}

# findMin(int arr[], int size) {
    int min;
    int i;

    min = arr[0];
    i = 1;

    while (i < size) {
        if (arr[i] < min) {
            min = arr[i];
        }
        i = i + 1;
    }

    return min;
}

# isPrime(int n) {
    int i;
    int result;

    if (n <= 1) {
        result = 0;
    } else {
        result = 1;
        i = 2;

        while (i < n) {
            if (n / i * i == n) {
                result = 0;
                i = n;
            } else {
                i = i + 1;
            }
        }
    }

    return result;
}

# countPrimes(int limit) {
    int count;
    int i;

    count = 0;
    i = 2;

    while (i <= limit) {
        if (isPrime(i) == 1) {
            count = count + 1;
        }
        i = i + 1;
    }

    return count;
}

# reverseArray(int arr[], int size) {
    int left;
    int right;
    int temp;

    left = 0;
    right = size - 1;

    while (left < right) {
        temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        left = left + 1;
        right = right - 1;
    }

    return 0;
}

# testComplexExpressions(int a, int b, int c) {
    int result;

    result = a + b * c - a / b;
    result = ((a + b) * (c - a)) / (b + 1);
    result = a * b + c * a - b / c + a - b + c;

    return result;
}

# testVoidFunction(int x) {
    int y;

    y = x * 2;
    print(y);

    return 0;
}

# printArray(int arr[], int size) {
    int i;

    i = 0;
    while (i < size) {
        print(arr[i]);
        i = i + 1;
    }

    return 0;
}

# multiply3(int a, int b, int c) {
    return a * b * c;
}

# add4(int a, int b, int c, int d) {
    return a + b + c + d;
}

# max3(int a, int b, int c) {
    int max;

    max = a;

    if (b > max) {
        max = b;
    }

    if (c > max) {
        max = c;
    }

    return max;
}

# fillArray(int arr[], int size, int value) {
    int i;

    i = 0;
    while (i < size) {
        arr[i] = value;
        i = i + 1;
    }

    return 0;
}

# copyArray(int source[], int dest[], int size) {
    int i;

    i = 0;
    while (i < size) {
        dest[i] = source[i];
        i = i + 1;
    }

    return 0;
}

# arrayEqual(int arr1[], int arr2[], int size) {
    int i;
    int equal;

    equal = 1;
    i = 0;

    while (i < size) {
        if (arr1[i] != arr2[i]) {
            equal = 0;
            i = size;
        } else {
            i = i + 1;
        }
    }

    return equal;
}

# absoluteValue(int x) {
    int result;

    if (x < 0) {
        result = 0 - x;
    } else {
        result = x;
    }

    return result;
}

# sign(int x) {
    int result;

    if (x < 0) {
        result = 0 - 1;
    } else {
        if (x > 0) {
            result = 1;
        } else {
            result = 0;
        }
    }

    return result;
}

# sumOfSquares(int n) {
    int sum;
    int i;

    sum = 0;
    i = 1;

    while (i <= n) {
        sum = sum + i * i;
        i = i + 1;
    }

    return sum;
}

# sumOfCubes(int n) {
    int sum;
    int i;

    sum = 0;
    i = 1;

    while (i <= n) {
        sum = sum + i * i * i;
        i = i + 1;
    }

    return sum;
}

# calculateMean(int arr[], int size) {
    int sum;
    int i;

    sum = 0;
    i = 0;

    while (i < size) {
        sum = sum + arr[i];
        i = i + 1;
    }

    return sum / size;
}

# countOccurrences(int arr[], int size, int value) {
    int count;
    int i;

    count = 0;
    i = 0;

    while (i < size) {
        if (arr[i] == value) {
            count = count + 1;
        }
        i = i + 1;
    }

    return count;
}

# leftShift(int n, int bits) {
    int result;
    int i;

    result = n;
    i = 0;

    while (i < bits) {
        result = result * 2;
        i = i + 1;
    }

    return result;
}

# rightShift(int n, int bits) {
    int result;
    int i;

    result = n;
    i = 0;

    while (i < bits) {
        result = result / 2;
        i = i + 1;
    }

    return result;
}

# arrayLength(int arr[], int maxSize) {
    int length;

    length = 0;

    while (length < maxSize) {
        if (arr[length] == 0) {
            length = maxSize;
        } else {
            length = length + 1;
        }
    }

    return length;
}

# main() {
    int testArray[10];
    int testArray2[10];
    int i;
    int result;
    int a;
    int b;
    int choice;

    globalCounter = 0;

    print(1);
    result = testArithmetic(10, 5);
    print(result);

    print(2);
    result = testRelational(5, 10);
    print(result);

    print(3);
    result = testIfElse(75);
    print(result);

    print(4);
    result = testWhileLoop(10);
    print(result);

    print(5);
    result = testNestedLoops(5, 5);
    print(result);

    print(6);
    testArrayOperations(testArray, 10);
    result = sumArray(testArray, 10);
    print(result);

    print(7);
    result = factorial(5);
    print(result);

    print(8);
    result = fibonacci(7);
    print(result);

    print(9);
    result = power(2, 5);
    print(result);

    print(10);
    result = gcd(48, 18);
    print(result);

    print(11);
    i = 0;
    while (i < 10) {
        testArray[i] = i * 3;
        i = i + 1;
    }
    result = linearSearch(testArray, 10, 15);
    print(result);

    print(12);
    testArray[0] = 5;
    testArray[1] = 2;
    testArray[2] = 8;
    testArray[3] = 1;
    testArray[4] = 9;
    bubbleSort(testArray, 5);
    printArray(testArray, 5);

    print(13);
    result = findMax(testArray, 5);
    print(result);
    result = findMin(testArray, 5);
    print(result);

    print(14);
    result = isPrime(17);
    print(result);
    result = isPrime(18);
    print(result);

    print(15);
    result = countPrimes(20);
    print(result);

    print(16);
    i = 0;
    while (i < 5) {
        testArray[i] = i + 1;
        i = i + 1;
    }
    reverseArray(testArray, 5);
    printArray(testArray, 5);

    print(17);
    result = multiply3(2, 3, 4);
    print(result);
    result = add4(1, 2, 3, 4);
    print(result);
    result = max3(5, 9, 3);
    print(result);

    print(18);
    fillArray(testArray, 10, 7);
    copyArray(testArray, testArray2, 10);
    result = arrayEqual(testArray, testArray2, 10);
    print(result);

    print(19);
    result = absoluteValue(0 - 15);
    print(result);
    result = sign(0 - 5);
    print(result);
    result = sign(5);
    print(result);
    result = sign(0);
    print(result);

    print(20);
    result = sumOfSquares(5);
    print(result);
    result = sumOfCubes(5);
    print(result);

    print(21);
    i = 0;
    while (i < 5) {
        testArray[i] = (i + 1) * 2;
        i = i + 1;
    }
    result = calculateMean(testArray, 5);
    print(result);
    testArray[0] = 5;
    testArray[1] = 5;
    testArray[2] = 3;
    testArray[3] = 5;
    testArray[4] = 7;
    result = countOccurrences(testArray, 5, 5);
    print(result);

    print(22);
    result = leftShift(3, 2);
    print(result);
    result = rightShift(16, 2);
    print(result);

    print(23);
    result = testComplexExpressions(10, 5, 3);
    print(result);

    print(24);
    globalCounter = 100;
    globalArray[0] = 10;
    globalArray[1] = 20;
    globalArray[2] = 30;
    print(globalCounter);
    print(globalArray[0] + globalArray[1] + globalArray[2]);

    print(25);
    testVoidFunction(5);

    print(999);

    return 0;
}

main();
