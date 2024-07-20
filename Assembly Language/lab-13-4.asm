INCLUDE Irvine32.inc
.386
.model flat, stdcall
.stack 4096
BUFFER_SIZE = 501
.data
    buffer BYTE BUFFER_SIZE DUP(?)
    oldfile BYTE BUFFER_SIZE DUP(?)
    stringLength DWORD ?
    str1 BYTE "Write Array [500]",0dh,0ah,0
    str2 BYTE "Not Already Present in the file",0dh,0ah,0
    
    filename     BYTE "umer.txt",0
    fileHandle   HANDLE ?
    bytesWritten DWORD ?

.code
main PROC

    mov edx,OFFSET filename
    call OpenInputFile
    mov fileHandle,eax
    mov edx,OFFSET oldfile
    mov ecx,BUFFER_SIZE
    call ReadFromFile
    mov eax,fileHandle
    call CloseFile
    
    mov edx,OFFSET oldfile
    call WriteString
    call crlf

    
    ; Create a new text file.
    mov edx,OFFSET filename
    call CreateOutputFile
    mov fileHandle,eax

    
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
        cmp dl,[oldfile+esi]
        jne notfound
        inc esi
        loop L1

    jmp skip
    notfound:
        mov edx,OFFSET str2
        call WriteString
    skip:
        
    mov eax,fileHandle
    mov edx,OFFSET buffer
    mov ecx,stringLength
    call WriteToFile
    call CloseFile

    exit
main ENDP
END main