.data

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
    li $t0, 5
    sw $t0, 4($sp)
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer equal
    xor $t2, $t0, $t1
    sltiu $t2, $t2, 1
    beq $t2, $zero, else_label_0
    li $t3, 1
    # Print integer (expr)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j endif_label_0
else_label_0:
    li $t0, 0
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_0:
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer not equal
    xor $t2, $t0, $t1
    sltu $t2, $zero, $t2
    beq $t2, $zero, else_label_1
    li $t3, 0
    # Print integer (expr)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j endif_label_1
else_label_1:
    li $t0, 1
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_1:
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer less than or equal
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    beq $t2, $zero, endif_label_2
    li $t3, 1
    # Print integer (expr)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_2:
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer greater than or equal
    slt $t2, $t0, $t1
    xori $t2, $t2, 1
    beq $t2, $zero, endif_label_3
    li $t3, 1
    # Print integer (expr)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_3:

    # Exit program
    addi $sp, $sp, 400
    li $v0, 10
    syscall
