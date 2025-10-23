.data

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400
    j main_code        # Jump to main program


# Function: multiply
multiply:
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
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Multiplication
    mul $t0, $t0, $t1
    move $v0, $t0       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
multiply_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: divide
divide:
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
    lw $t1, 0($sp)
    lw $t2, 4($sp)
    # Division
    div $t1, $t1, $t2
    move $v0, $t1       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
divide_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

main_code:
    # Declared x at offset 0
    li $t2, 5
    li $t3, 3
    # Multiplication
    mul $t2, $t2, $t3
    sw $t2, 0($sp)
    lw $t0, 0($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared y at offset 4
    li $t0, 20
    li $t1, 4
    # Division
    div $t0, $t0, $t1
    sw $t0, 4($sp)
    lw $t0, 4($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared z at offset 8
    li $t0, 10
    li $t1, 2
    li $t2, 3
    # Multiplication
    mul $t1, $t1, $t2
    # Addition
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared result at offset 12
    li $t0, 100
    li $t1, 10
    li $t2, 5
    # Subtraction
    sub $t1, $t1, $t2
    # Division
    div $t0, $t0, $t1
    sw $t0, 12($sp)
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared prod at offset 16
    # Function call: multiply
    li $t0, 7
    move $a0, $t0    # Arg 0
    li $t1, 8
    move $a1, $t1    # Arg 1
    jal multiply             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 16($sp)
    lw $t0, 16($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared quot at offset 20
    # Function call: divide
    li $t0, 50
    move $a0, $t0    # Arg 0
    li $t1, 5
    move $a1, $t1    # Arg 1
    jal divide             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 20($sp)
    lw $t0, 20($sp)
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
