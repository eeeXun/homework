.data
t: .word 2
A: .word 15
B: .word 5
JumpTable: .word L0, L1, L2, L3

.text
main:
    lw $s0, A
    lw $s1, B
    la $t4, JumpTable
    lw $t1, t
    li $t2, 4
    slt $t3, $t1, $zero
    bne $t3, $zero, exit
    slt $t3, $t1, $t2
    beq $t3, $zero, exit
    sll $t1, $t1, 2         # t1 *= 4
    add $t1, $t1, $t4       # t1 = addr of JumpTable[t]
    lw $t0, 0($t1)          # t0 = JumpTable[t]
    jr $t0

L0:
    add $s2, $s0, $s1
    j print
L1:
    sub $s2, $s0, $s1
    j print
L2:
    mul $s2, $s0, $s1
    j print
L3:
    div $s2, $s0, $s1
    j print

print:
    li $v0, 1
    addi $a0, $s2, 0
    syscall
    j exit
exit:
    li $v0, 10
    syscall
