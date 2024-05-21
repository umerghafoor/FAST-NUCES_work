INCLUDE Irvine32.inc
.386
.model flat, stdcall
.stack 4096
BUFFER_SIZE = 501
.data
    buffer BYTE BUFFER_SIZE DUP(?)
    stringLength DWORD ?
    str1 BYTE "Write Array [10]",0dh,0ah,0
    str2 BYTE "Push :",0
    str3 BYTE "pop  :",0

.code
main PROC
    mov ecx,BUFFER_SIZE
    
    mov edx,OFFSET str1
    call WriteString
    
    mov edx,OFFSET buffer
    call ReadString
    mov stringLength,eax

    mov edx,OFFSET str2
    call WriteString

    mov ecx, stringLength
    mov esi, 0
    L1:
        mov edx, 0
        mov dl, [buffer + esi]
        mov eax, edx
        call writechar
        push edx
        inc esi
        loop L1
    call crlf
    mov edx,OFFSET str3
    call WriteString
    mov ecx, stringLength
    mov eax,0
    L2:
        pop edx
        add eax,edx
        mov eax, edx
        call writechar
        loop L2
    call writeInt
        
    exit
main ENDP
END main