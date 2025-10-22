.data

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400
    j main_code        # Jump to main program


# Function: getNumber
getNumber:
    # Function prologue
    addi $sp, $sp, -32    # Allocate stack frame
    sw $ra, 28($sp)      # Save return address
    sw $fp, 24($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    # Function body
    # Return statement
    li $t0, 42
    move $v0, $t0       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
getNumber_return:
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
    sw $a0, 0($sp)     # Store param 'n'
    # Function body
    # Return statement
    lw $t1, 0($sp)
    lw $t2, 0($sp)
    # Addition
    add $t1, $t1, $t2
    move $v0, $t1       # Set return value
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
    # Return statement
    lw $t2, 0($sp)
    lw $t3, 4($sp)
    # Addition
    add $t2, $t2, $t3
    move $v0, $t2       # Set return value
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
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    sw $a2, 8($sp)     # Store param 'c'
    # Function body
    # Declared temp at offset 12
    # Function call: addTwo
    lw $t3, 0($sp)
    move $a0, $t3    # Arg 0
    lw $t4, 4($sp)
    move $a1, $t4    # Arg 1
    jal addTwo             # Call function
    move $t5, $v0      # Get return value
    sw $t5, 12($sp)
    # Return statement
    # Function call: addTwo
    lw $t0, 12($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 8($sp)
    move $a1, $t1    # Arg 1
    jal addTwo             # Call function
    move $t2, $v0      # Get return value
    move $v0, $t2       # Set return value
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

# Function: func
func:
    # Function prologue
    addi $sp, $sp, -32    # Allocate stack frame
    sw $ra, 28($sp)      # Save return address
    sw $fp, 24($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'x'
    # Function body
    # Declared y at offset 4
    lw $t3, 0($sp)
    li $t4, 10
    # Addition
    add $t3, $t3, $t4
    sw $t3, 4($sp)
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

main_code:
    # Declared x at offset 0
    # Function call: getNumber
    jal getNumber             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 0($sp)
    lw $t0, 0($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared result at offset 4
    # Function call: double
    li $t0, 21
    move $a0, $t0    # Arg 0
    jal double             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 4($sp)
    lw $t0, 4($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: addTwo
    li $t0, 10
    move $a0, $t0    # Arg 0
    li $t1, 32
    move $a1, $t1    # Arg 1
    jal addTwo             # Call function
    move $t2, $v0      # Get return value
    # Print integer (expr)
    move $a0, $t2
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: addThree
    li $t0, 1
    move $a0, $t0    # Arg 0
    li $t1, 2
    move $a1, $t1    # Arg 1
    li $t2, 3
    move $a2, $t2    # Arg 2
    jal addThree             # Call function
    move $t3, $v0      # Get return value
    # Print integer (expr)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared global_x at offset 8
    li $t0, 5
    sw $t0, 8($sp)
    # Function call: func
    lw $t0, 8($sp)
    move $a0, $t0    # Arg 0
    jal func             # Call function
    move $t1, $v0      # Get return value
    # Print integer (expr)
    move $a0, $t1
    li $v0, 1
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

    # Exit program
    addi $sp, $sp, 400
    li $v0, 10
    syscall
