.386
.model flat, stdcall
.stack 4096
ExitProcess PROTO, dwExitCode: DWORD

.data
	zero DWORD 0
	fifty DWORD 50;
	score1 DWORD 35;
	max1 DWORD 60
	score2 DWORD 45
	max2 DWORD 55
	numerator DWORD ?
	denominator DWORD ?
	quotient DWORD ?
	remainder DWORD ?


.code

main PROC
	mov edx, zero
	mov eax, score1
	mul fifty
	mul max2
	mov ebx, score2
	mul fifty
	mul max1
	add eax, ebx
	mov numerator, eax
	mov eax, max1
	mul max2
	mov denominator, eax
	mov eax, numerator
	div denominator
	mov quotient, eax
	mov remainder, edx


		INVOKE ExitProcess, 0 ; call exit function
 

main ENDP
END main