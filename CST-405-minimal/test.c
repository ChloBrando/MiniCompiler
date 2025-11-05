int parameter;
parameter = 10;

# bigger(int number){
    int bNumber;
    bNumber = number + number;
    return bNumber;
}

# smaller(int number){
    int sNumber;
    sNumber = number - 5;
    return sNumber;
}

int resultBigger;
resultBigger = bigger(parameter);
print(resultBigger);

int resultSmaller;
resultSmaller = smaller(parameter);
print(resultSmaller);



// Basic Array - Declaration and Assignment
int numbers[5];
numbers[0] = 10;
numbers[1] = 20;
numbers[2] = 30;
numbers[3] = 40;
numbers[4] = 50;

// Print array elements
print(numbers[0]);  // Prints 10
print(numbers[2]);  // Prints 30
print(numbers[4]);  // Prints 50