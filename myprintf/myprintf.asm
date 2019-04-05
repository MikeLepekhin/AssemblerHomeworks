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
_itoa_loop:
        cmp rax, 0
        je _itoa_end
        
        mov rdx, 0
        div rcx
        add rdx, '0'
        push rdx

        inc r10d
        jmp _itoa_loop
         
        

_itoa_end:
        jmp stack_to_output


itoa_shifts:
        mov r10d, 0

_itoa_shifts_loop:
        cmp rax, 0
        je _itoa_shifts_end
        
        mov rdx, rax
        and rdx, 2
        add rdx, '0'
        push rdx

        shr rax, 1
        inc r10d
        jmp _itoa_shifts_loop
         
        

_itoa_shifts_end:
        jmp stack_to_output


display_text:
        mov eax, 4
        mov ebx, 1
        mov ecx, output
        mov edx, 0
        mov edx, r9d
        int 80h

        ret

myprintf:
       
        mov eax, 2
        mov rcx, 2
        call itoa_shifts
        call display_text 

        ; Terminate program
;	mov eax,1            ; 'exit' system call
;	mov ebx,0            ; exit with error code 0
;	int 80h              ; call the kernel
        
        ret
