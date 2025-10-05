.data
str_literal_0: .asciiz "hi there"
str_literal_1: .asciiz "hello"
str_literal_2: .asciiz "world"
str_literal_3: .asciiz " "
str_literal_4: .asciiz "a = "
str_literal_5: .asciiz "b = "
str_literal_6: .asciiz "c = "
str_literal_7: .asciiz "arr[0] = "
str_literal_8: .asciiz "arr[1] = "
str_literal_9: .asciiz "arr[2] = "
str_literal_10: .asciiz "arr[3] = "
str_literal_11: .asciiz "arr[4] = "
str_literal_12: .asciiz "sum = "
str_literal_13: .asciiz "arr[i] = "

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400

    # Declared a at offset 0
    # Declared b at offset 4
    # Declared c at offset 8
    # Declared sum at offset 12
    # Declared array arr[5] at offset 16
    # Declared i at offset 36
    # Declared string s at offset 40
    # Declared string t at offset 44
    # Declared string u at offset 48
    # Declared string hi at offset 52
    # load address of string literal
    la $t0, str_literal_0
    sw $t0, 52($sp)
    lw $t0, 52($sp)
    # Print string variable hi
    lw $a0, 52($sp)
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # load address of string literal
    la $t0, str_literal_1
    sw $t0, 40($sp)
    # load address of string literal
    la $t0, str_literal_2
    sw $t0, 44($sp)
    lw $t0, 40($sp)
    # load address of string literal
    la $t1, str_literal_3
    # String concatenation
    move $a0, $t0
    move $a1, $t1
    jal concat
    move $t2, $v0
    lw $t3, 44($sp)
    # String concatenation
    move $a0, $t2
    move $a1, $t3
    jal concat
    move $t4, $v0
    sw $t4, 48($sp)
    lw $t0, 48($sp)
    # Print string variable u
    lw $a0, 48($sp)
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 5
    sw $t0, 0($sp)
    li $t0, 7
    sw $t0, 4($sp)
    # load address of string literal
    la $t0, str_literal_4
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
    la $t0, str_literal_5
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
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Addition
    add $t0, $t0, $t1
    li $t1, 3
    # Addition
    add $t0, $t0, $t1
    sw $t0, 8($sp)
    # load address of string literal
    la $t0, str_literal_6
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
    li $t0, 0
    li $t1, 1
    # Array assignment: arr[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t2, $sp, 16   # base address
    add $t2, $t2, $t0 # element address
    sw $t1, 0($t2)     # store value
    li $t0, 1
    li $t1, 2
    # Array assignment: arr[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t2, $sp, 16   # base address
    add $t2, $t2, $t0 # element address
    sw $t1, 0($t2)     # store value
    li $t0, 2
    lw $t1, 0($sp)
    lw $t2, 4($sp)
    # Addition
    add $t1, $t1, $t2
    # Array assignment: arr[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t2, $sp, 16   # base address
    add $t2, $t2, $t0 # element address
    sw $t1, 0($t2)     # store value
    li $t0, 2
    sw $t0, 36($sp)
    lw $t0, 36($sp)
    li $t1, 2
    # Array access: arr[index]
    sll $t1, $t1, 2    # index * 4
    addi $t2, $sp, 16   # base address
    add $t2, $t2, $t1 # element address
    lw $t2, 0($t2)     # load value
    lw $t3, 8($sp)
    # Addition
    add $t2, $t2, $t3
    # Array assignment: arr[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t3, $sp, 16   # base address
    add $t3, $t3, $t0 # element address
    sw $t2, 0($t3)     # store value
    li $t0, 4
    li $t1, 0
    # Array access: arr[index]
    sll $t1, $t1, 2    # index * 4
    addi $t2, $sp, 16   # base address
    add $t2, $t2, $t1 # element address
    lw $t2, 0($t2)     # load value
    li $t3, 1
    # Array access: arr[index]
    sll $t3, $t3, 2    # index * 4
    addi $t4, $sp, 16   # base address
    add $t4, $t4, $t3 # element address
    lw $t4, 0($t4)     # load value
    # Addition
    add $t2, $t2, $t4
    # Array assignment: arr[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t3, $sp, 16   # base address
    add $t3, $t3, $t0 # element address
    sw $t2, 0($t3)     # store value
    li $t0, 3
    li $t1, 0
    # Array access: arr[index]
    sll $t1, $t1, 2    # index * 4
    addi $t2, $sp, 16   # base address
    add $t2, $t2, $t1 # element address
    lw $t2, 0($t2)     # load value
    li $t3, 1
    # Array access: arr[index]
    sll $t3, $t3, 2    # index * 4
    addi $t4, $sp, 16   # base address
    add $t4, $t4, $t3 # element address
    lw $t4, 0($t4)     # load value
    # Addition
    add $t2, $t2, $t4
    li $t3, 4
    # Array access: arr[index]
    sll $t3, $t3, 2    # index * 4
    addi $t4, $sp, 16   # base address
    add $t4, $t4, $t3 # element address
    lw $t4, 0($t4)     # load value
    # Addition
    add $t2, $t2, $t4
    # Array assignment: arr[index] = value
    sll $t0, $t0, 2    # index * 4
    addi $t3, $sp, 16   # base address
    add $t3, $t3, $t0 # element address
    sw $t2, 0($t3)     # store value
    # load address of string literal
    la $t0, str_literal_7
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
    addi $t1, $sp, 16   # base address
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
    la $t0, str_literal_8
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
    addi $t1, $sp, 16   # base address
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
    la $t0, str_literal_9
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
    addi $t1, $sp, 16   # base address
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
    la $t0, str_literal_10
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 3
    # Array access: arr[index]
    sll $t0, $t0, 2    # index * 4
    addi $t1, $sp, 16   # base address
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
    la $t0, str_literal_11
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 4
    # Array access: arr[index]
    sll $t0, $t0, 2    # index * 4
    addi $t1, $sp, 16   # base address
    add $t1, $t1, $t0 # element address
    lw $t1, 0($t1)     # load value
    # Print integer (expr)
    move $a0, $t1
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    li $t0, 0
    # Array access: arr[index]
    sll $t0, $t0, 2    # index * 4
    addi $t1, $sp, 16   # base address
    add $t1, $t1, $t0 # element address
    lw $t1, 0($t1)     # load value
    li $t2, 1
    # Array access: arr[index]
    sll $t2, $t2, 2    # index * 4
    addi $t3, $sp, 16   # base address
    add $t3, $t3, $t2 # element address
    lw $t3, 0($t3)     # load value
    # Addition
    add $t1, $t1, $t3
    li $t2, 2
    # Array access: arr[index]
    sll $t2, $t2, 2    # index * 4
    addi $t3, $sp, 16   # base address
    add $t3, $t3, $t2 # element address
    lw $t3, 0($t3)     # load value
    # Addition
    add $t1, $t1, $t3
    li $t2, 4
    # Array access: arr[index]
    sll $t2, $t2, 2    # index * 4
    addi $t3, $sp, 16   # base address
    add $t3, $t3, $t2 # element address
    lw $t3, 0($t3)     # load value
    # Addition
    add $t1, $t1, $t3
    sw $t1, 12($sp)
    # load address of string literal
    la $t0, str_literal_12
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
    la $t0, str_literal_13
    # Print string expression
    move $a0, $t0
    li $v0, 4
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    lw $t0, 36($sp)
    # Array access: arr[index]
    sll $t0, $t0, 2    # index * 4
    addi $t1, $sp, 16   # base address
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

