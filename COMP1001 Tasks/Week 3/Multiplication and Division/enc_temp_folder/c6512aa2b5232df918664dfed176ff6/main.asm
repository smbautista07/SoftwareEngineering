.386
.model flat, stdcall
.stack 4096
ExitProcess PROTO, dwExitCode: DWORD

.data
	fifty DWORD 50;
	score1 DWORD 35;
	max1 DWORD 60
	score2 DWORD 45
	max2 BYTE 55
	temp DWORD ?
	dividend BYTE ?
	divisor DWORD ?
	quotient BYTE ?
	percentage BYTE ?


.code

main PROC
	; make divisor first
	mov eax, max1
	mul max2
	mov divisor, eax ;3300 expected
	mov eax, score1 
	mul max2
	mov temp, eax
	mov eax, score2
	mul max1
	add eax, temp
	mul fifty
	div divisor

		INVOKE ExitProcess, 0 ; call exit function
 

main ENDP
END main