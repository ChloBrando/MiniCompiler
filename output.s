.data

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400
    j main_code        # Jump to main program


# Function: bigger
bigger:
    # Function prologue
    addi $sp, $sp, -32    # Allocate stack frame
    sw $ra, 28($sp)      # Save return address
    sw $fp, 24($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'number'
    # Function body
    # Declared bNumber at offset 4
    lw $t0, 0($sp)
    lw $t1, 0($sp)
    # Addition
    add $t0, $t0, $t1
    sw $t0, 4($sp)
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
bigger_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: smaller
smaller:
    # Function prologue
    addi $sp, $sp, -32    # Allocate stack frame
    sw $ra, 28($sp)      # Save return address
    sw $fp, 24($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'number'
    # Function body
    # Declared sNumber at offset 4
    lw $t1, 0($sp)
    li $t2, 5
    # Subtraction
    sub $t1, $t1, $t2
    sw $t1, 4($sp)
    # Return statement
    lw $t0, 4($sp)
    move $v0, $t0       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
smaller_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

main_code:
    # Declared parameter at offset 0
    li $t1, 10
    sw $t1, 0($sp)
    # Declared resultBigger at offset 4
    # Function call: bigger
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    jal bigger             # Call function
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
    # Declared resultSmaller at offset 8
    # Function call: smaller
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    jal smaller             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 8($sp)
    lw $t0, 8($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared array numbers[5] at offset 12
    li $t0, 0
    li $t1, 10
    # Array assignment: numbers[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t2, $sp, 12   # base address
    add $t2, $t2, $t0 # element address
    sw $t1, 0($t2)     # store value
    li $t0, 1
    li $t1, 20
    # Array assignment: numbers[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t2, $sp, 12   # base address
    add $t2, $t2, $t0 # element address
    sw $t1, 0($t2)     # store value
    li $t0, 2
    li $t1, 30
    # Array assignment: numbers[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t2, $sp, 12   # base address
    add $t2, $t2, $t0 # element address
    sw $t1, 0($t2)     # store value
    li $t0, 3
    li $t1, 40
    # Array assignment: numbers[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t2, $sp, 12   # base address
    add $t2, $t2, $t0 # element address
    sw $t1, 0($t2)     # store value
    li $t0, 4
    li $t1, 50
    # Array assignment: numbers[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t2, $sp, 12   # base address
    add $t2, $t2, $t0 # element address
    sw $t1, 0($t2)     # store value
    li $t0, 0
    # Array access: numbers[index]
    sll $t0, $t0, 2    # index * 4
    addi $t1, $sp, 12   # base address
    add $t1, $t1, $t0 # element address
    lw $t1, 0($t1)     # load value
    # Print integer (expr)
    move $a0, $t1
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 2
    # Array access: numbers[index]
    sll $t0, $t0, 2    # index * 4
    addi $t1, $sp, 12   # base address
    add $t1, $t1, $t0 # element address
    lw $t1, 0($t1)     # load value
    # Print integer (expr)
    move $a0, $t1
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 4
    # Array access: numbers[index]
    sll $t0, $t0, 2    # index * 4
    addi $t1, $sp, 12   # base address
    add $t1, $t1, $t0 # element address
    lw $t1, 0($t1)     # load value
    # Print integer (expr)
    move $a0, $t1
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall

    # Exit program
    addi $sp, $sp, 400
    li $v0, 10
    syscall
