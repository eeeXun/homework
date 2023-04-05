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
    .globl putd
    .type putd @function
    putd:
        add $48, %rdi
        call putc
        ret
    .globl puts
    .type puts @function
    puts:
        movb (%rdi), %al
        cmp $0, %al
        jne phead
        jmp exit
    phead:
        # print first char
        push %rdi
        mov (%rdi), %rdi
        call putc
        pop %rdi
        add $1, %rdi
        jmp puts
    exit:
        ret
