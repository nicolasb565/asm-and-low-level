section .data
codes: db '0123456789ABCDEF'

section .text
global _start

_start:
    ;number 1122... in hexadecimal format
    mov rax, 0x1122334455667788
    
    mov rdi, 1 ; write to stdout
    mov rdx, 1 ; how many bytes to write (one at a time)
    mov rcx, 64 ; 64 bits qword, substract 4  bits each iteration
                ; to print each hex digits in rax
                
    ;print 0x prefix for hex number
    push rax
    push rcx
    mov rax, 1
    push 48 ; '0' character
    mov rsi, rsp
    syscall
    pop r11
    push 120 ; 'x' character
    syscall
    pop r11
    pop rcx
    pop rax
    
    .loop:
        push rax ;saves rax before modifying it
        sub rcx, 4 ; will write one hex digit (4 bits)
        sar rax, cl ; right arithmetic shift, cl is 8 lowest bits of rcx
                    ; so we will shift by 60 bits, 56, 52, ..., 4 , 0
        and rax, 0xf ; and the result to get only our digit
        lea rsi, [codes + rax] ; load effective address, will map the digit
                                ; to its hex character representation in the codes array
        
        ;write the digit
        mov rax, 1
        ;syscall changes rcx and r11, saves rcx
        push rcx
        syscall
        pop rcx
        pop rax ;get back original value of rax
        
        ;if rcx is not 0 we will loop again
        test rcx, rcx ; test perform bitwise AND on its two operands and discard the result, sets SF, ZF, PF
        jnz .loop ; if ZF (zero flag) not set loop again
        
    ;write new line...
    mov rax, 1
    push 10
    mov rsi, rsp
    syscall
        
    ;return 0
    mov rax, 60
    xor rdi,rdi
    syscall
    
