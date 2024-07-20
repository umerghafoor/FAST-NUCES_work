.386
.model flat, stdcall
.stack 4096
GetStdHandle PROTO, a1:DWORD
WriteConsoleA PROTO, a1:DWORD, a2: PTR BYTE, a3: Dword, a4: ptr dword, a5: dword
ReadConsoleA PROTO, a1:DWORD, a2: PTR BYTE, a3: Dword, a4: ptr dword, a5: dword
ExitProcess proto, dwExitProcess:dword

.data
buffer byte 15 dup(?)
x dword ?


.code
main proc
	invoke GetStdHandle, -10

	invoke ReadConsoleA, eax, offset buffer, lengthof buffer, offset x, 0
	mov ebx, x
	sub buffer, 32d
	

	invoke GetStdHandle, -11
	invoke WriteConsoleA, eax, offset buffer, ebx , offset x, 0
	mov ecx, 0

  INVOKE exitProcess,0

main endp

end main