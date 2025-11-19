.data

.text
.globl main
main:
    # Allocate stack space
    addi $sp, $sp, -400
    j main_code        # Jump to main program


# Function: max
func_max:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    # Function body
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, else_label_0
    # Return statement
    lw $t3, 0($sp)
    move $v0, $t3       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    j endif_label_0
else_label_0:
    # Return statement
    lw $t4, 4($sp)
    move $v0, $t4       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
endif_label_0:
    # Function epilogue (default return)
func_max_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: min
func_min:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    # Function body
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, else_label_1
    # Return statement
    lw $t3, 0($sp)
    move $v0, $t3       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    j endif_label_1
else_label_1:
    # Return statement
    lw $t4, 4($sp)
    move $v0, $t4       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
endif_label_1:
    # Function epilogue (default return)
func_min_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: absolute
func_absolute:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'n'
    # Function body
    # If statement
    lw $t0, 0($sp)
    li $t1, 0
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, else_label_2
    # Return statement
    li $t3, 0
    lw $t4, 0($sp)
    # Subtraction
    sub $t3, $t3, $t4
    move $v0, $t3       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    j endif_label_2
else_label_2:
    # Return statement
    lw $t4, 0($sp)
    move $v0, $t4       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
endif_label_2:
    # Function epilogue (default return)
func_absolute_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: sign
func_sign:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'n'
    # Function body
    # If statement
    lw $t0, 0($sp)
    li $t1, 0
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, else_label_3
    # Return statement
    li $t3, 1
    move $v0, $t3       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    j endif_label_3
else_label_3:
    # If statement
    lw $t4, 0($sp)
    li $t5, 0
    # Integer less than
    slt $t6, $t4, $t5
    beq $t6, $zero, else_label_4
    # Return statement
    li $t7, 0
    li $t0, 1
    # Subtraction
    sub $t0, $t0, $t0
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    j endif_label_4
else_label_4:
    # Return statement
    li $t1, 0
    move $v0, $t1       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
endif_label_4:
endif_label_3:
    # Function epilogue (default return)
func_sign_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: compare
func_compare:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    # Function body
    # Declared result at offset 8
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, else_label_5
    li $t3, 1
    sw $t3, 8($sp)
    j endif_label_5
else_label_5:
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, else_label_6
    li $t3, 0
    li $t4, 1
    # Subtraction
    sub $t3, $t3, $t4
    sw $t3, 8($sp)
    j endif_label_6
else_label_6:
    li $t0, 0
    sw $t0, 8($sp)
endif_label_6:
endif_label_5:
    # Return statement
    lw $t0, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_compare_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: max3
func_max3:
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
    # Declared maxAB at offset 12
    # If statement
    lw $t1, 0($sp)
    lw $t2, 4($sp)
    # Integer greater than
    slt $t3, $t2, $t1
    beq $t3, $zero, else_label_7
    lw $t4, 0($sp)
    sw $t4, 12($sp)
    j endif_label_7
else_label_7:
    lw $t0, 4($sp)
    sw $t0, 12($sp)
endif_label_7:
    # If statement
    lw $t0, 12($sp)
    lw $t1, 8($sp)
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, else_label_8
    # Return statement
    lw $t3, 12($sp)
    move $v0, $t3       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    j endif_label_8
else_label_8:
    # Return statement
    lw $t4, 8($sp)
    move $v0, $t4       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
endif_label_8:
    # Function epilogue (default return)
func_max3_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: min3
func_min3:
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
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, else_label_9
    # If statement
    lw $t3, 0($sp)
    lw $t4, 8($sp)
    # Integer less than
    slt $t5, $t3, $t4
    beq $t5, $zero, else_label_10
    # Return statement
    lw $t6, 0($sp)
    move $v0, $t6       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    j endif_label_10
else_label_10:
    # Return statement
    lw $t7, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
endif_label_10:
    j endif_label_9
else_label_9:
    # If statement
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, else_label_11
    # Return statement
    lw $t3, 4($sp)
    move $v0, $t3       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    j endif_label_11
else_label_11:
    # Return statement
    lw $t4, 8($sp)
    move $v0, $t4       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
endif_label_11:
endif_label_9:
    # Function epilogue (default return)
