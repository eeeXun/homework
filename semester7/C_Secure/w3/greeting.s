.data
s1:
    .ascii "Your name? "
s2:
    .ascii "Hello "

.bss
    .lcomm buf, 10

.text

.global _start

_start:
    # print question
    mov $4, %rax
    mov $1, %rbx
    mov $s1, %rcx
    mov $11, %rdx
    int $0x80
    # read name
    mov $3, %rax
    mov $0, %rbx
    mov $buf, %rcx
    mov $10, %rdx
    int $0x80
    # print hello
    mov $4, %rax
    mov $1, %rbx
    mov $s2, %rcx
    mov $10, %rdx
    int $0x80
    # print name
    mov $4, %rax
    mov $1, %rbx
    mov $buf, %rcx
    mov $10, %rdx
    int $0x80
    # exit
    mov $1, %rax
    mov $0, %rbx
    int $0x80
