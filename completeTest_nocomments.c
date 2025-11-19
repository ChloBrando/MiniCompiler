

# max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}


# min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}


# absolute(int n) {
    if (n < 0) {
        return 0 - n;
    } else {
        return n;
    }
}


# sign(int n) {
    if (n > 0) {
        return 1;
    } else {
        if (n < 0) {
            return 0 - 1;
        } else {
            return 0;
        }
    }
}

# compare(int a, int b) {
    int result;
    if (a > b) {
        result = 1;
    } else {
        if (a < b) {
            result = 0 - 1;
        } else {
            result = 0;
        }
    }
    return result;
}


# max3(int a, int b, int c) {
    int maxAB;
    if (a > b) {
        maxAB = a;
    } else {
        maxAB = b;
    }

    if (maxAB > c) {
        return maxAB;
    } else {
        return c;
    }
}


# min3(int a, int b, int c) {
    if (a < b) {
        if (a < c) {
            return a;
        } else {
            return c;
        }
    } else {
        if (b < c) {
            return b;
        } else {
            return c;
        }
    }
}


# inRange(int value, int low, int high) {
    if (value >= low) {
        if (value <= high) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}


# conditionalAdd(int a, int b) {
    if (a > 0) {
        if (b > 0) {
            return a + b;
        } else {
            return a;
        }
    } else {
        if (b > 0) {
            return b;
        } else {
            return 0;
        }
    }
}


# safeDivide(int numerator, int denominator) {
    if (denominator == 0) {
        return 0;
    } else {
        return numerator / denominator;
    }
}


# conditionalMultiply(int a, int b) {
    int result;
    if (a != 0) {
        if (b != 0) {
            result = a * b;
        } else {
            result = 0;
        }
    } else {
        result = 0;
    }
    return result;
}


# complexCondition(int x, int y, int z) {
    int result;

    if (max(x, y) > z) {
        result = max(x, y) + z;
    } else {
        if (min(x, y) < z) {
            result = min(x, y) - z;
        } else {
            result = x + y + z;
        }
    }

    return result;
}


# nestedWithFunctions(int a, int b, int c) {
    int result;

    if (absolute(a) > absolute(b)) {
        if (max(a, c) > 0) {
            result = max(a, c) + min(b, c);
        } else {
            result = absolute(a - b);
        }
    } else {
        if (compare(b, c) > 0) {
            result = b * c;
        } else {
            result = b + c;
        }
    }

    return result;
}


# conditionalArraySum(int arr[], int size, int threshold) {
    int sum;
    int temp;

    sum = 0;

    
    temp = arr[0];
    if (temp > threshold) {
        sum = sum + temp;
    }

    temp = arr[1];
    if (temp > threshold) {
        sum = sum + temp;
    }

    temp = arr[2];
    if (temp > threshold) {
        sum = sum + temp;
    }

    temp = arr[3];
    if (temp > threshold) {
        sum = sum + temp;
    }

    temp = arr[4];
    if (temp > threshold) {
        sum = sum + temp;
    }

    return sum;
}


# arrayMax(int arr[], int size) {
    int maxVal;

    maxVal = arr[0];

    if (arr[1] > maxVal) {
        maxVal = arr[1];
    }

    if (arr[2] > maxVal) {
        maxVal = arr[2];
    }

    if (arr[3] > maxVal) {
        maxVal = arr[3];
    }

    if (arr[4] > maxVal) {
        maxVal = arr[4];
    }

    return maxVal;
}


# countPositive(int arr[], int size) {
    int count;

    count = 0;

    if (arr[0] > 0) {
        count = count + 1;
    }

    if (arr[1] > 0) {
        count = count + 1;
    }

    if (arr[2] > 0) {
        count = count + 1;
    }

    if (arr[3] > 0) {
        count = count + 1;
    }

    if (arr[4] > 0) {
        count = count + 1;
    }

    return count;
}


