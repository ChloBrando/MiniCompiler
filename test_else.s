.data
str_literal_0: .asciiz "a is greater"
str_literal_1: .asciiz "b is greater or equal"
str_literal_2: .asciiz "they are equal"
str_literal_3: .asciiz "they are not equal"

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400
    j main_code        # Jump to main program


main_code:
    # Declared a at offset 0
    # Declared b at offset 4
    li $t0, 5
    sw $t0, 0($sp)
    li $t0, 10
    sw $t0, 4($sp)
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, else_label_0
    # load address of string literal
    la $t3, str_literal_0
    # Print string expression
    move $a0, $t3
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j endif_label_0
else_label_0:
    # load address of string literal
    la $t0, str_literal_1
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_0:
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer equal
    xor $t2, $t0, $t1
    sltiu $t2, $t2, 1
    beq $t2, $zero, else_label_1
    # load address of string literal
    la $t3, str_literal_2
    # Print string expression
    move $a0, $t3
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j endif_label_1
else_label_1:
    # load address of string literal
    la $t0, str_literal_3
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_1:

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

