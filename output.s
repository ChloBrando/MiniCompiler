.data
str_literal_0: .asciiz "=== Simple Test ==="
str_literal_1: .asciiz "Hello"
str_literal_2: .asciiz "=== Done ==="
float_literal_0: .float 3.140000

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400
    j main_code        # Jump to main program


# Function: addNums
addNums:
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
    # Addition
    add $t0, $t0, $t1
    move $v0, $t0       # Set return value
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
addNums_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: return5
return5:
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
return5_return:
    lw $fp, 24($sp)      # Restore frame pointer
    lw $ra, 28($sp)      # Restore return address
    addi $sp, $sp, 32    # Deallocate stack frame
    jr $ra               # Return to caller

main_code:
    # load address of string literal
    la $t2, str_literal_0
    # Print string expression
    move $a0, $t2
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared x at offset 0
    li $t0, 10
    sw $t0, 0($sp)
    lw $t0, 0($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared float y at offset 4
    # Load float literal 3.140000
    la $t0, float_literal_0
    lwc1 $f0, 0($t0)
    swc1 $f0, 4($sp)
    lwc1 $f0, 4($sp)
    # Print float
    mov.s $f12, $f0
    li $v0, 2
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared string s at offset 8
    # load address of string literal
    la $t0, str_literal_1
    sw $t0, 8($sp)
    lw $t0, 8($sp)
    # Print string variable s
    lw $a0, 8($sp)
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Declared array arr[2] at offset 12
    li $t0, 0
    li $t1, 5
    # Array assignment: arr[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t2, $sp, 12   # base address
    add $t2, $t2, $t0 # element address
    sw $t1, 0($t2)     # store value
    li $t0, 1
    li $t1, 0
    # Array access: arr[index]
    sll $t1, $t1, 2    # index * 4
    addi $t2, $sp, 12   # base address
    add $t2, $t2, $t1 # element address
    lw $t2, 0($t2)     # load value
    li $t3, 3
    # Addition
    add $t2, $t2, $t3
    # Array assignment: arr[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t3, $sp, 12   # base address
    add $t3, $t3, $t0 # element address
    sw $t2, 0($t3)     # store value
    li $t0, 1
    # Array access: arr[index]
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
    # Declared result at offset 20
    # Function call: addNums
    li $t0, 4
    move $a0, $t0    # Arg 0
    li $t1, 6
    move $a1, $t1    # Arg 1
    jal addNums             # Call function
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
    # Declared five at offset 24
    # Function call: return5
    jal return5             # Call function
    move $t0, $v0      # Get return value
    sw $t0, 24($sp)
    lw $t0, 24($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_2
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

