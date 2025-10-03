; A simple example adding two numbers.
.386  ; Specify instruction set
.model flat, stdcall  ; Flat memory model, std. calling convention
.stack 4096 ; Reserve stack space
ExitProcess PROTO, dwExitCode: DWORD  ; Exit process prototype

.data ; data segment
	; define your variables here
  sum SDWORD 0  ; define a variable sum (32-bit) with initial value 0
  sum2 SDWORD 0
  
.code ; code segment
	
main PROC ; main procedure
	; write your assembly code here
  mov eax, 2 ; move literal value  to eax
  mov ebx, 3 ; move literal value 30 to ebx
  mov ecx, 4
  mov edx, 5
  add eax, ebx  ; add eax and ebx, and put value in eax
  add ecx, edx  ; add eax and ebx, and put value in eax
  sub eax, ecx

	INVOKE ExitProcess, 0 ; call exit function

  
main ENDP ; exit main procedure
END main  ; stop assembling