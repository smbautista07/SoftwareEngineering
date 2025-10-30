; A simple example adding two numbers.
.386  ; Specify instruction set
.model flat, stdcall  ; Flat memory model, std. calling convention
.stack 4096 ; Reserve stack space
ExitProcess PROTO, dwExitCode: DWORD  ; Exit process prototype

.data ; data segment
	c BYTE 10,20,30,40; initialise array with values from assignment
  
.code ; code segment
main PROC ; main procedure
	lea ebx, c ;loads the address of the first item in the array to register eax
	mov cl, 3; register cl stores value 3
	mov al, [ebx + BYTE * 3] ;loads last element (index 3) of the array to 8-bit primary accumulator register al
	mul cl; multiply the value stored in the accumulator register (40) by the value stored in cl (3)
	mov cl, 6
	div cl; 
	mov [ebx + BYTE * 3], al
		INVOKE ExitProcess, 0 ; call exit function
  
main ENDP ; exit main procedure
END main  ; stop assembling