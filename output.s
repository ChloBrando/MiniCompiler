.data
str_literal_0: .asciiz "===== FUNCTION TESTS ====="
str_literal_1: .asciiz "Test 1: getConstant()"
str_literal_2: .asciiz "Result: "
str_literal_3: .asciiz "Expected: 42"
str_literal_4: .asciiz "Test 2: double(7)"
str_literal_5: .asciiz "Expected: 14"
str_literal_6: .asciiz "Test 3: addTwo(5, 3)"
str_literal_7: .asciiz "Expected: 8"
str_literal_8: .asciiz "Test 4: addThree(1, 2, 3)"
str_literal_9: .asciiz "Expected: 6"
str_literal_10: .asciiz "Test 5: compute(5, 10)"
str_literal_11: .asciiz "Expected: 20"
str_literal_12: .asciiz "Test 6: testScope(50)"
str_literal_13: .asciiz "Expected: 60"
str_literal_14: .asciiz "Global x still: "
str_literal_15: .asciiz "Expected: 100"
str_literal_16: .asciiz "Test 7: getFive()"
str_literal_17: .asciiz "Expected: 5"
str_literal_18: .asciiz "Test 8: addTwo(getFive(), double(3))"
str_literal_19: .asciiz "Expected: 11"
str_literal_20: .asciiz "Test 9: Arrays with functions"
str_literal_21: .asciiz "arr[0]: "
str_literal_22: .asciiz "arr[1]: "
str_literal_23: .asciiz "arr[2]: "
str_literal_24: .asciiz "Expected: 5, 8, 13"
str_literal_25: .asciiz "===== ALL TESTS COMPLETE ====="

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400
    j main_code        # Jump to main program


