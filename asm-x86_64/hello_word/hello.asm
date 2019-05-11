global _start
    
section .data
message: db'hello, world!', 10 ;10 = new line character
    
section .text
_start:
    mov rax, 1  ;system call number 1 (write)
    mov rdi, 1  ;argument 1 where to write (stdout)
    mov rsi, message    ;argument 2 where the string start
    mov rdx, 14 ;argument 3 how many bytes to write
    syscall
    
    mov rax, 60 ;exit syscall
    xor rdi, rdi;return value is 0 (rdi = rdi xor rdi)
    ;we could have return value of 1 by doing mov rdi, 1
    syscall