func_min3_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: inRange
func_inRange:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'value'
    sw $a1, 4($sp)     # Store param 'low'
    sw $a2, 8($sp)     # Store param 'high'
    # Function body
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer greater than or equal
    slt $t2, $t0, $t1
    xori $t2, $t2, 1
    beq $t2, $zero, else_label_12
    # If statement
    lw $t3, 0($sp)
    lw $t4, 8($sp)
    # Integer less than or equal
    slt $t5, $t4, $t3
    xori $t5, $t5, 1
    beq $t5, $zero, else_label_13
    # Return statement
    li $t6, 1
    move $v0, $t6       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    j endif_label_13
else_label_13:
    # Return statement
    li $t7, 0
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
endif_label_13:
    j endif_label_12
else_label_12:
    # Return statement
    li $t0, 0
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
endif_label_12:
    # Function epilogue (default return)
func_inRange_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: conditionalAdd
func_conditionalAdd:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    # Function body
    # If statement
    lw $t0, 0($sp)
    li $t1, 0
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, else_label_14
    # If statement
    lw $t3, 4($sp)
    li $t4, 0
    # Integer greater than
    slt $t5, $t4, $t3
    beq $t5, $zero, else_label_15
    # Return statement
    lw $t6, 0($sp)
    lw $t7, 4($sp)
    # Addition
    add $t6, $t6, $t0
    move $v0, $t6       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    j endif_label_15
