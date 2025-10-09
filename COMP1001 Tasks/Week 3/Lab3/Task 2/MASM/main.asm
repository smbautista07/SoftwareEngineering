; A simple example adding two numbers.
.386  ; Specify instruction set
.model flat, stdcall  ; Flat memory model, std. calling convention
.stack 4096 ; Reserve stack space
ExitProcess PROTO, dwExitCode: DWORD  ; Exit process prototype



.data ; data segment
; define your variables here
dwordArray DWORD 4, 3, 5, 6


.code ; code segment
main PROC ; main procedure
; write your assembly code here
mov ecx, [dwordArray+DWORD*1] ;load the value of the second element of the list into ecx
lea ebx, dwordArray
mov [dwordArray+DWORD*1], 10h

    INVOKE ExitProcess, 0 ; call exit function
 
main ENDP ; exit main procedure
END main  ; stop assembling