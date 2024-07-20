.386
.model flat,stdcall
.stack 4049
ExitProcess proto,dwExitProcess:dword

.data
ansArr db 1h,2h,3h,4h,5h
.code

main PROC
	mov esi, 0
	mov ecx, 5
	mov al, 1
	L1:
		shl al, 1
		mov [ansArr+esi],al
		inc esi
		loop L1

  INVOKE exitProcess,0
main ENDP
END main
