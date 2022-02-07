.data
num1: .word 5
num2: .word 4

.text
main:
    lw $s0, num1
    add $t3, $s0, $s0
    add $t3, $t3, $t3
    lw $s1, num2
    add $t4, $s1, $s1
    sub $t5, $t3, $t4
    add $t5, $t5, $t5
    add $t5, $t5, $t5
    add $s3, $t5, $t5
    li $v0, 1
    add $a0, $zero, $s3
    syscall
    jr $ra
