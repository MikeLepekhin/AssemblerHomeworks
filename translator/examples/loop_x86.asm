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

push_r: 
        pop rax
        push r8
        push r11
        push r13
        push r14
        push r15
        push rax
        ret

pop_r: 
        pop rax
        pop r15
        pop r14
        pop r13
        pop r11
        pop r8
        push rax
        ret

display_text:                    ; display text written in output buffer
        cmp r9d, 0
        je _display_text_zero
        call push_r
        mov rax, 1
        mov rdi, 1
        mov rsi, output
        mov rdx, r9
        syscall
        call pop_r
        jmp display_newline        

; display zero character
_display_text_zero:            
        mov byte [digits + 16], '0'
        call _display_text_char
        jmp display_newline

; display one character from [digits + 16]
_display_text_char:   
        call push_r
        mov rax, 1
        mov rdi, 1
        mov rsi, digits
        add rsi, 16
        mov rdx, 1
        syscall
        call pop_r
        ret

exit_program:
        mov eax, 60
        xor edi, edi
        syscall

my_in:
        call push_r
        xor rax, rax
        mov rdi, int_format
        mov rsi, input
        call scanf
        call pop_r
        ret

my_out:
        call itoa
        jmp display_text

main:
        call my_in
        mov r8, [input]

label_cmd_1:
        push r8
        push 0
        pop rbx
        pop rax
        cmp rax, rbx
        je label_cmd_10
        mov rax, r8
        call my_out
        push r8
        push 1
        pop rbx
        pop rax
        sub rax, rbx
        push rax
        pop r8
        jmp label_cmd_1

label_cmd_10:
        jmp exit_program
