.386
.model flat, stdcall
.stack 4096
GetStdHandle PROTO, a1:DWORD
WriteConsoleA PROTO, a1:DWORD, a2: PTR BYTE, a3: Dword, a4: ptr dword, a5: dword
ReadConsoleA PROTO, a1:DWORD, a2: PTR BYTE, a3: Dword, a4: ptr dword, a5: dword
ExitProcess proto, dwExitProcess:dword

.data
buffer byte 15 dup(?)
x byte ?

.code
main proc
	invoke GetStdHandle, -10
	invoke ReadConsoleA, eax, offset buffer, lengthof buffer, offset x, 0
	mov ebx, 0
	mov bl, x

	mov ecx, 0
	mov cl, [buffer]
	sub cl, 30h
	mov al, 0
	L1:
		mov bl, [buffer]
		add al, bl
		aaa
		loop L1

	mov [buffer], ah
	add [buffer], 30h
	mov [buffer+1], al
	add [buffer+1], 30h
	mov [buffer+2], 0dh
	mov [buffer+3], 0ah
	add x, 1

	invoke GetStdHandle, -11
	invoke WriteConsoleA, eax, offset buffer, ebx , offset x, 0
	mov ecx, 0

  INVOKE exitProcess,0

main endp

end main