.data

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400

    # Declared array data[4] at offset 0
    # Declared index at offset 16
    # Declared sum at offset 20
    li $t0, 0
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    li $t1, 100
    # Array assignment: data[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t2, $sp, 0   # base address
    add $t2, $t2, $t0 # element address
    sw $t1, 0($t2)     # store value
    li $t0, 1
    sw $t0, 16($sp)
    lw $t0, 16($sp)
    li $t1, 200
    # Array assignment: data[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t2, $sp, 0   # base address
    add $t2, $t2, $t0 # element address
    sw $t1, 0($t2)     # store value
    li $t0, 0
    # Array access: data[index]
    sll $t0, $t0, 2    # index * 4
    addi $t1, $sp, 0   # base address
    add $t1, $t1, $t0 # element address
    lw $t1, 0($t1)     # load value
    li $t2, 1
    # Array access: data[index]
    sll $t2, $t2, 2    # index * 4
    addi $t3, $sp, 0   # base address
    add $t3, $t3, $t2 # element address
    lw $t3, 0($t3)     # load value
    # Addition
    add $t1, $t1, $t3
    sw $t1, 20($sp)
    lw $t0, 20($sp)
    # Print integer
    move $a0, $t0
    li $v0, 1
    syscall
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall

    # Exit program
    addi $sp, $sp, 400
    li $v0, 10
    syscall
