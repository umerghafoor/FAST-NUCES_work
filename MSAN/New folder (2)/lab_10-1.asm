.386
.model flat,stdcall
.stack 4096
GetStdHandle PROTO, a1:DWORD
WriteConsoleA PROTO, a1:DWORD, a2: PTR BYTE, a3: Dword, a4: ptr dword, a5: dword
ReadConsoleA PROTO, a1:DWORD, a2: PTR BYTE, a3: Dword, a4: ptr dword, a5: dword
ExitProcess proto, dwExitProcess:dword

.data
    arr dw '1','1','1','1','1'
    buffer byte 15 dup(?)
    x byte ?
.code
    main PROC

    invoke GetStdHandle, -10
	invoke ReadConsoleA, eax, offset buffer, lengthof buffer, offset x, 0
	mov ebx, 0
	mov bl, x
    
    mov ax, 0
    mov esi, 0
    mov ecx, lengthof arr
    L1:
        add ax, [arr+esi]
        aaa
        add esi, 2
        loop L1

    mov buffer, al
    add buffer, 30h
    mov [buffer+1],0dh
    mov [buffer+2],0ah
    
	
    mov x, 3
	invoke GetStdHandle, -11
	invoke WriteConsoleA, eax, offset buffer, ebx , offset x, 0
	mov ecx, 0


INVOKE ExitProcess,0
main endp
end main


