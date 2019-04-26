; in the data section
section .data
	digits:     db '0123456789abcdef?',0           
        output: db '00000000000000000000000000000',0    ; buffer for printing digits
        

; Code goes in the text section
section .text
	global myprintf 

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


itoa_bin:                           ; convert integer to string of binary representation
        mov r10d, 0

_itoa_bin_loop:
        cmp rax, 0
        je _itoa_bin_end
        
        mov rdx, rax
        and rdx, 1
        mov rbx, [digits + rdx]
        push rbx

        shr rax, 1
        inc r10d
        jmp _itoa_bin_loop

_itoa_bin_end:
        jmp stack_to_output


itoa_hex:                         ; convert integer to string of heximal representation
        mov r10d, 0

_itoa_hex_loop:
        cmp rax, 0
        je _itoa_hex_end
        
        mov rdx, rax
        and rdx, 15
        mov rbx, [digits + rdx]
        push rbx

        shr rax, 4
        inc r10d
        jmp _itoa_hex_loop

_itoa_hex_end:
        jmp stack_to_output

display_text:                    ; display text written in output buffer
        cmp r9d, 0
        je _display_text_zero

        mov eax, 4
        mov ebx, 1
        mov ecx, output
        mov edx, r9d
        int 80h

        ret

_display_text_zero:            ; display zero character
        mov byte [digits + 16], '0'
        jmp _display_text_char

_display_text_char:            ; display one character from [digits + 16]
        mov eax, 4
        mov ebx, 1
        mov ecx, digits
        add ecx, 16
        mov edx, 1
        int 80h

        ret

_display_text_string:         ; display string with pointer in r14 
        cmp byte [r14], 0
        je _display_text_string_ret
        mov ax, [r14]
        mov byte [digits + 16], al
        call _display_text_char
        inc r14
        jmp _display_text_string

_display_text_string_ret:
        ret

handle_params:               ; push all the parameters of function onto stack
        pop rax
        pop rbx

        push r9
        push r8
        push rcx
        push rdx
        push rsi
        push rdi

        push rbx
        push rax
        ret

handle_char:
        mov eax, 4
        mov ebx, 1
        mov rcx, rdi
        mov edx, 1
        int 80h
        
        ret

myprintf:                 ; general function
        call handle_params         
        mov r13, 0 

        pop rsi
        pop rdi
        inc r13

_myprintf_format_loop:        
        cmp byte [rdi], 0
        je _myprintf_ret
        cmp byte [rdi], '%'
        je _myprintf_handle_int

        call handle_char

        inc rdi
        jmp _myprintf_format_loop 

_myprintf_handle_int:
        inc rdi

        cmp byte [rdi], '%'
        je _handle_percent

        pop rax
        inc r13

        cmp byte [rdi], 'b'
        je _handle_int_bin
        
        cmp byte [rdi], 'x'
        je _handle_int_hex
        
        cmp byte [rdi], 'd'
        je _handle_int_dec
 
        cmp byte [rdi], 'c'
        je _handle_char

        cmp byte [rdi], 's'
        je _handle_string

_handle_int_dec:
        call itoa
        call display_text
        inc rdi
        jmp _myprintf_format_loop 

_handle_int_bin:
        call itoa_bin
        call display_text
        inc rdi
        jmp _myprintf_format_loop 
        
_handle_int_hex:
        call itoa_hex
        call display_text
        inc rdi
        jmp _myprintf_format_loop 

_handle_percent:
        mov byte [digits + 16], '%'
        call _display_text_char
        inc rdi
        jmp _myprintf_format_loop 

_handle_char:
        mov byte [digits + 16], al
        call _display_text_char
        inc rdi
        jmp _myprintf_format_loop 

_handle_string:
        mov r14, rax
        call _display_text_string
        inc rdi
        jmp _myprintf_format_loop 

_myprintf_ret:
        cmp r13, 6 
        jl _myprintf_fix_stack
        
        push rsi
        ret

_myprintf_fix_stack:
        pop rdi
        inc r13
        jmp _myprintf_ret
        