# deeplyNested(int a, int b, int c, int d) {
    int result;

    if (a > 0) {
        if (b > 0) {
            if (c > 0) {
                if (d > 0) {
                    result = a + b + c + d;
                } else {
                    result = a + b + c;
                }
            } else {
                if (d > 0) {
                    result = a + b + d;
                } else {
                    result = a + b;
                }
            }
        } else {
            if (c > 0) {
                if (d > 0) {
                    result = a + c + d;
                } else {
                    result = a + c;
                }
            } else {
                result = a;
            }
        }
    } else {
        if (b > 0) {
            if (c > 0) {
                result = b + c;
            } else {
                result = b;
            }
        } else {
            result = 0;
        }
    }

    return result;
}


# conditionalPrint(int value, int threshold) {
    if (value > threshold) {
        print(value);
    } else {
        print(threshold);
    }
    return 0;
}


# printMax(int a, int b, int c) {
    int maximum;

    maximum = max(a, b);

    if (maximum < c) {
        print(c);
    } else {
        print(maximum);
    }
    return 0;
}


# processArray(int arr[], int size, int limit) {
    if (arrayMax(arr, size) > limit) {
        print(arrayMax(arr, size));
    } else {
        print(conditionalArraySum(arr, size, 0));
    }
    return 0;
}


# main() {
    int x;
    int y;
    int z;
    int result;
    int nums[5];
    int comparison;
    int maxValue;
    int minValue;
    int absValue;
    int signValue;
    int threshold;

    
    x = input();
    y = input();
    z = input();

    
    maxValue = max(x, y);
    print(maxValue);

    minValue = min(x, y);
    print(minValue);

    absValue = absolute(x);
    print(absValue);

    signValue = sign(x);
    print(signValue);

    
    comparison = compare(x, y);
    print(comparison);

    
    result = max3(x, y, z);
    print(result);

    result = min3(x, y, z);
    print(result);

    
    if (inRange(x, 0, 100) == 1) {
        print(x);
    } else {
        print(0);
    }

    
    result = conditionalAdd(x, y);
    print(result);

    result = safeDivide(x, y);
    print(result);

    result = conditionalMultiply(x, y);
    print(result);

    
    nums[0] = x;
    nums[1] = y;
    nums[2] = z;
    nums[3] = 0 - x;
    nums[4] = y - z;

    
    threshold = 0;
    result = conditionalArraySum(nums, 5, threshold);
    print(result);

    maxValue = arrayMax(nums, 5);
    print(maxValue);

    result = countPositive(nums, 5);
    print(result);

    
    result = complexCondition(x, y, z);
    print(result);

    result = nestedWithFunctions(x, y, z);
    print(result);

    
    result = deeplyNested(x, y, z, 5);
    print(result);

    
    if (max(x, y) > min(y, z)) {
        if (absolute(x) >= absolute(z)) {
            result = x + z;
        } else {
            result = x - z;
        }
    } else {
        if (compare(y, z) == 0) {
            result = y * z;
        } else {
            result = y / safeDivide(z, 2);
        }
    }
    print(result);

    
    conditionalPrint(x, y);
    printMax(x, y, z);
    processArray(nums, 5, 10);

    
    if (x > 0) {
        print(1);
    }

    if (y < 0) {
        print(2);
    }

    if (z == 0) {
        print(3);
    }

    if (x != y) {
        print(4);
    }

    if (x <= y) {
        print(5);
    }

    if (y >= z) {
        print(6);
    }

    
    if (max(absolute(x), absolute(y)) > min3(z, x, y)) {
        print(max(absolute(x), absolute(y)));
    } else {
        print(min3(z, x, y));
    }

    
    if (compare(max(x, y), min(y, z)) > 0) {
        if (inRange(z, min(x, y), max(x, y)) == 1) {
            result = conditionalAdd(x, y) + conditionalMultiply(y, z);
        } else {
            result = safeDivide(max3(x, y, z), min3(x, y, z));
        }
    } else {
        if (absolute(x - y) > absolute(y - z)) {
            result = absolute(x - y);
        } else {
            result = absolute(y - z);
        }
    }
    print(result);

    return 0;
}


main();
