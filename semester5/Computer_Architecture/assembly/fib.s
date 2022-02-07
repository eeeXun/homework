.data
num: .space 20
f_0: .word 0
f_1: .word 1
space: .asciiz ", "
size: .word 10

.text
main:
    lw $t0, f_0
    li $t1, 0
    sw $t0, num($t1)
    lw $t0, f_1
    li $t1, 4
    sw $t0, num($t1)
    li $t0, 8
    li $s0, 4
    li $s1, 8
    # s2 = size = 4 * size
    lw $s2, size
    li $s3, 4
    mul $s2, $s2, $s3
    j fib

fib:
    # fn = fn-1 + fn-2
    # t0 = n
    # t1 = n-1
    # t2 = n-2
    # t3 = fn-1
    # t4 = fn-2
    # t5 = fn
    # s0 = 4
    # s1 = 8
    # s2 = size
    bgt $t0, $s2, print
    sub $t1, $t0, $s0
    sub $t2, $t0, $s1
    lw $t3, num($t1)
    lw $t4, num($t2)
    add $t5, $t3, $t4
    sw $t5, num($t0)
    addi $t0, 4
    j fib


print:
    li $t0, 0
    j printloop
printloop:
    # s2 = size
    bgt $t0, $s2, exit
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