# Function: getConstant
getConstant:
    # Function prologue
    addi $sp, $sp, -32    # Allocate stack frame
    sw $ra, 28($sp)      # Save return address
    sw $fp, 24($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    # Function body
    # Declared value at offset 0
    li $t0, 42
    sw $t0, 0($sp)
    # Return statement
    lw $t0, 0($sp)
    move $v0, $t0       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
getConstant_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: double
double:
    # Function prologue
    addi $sp, $sp, -32    # Allocate stack frame
    sw $ra, 28($sp)      # Save return address
    sw $fp, 24($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'x'
    # Function body
    # Declared result at offset 4
    lw $t1, 0($sp)
    lw $t2, 0($sp)
    # Addition
    add $t1, $t1, $t2
    sw $t1, 4($sp)
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
double_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: addTwo
addTwo:
    # Function prologue
    addi $sp, $sp, -32    # Allocate stack frame
    sw $ra, 28($sp)      # Save return address
    sw $fp, 24($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    # Function body
    # Declared sum at offset 8
    lw $t1, 0($sp)
    lw $t2, 4($sp)
    # Addition
    add $t1, $t1, $t2
    sw $t1, 8($sp)
    # Return statement
    lw $t0, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
addTwo_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: addThree
addThree:
    # Function prologue
    addi $sp, $sp, -32    # Allocate stack frame
    sw $ra, 28($sp)      # Save return address
    sw $fp, 24($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'x'
    sw $a1, 4($sp)     # Store param 'y'
    sw $a2, 8($sp)     # Store param 'z'
    # Function body
    # Declared temp at offset 12
    # Declared result at offset 16
    lw $t1, 0($sp)
    lw $t2, 4($sp)
    # Addition
    add $t1, $t1, $t2
    sw $t1, 12($sp)
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    # Addition
    add $t0, $t0, $t1
    sw $t0, 16($sp)
    # Return statement
    lw $t0, 16($sp)
    move $v0, $t0       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
addThree_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: compute
compute:
    # Function prologue
    addi $sp, $sp, -32    # Allocate stack frame
    sw $ra, 28($sp)      # Save return address
    sw $fp, 24($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    # Function body
    # Declared doubled at offset 8
    # Declared added at offset 12
    # Function call: double
    lw $t1, 0($sp)
    move $a0, $t1    # Arg 0
    jal double             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 8($sp)
    # Function call: addTwo
    lw $t0, 8($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal addTwo             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 12($sp)
    # Return statement
    lw $t0, 12($sp)
    move $v0, $t0       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
compute_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: testScope
testScope:
    # Function prologue
    addi $sp, $sp, -32    # Allocate stack frame
    sw $ra, 28($sp)      # Save return address
    sw $fp, 24($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'x'
    # Function body
    # Declared y at offset 4
    lw $t1, 0($sp)
    li $t2, 10
    # Addition
    add $t1, $t1, $t2
    sw $t1, 4($sp)
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
testScope_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: getFive
getFive:
    # Function prologue
    addi $sp, $sp, -32    # Allocate stack frame
    sw $ra, 28($sp)      # Save return address
    sw $fp, 24($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    # Function body
    # Return statement
    li $t1, 5
    move $v0, $t1       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
getFive_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

main_code:
    # Declared x at offset 0
    li $t2, 100
    sw $t2, 0($sp)
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
    # Declared const at offset 4
    # Function call: getConstant
    jal getConstant             # Call function
    move $t0, $v0      # Get return value
    sw $t0, 4($sp)
    # load address of string literal
    la $t0, str_literal_2
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 4($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_3
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_4
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared doubled at offset 8
    # Function call: double
    li $t0, 7
    move $a0, $t0    # Arg 0
    jal double             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 8($sp)
    # load address of string literal
    la $t0, str_literal_2
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 8($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_5
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_6
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared sum at offset 12
    # Function call: addTwo
    li $t0, 5
    move $a0, $t0    # Arg 0
    li $t1, 3
    move $a1, $t1    # Arg 1
    jal addTwo             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 12($sp)
    # load address of string literal
    la $t0, str_literal_2
    # Print string expression
    move $a0, $t0
    li $v0, 4
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
    # load address of string literal
    la $t0, str_literal_7
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_8
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared sum3 at offset 16
    # Function call: addThree
    move $a0, $t0    # Arg 0
    li $t0, 3
    move $a1, $t0    # Arg 1
    jal addThree             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 16($sp)
    # load address of string literal
    la $t0, str_literal_2
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 16($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_9
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_10
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared result at offset 20
    # Function call: compute
    li $t0, 5
    move $a0, $t0    # Arg 0
    li $t1, 10
    move $a1, $t1    # Arg 1
    jal compute             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 20($sp)
    # load address of string literal
    la $t0, str_literal_2
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 20($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_11
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_12
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared scoped at offset 24
    # Function call: testScope
    li $t0, 50
    move $a0, $t0    # Arg 0
    jal testScope             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 24($sp)
    # load address of string literal
    la $t0, str_literal_2
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 24($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_13
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_14
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 0($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_15
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_16
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared five at offset 28
    # Function call: getFive
    jal getFive             # Call function
    move $t0, $v0      # Get return value
    sw $t0, 28($sp)
    # load address of string literal
    la $t0, str_literal_2
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 28($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_17
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_18
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared complex at offset 32
    # Function call: addTwo
    # Function call: getFive
    jal getFive             # Call function
    move $t0, $v0      # Get return value
    move $a0, $t0    # Arg 0
    # Function call: double
    li $t1, 3
    move $a0, $t1    # Arg 0
    jal double             # Call function
    move $t2, $v0      # Get return value
    move $a1, $t2    # Arg 1
    jal addTwo             # Call function
    move $t3, $v0      # Get return value
    sw $t3, 32($sp)
    # load address of string literal
    la $t0, str_literal_2
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 32($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_19
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_20
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared array arr[3] at offset 36
    li $t0, 0
    # Function call: getFive
    jal getFive             # Call function
    move $t1, $v0      # Get return value
    # Array assignment: arr[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t2, $sp, 36   # base address
    add $t2, $t2, $t0 # element address
    sw $t1, 0($t2)     # store value
    li $t0, 1
    # Function call: double
    li $t1, 4
    move $a0, $t1    # Arg 0
    jal double             # Call function
    move $t2, $v0      # Get return value
    # Array assignment: arr[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t3, $sp, 36   # base address
    add $t3, $t3, $t0 # element address
    sw $t2, 0($t3)     # store value
    li $t0, 2
    # Function call: addTwo
    li $t1, 0
    # Array access: arr[index]
    sll $t1, $t1, 2    # index * 4
    addi $t2, $sp, 36   # base address
    add $t2, $t2, $t1 # element address
    lw $t2, 0($t2)     # load value
    move $a0, $t2    # Arg 0
    li $t3, 1
    # Array access: arr[index]
    sll $t3, $t3, 2    # index * 4
    addi $t4, $sp, 36   # base address
    add $t4, $t4, $t3 # element address
    lw $t4, 0($t4)     # load value
    move $a1, $t4    # Arg 1
    jal addTwo             # Call function
    move $t5, $v0      # Get return value
    # Array assignment: arr[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t6, $sp, 36   # base address
    add $t6, $t6, $t0 # element address
    sw $t5, 0($t6)     # store value
    # load address of string literal
    la $t0, str_literal_21
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 0
    # Array access: arr[index]
    sll $t0, $t0, 2    # index * 4
    addi $t1, $sp, 36   # base address
    add $t1, $t1, $t0 # element address
    lw $t1, 0($t1)     # load value
    # Print integer (expr)
    move $a0, $t1
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_22
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 1
    # Array access: arr[index]
    sll $t0, $t0, 2    # index * 4
    addi $t1, $sp, 36   # base address
    add $t1, $t1, $t0 # element address
    lw $t1, 0($t1)     # load value
    # Print integer (expr)
    move $a0, $t1
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_23
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 2
    # Array access: arr[index]
    sll $t0, $t0, 2    # index * 4
    addi $t1, $sp, 36   # base address
    add $t1, $t1, $t0 # element address
    lw $t1, 0($t1)     # load value
    # Print integer (expr)
    move $a0, $t1
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_24
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_25
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall

    # Exit program
    addi $sp, $sp, 400
    li $v0, 10
    syscall

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

