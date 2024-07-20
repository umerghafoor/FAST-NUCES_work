INCLUDE Irvine32.inc
.386
.model flat, stdcall
.stack 4096
BUFFER_SIZE = 501
.data
    buffer BYTE ?
    stringLength DWORD ?
    str1 BYTE "Write Number",0dh,0ah,0
    str2 BYTE "Push :",0
    str3 BYTE "pop  :",0

.code
main PROC
    mov ecx,BUFFER_SIZE
    
    mov edx,OFFSET str1
    call WriteString
    
    call ReadInt

    
    mov ecx, eax
    L1:
        push ecx
        loop L1
    mov ecx, eax
    mov eax,1
    L2:
        pop edx
        mul edx
        loop L2


    call crlf
    call WriteInt
    
    exit
main ENDP
END main