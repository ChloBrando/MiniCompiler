.data

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400
    j main_code        # Jump to main program


# Function: testArithmetic
func_testArithmetic:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    # Function body
    # Declared sum at offset 8
    # Declared diff at offset 12
    # Declared prod at offset 16
    # Declared quot at offset 20
    # Declared complex at offset 24
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Addition
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Subtraction
    sub $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Multiplication
    mul $t0, $t0, $t1
    sw $t0, 16($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Division
    div $t0, $t1      # Divide: result in LO
    mflo $t0           # Move quotient from LO
    sw $t0, 20($sp)
    li $t0, 2
    li $t1, 3
    li $t2, 4
    # Multiplication
    mul $t1, $t1, $t2
    # Addition
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    li $t0, 2
    li $t1, 3
    # Addition
    add $t0, $t0, $t1
    li $t1, 4
    # Multiplication
    mul $t0, $t0, $t1
    sw $t0, 24($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Multiplication
    mul $t0, $t0, $t1
    lw $t1, 0($sp)
    lw $t2, 4($sp)
    # Division
    div $t1, $t2      # Divide: result in LO
    mflo $t1           # Move quotient from LO
    # Addition
    add $t0, $t0, $t1
    lw $t1, 0($sp)
    # Subtraction
    sub $t0, $t0, $t1
    lw $t1, 4($sp)
    # Addition
    add $t0, $t0, $t1
    sw $t0, 24($sp)
    # Return statement
    lw $t0, 8($sp)
    lw $t1, 12($sp)
    # Addition
    add $t0, $t0, $t1
    lw $t1, 16($sp)
    # Addition
    add $t0, $t0, $t1
    lw $t1, 20($sp)
    # Addition
    add $t0, $t0, $t1
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_testArithmetic_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: testRelational
func_testRelational:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'x'
    sw $a1, 4($sp)     # Store param 'y'
    # Function body
    # Declared result at offset 8
    li $t1, 0
    sw $t1, 8($sp)
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, endif_label_0
    lw $t3, 8($sp)
    li $t4, 1
    # Addition
    add $t3, $t3, $t4
    sw $t3, 8($sp)
endif_label_0:
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer less than or equal
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    beq $t2, $zero, endif_label_1
    lw $t3, 8($sp)
    li $t4, 10
    # Addition
    add $t3, $t3, $t4
    sw $t3, 8($sp)
endif_label_1:
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, endif_label_2
    lw $t3, 8($sp)
    li $t4, 100
    # Addition
    add $t3, $t3, $t4
    sw $t3, 8($sp)
endif_label_2:
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer greater than or equal
    slt $t2, $t0, $t1
    xori $t2, $t2, 1
    beq $t2, $zero, endif_label_3
    lw $t3, 8($sp)
    li $t4, 1000
    # Addition
    add $t3, $t3, $t4
    sw $t3, 8($sp)
endif_label_3:
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer equal
    xor $t2, $t0, $t1
    sltiu $t2, $t2, 1
    beq $t2, $zero, endif_label_4
    lw $t3, 8($sp)
    li $t4, 10000
    # Addition
    add $t3, $t3, $t4
    sw $t3, 8($sp)
endif_label_4:
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer not equal
    xor $t2, $t0, $t1
    sltu $t2, $zero, $t2
    beq $t2, $zero, endif_label_5
    lw $t3, 8($sp)
    li $t4, 100000
    # Addition
    add $t3, $t3, $t4
    sw $t3, 8($sp)
endif_label_5:
    # Return statement
    lw $t0, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_testRelational_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: testIfElse
func_testIfElse:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'value'
    # Function body
    # Declared result at offset 4
    # If statement
    lw $t1, 0($sp)
    li $t2, 0
    # Integer greater than
    slt $t3, $t2, $t1
    beq $t3, $zero, endif_label_6
    li $t4, 1
    sw $t4, 4($sp)
endif_label_6:
    # If statement
    lw $t0, 0($sp)
    li $t1, 0
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, else_label_7
    li $t3, 0
    li $t4, 1
    # Subtraction
    sub $t3, $t3, $t4
    sw $t3, 4($sp)
    j endif_label_7
else_label_7:
    li $t0, 0
    sw $t0, 4($sp)
endif_label_7:
    # If statement
    lw $t0, 0($sp)
    li $t1, 100
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, else_label_8
    # If statement
    lw $t3, 0($sp)
    li $t4, 200
    # Integer greater than
    slt $t5, $t4, $t3
    beq $t5, $zero, else_label_9
    li $t6, 200
    sw $t6, 4($sp)
    j endif_label_9
else_label_9:
    li $t0, 100
    sw $t0, 4($sp)
endif_label_9:
    j endif_label_8
else_label_8:
    # If statement
    lw $t0, 0($sp)
    li $t1, 50
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, else_label_10
    li $t3, 50
    sw $t3, 4($sp)
    j endif_label_10
else_label_10:
    li $t0, 0
    sw $t0, 4($sp)
endif_label_10:
endif_label_8:
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_testIfElse_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: testWhileLoop
func_testWhileLoop:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'n'
    # Function body
    # Declared sum at offset 4
    # Declared i at offset 8
    li $t1, 0
    sw $t1, 4($sp)
    li $t0, 1
    sw $t0, 8($sp)
    # While loop
while_start_0:
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    # Integer less than or equal
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    beq $t2, $zero, while_end_0
    lw $t3, 4($sp)
    lw $t4, 8($sp)
    # Addition
    add $t3, $t3, $t4
    sw $t3, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    j while_start_0
while_end_0:
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_testWhileLoop_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: testNestedLoops
func_testNestedLoops:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'rows'
    sw $a1, 4($sp)     # Store param 'cols'
    # Function body
    # Declared total at offset 8
    # Declared i at offset 12
    # Declared j at offset 16
    li $t1, 0
    sw $t1, 8($sp)
    li $t0, 0
    sw $t0, 12($sp)
    # While loop
while_start_1:
    lw $t0, 12($sp)
    lw $t1, 0($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_1
    li $t3, 0
    sw $t3, 16($sp)
    # While loop
while_start_2:
    lw $t0, 16($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_2
    lw $t3, 8($sp)
    li $t4, 1
    # Addition
    add $t3, $t3, $t4
    sw $t3, 8($sp)
    lw $t0, 16($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    j while_start_2
while_end_2:
    lw $t0, 12($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    j while_start_1
while_end_1:
    # Return statement
    lw $t0, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_testNestedLoops_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: testArrayOperations
func_testArrayOperations:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'arr'
    sw $a1, 4($sp)     # Store param 'size'
    # Function body
    # Declared i at offset 8
    li $t1, 0
    sw $t1, 8($sp)
    # While loop
while_start_3:
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_3
    lw $t5, 8($sp)
    lw $t6, 8($sp)
    li $t7, 2
    # Multiplication
    mul $t6, $t6, $t0
    # Array assignment: arr[index] = value
    lw $t4, 0($sp)     # load array pointer (parameter)
    sll $t5, $t5, 2    # index * 4
    add $t3, $t4, $t5 # element address
    sw $t6, 0($t3)     # store value
    lw $t0, 8($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    j while_start_3
while_end_3:
    li $t0, 0
    sw $t0, 8($sp)
    # While loop
while_start_4:
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_4
    lw $t5, 8($sp)
    lw $t7, 8($sp)
    # Array access: arr[index]
    lw $t6, 0($sp)     # load array pointer (parameter)
    sll $t7, $t7, 2    # index * 4
    add $t6, $t6, $t7 # element address
    lw $t6, 0($t6)     # load value
    li $t7, 1
    # Addition
    add $t6, $t6, $t0
    # Array assignment: arr[index] = value
    lw $t4, 0($sp)     # load array pointer (parameter)
    sll $t5, $t5, 2    # index * 4
    add $t3, $t4, $t5 # element address
    sw $t6, 0($t3)     # store value
    lw $t0, 8($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    j while_start_4
while_end_4:
    # Return statement
    li $t0, 0
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_testArrayOperations_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: sumArray
func_sumArray:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'arr'
    sw $a1, 4($sp)     # Store param 'size'
    # Function body
    # Declared sum at offset 8
    # Declared i at offset 12
    li $t1, 0
    sw $t1, 8($sp)
    li $t0, 0
    sw $t0, 12($sp)
    # While loop
while_start_5:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_5
    lw $t3, 8($sp)
    lw $t5, 12($sp)
    # Array access: arr[index]
    lw $t4, 0($sp)     # load array pointer (parameter)
    sll $t5, $t5, 2    # index * 4
    add $t4, $t4, $t5 # element address
    lw $t4, 0($t4)     # load value
    # Addition
    add $t3, $t3, $t4
    sw $t3, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    j while_start_5
while_end_5:
    # Return statement
    lw $t0, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_sumArray_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: factorial
func_factorial:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'n'
    # Function body
    # Declared result at offset 4
    # If statement
    lw $t1, 0($sp)
    li $t2, 1
    # Integer less than or equal
    slt $t3, $t2, $t1
    xori $t3, $t3, 1
    beq $t3, $zero, else_label_11
    li $t4, 1
    sw $t4, 4($sp)
    j endif_label_11
else_label_11:
    lw $t0, 0($sp)
    # Function call: factorial
    lw $t1, 0($sp)
    li $t2, 1
    # Subtraction
    sub $t1, $t1, $t2
    move $a0, $t1    # Arg 0
    jal func_factorial             # Call function
    move $t2, $v0      # Get return value
    # Multiplication
    mul $t0, $t0, $t2
    sw $t0, 4($sp)
endif_label_11:
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_factorial_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: fibonacci
func_fibonacci:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'n'
    # Function body
    # Declared result at offset 4
    # If statement
    lw $t1, 0($sp)
    li $t2, 1
    # Integer less than or equal
    slt $t3, $t2, $t1
    xori $t3, $t3, 1
    beq $t3, $zero, else_label_12
    lw $t4, 0($sp)
    sw $t4, 4($sp)
    j endif_label_12
else_label_12:
    # Function call: fibonacci
    lw $t0, 0($sp)
    li $t1, 1
    # Subtraction
    sub $t0, $t0, $t1
    move $a0, $t0    # Arg 0
    jal func_fibonacci             # Call function
    move $t1, $v0      # Get return value
    # Function call: fibonacci
    lw $t2, 0($sp)
    li $t3, 2
    # Subtraction
    sub $t2, $t2, $t3
    move $a0, $t2    # Arg 0
    jal func_fibonacci             # Call function
    move $t3, $v0      # Get return value
    # Addition
    add $t1, $t1, $t3
    sw $t1, 4($sp)
endif_label_12:
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_fibonacci_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: power
func_power:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'base'
    sw $a1, 4($sp)     # Store param 'exp'
    # Function body
    # Declared result at offset 8
    # If statement
    lw $t1, 4($sp)
    li $t2, 0
    # Integer equal
    xor $t3, $t1, $t2
    sltiu $t3, $t3, 1
    beq $t3, $zero, else_label_13
    li $t4, 1
    sw $t4, 8($sp)
    j endif_label_13
else_label_13:
    lw $t0, 0($sp)
    # Function call: power
    lw $t1, 0($sp)
    move $a0, $t1    # Arg 0
    lw $t2, 4($sp)
    li $t3, 1
    # Subtraction
    sub $t2, $t2, $t3
    move $a1, $t2    # Arg 1
    jal func_power             # Call function
    move $t3, $v0      # Get return value
    # Multiplication
    mul $t0, $t0, $t3
    sw $t0, 8($sp)
endif_label_13:
    # Return statement
    lw $t0, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_power_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: gcd
func_gcd:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    # Function body
    # Declared remainder at offset 8
    # While loop
while_start_6:
    lw $t1, 4($sp)
    li $t2, 0
    # Integer not equal
    xor $t3, $t1, $t2
    sltu $t3, $zero, $t3
    beq $t3, $zero, while_end_6
    lw $t4, 0($sp)
    lw $t5, 0($sp)
    lw $t6, 4($sp)
    # Division
    div $t5, $t6      # Divide: result in LO
    mflo $t5           # Move quotient from LO
    lw $t6, 4($sp)
    # Multiplication
    mul $t5, $t5, $t6
    # Subtraction
    sub $t4, $t4, $t5
    sw $t4, 8($sp)
    lw $t0, 4($sp)
    sw $t0, 0($sp)
    lw $t0, 8($sp)
    sw $t0, 4($sp)
    j while_start_6
while_end_6:
    # Return statement
    lw $t0, 0($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_gcd_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: linearSearch
func_linearSearch:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'arr'
    sw $a1, 4($sp)     # Store param 'size'
    sw $a2, 8($sp)     # Store param 'target'
    # Function body
    # Declared i at offset 12
    # Declared found at offset 16
    li $t1, 0
    sw $t1, 12($sp)
    li $t0, 0
    li $t1, 1
    # Subtraction
    sub $t0, $t0, $t1
    sw $t0, 16($sp)
    # While loop
while_start_7:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_7
    # If statement
    lw $t4, 12($sp)
    # Array access: arr[index]
    lw $t3, 0($sp)     # load array pointer (parameter)
    sll $t4, $t4, 2    # index * 4
    add $t3, $t3, $t4 # element address
    lw $t3, 0($t3)     # load value
    lw $t4, 8($sp)
    # Integer equal
    xor $t5, $t3, $t4
    sltiu $t5, $t5, 1
    beq $t5, $zero, else_label_14
    lw $t6, 12($sp)
    sw $t6, 16($sp)
    lw $t0, 4($sp)
    sw $t0, 12($sp)
    j endif_label_14
else_label_14:
    lw $t0, 12($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
endif_label_14:
    j while_start_7
while_end_7:
    # Return statement
    lw $t0, 16($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_linearSearch_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: bubbleSort
func_bubbleSort:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'arr'
    sw $a1, 4($sp)     # Store param 'size'
    # Function body
    # Declared i at offset 8
    # Declared j at offset 12
    # Declared temp at offset 16
    li $t1, 0
    sw $t1, 8($sp)
    # While loop
while_start_8:
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    li $t2, 1
    # Subtraction
    sub $t1, $t1, $t2
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_8
    li $t3, 0
    sw $t3, 12($sp)
    # While loop
while_start_9:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    lw $t2, 8($sp)
    # Subtraction
    sub $t1, $t1, $t2
    li $t2, 1
    # Subtraction
    sub $t1, $t1, $t2
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_9
    # If statement
    lw $t4, 12($sp)
    # Array access: arr[index]
    lw $t3, 0($sp)     # load array pointer (parameter)
    sll $t4, $t4, 2    # index * 4
    add $t3, $t3, $t4 # element address
    lw $t3, 0($t3)     # load value
    lw $t5, 12($sp)
    li $t6, 1
    # Addition
    add $t5, $t5, $t6
    # Array access: arr[index]
    lw $t4, 0($sp)     # load array pointer (parameter)
    sll $t5, $t5, 2    # index * 4
    add $t4, $t4, $t5 # element address
    lw $t4, 0($t4)     # load value
    # Integer greater than
    slt $t5, $t4, $t3
    beq $t5, $zero, endif_label_15
    lw $t7, 12($sp)
    # Array access: arr[index]
    lw $t6, 0($sp)     # load array pointer (parameter)
    sll $t7, $t7, 2    # index * 4
    add $t6, $t6, $t7 # element address
    lw $t6, 0($t6)     # load value
    sw $t6, 16($sp)
    lw $t2, 12($sp)
    lw $t4, 12($sp)
    li $t5, 1
    # Addition
    add $t4, $t4, $t5
    # Array access: arr[index]
    lw $t3, 0($sp)     # load array pointer (parameter)
    sll $t4, $t4, 2    # index * 4
    add $t3, $t3, $t4 # element address
    lw $t3, 0($t3)     # load value
    # Array assignment: arr[index] = value
    lw $t1, 0($sp)     # load array pointer (parameter)
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    lw $t2, 12($sp)
    li $t3, 1
    # Addition
    add $t2, $t2, $t3
    lw $t3, 16($sp)
    # Array assignment: arr[index] = value
    lw $t1, 0($sp)     # load array pointer (parameter)
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
endif_label_15:
    lw $t0, 12($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    j while_start_9
while_end_9:
    lw $t0, 8($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    j while_start_8
while_end_8:
    # Return statement
    li $t0, 0
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_bubbleSort_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: findMax
func_findMax:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'arr'
    sw $a1, 4($sp)     # Store param 'size'
    # Function body
    # Declared max at offset 8
    # Declared i at offset 12
    li $t2, 0
    # Array access: arr[index]
    lw $t1, 0($sp)     # load array pointer (parameter)
    sll $t2, $t2, 2    # index * 4
    add $t1, $t1, $t2 # element address
    lw $t1, 0($t1)     # load value
    sw $t1, 8($sp)
    li $t0, 1
    sw $t0, 12($sp)
    # While loop
while_start_10:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_10
    # If statement
    lw $t4, 12($sp)
    # Array access: arr[index]
    lw $t3, 0($sp)     # load array pointer (parameter)
    sll $t4, $t4, 2    # index * 4
    add $t3, $t3, $t4 # element address
    lw $t3, 0($t3)     # load value
    lw $t4, 8($sp)
    # Integer greater than
    slt $t5, $t4, $t3
    beq $t5, $zero, endif_label_16
    lw $t7, 12($sp)
    # Array access: arr[index]
    lw $t6, 0($sp)     # load array pointer (parameter)
    sll $t7, $t7, 2    # index * 4
    add $t6, $t6, $t7 # element address
    lw $t6, 0($t6)     # load value
    sw $t6, 8($sp)
endif_label_16:
    lw $t0, 12($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    j while_start_10
while_end_10:
    # Return statement
    lw $t0, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_findMax_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: findMin
func_findMin:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'arr'
    sw $a1, 4($sp)     # Store param 'size'
    # Function body
    # Declared min at offset 8
    # Declared i at offset 12
    li $t2, 0
    # Array access: arr[index]
    lw $t1, 0($sp)     # load array pointer (parameter)
    sll $t2, $t2, 2    # index * 4
    add $t1, $t1, $t2 # element address
    lw $t1, 0($t1)     # load value
    sw $t1, 8($sp)
    li $t0, 1
    sw $t0, 12($sp)
    # While loop
while_start_11:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_11
    # If statement
    lw $t4, 12($sp)
    # Array access: arr[index]
    lw $t3, 0($sp)     # load array pointer (parameter)
    sll $t4, $t4, 2    # index * 4
    add $t3, $t3, $t4 # element address
    lw $t3, 0($t3)     # load value
    lw $t4, 8($sp)
    # Integer less than
    slt $t5, $t3, $t4
    beq $t5, $zero, endif_label_17
    lw $t7, 12($sp)
    # Array access: arr[index]
    lw $t6, 0($sp)     # load array pointer (parameter)
    sll $t7, $t7, 2    # index * 4
    add $t6, $t6, $t7 # element address
    lw $t6, 0($t6)     # load value
    sw $t6, 8($sp)
endif_label_17:
    lw $t0, 12($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    j while_start_11
while_end_11:
    # Return statement
    lw $t0, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_findMin_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: isPrime
func_isPrime:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'n'
    # Function body
    # Declared i at offset 4
    # Declared result at offset 8
    # If statement
    lw $t1, 0($sp)
    li $t2, 1
    # Integer less than or equal
    slt $t3, $t2, $t1
    xori $t3, $t3, 1
    beq $t3, $zero, else_label_18
    li $t4, 0
    sw $t4, 8($sp)
    j endif_label_18
else_label_18:
    li $t0, 1
    sw $t0, 8($sp)
    li $t0, 2
    sw $t0, 4($sp)
    # While loop
while_start_12:
    lw $t0, 4($sp)
    lw $t1, 0($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_12
    # If statement
    lw $t3, 0($sp)
    lw $t4, 4($sp)
    # Division
    div $t3, $t4      # Divide: result in LO
    mflo $t3           # Move quotient from LO
    lw $t4, 4($sp)
    # Multiplication
    mul $t3, $t3, $t4
    lw $t4, 0($sp)
    # Integer equal
    xor $t5, $t3, $t4
    sltiu $t5, $t5, 1
    beq $t5, $zero, else_label_19
    li $t6, 0
    sw $t6, 8($sp)
    lw $t0, 0($sp)
    sw $t0, 4($sp)
    j endif_label_19
else_label_19:
    lw $t0, 4($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 4($sp)
endif_label_19:
    j while_start_12
while_end_12:
endif_label_18:
    # Return statement
    lw $t0, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_isPrime_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: countPrimes
func_countPrimes:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'limit'
    # Function body
    # Declared count at offset 4
    # Declared i at offset 8
    li $t1, 0
    sw $t1, 4($sp)
    li $t0, 2
    sw $t0, 8($sp)
    # While loop
while_start_13:
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    # Integer less than or equal
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    beq $t2, $zero, while_end_13
    # If statement
    # Function call: isPrime
    lw $t3, 8($sp)
    move $a0, $t3    # Arg 0
    jal func_isPrime             # Call function
    move $t4, $v0      # Get return value
    li $t5, 1
    # Integer equal
    xor $t6, $t4, $t5
    sltiu $t6, $t6, 1
    beq $t6, $zero, endif_label_20
    lw $t7, 4($sp)
    li $t0, 1
    # Addition
    add $t0, $t0, $t0
    sw $t0, 4($sp)
endif_label_20:
    lw $t0, 8($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    j while_start_13
while_end_13:
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_countPrimes_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: reverseArray
func_reverseArray:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'arr'
    sw $a1, 4($sp)     # Store param 'size'
    # Function body
    # Declared left at offset 8
    # Declared right at offset 12
    # Declared temp at offset 16
    li $t1, 0
    sw $t1, 8($sp)
    lw $t0, 4($sp)
    li $t1, 1
    # Subtraction
    sub $t0, $t0, $t1
    sw $t0, 12($sp)
    # While loop
while_start_14:
    lw $t0, 8($sp)
    lw $t1, 12($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_14
    lw $t4, 8($sp)
    # Array access: arr[index]
    lw $t3, 0($sp)     # load array pointer (parameter)
    sll $t4, $t4, 2    # index * 4
    add $t3, $t3, $t4 # element address
    lw $t3, 0($t3)     # load value
    sw $t3, 16($sp)
    lw $t2, 8($sp)
    lw $t4, 12($sp)
    # Array access: arr[index]
    lw $t3, 0($sp)     # load array pointer (parameter)
    sll $t4, $t4, 2    # index * 4
    add $t3, $t3, $t4 # element address
    lw $t3, 0($t3)     # load value
    # Array assignment: arr[index] = value
    lw $t1, 0($sp)     # load array pointer (parameter)
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    lw $t2, 12($sp)
    lw $t3, 16($sp)
    # Array assignment: arr[index] = value
    lw $t1, 0($sp)     # load array pointer (parameter)
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    lw $t0, 8($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    # Subtraction
    sub $t0, $t0, $t1
    sw $t0, 12($sp)
    j while_start_14
while_end_14:
    # Return statement
    li $t0, 0
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_reverseArray_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: testComplexExpressions
func_testComplexExpressions:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    sw $a2, 8($sp)     # Store param 'c'
    # Function body
    # Declared result at offset 12
    lw $t1, 0($sp)
    lw $t2, 4($sp)
    lw $t3, 8($sp)
    # Multiplication
    mul $t2, $t2, $t3
    # Addition
    add $t1, $t1, $t2
    lw $t2, 0($sp)
    lw $t3, 4($sp)
    # Division
    div $t2, $t3      # Divide: result in LO
    mflo $t2           # Move quotient from LO
    # Subtraction
    sub $t1, $t1, $t2
    sw $t1, 12($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Addition
    add $t0, $t0, $t1
    lw $t1, 8($sp)
    lw $t2, 0($sp)
    # Subtraction
    sub $t1, $t1, $t2
    # Multiplication
    mul $t0, $t0, $t1
    lw $t1, 4($sp)
    li $t2, 1
    # Addition
    add $t1, $t1, $t2
    # Division
    div $t0, $t1      # Divide: result in LO
    mflo $t0           # Move quotient from LO
    sw $t0, 12($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Multiplication
    mul $t0, $t0, $t1
    lw $t1, 8($sp)
    lw $t2, 0($sp)
    # Multiplication
    mul $t1, $t1, $t2
    # Addition
    add $t0, $t0, $t1
    lw $t1, 4($sp)
    lw $t2, 8($sp)
    # Division
    div $t1, $t2      # Divide: result in LO
    mflo $t1           # Move quotient from LO
    # Subtraction
    sub $t0, $t0, $t1
    lw $t1, 0($sp)
    # Addition
    add $t0, $t0, $t1
    lw $t1, 4($sp)
    # Subtraction
    sub $t0, $t0, $t1
    lw $t1, 8($sp)
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    # Return statement
    lw $t0, 12($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_testComplexExpressions_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: testVoidFunction
func_testVoidFunction:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'x'
    # Function body
    # Declared y at offset 4
    lw $t1, 0($sp)
    li $t2, 2
    # Multiplication
    mul $t1, $t1, $t2
    sw $t1, 4($sp)
    lw $t0, 4($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Return statement
    li $t0, 0
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_testVoidFunction_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: printArray
func_printArray:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'arr'
    sw $a1, 4($sp)     # Store param 'size'
    # Function body
    # Declared i at offset 8
    li $t1, 0
    sw $t1, 8($sp)
    # While loop
while_start_15:
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_15
    lw $t4, 8($sp)
    # Array access: arr[index]
    lw $t3, 0($sp)     # load array pointer (parameter)
    sll $t4, $t4, 2    # index * 4
    add $t3, $t3, $t4 # element address
    lw $t3, 0($t3)     # load value
    # Print integer (expr)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 8($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    j while_start_15
while_end_15:
    # Return statement
    li $t0, 0
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_printArray_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: multiply3
func_multiply3:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    sw $a2, 8($sp)     # Store param 'c'
    # Function body
    # Return statement
    lw $t1, 0($sp)
    lw $t2, 4($sp)
    # Multiplication
    mul $t1, $t1, $t2
    lw $t2, 8($sp)
    # Multiplication
    mul $t1, $t1, $t2
    move $v0, $t1       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_multiply3_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: add4
func_add4:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    sw $a2, 8($sp)     # Store param 'c'
    sw $a3, 12($sp)     # Store param 'd'
    # Function body
    # Return statement
    lw $t2, 0($sp)
    lw $t3, 4($sp)
    # Addition
    add $t2, $t2, $t3
    lw $t3, 8($sp)
    # Addition
    add $t2, $t2, $t3
    lw $t3, 12($sp)
    # Addition
    add $t2, $t2, $t3
    move $v0, $t2       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_add4_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: max3
func_max3:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    sw $a2, 8($sp)     # Store param 'c'
    # Function body
    # Declared max at offset 12
    lw $t3, 0($sp)
    sw $t3, 12($sp)
    # If statement
    lw $t0, 4($sp)
    lw $t1, 12($sp)
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, endif_label_21
    lw $t3, 4($sp)
    sw $t3, 12($sp)
endif_label_21:
    # If statement
    lw $t0, 8($sp)
    lw $t1, 12($sp)
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, endif_label_22
    lw $t3, 8($sp)
    sw $t3, 12($sp)
endif_label_22:
    # Return statement
    lw $t0, 12($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_max3_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: fillArray
func_fillArray:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'arr'
    sw $a1, 4($sp)     # Store param 'size'
    sw $a2, 8($sp)     # Store param 'value'
    # Function body
    # Declared i at offset 12
    li $t1, 0
    sw $t1, 12($sp)
    # While loop
while_start_16:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_16
    lw $t5, 12($sp)
    lw $t6, 8($sp)
    # Array assignment: arr[index] = value
    lw $t4, 0($sp)     # load array pointer (parameter)
    sll $t5, $t5, 2    # index * 4
    add $t3, $t4, $t5 # element address
    sw $t6, 0($t3)     # store value
    lw $t0, 12($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    j while_start_16
while_end_16:
    # Return statement
    li $t0, 0
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_fillArray_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: copyArray
func_copyArray:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'source'
    sw $a1, 4($sp)     # Store param 'dest'
    sw $a2, 8($sp)     # Store param 'size'
    # Function body
    # Declared i at offset 12
    li $t1, 0
    sw $t1, 12($sp)
    # While loop
while_start_17:
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_17
    lw $t5, 12($sp)
    lw $t7, 12($sp)
    # Array access: source[index]
    lw $t6, 0($sp)     # load array pointer (parameter)
    sll $t7, $t7, 2    # index * 4
    add $t6, $t6, $t7 # element address
    lw $t6, 0($t6)     # load value
    # Array assignment: dest[index] = value
    lw $t4, 4($sp)     # load array pointer (parameter)
    sll $t5, $t5, 2    # index * 4
    add $t3, $t4, $t5 # element address
    sw $t6, 0($t3)     # store value
    lw $t0, 12($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    j while_start_17
while_end_17:
    # Return statement
    li $t0, 0
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_copyArray_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: arrayEqual
func_arrayEqual:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'arr1'
    sw $a1, 4($sp)     # Store param 'arr2'
    sw $a2, 8($sp)     # Store param 'size'
    # Function body
    # Declared i at offset 12
    # Declared equal at offset 16
    li $t1, 1
    sw $t1, 16($sp)
    li $t0, 0
    sw $t0, 12($sp)
    # While loop
while_start_18:
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_18
    # If statement
    lw $t4, 12($sp)
    # Array access: arr1[index]
    lw $t3, 0($sp)     # load array pointer (parameter)
    sll $t4, $t4, 2    # index * 4
    add $t3, $t3, $t4 # element address
    lw $t3, 0($t3)     # load value
    lw $t5, 12($sp)
    # Array access: arr2[index]
    lw $t4, 4($sp)     # load array pointer (parameter)
    sll $t5, $t5, 2    # index * 4
    add $t4, $t4, $t5 # element address
    lw $t4, 0($t4)     # load value
    # Integer not equal
    xor $t5, $t3, $t4
    sltu $t5, $zero, $t5
    beq $t5, $zero, else_label_23
    li $t6, 0
    sw $t6, 16($sp)
    lw $t0, 8($sp)
    sw $t0, 12($sp)
    j endif_label_23
else_label_23:
    lw $t0, 12($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
endif_label_23:
    j while_start_18
while_end_18:
    # Return statement
    lw $t0, 16($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_arrayEqual_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: absoluteValue
func_absoluteValue:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'x'
    # Function body
    # Declared result at offset 4
    # If statement
    lw $t1, 0($sp)
    li $t2, 0
    # Integer less than
    slt $t3, $t1, $t2
    beq $t3, $zero, else_label_24
    li $t4, 0
    lw $t5, 0($sp)
    # Subtraction
    sub $t4, $t4, $t5
    sw $t4, 4($sp)
    j endif_label_24
else_label_24:
    lw $t0, 0($sp)
    sw $t0, 4($sp)
endif_label_24:
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_absoluteValue_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: sign
func_sign:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'x'
    # Function body
    # Declared result at offset 4
    # If statement
    lw $t1, 0($sp)
    li $t2, 0
    # Integer less than
    slt $t3, $t1, $t2
    beq $t3, $zero, else_label_25
    li $t4, 0
    li $t5, 1
    # Subtraction
    sub $t4, $t4, $t5
    sw $t4, 4($sp)
    j endif_label_25
else_label_25:
    # If statement
    lw $t0, 0($sp)
    li $t1, 0
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, else_label_26
    li $t3, 1
    sw $t3, 4($sp)
    j endif_label_26
else_label_26:
    li $t0, 0
    sw $t0, 4($sp)
endif_label_26:
endif_label_25:
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_sign_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: sumOfSquares
func_sumOfSquares:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'n'
    # Function body
    # Declared sum at offset 4
    # Declared i at offset 8
    li $t1, 0
    sw $t1, 4($sp)
    li $t0, 1
    sw $t0, 8($sp)
    # While loop
while_start_19:
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    # Integer less than or equal
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    beq $t2, $zero, while_end_19
    lw $t3, 4($sp)
    lw $t4, 8($sp)
    lw $t5, 8($sp)
    # Multiplication
    mul $t4, $t4, $t5
    # Addition
    add $t3, $t3, $t4
    sw $t3, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    j while_start_19
while_end_19:
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_sumOfSquares_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: sumOfCubes
func_sumOfCubes:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'n'
    # Function body
    # Declared sum at offset 4
    # Declared i at offset 8
    li $t1, 0
    sw $t1, 4($sp)
    li $t0, 1
    sw $t0, 8($sp)
    # While loop
while_start_20:
    lw $t0, 8($sp)
    lw $t1, 0($sp)
    # Integer less than or equal
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    beq $t2, $zero, while_end_20
    lw $t3, 4($sp)
    lw $t4, 8($sp)
    lw $t5, 8($sp)
    # Multiplication
    mul $t4, $t4, $t5
    lw $t5, 8($sp)
    # Multiplication
    mul $t4, $t4, $t5
    # Addition
    add $t3, $t3, $t4
    sw $t3, 4($sp)
    lw $t0, 8($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    j while_start_20
while_end_20:
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_sumOfCubes_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: calculateMean
func_calculateMean:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'arr'
    sw $a1, 4($sp)     # Store param 'size'
    # Function body
    # Declared sum at offset 8
    # Declared i at offset 12
    li $t1, 0
    sw $t1, 8($sp)
    li $t0, 0
    sw $t0, 12($sp)
    # While loop
while_start_21:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_21
    lw $t3, 8($sp)
    lw $t5, 12($sp)
    # Array access: arr[index]
    lw $t4, 0($sp)     # load array pointer (parameter)
    sll $t5, $t5, 2    # index * 4
    add $t4, $t4, $t5 # element address
    lw $t4, 0($t4)     # load value
    # Addition
    add $t3, $t3, $t4
    sw $t3, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    j while_start_21
while_end_21:
    # Return statement
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    # Division
    div $t0, $t1      # Divide: result in LO
    mflo $t0           # Move quotient from LO
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_calculateMean_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: countOccurrences
func_countOccurrences:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'arr'
    sw $a1, 4($sp)     # Store param 'size'
    sw $a2, 8($sp)     # Store param 'value'
    # Function body
    # Declared count at offset 12
    # Declared i at offset 16
    li $t1, 0
    sw $t1, 12($sp)
    li $t0, 0
    sw $t0, 16($sp)
    # While loop
while_start_22:
    lw $t0, 16($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_22
    # If statement
    lw $t4, 16($sp)
    # Array access: arr[index]
    lw $t3, 0($sp)     # load array pointer (parameter)
    sll $t4, $t4, 2    # index * 4
    add $t3, $t3, $t4 # element address
    lw $t3, 0($t3)     # load value
    lw $t4, 8($sp)
    # Integer equal
    xor $t5, $t3, $t4
    sltiu $t5, $t5, 1
    beq $t5, $zero, endif_label_27
    lw $t6, 12($sp)
    li $t7, 1
    # Addition
    add $t6, $t6, $t0
    sw $t6, 12($sp)
endif_label_27:
    lw $t0, 16($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    j while_start_22
while_end_22:
    # Return statement
    lw $t0, 12($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_countOccurrences_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: leftShift
func_leftShift:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'n'
    sw $a1, 4($sp)     # Store param 'bits'
    # Function body
    # Declared result at offset 8
    # Declared i at offset 12
    lw $t1, 0($sp)
    sw $t1, 8($sp)
    li $t0, 0
    sw $t0, 12($sp)
    # While loop
while_start_23:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_23
    lw $t3, 8($sp)
    li $t4, 2
    # Multiplication
    mul $t3, $t3, $t4
    sw $t3, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    j while_start_23
while_end_23:
    # Return statement
    lw $t0, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_leftShift_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: rightShift
func_rightShift:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'n'
    sw $a1, 4($sp)     # Store param 'bits'
    # Function body
    # Declared result at offset 8
    # Declared i at offset 12
    lw $t1, 0($sp)
    sw $t1, 8($sp)
    li $t0, 0
    sw $t0, 12($sp)
    # While loop
while_start_24:
    lw $t0, 12($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_24
    lw $t3, 8($sp)
    li $t4, 2
    # Division
    div $t3, $t4      # Divide: result in LO
    mflo $t3           # Move quotient from LO
    sw $t3, 8($sp)
    lw $t0, 12($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    j while_start_24
while_end_24:
    # Return statement
    lw $t0, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_rightShift_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: arrayLength
func_arrayLength:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'arr'
    sw $a1, 4($sp)     # Store param 'maxSize'
    # Function body
    # Declared length at offset 8
    li $t1, 0
    sw $t1, 8($sp)
    # While loop
while_start_25:
    lw $t0, 8($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_25
    # If statement
    lw $t4, 8($sp)
    # Array access: arr[index]
    lw $t3, 0($sp)     # load array pointer (parameter)
    sll $t4, $t4, 2    # index * 4
    add $t3, $t3, $t4 # element address
    lw $t3, 0($t3)     # load value
    li $t4, 0
    # Integer equal
    xor $t5, $t3, $t4
    sltiu $t5, $t5, 1
    beq $t5, $zero, else_label_28
    lw $t6, 4($sp)
    sw $t6, 8($sp)
    j endif_label_28
else_label_28:
    lw $t0, 8($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 8($sp)
endif_label_28:
    j while_start_25
while_end_25:
    # Return statement
    lw $t0, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_arrayLength_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: main
_user_main:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    # Function body
    # Declared array testArray[10] at offset 0
    # Declared array testArray2[10] at offset 40
    # Declared i at offset 80
    # Declared result at offset 84
    # Declared a at offset 88
    # Declared b at offset 92
    # Declared choice at offset 96
    li $t1, 0
    sw $t1, 0($sp)
    li $t0, 1
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: testArithmetic
    li $t0, 10
    move $a0, $t0    # Arg 0
    li $t1, 5
    move $a1, $t1    # Arg 1
    jal func_testArithmetic             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 2
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: testRelational
    li $t0, 5
    move $a0, $t0    # Arg 0
    li $t1, 10
    move $a1, $t1    # Arg 1
    jal func_testRelational             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 3
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: testIfElse
    li $t0, 75
    move $a0, $t0    # Arg 0
    jal func_testIfElse             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 4
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: testWhileLoop
    li $t0, 10
    move $a0, $t0    # Arg 0
    jal func_testWhileLoop             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 5
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: testNestedLoops
    li $t0, 5
    move $a0, $t0    # Arg 0
    li $t1, 5
    move $a1, $t1    # Arg 1
    jal func_testNestedLoops             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 6
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: testArrayOperations
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    li $t1, 10
    move $a1, $t1    # Arg 1
    jal func_testArrayOperations             # Call function
    move $t2, $v0      # Get return value
    # Function call: sumArray
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    li $t1, 10
    move $a1, $t1    # Arg 1
    jal func_sumArray             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 7
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: factorial
    li $t0, 5
    move $a0, $t0    # Arg 0
    jal func_factorial             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 8
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: fibonacci
    li $t0, 7
    move $a0, $t0    # Arg 0
    jal func_fibonacci             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 9
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: power
    li $t0, 2
    move $a0, $t0    # Arg 0
    li $t1, 5
    move $a1, $t1    # Arg 1
    jal func_power             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 10
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: gcd
    li $t0, 48
    move $a0, $t0    # Arg 0
    li $t1, 18
    move $a1, $t1    # Arg 1
    jal func_gcd             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 11
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 0
    sw $t0, 80($sp)
    # While loop
while_start_26:
    lw $t0, 80($sp)
    li $t1, 10
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_26
    lw $t5, 80($sp)
    lw $t6, 80($sp)
    li $t7, 3
    # Multiplication
    mul $t6, $t6, $t0
    # Array assignment: testArray[index] = value
    addi $t4, $sp, 0   # local array base address
    sll $t5, $t5, 2    # index * 4
    add $t3, $t4, $t5 # element address
    sw $t6, 0($t3)     # store value
    lw $t0, 80($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 80($sp)
    j while_start_26
while_end_26:
    # Function call: linearSearch
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    li $t1, 10
    move $a1, $t1    # Arg 1
    li $t2, 15
    move $a2, $t2    # Arg 2
    jal func_linearSearch             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 12
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t2, 0
    li $t3, 5
    # Array assignment: testArray[index] = value
    addi $t1, $sp, 0   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    li $t2, 1
    li $t3, 2
    # Array assignment: testArray[index] = value
    addi $t1, $sp, 0   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    li $t2, 2
    li $t3, 8
    # Array assignment: testArray[index] = value
    addi $t1, $sp, 0   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    li $t2, 3
    li $t3, 1
    # Array assignment: testArray[index] = value
    addi $t1, $sp, 0   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    li $t2, 4
    li $t3, 9
    # Array assignment: testArray[index] = value
    addi $t1, $sp, 0   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    # Function call: bubbleSort
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    li $t1, 5
    move $a1, $t1    # Arg 1
    jal func_bubbleSort             # Call function
    move $t2, $v0      # Get return value
    # Function call: printArray
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    li $t1, 5
    move $a1, $t1    # Arg 1
    jal func_printArray             # Call function
    move $t2, $v0      # Get return value
    li $t0, 13
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: findMax
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    li $t1, 5
    move $a1, $t1    # Arg 1
    jal func_findMax             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: findMin
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    li $t1, 5
    move $a1, $t1    # Arg 1
    jal func_findMin             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 14
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: isPrime
    li $t0, 17
    move $a0, $t0    # Arg 0
    jal func_isPrime             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: isPrime
    li $t0, 18
    move $a0, $t0    # Arg 0
    jal func_isPrime             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 15
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: countPrimes
    li $t0, 20
    move $a0, $t0    # Arg 0
    jal func_countPrimes             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 16
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 0
    sw $t0, 80($sp)
    # While loop
while_start_27:
    lw $t0, 80($sp)
    li $t1, 5
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_27
    lw $t5, 80($sp)
    lw $t6, 80($sp)
    li $t7, 1
    # Addition
    add $t6, $t6, $t0
    # Array assignment: testArray[index] = value
    addi $t4, $sp, 0   # local array base address
    sll $t5, $t5, 2    # index * 4
    add $t3, $t4, $t5 # element address
    sw $t6, 0($t3)     # store value
    lw $t0, 80($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 80($sp)
    j while_start_27
while_end_27:
    # Function call: reverseArray
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    li $t1, 5
    move $a1, $t1    # Arg 1
    jal func_reverseArray             # Call function
    move $t2, $v0      # Get return value
    # Function call: printArray
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    li $t1, 5
    move $a1, $t1    # Arg 1
    jal func_printArray             # Call function
    move $t2, $v0      # Get return value
    li $t0, 17
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: multiply3
    li $t0, 2
    move $a0, $t0    # Arg 0
    li $t1, 3
    move $a1, $t1    # Arg 1
    li $t2, 4
    move $a2, $t2    # Arg 2
    jal func_multiply3             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: add4
    li $t0, 1
    move $a0, $t0    # Arg 0
    li $t1, 2
    move $a1, $t1    # Arg 1
    li $t2, 3
    move $a2, $t2    # Arg 2
    li $t3, 4
    move $a3, $t3    # Arg 3
    jal func_add4             # Call function
    move $t4, $v0      # Get return value
    sw $t4, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: max3
    li $t0, 5
    move $a0, $t0    # Arg 0
    li $t1, 9
    move $a1, $t1    # Arg 1
    li $t2, 3
    move $a2, $t2    # Arg 2
    jal func_max3             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 18
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: fillArray
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    li $t1, 10
    move $a1, $t1    # Arg 1
    li $t2, 7
    move $a2, $t2    # Arg 2
    jal func_fillArray             # Call function
    move $t3, $v0      # Get return value
    # Function call: copyArray
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    addi $t1, $sp, 40    # Arg 1: local array address
    move $a1, $t1
    li $t2, 10
    move $a2, $t2    # Arg 2
    jal func_copyArray             # Call function
    move $t3, $v0      # Get return value
    # Function call: arrayEqual
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    addi $t1, $sp, 40    # Arg 1: local array address
    move $a1, $t1
    li $t2, 10
    move $a2, $t2    # Arg 2
    jal func_arrayEqual             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 19
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: absoluteValue
    li $t0, 0
    li $t1, 15
    # Subtraction
    sub $t0, $t0, $t1
    move $a0, $t0    # Arg 0
    jal func_absoluteValue             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: sign
    li $t0, 0
    li $t1, 5
    # Subtraction
    sub $t0, $t0, $t1
    move $a0, $t0    # Arg 0
    jal func_sign             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: sign
    li $t0, 5
    move $a0, $t0    # Arg 0
    jal func_sign             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: sign
    li $t0, 0
    move $a0, $t0    # Arg 0
    jal func_sign             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 20
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: sumOfSquares
    li $t0, 5
    move $a0, $t0    # Arg 0
    jal func_sumOfSquares             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: sumOfCubes
    li $t0, 5
    move $a0, $t0    # Arg 0
    jal func_sumOfCubes             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 21
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 0
    sw $t0, 80($sp)
    # While loop
while_start_28:
    lw $t0, 80($sp)
    li $t1, 5
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, while_end_28
    lw $t5, 80($sp)
    lw $t6, 80($sp)
    li $t7, 1
    # Addition
    add $t6, $t6, $t0
    li $t7, 2
    # Multiplication
    mul $t6, $t6, $t0
    # Array assignment: testArray[index] = value
    addi $t4, $sp, 0   # local array base address
    sll $t5, $t5, 2    # index * 4
    add $t3, $t4, $t5 # element address
    sw $t6, 0($t3)     # store value
    lw $t0, 80($sp)
    li $t1, 1
    # Addition
    add $t0, $t0, $t1
    sw $t0, 80($sp)
    j while_start_28
while_end_28:
    # Function call: calculateMean
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    li $t1, 5
    move $a1, $t1    # Arg 1
    jal func_calculateMean             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t2, 0
    li $t3, 5
    # Array assignment: testArray[index] = value
    addi $t1, $sp, 0   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    li $t2, 1
    li $t3, 5
    # Array assignment: testArray[index] = value
    addi $t1, $sp, 0   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    li $t2, 2
    li $t3, 3
    # Array assignment: testArray[index] = value
    addi $t1, $sp, 0   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    li $t2, 3
    li $t3, 5
    # Array assignment: testArray[index] = value
    addi $t1, $sp, 0   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    li $t2, 4
    li $t3, 7
    # Array assignment: testArray[index] = value
    addi $t1, $sp, 0   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    # Function call: countOccurrences
    addi $t0, $sp, 0    # Arg 0: local array address
    move $a0, $t0
    li $t1, 5
    move $a1, $t1    # Arg 1
    li $t2, 5
    move $a2, $t2    # Arg 2
    jal func_countOccurrences             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 22
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: leftShift
    li $t0, 3
    move $a0, $t0    # Arg 0
    li $t1, 2
    move $a1, $t1    # Arg 1
    jal func_leftShift             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: rightShift
    li $t0, 16
    move $a0, $t0    # Arg 0
    li $t1, 2
    move $a1, $t1    # Arg 1
    jal func_rightShift             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 23
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: testComplexExpressions
    li $t0, 10
    move $a0, $t0    # Arg 0
    li $t1, 5
    move $a1, $t1    # Arg 1
    li $t2, 3
    move $a2, $t2    # Arg 2
    jal func_testComplexExpressions             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 84($sp)
    lw $t0, 84($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 24
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 100
    sw $t0, 0($sp)
    li $t2, 0
    li $t3, 10
    # Array assignment: globalArray[index] = value
    addi $t1, $sp, 4   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    li $t2, 1
    li $t3, 20
    # Array assignment: globalArray[index] = value
    addi $t1, $sp, 4   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    li $t2, 2
    li $t3, 30
    # Array assignment: globalArray[index] = value
    addi $t1, $sp, 4   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t3, 0($t0)     # store value
    lw $t0, 0($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t1, 0
    # Array access: globalArray[index]
    addi $t0, $sp, 4   # local array base address
    sll $t1, $t1, 2    # index * 4
    add $t0, $t0, $t1 # element address
    lw $t0, 0($t0)     # load value
    li $t2, 1
    # Array access: globalArray[index]
    addi $t1, $sp, 4   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t1, $t1, $t2 # element address
    lw $t1, 0($t1)     # load value
    # Addition
    add $t0, $t0, $t1
    li $t2, 2
    # Array access: globalArray[index]
    addi $t1, $sp, 4   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t1, $t1, $t2 # element address
    lw $t1, 0($t1)     # load value
    # Addition
    add $t0, $t0, $t1
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 25
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: testVoidFunction
    li $t0, 5
    move $a0, $t0    # Arg 0
    jal func_testVoidFunction             # Call function
    move $t1, $v0      # Get return value
    li $t0, 999
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Return statement
    li $t0, 0
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
_user_main_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

main_code:
    # Declared globalCounter at offset 0
    # Declared array globalArray[20] at offset 4
    # Declared globalResult at offset 84
    # Function call: main
    jal _user_main             # Call function
    move $t1, $v0      # Get return value

    # Exit program
    addi $sp, $sp, 400
    li $v0, 10
    syscall

# Infinite loop to prevent bad instruction exceptions
__post_exit_stub:
    li $v0, 10
    syscall
    j __post_exit_stub    # Loop forever
