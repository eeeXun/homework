.data
    tab:
        .ascii "\t"
.bss
    .lcomm ch, 1

.text
    .globl putc
    .type putc @function
    putc:
        mov %dil, ch
        mov $4, %rax
        mov $1, %rbx
        mov $ch, %rcx
        mov $1, %rdx
        int $0x80
        ret

    .globl putd
    .type putd @function
    putd:
        push %rbp
        mov %rsp, %rbp
        mov %rdi, %rax
        mov $10, %rbx
    div10:
        mov $0, %rdx
        idiv %rbx, %rax
        push %rdx
        cmp $0, %rax
        jg div10
    printd:
        pop %rdi
        add $48, %rdi
        call putc
        cmp %rbp, %rsp
        jl printd
        pop %rbp
        ret

    .globl print_array
    .type print_array @function
    print_array:
        push %rbp
        mov %rsp, %rbp # addr of rbp = (rbp)
        push %rdi # rdi = -8(rbp) arr
        push %rsi # rsi = -16(rbp) N
        push $0 # index = -24(rbp)
    print_init:
        mov -24(%rbp), %rax # index
        mov -16(%rbp), %rbx # N
        cmp %rbx, %rax
        jl call_putd
        lea (%rbp), %rsp
        pop %rbp
        ret
    call_putd:
        mov -8(%rbp), %rdi # addr of arr
        mov -24(%rbp), %rax
        imul $4, %rax
        add %rax, %rdi # addr of arr[i]
        movl (%rdi), %edi # value of arr[i]
        call putd
        mov tab, %rdi
        call putc
        mov -24(%rbp), %rax
        add $1, %rax
        mov %rax, -24(%rbp)
        jmp print_init
