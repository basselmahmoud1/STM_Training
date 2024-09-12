global main

EXTERN sbrk
SECTION .data
msg: db "Hello World from x86_64 machine", 0Ah, 0h
len_msg: equ $ - msg

SECTION .text
main:
	mov rax,0
        call sbrk 
infinite:
        jmp infinite
	mov rax,1 
	mov rdi,1 
	mov rsi,msg
	mov rdx,len_msg
	syscall         ; write(1, msg, len_msg);

	mov rax,0
        call sbrk 
