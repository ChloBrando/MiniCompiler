.data
str_literal_0: .asciiz "Function Tests Start"
str_literal_1: .asciiz "Enter three numbers:"

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400
    j main_code        # Jump to main program


# Function: add
func_add:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    # Function body
    # Return statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Addition
    add $t0, $t0, $t1
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_add_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: subtract
func_subtract:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'x'
    sw $a1, 4($sp)     # Store param 'y'
    # Function body
    # Return statement
    lw $t1, 0($sp)
    lw $t2, 4($sp)
    # Subtraction
    sub $t1, $t1, $t2
    move $v0, $t1       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_subtract_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: multiply
func_multiply:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    # Function body
    # Return statement
    lw $t2, 0($sp)
    lw $t3, 4($sp)
    # Multiplication
    mul $t2, $t2, $t3
    move $v0, $t2       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_multiply_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: divide
func_divide:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'numerator'
    sw $a1, 4($sp)     # Store param 'denominator'
    # Function body
    # Return statement
    lw $t3, 0($sp)
    lw $t4, 4($sp)
    # Division
    div $t3, $t4      # Divide: result in LO
    mflo $t3           # Move quotient from LO
    move $v0, $t3       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_divide_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: complexExpression
func_complexExpression:
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
    # Declared temp at offset 12
    lw $t4, 0($sp)
    lw $t5, 4($sp)
    # Multiplication
    mul $t4, $t4, $t5
    lw $t5, 8($sp)
    # Addition
    add $t4, $t4, $t5
    lw $t5, 0($sp)
    lw $t6, 4($sp)
    # Division
    div $t5, $t6      # Divide: result in LO
    mflo $t5           # Move quotient from LO
    # Subtraction
    sub $t4, $t4, $t5
    sw $t4, 12($sp)
    # Return statement
    lw $t0, 12($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_complexExpression_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: addAndMultiply
func_addAndMultiply:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'x'
    sw $a1, 4($sp)     # Store param 'y'
    sw $a2, 8($sp)     # Store param 'z'
    # Function body
    # Declared sum at offset 12
    # Function call: add
    lw $t1, 0($sp)
    move $a0, $t1    # Arg 0
    lw $t2, 4($sp)
    move $a1, $t2    # Arg 1
    jal func_add             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 12($sp)
    # Return statement
    # Function call: multiply
    lw $t0, 12($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 8($sp)
    move $a1, $t1    # Arg 1
    jal func_multiply             # Call function
    move $t2, $v0      # Get return value
    move $v0, $t2       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_addAndMultiply_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: nestedCalls
func_nestedCalls:
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
    # Function call: add
    # Function call: multiply
    lw $t3, 0($sp)
    move $a0, $t3    # Arg 0
    lw $t4, 4($sp)
    move $a1, $t4    # Arg 1
    jal func_multiply             # Call function
    move $t5, $v0      # Get return value
    move $a0, $t5    # Arg 0
    # Function call: subtract
    lw $t6, 8($sp)
    move $a0, $t6    # Arg 0
    lw $t7, 12($sp)
    move $a1, $t0    # Arg 1
    jal func_subtract             # Call function
    move $t0, $v0      # Get return value
    move $a1, $t0    # Arg 1
    jal func_add             # Call function
    move $t1, $v0      # Get return value
    move $v0, $t1       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_nestedCalls_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: average
func_average:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'num1'
    sw $a1, 4($sp)     # Store param 'num2'
    sw $a2, 8($sp)     # Store param 'num3'
    # Function body
    # Declared total at offset 12
    # Declared result at offset 16
    # Function call: add
    # Function call: add
    lw $t2, 0($sp)
    move $a0, $t2    # Arg 0
    lw $t3, 4($sp)
    move $a1, $t3    # Arg 1
    jal func_add             # Call function
    move $t4, $v0      # Get return value
    move $a0, $t4    # Arg 0
    lw $t5, 8($sp)
    move $a1, $t5    # Arg 1
    jal func_add             # Call function
    move $t6, $v0      # Get return value
    sw $t6, 12($sp)
    # Function call: divide
    lw $t0, 12($sp)
    move $a0, $t0    # Arg 0
    li $t1, 3
    move $a1, $t1    # Arg 1
    jal func_divide             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 16($sp)
    # Return statement
    lw $t0, 16($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_average_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: polynomial
func_polynomial:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'x'
    sw $a2, 8($sp)     # Store param 'b'
    sw $a3, 12($sp)     # Store param 'c'
    # Function body
    # Declared xSquared at offset 16
    # Declared term1 at offset 20
    # Declared term2 at offset 24
    # Declared result at offset 28
    # Function call: multiply
    lw $t1, 4($sp)
    move $a0, $t1    # Arg 0
    lw $t2, 4($sp)
    move $a1, $t2    # Arg 1
    jal func_multiply             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 16($sp)
    # Function call: multiply
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 16($sp)
    move $a1, $t1    # Arg 1
    jal func_multiply             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 20($sp)
    # Function call: multiply
    lw $t0, 8($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_multiply             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 24($sp)
    # Function call: add
    # Function call: add
    lw $t0, 20($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 24($sp)
    move $a1, $t1    # Arg 1
    jal func_add             # Call function
    move $t2, $v0      # Get return value
    move $a0, $t2    # Arg 0
    lw $t3, 12($sp)
    move $a1, $t3    # Arg 1
    jal func_add             # Call function
    move $t4, $v0      # Get return value
    sw $t4, 28($sp)
    # Return statement
    lw $t0, 28($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_polynomial_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: chainOperations
func_chainOperations:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'value'
    # Function body
    # Declared result at offset 4
    lw $t1, 0($sp)
    sw $t1, 4($sp)
    # Function call: add
    lw $t0, 4($sp)
    move $a0, $t0    # Arg 0
    li $t1, 10
    move $a1, $t1    # Arg 1
    jal func_add             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 4($sp)
    # Function call: multiply
    lw $t0, 4($sp)
    move $a0, $t0    # Arg 0
    li $t1, 2
    move $a1, $t1    # Arg 1
    jal func_multiply             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 4($sp)
    # Function call: subtract
    lw $t0, 4($sp)
    move $a0, $t0    # Arg 0
    li $t1, 5
    move $a1, $t1    # Arg 1
    jal func_subtract             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 4($sp)
    # Function call: divide
    lw $t0, 4($sp)
    move $a0, $t0    # Arg 0
    li $t1, 3
    move $a1, $t1    # Arg 1
    jal func_divide             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 4($sp)
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_chainOperations_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: deepNesting
func_deepNesting:
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
    # Function call: multiply
    # Function call: add
    # Function call: subtract
    lw $t1, 0($sp)
    move $a0, $t1    # Arg 0
    lw $t2, 4($sp)
    move $a1, $t2    # Arg 1
    jal func_subtract             # Call function
    move $t3, $v0      # Get return value
    move $a0, $t3    # Arg 0
    lw $t4, 8($sp)
    move $a1, $t4    # Arg 1
    jal func_add             # Call function
    move $t5, $v0      # Get return value
    move $a0, $t5    # Arg 0
    # Function call: divide
    # Function call: add
    lw $t6, 0($sp)
    move $a0, $t6    # Arg 0
    lw $t7, 8($sp)
    move $a1, $t0    # Arg 1
    jal func_add             # Call function
    move $t0, $v0      # Get return value
    move $a0, $t0    # Arg 0
    # Function call: subtract
    lw $t1, 8($sp)
    move $a0, $t1    # Arg 0
    lw $t2, 4($sp)
    move $a1, $t2    # Arg 1
    jal func_subtract             # Call function
    move $t3, $v0      # Get return value
    move $a1, $t3    # Arg 1
    jal func_divide             # Call function
    move $t4, $v0      # Get return value
    move $a1, $t4    # Arg 1
    jal func_multiply             # Call function
    move $t5, $v0      # Get return value
    move $v0, $t5       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_deepNesting_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: allOperators
func_allOperators:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'w'
    sw $a1, 4($sp)     # Store param 'x'
    sw $a2, 8($sp)     # Store param 'y'
    sw $a3, 12($sp)     # Store param 'z'
    # Function body
    # Declared part1 at offset 16
    # Declared part2 at offset 20
    # Declared result at offset 24
    lw $t6, 0($sp)
    lw $t7, 4($sp)
    # Multiplication
    mul $t6, $t6, $t0
    lw $t7, 8($sp)
    # Addition
    add $t6, $t6, $t0
    lw $t7, 12($sp)
    # Subtraction
    sub $t6, $t6, $t0
    sw $t6, 16($sp)
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Division
    div $t0, $t1      # Divide: result in LO
    mflo $t0           # Move quotient from LO
    lw $t1, 8($sp)
    # Subtraction
    sub $t0, $t0, $t1
    lw $t1, 12($sp)
    # Addition
    add $t0, $t0, $t1
    sw $t0, 20($sp)
    lw $t0, 16($sp)
    lw $t1, 20($sp)
    # Multiplication
    mul $t0, $t0, $t1
    sw $t0, 24($sp)
    # Return statement
    lw $t0, 24($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_allOperators_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: printCalculation
func_printCalculation:
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
    # Declared product at offset 12
    # Function call: add
    lw $t1, 0($sp)
    move $a0, $t1    # Arg 0
    lw $t2, 4($sp)
    move $a1, $t2    # Arg 1
    jal func_add             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 8($sp)
    # Function call: multiply
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_multiply             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 12($sp)
    lw $t0, 8($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function epilogue (default return)
func_printCalculation_return:
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
    # Declared x at offset 0
    # Declared y at offset 4
    # Declared z at offset 8
    # Declared result at offset 12
    # Declared array numbers[5] at offset 16
    # Declared arraySum at offset 36
    # Declared arrayAvg at offset 40
    # Declared poly at offset 44
    # Declared deep at offset 48
    # Declared chain at offset 52
    # load address of string literal
    la $t0, str_literal_0
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_1
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 5
    sw $t0, 0($sp)
    li $t0, 10
    sw $t0, 4($sp)
    li $t0, 15
    sw $t0, 8($sp)
    # Function call: add
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_add             # Call function
    move $t2, $v0      # Get return value
    # Print integer (expr)
    move $a0, $t2
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: subtract
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_subtract             # Call function
    move $t2, $v0      # Get return value
    # Print integer (expr)
    move $a0, $t2
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: multiply
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_multiply             # Call function
    move $t2, $v0      # Get return value
    # Print integer (expr)
    move $a0, $t2
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: divide
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_divide             # Call function
    move $t2, $v0      # Get return value
    # Print integer (expr)
    move $a0, $t2
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: complexExpression
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    lw $t2, 8($sp)
    move $a2, $t2    # Arg 2
    jal func_complexExpression             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 12($sp)
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: addAndMultiply
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    lw $t2, 8($sp)
    move $a2, $t2    # Arg 2
    jal func_addAndMultiply             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 12($sp)
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: nestedCalls
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    lw $t2, 8($sp)
    move $a2, $t2    # Arg 2
    lw $t3, 0($sp)
    move $a3, $t3    # Arg 3
    jal func_nestedCalls             # Call function
    move $t4, $v0      # Get return value
    sw $t4, 12($sp)
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: average
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    lw $t2, 8($sp)
    move $a2, $t2    # Arg 2
    jal func_average             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 12($sp)
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t2, 0
    # Function call: add
    lw $t3, 0($sp)
    move $a0, $t3    # Arg 0
    lw $t4, 4($sp)
    move $a1, $t4    # Arg 1
    jal func_add             # Call function
    move $t5, $v0      # Get return value
    # Array assignment: numbers[index] = value
    addi $t1, $sp, 16   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t5, 0($t0)     # store value
    li $t2, 1
    # Function call: multiply
    lw $t3, 0($sp)
    move $a0, $t3    # Arg 0
    li $t4, 2
    move $a1, $t4    # Arg 1
    jal func_multiply             # Call function
    move $t5, $v0      # Get return value
    # Array assignment: numbers[index] = value
    addi $t1, $sp, 16   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t5, 0($t0)     # store value
    li $t2, 2
    # Function call: subtract
    lw $t3, 4($sp)
    move $a0, $t3    # Arg 0
    li $t4, 3
    move $a1, $t4    # Arg 1
    jal func_subtract             # Call function
    move $t5, $v0      # Get return value
    # Array assignment: numbers[index] = value
    addi $t1, $sp, 16   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t5, 0($t0)     # store value
    li $t2, 3
    # Function call: divide
    lw $t3, 8($sp)
    move $a0, $t3    # Arg 0
    li $t4, 2
    move $a1, $t4    # Arg 1
    jal func_divide             # Call function
    move $t5, $v0      # Get return value
    # Array assignment: numbers[index] = value
    addi $t1, $sp, 16   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t5, 0($t0)     # store value
    li $t2, 4
    # Function call: add
    lw $t3, 0($sp)
    move $a0, $t3    # Arg 0
    lw $t4, 8($sp)
    move $a1, $t4    # Arg 1
    jal func_add             # Call function
    move $t5, $v0      # Get return value
    # Array assignment: numbers[index] = value
    addi $t1, $sp, 16   # local array base address
    sll $t2, $t2, 2    # index * 4
    add $t0, $t1, $t2 # element address
    sw $t5, 0($t0)     # store value
    li $t1, 0
    # Array access: numbers[index]
    addi $t0, $sp, 16   # local array base address
    sll $t1, $t1, 2    # index * 4
    add $t0, $t0, $t1 # element address
    lw $t0, 0($t0)     # load value
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t1, 1
    # Array access: numbers[index]
    addi $t0, $sp, 16   # local array base address
    sll $t1, $t1, 2    # index * 4
    add $t0, $t0, $t1 # element address
    lw $t0, 0($t0)     # load value
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t1, 2
    # Array access: numbers[index]
    addi $t0, $sp, 16   # local array base address
    sll $t1, $t1, 2    # index * 4
    add $t0, $t0, $t1 # element address
    lw $t0, 0($t0)     # load value
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t1, 3
    # Array access: numbers[index]
    addi $t0, $sp, 16   # local array base address
    sll $t1, $t1, 2    # index * 4
    add $t0, $t0, $t1 # element address
    lw $t0, 0($t0)     # load value
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t1, 4
    # Array access: numbers[index]
    addi $t0, $sp, 16   # local array base address
    sll $t1, $t1, 2    # index * 4
    add $t0, $t0, $t1 # element address
    lw $t0, 0($t0)     # load value
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: polynomial
    li $t0, 2
    move $a0, $t0    # Arg 0
    lw $t1, 0($sp)
    move $a1, $t1    # Arg 1
    li $t2, 3
    move $a2, $t2    # Arg 2
    li $t3, 5
    move $a3, $t3    # Arg 3
    jal func_polynomial             # Call function
    move $t4, $v0      # Get return value
    sw $t4, 44($sp)
    lw $t0, 44($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: chainOperations
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    jal func_chainOperations             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 52($sp)
    lw $t0, 52($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: deepNesting
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    lw $t2, 8($sp)
    move $a2, $t2    # Arg 2
    jal func_deepNesting             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 48($sp)
    lw $t0, 48($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: allOperators
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    lw $t2, 8($sp)
    move $a2, $t2    # Arg 2
    li $t3, 10
    move $a3, $t3    # Arg 3
    jal func_allOperators             # Call function
    move $t4, $v0      # Get return value
    sw $t4, 12($sp)
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: printCalculation
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_printCalculation             # Call function
    move $t2, $v0      # Get return value
    # Function call: add
    # Function call: multiply
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_multiply             # Call function
    move $t2, $v0      # Get return value
    move $a0, $t2    # Arg 0
    # Function call: divide
    # Function call: subtract
    lw $t3, 8($sp)
    move $a0, $t3    # Arg 0
    lw $t4, 0($sp)
    move $a1, $t4    # Arg 1
    jal func_subtract             # Call function
    move $t5, $v0      # Get return value
    move $a0, $t5    # Arg 0
    # Function call: add
    lw $t6, 4($sp)
    move $a0, $t6    # Arg 0
    li $t7, 2
    move $a1, $t0    # Arg 1
    jal func_add             # Call function
    move $t0, $v0      # Get return value
    move $a1, $t0    # Arg 1
    jal func_divide             # Call function
    move $t1, $v0      # Get return value
    move $a1, $t1    # Arg 1
    jal func_add             # Call function
    move $t2, $v0      # Get return value
    # Print integer (expr)
    move $a0, $t2
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: add
    # Function call: multiply
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    li $t1, 5
    move $a1, $t1    # Arg 1
    jal func_multiply             # Call function
    move $t2, $v0      # Get return value
    move $a0, $t2    # Arg 0
    # Function call: subtract
    lw $t3, 4($sp)
    move $a0, $t3    # Arg 0
    li $t4, 10
    move $a1, $t4    # Arg 1
    jal func_subtract             # Call function
    move $t5, $v0      # Get return value
    move $a1, $t5    # Arg 1
    jal func_add             # Call function
    move $t6, $v0      # Get return value
    # Function call: divide
    lw $t7, 8($sp)
    move $a0, $t0    # Arg 0
    li $t0, 2
    move $a1, $t0    # Arg 1
    jal func_divide             # Call function
    move $t1, $v0      # Get return value
    # Addition
    add $t6, $t6, $t1
    sw $t6, 12($sp)
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function epilogue (default return)
_user_main_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

main_code:
    # Function call: main
    jal _user_main             # Call function
    move $t0, $v0      # Get return value

    # Exit program
    addi $sp, $sp, 400
    li $v0, 10
    syscall

# Infinite loop to prevent bad instruction exceptions
__post_exit_stub:
    li $v0, 10
    syscall
    j __post_exit_stub    # Loop forever

# concat helper - allocate and concatenate two asciiz strings
# Inputs: a0 = ptr1, a1 = ptr2; Returns: v0 = ptr to new buffer
concat:
    addi $sp, $sp, -32
    sw $ra, 28($sp)
    sw $s0, 24($sp)
    sw $s1, 20($sp)
    sw $s2, 16($sp)
    move $s1, $a0
    move $s2, $a1
    move $t0, $s1
    li $t1, 0
strlen_loop1:
    lb $t2, 0($t0)
    beq $t2, $zero, strlen_done1
    addi $t1, $t1, 1
    addi $t0, $t0, 1
    j strlen_loop1
strlen_done1:
    move $t0, $s2
    li $t2, 0
strlen_loop2:
    lb $t3, 0($t0)
    beq $t3, $zero, strlen_done2
    addi $t2, $t2, 1
    addi $t0, $t0, 1
    j strlen_loop2
strlen_done2:
    add $a0, $t1, $t2
    addi $a0, $a0, 1
    li $v0, 9
    syscall
    move $s0, $v0    # s0 = dest ptr
    move $t6, $s1
    move $t7, $s0
copy1_loop:
    lb $t8, 0($t6)
    beq $t8, $zero, copy1_done
    sb $t8, 0($t7)
    addi $t6, $t6, 1
    addi $t7, $t7, 1
    j copy1_loop
copy1_done:
    move $t6, $s2
copy2_loop:
    lb $t8, 0($t6)
    beq $t8, $zero, copy2_done
    sb $t8, 0($t7)
    addi $t6, $t6, 1
    addi $t7, $t7, 1
    j copy2_loop
copy2_done:
    sb $zero, 0($t7)
    move $v0, $s0
    lw $s2, 16($sp)
    lw $s1, 20($sp)
    lw $s0, 24($sp)
    lw $ra, 28($sp)
    addi $sp, $sp, 32
    jr $ra

