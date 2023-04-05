.data
    N:
        .quad 9
    NUM:
        .ascii "0123456789"
    STAR:
        .ascii "*"
    EQUAL:
        .ascii "="
    LF:
        .ascii "\n"

# for (int i = 1; i <= 9; i++) {
#     for (int j = 1; j <= 9; j++) {
#         printf("%d*%d=%d\n", i, j, i * j);
#     }
# }
.text
    .globl _start
    _start:
        # i = r8
        mov $0, %r8
        mov $10, %r10

    L1:
        # j = r9
        add $1, %r8
        mov $0, %r9
        cmp N, %r8
        jle L2
        jmp EXIT

    L2:
        add $1, %r9
        # print i
        mov $4, %rax
        mov $1, %rbx
        mov $NUM, %rcx
        add %r8, %rcx
        mov $1, %rdx
        int $0x80
        # print STAR
        mov $4, %rax
        mov $1, %rbx
        mov $STAR, %rcx
        mov $1, %rdx
        int $0x80
        # print j
        mov $4, %rax
        mov $1, %rbx
        mov $NUM, %rcx
        add %r9, %rcx
        mov $1, %rdx
        int $0x80
        # print EQUAL
        mov $4, %rax
        mov $1, %rbx
        mov $EQUAL, %rcx
        mov $1, %rdx
        int $0x80
        # i * j, Quotient = r11, Remainder = r12
        mov %r8, %rax
        imul %r9, %rax
        mov $0, %rdx
        div %r10
        mov %rax, %r11
        mov %rdx, %r12
        # check to print tens
        cmp $0, %r11
        jg PTEN
        jmp PDIGIT
    PTEN:
        # print quotient
        mov $4, %rax
        mov $1, %rbx
        mov $NUM, %rcx
        add %r11, %rcx
        mov $1, %rdx
        int $0x80
    PDIGIT:
        # print remainder
        mov $4, %rax
        mov $1, %rbx
        mov $NUM, %rcx
        add %r12, %rcx
        mov $1, %rdx
        int $0x80
        # print LF
        mov $4, %rax
        mov $1, %rbx
        mov $LF, %rcx
        mov $1, %rdx
        int $0x80

        cmp N, %r9
        jl L2
        jmp L1

    EXIT:
        mov $1, %rax
        mov $0, %rbx
        int $0x80
