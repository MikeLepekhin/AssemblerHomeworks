
; in the data section
section .data
	digits: db '0123456789abcdef?',0           
        output: db '00000000000000000000000000000',0    ; buffer for printing digits
        int_format: db '%d',0 
        input: times 8 db 0  

; Code goes in the text section
section .text
	global main 
        extern scanf

stack_to_output:                       ; move digits from stack to utput buffer
        mov r9d, r10d
        mov r10d, 0
_stack_to_output_loop:
        cmp r10d, r9d
        je _stack_to_output_end
        pop rdx
        
        mov [output + r10d], dl
        inc r10d
        jmp _stack_to_output_loop

_stack_to_output_end:
        ret

itoa:                                 ; convert integer to string of decimal representation
        mov r10d, 0
        mov r12d, 10
_itoa_loop:
        cmp rax, 0
        je _itoa_end
        
        mov rdx, 0
        div r12d
        mov rbx, [digits + rdx]
        push rbx

        inc r10d
        jmp _itoa_loop
_itoa_end:
        jmp stack_to_output

display_newline:
        mov byte [digits + 16], 10
        jmp _display_text_char

display_text:                    ; display text written in output buffer
        cmp r9d, 0
        je _display_text_zero

        mov eax, 4
        mov ebx, 1
        mov ecx, output
        mov edx, r9d
        int 80h

        jmp display_newline        

_display_text_zero:            ; display zero character
        mov byte [digits + 16], '0'
        call _display_text_char
        jmp display_newline

_display_text_char:            ; display one character from [digits + 16]
        mov eax, 4
        mov ebx, 1
        mov ecx, digits
        add ecx, 16
        mov edx, 1
        int 80h

        ret

exit_program:
        mov eax, 60
        xor edi, edi
        syscall

my_in:
        xor rax, rax
        mov rdi, int_format
        mov rsi, input
        jmp scanf

my_out:
        call itoa
        jmp display_text

_my_main:
call my_in
mov r8, [input]
push r8
push 1
pop r14

label_cmd_4:
pop rax
push rax
push rax
push 1
pop rbx
pop rax
cmp rax, rbx
je label_cmd_19
pop rax
push rax
push rax
push r14
pop rbx
pop rax
mul rbx
push rax
pop r14
mov rax, r14
call my_out
pop rax
push rax
push rax
push 1
pop rbx
pop rax
sub rax, rbx
push rax
pop r13
push r13
jmp label_cmd_4
pop rbx
pop rax
mul rbx
push rax

label_cmd_19:
mov rax, r14
call my_out
jmp exit_program