else_label_15:
    # Return statement
    lw $t7, 0($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
endif_label_15:
    j endif_label_14
else_label_14:
    # If statement
    lw $t0, 4($sp)
    li $t1, 0
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, else_label_16
    # Return statement
    lw $t3, 4($sp)
    move $v0, $t3       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    j endif_label_16
else_label_16:
    # Return statement
    li $t4, 0
    move $v0, $t4       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
endif_label_16:
endif_label_14:
    # Function epilogue (default return)
func_conditionalAdd_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: safeDivide
func_safeDivide:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'numerator'
    sw $a1, 4($sp)     # Store param 'denominator'
    # Function body
    # If statement
    lw $t0, 4($sp)
    li $t1, 0
    # Integer equal
    xor $t2, $t0, $t1
    sltiu $t2, $t2, 1
    beq $t2, $zero, else_label_17
    # Return statement
    li $t3, 0
    move $v0, $t3       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    j endif_label_17
else_label_17:
    # Return statement
    lw $t4, 0($sp)
    lw $t5, 4($sp)
    # Division
    div $t4, $t5      # Divide: result in LO
    mflo $t4           # Move quotient from LO
    move $v0, $t4       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
endif_label_17:
    # Function epilogue (default return)
func_safeDivide_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: conditionalMultiply
func_conditionalMultiply:
    # Function prologue
    addi $sp, $sp, -128    # Allocate stack frame
    sw $ra, 124($sp)      # Save return address
    sw $fp, 120($sp)      # Save frame pointer
    move $fp, $sp        # Set new frame pointer
    # Store parameters
    sw $a0, 0($sp)     # Store param 'a'
    sw $a1, 4($sp)     # Store param 'b'
    # Function body
    # Declared result at offset 8
    # If statement
    lw $t0, 0($sp)
    li $t1, 0
    # Integer not equal
    xor $t2, $t0, $t1
    sltu $t2, $zero, $t2
    beq $t2, $zero, else_label_18
    # If statement
    lw $t3, 4($sp)
    li $t4, 0
    # Integer not equal
    xor $t5, $t3, $t4
    sltu $t5, $zero, $t5
    beq $t5, $zero, else_label_19
    lw $t6, 0($sp)
    lw $t7, 4($sp)
    # Multiplication
    mul $t6, $t6, $t0
    sw $t6, 8($sp)
    j endif_label_19
else_label_19:
    li $t0, 0
    sw $t0, 8($sp)
endif_label_19:
    j endif_label_18
else_label_18:
    li $t0, 0
    sw $t0, 8($sp)
endif_label_18:
    # Return statement
    lw $t0, 8($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_conditionalMultiply_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: complexCondition
func_complexCondition:
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
    # Declared result at offset 12
    # If statement
    # Function call: max
    lw $t1, 0($sp)
    move $a0, $t1    # Arg 0
    lw $t2, 4($sp)
    move $a1, $t2    # Arg 1
    jal func_max             # Call function
    move $t3, $v0      # Get return value
    lw $t4, 8($sp)
    # Integer greater than
    slt $t5, $t4, $t3
    beq $t5, $zero, else_label_20
    # Function call: max
    lw $t6, 0($sp)
    move $a0, $t6    # Arg 0
    lw $t7, 4($sp)
    move $a1, $t0    # Arg 1
    jal func_max             # Call function
    move $t0, $v0      # Get return value
    lw $t1, 8($sp)
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
    j endif_label_20
else_label_20:
    # If statement
    # Function call: min
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_min             # Call function
    move $t2, $v0      # Get return value
    lw $t3, 8($sp)
    # Integer less than
    slt $t4, $t2, $t3
    beq $t4, $zero, else_label_21
    # Function call: min
    lw $t5, 0($sp)
    move $a0, $t5    # Arg 0
    lw $t6, 4($sp)
    move $a1, $t6    # Arg 1
    jal func_min             # Call function
    move $t7, $v0      # Get return value
    lw $t0, 8($sp)
    # Subtraction
    sub $t0, $t0, $t0
    sw $t0, 12($sp)
    j endif_label_21
else_label_21:
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Addition
    add $t0, $t0, $t1
    lw $t1, 8($sp)
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
endif_label_21:
endif_label_20:
    # Return statement
    lw $t0, 12($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_complexCondition_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

# Function: nestedWithFunctions
func_nestedWithFunctions:
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
    # Declared result at offset 12
    # If statement
    # Function call: absolute
    lw $t1, 0($sp)
    move $a0, $t1    # Arg 0
    jal func_absolute             # Call function
    move $t2, $v0      # Get return value
    # Function call: absolute
    lw $t3, 4($sp)
    move $a0, $t3    # Arg 0
    jal func_absolute             # Call function
    move $t4, $v0      # Get return value
    # Integer greater than
    slt $t5, $t4, $t2
    beq $t5, $zero, else_label_22
    # If statement
    # Function call: max
    lw $t6, 0($sp)
    move $a0, $t6    # Arg 0
    lw $t7, 8($sp)
    move $a1, $t0    # Arg 1
    jal func_max             # Call function
    move $t0, $v0      # Get return value
    li $t1, 0
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, else_label_23
    # Function call: max
    lw $t3, 0($sp)
    move $a0, $t3    # Arg 0
    lw $t4, 8($sp)
    move $a1, $t4    # Arg 1
    jal func_max             # Call function
    move $t5, $v0      # Get return value
    # Function call: min
    lw $t6, 4($sp)
    move $a0, $t6    # Arg 0
    lw $t7, 8($sp)
    move $a1, $t0    # Arg 1
    jal func_min             # Call function
    move $t0, $v0      # Get return value
    # Addition
    add $t5, $t5, $t0
    sw $t5, 12($sp)
    j endif_label_23
else_label_23:
    # Function call: absolute
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Subtraction
    sub $t0, $t0, $t1
    move $a0, $t0    # Arg 0
    jal func_absolute             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 12($sp)
endif_label_23:
    j endif_label_22
else_label_22:
    # If statement
    # Function call: compare
    lw $t0, 4($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 8($sp)
    move $a1, $t1    # Arg 1
    jal func_compare             # Call function
    move $t2, $v0      # Get return value
    li $t3, 0
    # Integer greater than
    slt $t4, $t3, $t2
    beq $t4, $zero, else_label_24
    lw $t5, 4($sp)
    lw $t6, 8($sp)
    # Multiplication
    mul $t5, $t5, $t6
    sw $t5, 12($sp)
    j endif_label_24
else_label_24:
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
endif_label_24:
endif_label_22:
    # Return statement
    lw $t0, 12($sp)
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
func_nestedWithFunctions_return:
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
    # Declared maxValue at offset 16
    # Declared minValue at offset 20
    # Declared absValue at offset 24
    # Declared signValue at offset 28
    # Read integer from user
    li $v0, 5           # Syscall 5: read integer
    syscall
    move $t1, $v0      # Store input value
    sw $t1, 0($sp)
    # Read integer from user
    li $v0, 5           # Syscall 5: read integer
    syscall
    move $t0, $v0      # Store input value
    sw $t0, 4($sp)
    # Read integer from user
    li $v0, 5           # Syscall 5: read integer
    syscall
    move $t0, $v0      # Store input value
    sw $t0, 8($sp)
    # Function call: max
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_max             # Call function
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
    # Function call: min
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_min             # Call function
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
    # Function call: absolute
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    jal func_absolute             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 24($sp)
    lw $t0, 24($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: sign
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    jal func_sign             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 28($sp)
    lw $t0, 28($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: compare
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_compare             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: max3
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    lw $t2, 8($sp)
    move $a2, $t2    # Arg 2
    jal func_max3             # Call function
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
    # Function call: min3
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    lw $t2, 8($sp)
    move $a2, $t2    # Arg 2
    jal func_min3             # Call function
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
    # If statement
    # Function call: inRange
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    li $t1, 0
    move $a1, $t1    # Arg 1
    li $t2, 100
    move $a2, $t2    # Arg 2
    jal func_inRange             # Call function
    move $t3, $v0      # Get return value
    li $t4, 1
    # Integer equal
    xor $t5, $t3, $t4
    sltiu $t5, $t5, 1
    beq $t5, $zero, else_label_25
    lw $t6, 0($sp)
    # Print integer (expr)
    move $a0, $t6
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j endif_label_25
else_label_25:
    li $t0, 0
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_25:
    # Function call: conditionalAdd
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_conditionalAdd             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: safeDivide
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_safeDivide             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: conditionalMultiply
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_conditionalMultiply             # Call function
    move $t2, $v0      # Get return value
    sw $t2, 12($sp)
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Function call: complexCondition
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    lw $t2, 8($sp)
    move $a2, $t2    # Arg 2
    jal func_complexCondition             # Call function
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
    # Function call: nestedWithFunctions
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    lw $t2, 8($sp)
    move $a2, $t2    # Arg 2
    jal func_nestedWithFunctions             # Call function
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
    # If statement
    # Function call: max
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_max             # Call function
    move $t2, $v0      # Get return value
    # Function call: min
    lw $t3, 4($sp)
    move $a0, $t3    # Arg 0
    lw $t4, 8($sp)
    move $a1, $t4    # Arg 1
    jal func_min             # Call function
    move $t5, $v0      # Get return value
    # Integer greater than
    slt $t6, $t5, $t2
    beq $t6, $zero, else_label_26
    # If statement
    # Function call: absolute
    lw $t7, 0($sp)
    move $a0, $t0    # Arg 0
    jal func_absolute             # Call function
    move $t0, $v0      # Get return value
    # Function call: absolute
    lw $t1, 8($sp)
    move $a0, $t1    # Arg 0
    jal func_absolute             # Call function
    move $t2, $v0      # Get return value
    # Integer greater than or equal
    slt $t3, $t0, $t2
    xori $t3, $t3, 1
    beq $t3, $zero, else_label_27
    lw $t4, 0($sp)
    lw $t5, 8($sp)
    # Addition
    add $t4, $t4, $t5
    sw $t4, 12($sp)
    j endif_label_27
else_label_27:
    lw $t0, 0($sp)
    lw $t1, 8($sp)
    # Subtraction
    sub $t0, $t0, $t1
    sw $t0, 12($sp)
endif_label_27:
    j endif_label_26
else_label_26:
    # If statement
    # Function call: compare
    lw $t0, 4($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 8($sp)
    move $a1, $t1    # Arg 1
    jal func_compare             # Call function
    move $t2, $v0      # Get return value
    li $t3, 0
    # Integer equal
    xor $t4, $t2, $t3
    sltiu $t4, $t4, 1
    beq $t4, $zero, else_label_28
    lw $t5, 4($sp)
    lw $t6, 8($sp)
    # Multiplication
    mul $t5, $t5, $t6
    sw $t5, 12($sp)
    j endif_label_28
else_label_28:
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    # Addition
    add $t0, $t0, $t1
    sw $t0, 12($sp)
endif_label_28:
endif_label_26:
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # If statement
    lw $t0, 0($sp)
    li $t1, 0
    # Integer greater than
    slt $t2, $t1, $t0
    beq $t2, $zero, endif_label_29
    li $t3, 1
    # Print integer (expr)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_29:
    # If statement
    lw $t0, 4($sp)
    li $t1, 0
    # Integer less than
    slt $t2, $t0, $t1
    beq $t2, $zero, endif_label_30
    li $t3, 2
    # Print integer (expr)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_30:
    # If statement
    lw $t0, 8($sp)
    li $t1, 0
    # Integer equal
    xor $t2, $t0, $t1
    sltiu $t2, $t2, 1
    beq $t2, $zero, endif_label_31
    li $t3, 3
    # Print integer (expr)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_31:
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer not equal
    xor $t2, $t0, $t1
    sltu $t2, $zero, $t2
    beq $t2, $zero, endif_label_32
    li $t3, 4
    # Print integer (expr)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_32:
    # If statement
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Integer less than or equal
    slt $t2, $t1, $t0
    xori $t2, $t2, 1
    beq $t2, $zero, endif_label_33
    li $t3, 5
    # Print integer (expr)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_33:
    # If statement
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    # Integer greater than or equal
    slt $t2, $t0, $t1
    xori $t2, $t2, 1
    beq $t2, $zero, endif_label_34
    li $t3, 6
    # Print integer (expr)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_34:
    # If statement
    # Function call: max
    # Function call: absolute
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    jal func_absolute             # Call function
    move $t1, $v0      # Get return value
    move $a0, $t1    # Arg 0
    # Function call: absolute
    lw $t2, 4($sp)
    move $a0, $t2    # Arg 0
    jal func_absolute             # Call function
    move $t3, $v0      # Get return value
    move $a1, $t3    # Arg 1
    jal func_max             # Call function
    move $t4, $v0      # Get return value
    # Function call: min3
    lw $t5, 8($sp)
    move $a0, $t5    # Arg 0
    lw $t6, 0($sp)
    move $a1, $t6    # Arg 1
    lw $t7, 4($sp)
    move $a2, $t0    # Arg 2
    jal func_min3             # Call function
    move $t0, $v0      # Get return value
    # Integer greater than
    slt $t1, $t0, $t4
    beq $t1, $zero, else_label_35
    # Function call: max
    # Function call: absolute
    lw $t2, 0($sp)
    move $a0, $t2    # Arg 0
    jal func_absolute             # Call function
    move $t3, $v0      # Get return value
    move $a0, $t3    # Arg 0
    # Function call: absolute
    lw $t4, 4($sp)
    move $a0, $t4    # Arg 0
    jal func_absolute             # Call function
    move $t5, $v0      # Get return value
    move $a1, $t5    # Arg 1
    jal func_max             # Call function
    move $t6, $v0      # Get return value
    # Print integer (expr)
    move $a0, $t6
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    j endif_label_35
else_label_35:
    # Function call: min3
    lw $t0, 8($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 0($sp)
    move $a1, $t1    # Arg 1
    lw $t2, 4($sp)
    move $a2, $t2    # Arg 2
    jal func_min3             # Call function
    move $t3, $v0      # Get return value
    # Print integer (expr)
    move $a0, $t3
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
endif_label_35:
    # If statement
    # Function call: compare
    # Function call: max
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    jal func_max             # Call function
    move $t2, $v0      # Get return value
    move $a0, $t2    # Arg 0
    # Function call: min
    lw $t3, 4($sp)
    move $a0, $t3    # Arg 0
    lw $t4, 8($sp)
    move $a1, $t4    # Arg 1
    jal func_min             # Call function
    move $t5, $v0      # Get return value
    move $a1, $t5    # Arg 1
    jal func_compare             # Call function
    move $t6, $v0      # Get return value
    li $t7, 0
    # Integer greater than
    slt $t0, $t7, $t6
    beq $t0, $zero, else_label_36
    # If statement
    # Function call: inRange
    lw $t1, 8($sp)
    move $a0, $t1    # Arg 0
    # Function call: min
    lw $t2, 0($sp)
    move $a0, $t2    # Arg 0
    lw $t3, 4($sp)
    move $a1, $t3    # Arg 1
    jal func_min             # Call function
    move $t4, $v0      # Get return value
    move $a1, $t4    # Arg 1
    # Function call: max
    lw $t5, 0($sp)
    move $a0, $t5    # Arg 0
    lw $t6, 4($sp)
    move $a1, $t6    # Arg 1
    jal func_max             # Call function
    move $t7, $v0      # Get return value
    move $a2, $t0    # Arg 2
    jal func_inRange             # Call function
    move $t0, $v0      # Get return value
    li $t1, 1
    # Integer equal
    xor $t2, $t0, $t1
    sltiu $t2, $t2, 1
    beq $t2, $zero, else_label_37
    # Function call: conditionalAdd
    lw $t3, 0($sp)
    move $a0, $t3    # Arg 0
    lw $t4, 4($sp)
    move $a1, $t4    # Arg 1
    jal func_conditionalAdd             # Call function
    move $t5, $v0      # Get return value
    # Function call: conditionalMultiply
    lw $t6, 4($sp)
    move $a0, $t6    # Arg 0
    lw $t7, 8($sp)
    move $a1, $t0    # Arg 1
    jal func_conditionalMultiply             # Call function
    move $t0, $v0      # Get return value
    # Addition
    add $t5, $t5, $t0
    sw $t5, 12($sp)
    j endif_label_37
else_label_37:
    # Function call: safeDivide
    # Function call: max3
    lw $t0, 0($sp)
    move $a0, $t0    # Arg 0
    lw $t1, 4($sp)
    move $a1, $t1    # Arg 1
    lw $t2, 8($sp)
    move $a2, $t2    # Arg 2
    jal func_max3             # Call function
    move $t3, $v0      # Get return value
    move $a0, $t3    # Arg 0
    # Function call: min3
    lw $t4, 0($sp)
    move $a0, $t4    # Arg 0
    lw $t5, 4($sp)
    move $a1, $t5    # Arg 1
    lw $t6, 8($sp)
    move $a2, $t6    # Arg 2
    jal func_min3             # Call function
    move $t7, $v0      # Get return value
    move $a1, $t0    # Arg 1
    jal func_safeDivide             # Call function
    move $t0, $v0      # Get return value
    sw $t0, 12($sp)
endif_label_37:
    j endif_label_36
else_label_36:
    # If statement
    # Function call: absolute
    lw $t0, 0($sp)
    lw $t1, 4($sp)
    # Subtraction
    sub $t0, $t0, $t1
    move $a0, $t0    # Arg 0
    jal func_absolute             # Call function
    move $t1, $v0      # Get return value
    # Function call: absolute
    lw $t2, 4($sp)
    lw $t3, 8($sp)
    # Subtraction
    sub $t2, $t2, $t3
    move $a0, $t2    # Arg 0
    jal func_absolute             # Call function
    move $t3, $v0      # Get return value
    # Integer greater than
    slt $t4, $t3, $t1
    beq $t4, $zero, else_label_38
    # Function call: absolute
    lw $t5, 0($sp)
    lw $t6, 4($sp)
    # Subtraction
    sub $t5, $t5, $t6
    move $a0, $t5    # Arg 0
    jal func_absolute             # Call function
    move $t6, $v0      # Get return value
    sw $t6, 12($sp)
    j endif_label_38
else_label_38:
    # Function call: absolute
    lw $t0, 4($sp)
    lw $t1, 8($sp)
    # Subtraction
    sub $t0, $t0, $t1
    move $a0, $t0    # Arg 0
    jal func_absolute             # Call function
    move $t1, $v0      # Get return value
    sw $t1, 12($sp)
endif_label_38:
endif_label_36:
    lw $t0, 12($sp)
    # Print integer (expr)
    move $a0, $t0
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 10
    syscall
    # Return statement
    li $t0, 0
    move $v0, $t0       # Set return value
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller
    # Function epilogue (default return)
_user_main_return:
    lw $fp, 120($sp)      # Restore frame pointer
    lw $ra, 124($sp)      # Restore return address
    addi $sp, $sp, 128    # Deallocate stack frame
    jr $ra               # Return to caller

main_code:
    # Function call: main
    jal _user_main             # Call function
    move $t1, $v0      # Get return value

    # Exit program
    addi $sp, $sp, 400
    li $v0, 10
    syscall

# Infinite loop to prevent bad instruction exceptions
__post_exit_stub:
    li $v0, 10
    syscall
    j __post_exit_stub    # Loop forever
