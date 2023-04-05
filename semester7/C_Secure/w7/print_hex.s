.bss
    .lcomm ch, 1

.text
    .globl putc
    .type putc @function
    putc:
        mov %rdi, %rax
        mov %al, ch
        mov $4, %rax
        mov $1, %rbx
        mov $ch, %rcx
        mov $1, %rdx
        int $0x80
        ret

    .globl print_hex
    .type print_hex @function
    print_hex:
        mov %rsp, %rbp
        mov %rdi, %rax
        mov $16, %rbx
    div16:
        mov $0, %rdx
        idiv %rbx, %rax
        push %rdx
        cmp $0, %rax
        jg div16
    printInit:
        pop %rdi
        cmp $10, %rdi
        jge phex
        add $48, %rdi
        call putc
        cmp %rbp, %rsp
        jl printInit
        ret
    phex:
        add $55, %rdi
        call putc
        cmp %rbp, %rsp
        jl printInit
        ret
