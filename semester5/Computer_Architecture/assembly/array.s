.data
num: .word 5, 4, 3, 2, 1
s: .word 2
space: .asciiz ", "

.text
main:   
    li $t0, 0
    lw $s0, s
    li $s1, 5
    li $s2, 2
    j loop

loop:
    # A[i] = A[(i + s * i) % 5] + 2 * i;
    # s0 = s, s1 = 5, s2 = 2
    # t0 = i,
    # t1 = s * i
    # t2 = i + t1
    # t3 = t2 % 5
    # t4 = A[t3]
    # t5 = 2 * i
    # t6 = t4 + t5
    # t7 = tmp(i * 4)
    bgt $t0, 4, print
    mul $t1, $s0, $t0
    add $t2, $t0, $t1
    rem $t3, $t2, $s1
    sll $t7, $t3, 2
    lw $t4, num($t7)
    mul $t5, $s2, $t0
    add $t6, $t4, $t5
    sll $t7, $t0, 2
    sw $t6, num($t7)
    addi, $t0, $t0, 1
    j loop

print:
    li $t0, 0
    j printloop
printloop:
    bgt $t0, 16, exit
    li $v0, 1
    lw $a0, num($t0)
    syscall
    li $v0, 4
    la $a0, space
    syscall
    addi $t0, 4
    j printloop

exit:
    li $v0, 10
    syscall
