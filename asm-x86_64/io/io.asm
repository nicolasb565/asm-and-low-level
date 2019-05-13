section .data
codes: db '0123456789ABCDEF'
str1: db 'ab',10, 0
newline: db 10,0

section .text
global _start

_start:
    mov rdi, str1
    call .puts
    mov rdi, str1
    call .strlen
    mov rdi, rax
    call .print_qword_hex
    mov rdi, newline
    call .puts
    
    push rax
    mov rdi, rsp
    push 0
    call .puts
    
    ;return 0
    mov rax, 60
    xor rdi,rdi
    syscall
    
    .puts:
        push rcx
        push r11
        mov rax, 1 ; syscall write
        mov rsi, rdi ; address to beginning of string goes into rsi
        mov rdi, 1; stdout
        mov rdx, 1 ; print one at a time
    
        .puts_loop:
        mov cl, [rsi]
        cmp cl, 0
        jz .puts_exit
        syscall
        add rsi, 1
        jmp .puts_loop
        
        .puts_exit:
        pop r11
        pop rcx
        ret
        
    .strlen:
        mov rsi, 0
    .strlen_loop:
        mov dl, [rdi + rsi]
        cmp dl, 0
        jz .strlen_end
        add rsi, 1
        jmp .strlen_loop
        
    .strlen_end:
        mov rax, rsi
        ret
        
    .print_qword_hex:
    push r11
    mov rax, rdi ;value we want to print
    
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
    
    .print_qword_hex_loop:
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
    jnz .print_qword_hex_loop ; if ZF (zero flag) not set loop again
    pop r11
    ret
    
