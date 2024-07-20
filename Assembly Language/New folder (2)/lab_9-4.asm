.386
.model flat, stdcall
.stack 4096
GetStdHandle PROTO, a1:DWORD
WriteConsoleA PROTO, a1:DWORD, a2: PTR BYTE, a3: Dword, a4: ptr dword, a5: dword
ReadConsoleA PROTO, a1:DWORD, a2: PTR BYTE, a3: Dword, a4: ptr dword, a5: dword
ExitProcess proto, dwExitProcess:dword

.data
buffer dword ?
x dword ?


.code
main proc
	invoke GetStdHandle, -10

	invoke ReadConsoleA, eax, offset buffer, lengthof buffer, offset x, 0
	
  INVOKE exitProcess,0

main endp

end main