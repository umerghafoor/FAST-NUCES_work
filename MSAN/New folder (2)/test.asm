.386
.model flat,stdcall
.stack 4049
ExitProcess proto,dwExitProcess:dword

.data

arr db 10,20,30,40,50,60,70,80,90,100
ansArr db 1h,2h,3h,4h,5,6h,7h,8h,9h,0Fh

.code

main PROC
	mov esi, 0
	mov ecx, 10
	L1:
		mov al, [arr+esi]
		shr al, 1
		mov [ansArr+esi],al
		inc esi
		loop L1

  INVOKE exitProcess,0
main ENDP
END main
