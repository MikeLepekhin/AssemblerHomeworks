; in the data section
section .data
	digits:     db '0123456789abcdef',0
        output: db '00000000000000000000000000000',0
        

; Code goes in the text section
section .text
	global myprintf 

stack_to_output:
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

itoa:
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


itoa_bin:
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


itoa_hex:
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

display_text:
        mov eax, 4
        mov ebx, 1
        mov ecx, output
        mov edx, 0
        mov edx, r9d
        int 80h

        ret

handle_params:
        pop rax
        pop rbx

        push rdi

        push rbx
        push rax
        ret

myprintf:
        call handle_params

        pop rsi
        pop rax

        call itoa
        call display_text 

        ; Terminate program
;	mov eax,1            ; 'exit' system call
;	mov ebx,0            ; exit with error code 0
;	int 80h              ; call the kernel
        
        push rsi
        ret
