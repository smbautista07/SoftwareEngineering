; A simple example adding two numbers.
.386  ; Specify instruction set
.model flat, stdcall  ; Flat memory model, std. calling convention
.stack 4096 ; Reserve stack space
ExitProcess PROTO, dwExitCode: DWORD  ; Exit process prototype

.data ; data segment
	num1 BYTE 1
	num2 BYTE 2
	arrB BYTE 10 DUP (?) ;initialises an array with 10 unknown byte elements
	arrA BYTE 3,2,3,1,7,5,0,8,9,2 ;initialises an array 10 bytes long with 10 specified values named A
	arrC BYTE 1,3,2,5,4,6,0,4,5,8
  
  
.code ; code segment

main PROC ; main procedure

	mov esi, 0 ;assigns 0 to esi register. Used this register for loop count and indexes to reduce memory usage
	
	loo: ;loop label. 'loop' causes syntax errors

		mov bl, [arrA+esi*BYTE] ;moves the value A[i] in bl. 
		shl bl, 1; left shifts the value in bl. A[i]*2 in bl. 
		;I used this command since it accepts immediate values unlike mul, which saves the instructions of assigning 2 to a register and transferring the result away from the accumulator for later calculations.
		add bl, 1; increases value in bl by 1. A[i]*2 + 1 in bl

		mov al, [arrC+esi*BYTE]; al holds C[i]
		mov dl, 3; assigns 3 to dl register
		mul dl; multiply accumulator contents by value in dl (3): C[i]*3 in accumulator
		add al, 1; increments by 1: C[i]*3 + 1 in accumulator
		
		add bl, al; bl holds (A[i]*2 + 1) + (C[i]*3 + 1)
		
		mov al, [arrA+esi*BYTE]; A[i] in accumulator
		add al, [arrC+esi*BYTE]; A[i] + C[i] in accumulator
		div dl; divide accumulator contents by value in dl (3): quotient of (A[i] + C[i])/3 in accumulator
		
		add bl, al; bl holds (A[i]*2 + 1) + (C[i]*3 + 1) + (A[i] + C[i])/3

		mov [arrB+esi*BYTE], bl; write contents of bl to B[i]

		inc esi ;increments i
		cmp esi, 10 ;compares i with 10
		jne loo ;jump back to loop lable if i is less than 10
	
	INVOKE ExitProcess, 0 ; call exit function
  
main ENDP ; exit main procedure
END main  ; stop assembling