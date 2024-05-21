INCLUDE Irvine32.inc
.386
.model flat, stdcall
.stack 4096
BUFFER_SIZE = 501
.data
    buffer BYTE BUFFER_SIZE DUP(?)
    stringLength DWORD ?
    str1 BYTE "Write Array [10]",0dh,0ah,0
    str2 BYTE "Palindrome",0dh,0ah,0
    str3 BYTE "Not palindrome",0dh,0ah,0

.code
main PROC
    mov ecx,BUFFER_SIZE
    
    mov edx,OFFSET str1
    call WriteString
    
    mov edx,OFFSET buffer
    call ReadString
    mov stringLength,eax

    mov ecx, stringLength
    mov esi, 0
    L1:
        mov edx, 0
        mov dl, [buffer + esi]
        push edx
        inc esi
        loop L1
    call crlf
    mov ecx, stringLength
    mov esi, 0
    L2:
        pop edx
        cmp [buffer + esi], dl
        jne noPal
        inc esi
        loop L2
    
    mov edx,OFFSET str2
    call WriteString
    jmp skip

    noPal:
        mov edx,OFFSET str3
        call WriteString
    skip:
    exit
main ENDP
END main