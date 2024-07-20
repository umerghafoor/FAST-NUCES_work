.model flat, stdcall
.stack 4096
GetStdHandle PROTO, a1:DWORD
WriteConsoleA PROTO, a1:DWORD, a2:PTR BYTE, a3:DWORD, a4:PTR DWORD, a5:DWORD
ReadConsoleA PROTO, a1:DWORD, a2:PTR BYTE, a3:DWORD, a4:PTR DWORD, a5:DWORD
ExitProcess PROTO, dwExitProcess:DWORD

.data
buffer BYTE 15 dup(0)
x DWORD ?

.code
main PROC
    mov esi, OFFSET buffer
    mov ecx, 10

L1:
    mov ebx, ecx
    invoke GetStdHandle, -10
    invoke ReadConsoleA, eax, esi, LENGTHOF buffer, ADDR x, 0
    inc esi
    mov ecx, ebx
    loop L1

mov x, 12
mov esi, 0

mov ecx, 10

L2:
    sub BYTE PTR [buffer + esi], 30h
    inc esi
    loop L2

mov esi, 0

outer_loop:
    cmp ecx, 10
    jge done

    mov ebx, ecx
    mov eax, ecx

inner_loop:
    cmp ebx, 10
    jge inner_done

    mov edx, eax
    mov esi, ebx
    mov al, BYTE PTR [buffer + esi]
    mov bl, BYTE PTR [buffer + edx]
    cmp al, bl
    jl update_min

update_min:
    mov eax, ebx
    inc ebx
    jmp inner_loop

inner_done:
    mov edx, eax
    mov esi, ecx
    mov al, BYTE PTR [buffer + esi]
    mov bl, BYTE PTR [buffer + edx]
    mov BYTE PTR [buffer + edx], al
    mov BYTE PTR [buffer + esi], bl
    inc ecx
    jmp outer_loop

done:
mov ecx, 0
INVOKE ExitProcess, 0

main ENDP

END main
