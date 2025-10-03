; A simple example adding two numbers.
.386  ; Specify instruction set
.model flat, stdcall  ; Flat memory model, std. calling convention
.stack 4096 ; Reserve stack space
ExitProcess PROTO, dwExitCode: DWORD  ; Exit process prototype

.data ;define data here
	sum DWORD 65536 ;val is the variable name, DWORD is the type and 65536 is the val
	;10000h can be used to specify hex values
	num BYTE ?; initialises a variable with no initial value up to 255

.code ; code segment


main PROC ; main procedure
	INVOKE ExitProcess, 0 ; call exit function

main ENDP ; exit main procedure
END main  ; stop assembling