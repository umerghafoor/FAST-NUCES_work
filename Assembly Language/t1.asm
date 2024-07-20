INCLUDE Irvine32.inc

.data
    userInput   BYTE    100 DUP(?)
    prompt      BYTE    "Enter your uppercase name: ", 0
    result      BYTE    "Lowercase name: ", 0

.code

main PROC
    mov edx, OFFSET prompt
    call WriteString
    mov edx, OFFSET userInput
    mov ecx, SIZEOF userInput
    call ReadString

    mov esi, OFFSET userInput
    mov edi, OFFSET userInput
    call UppercaseToLowercase


    mov edx, OFFSET result
    call WriteString
    mov edx, OFFSET userInput
    call WriteString

    exit
main ENDP

UppercaseToLowercase PROC
    L1:
        mov al, [esi]
        cmp al, 0
        je  L2
        cmp al, 'A'
        jb  L2
        cmp al, 'Z'
        ja  L3
        add al, 32
        mov [edi], al
        inc esi
        inc edi
        jmp L1

    L2:
        ret

    L3:
        inc esi
        inc edi
        jmp L1

UppercaseToLowercase ENDP

END main



////////////////////////////////////////////////////////////////////////////////

INCLUDE Irvine32.inc

.data
    array       WORD    1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    arraySize   DWORD   10
    prompt1     BYTE    "Enter the index (0-9): ", 0
    prompt2     BYTE    "Sum printed: ", 0
    newline     BYTE    10, 13, 0

.code
main PROC
    mov edx, OFFSET prompt1
    call WriteString
    call ReadInt
    movzx ecx, ax

    cmp ecx, arraySize
    jae InvalidIndex

    movzx eax, word ptr [array + ecx * 2]

    mov edx, ecx
    inc edx
    shl edx, 1
    movzx edx, word ptr [array + edx]

    ; Continue with the calculation
    mov ebx, eax
    add ebx, edx
    add eax, ebx
    dec eax
    
    mov edx, OFFSET prompt2
    call WriteString
    call WriteInt
    mov edx, OFFSET newline
    call WriteString

    jmp ExitProgram

InvalidIndex:
    
ExitProgram:
    exit
main ENDP

END main


////////////////////////////////////////////////////////////////////////////////
INCLUDE Irvine32.inc

.data
    array       DWORD   5 DUP(?)
    arraySize   DWORD   5
    sum         DWORD   ?
    prompt      BYTE    "Enter element %d: ", 0
    resultMsg   BYTE    "Sum of elements at odd indexes: ", 0

.code
main PROC
    mov ecx, arraySize
    mov esi, 0

    ; Loop to input 5 elements
    InputLoop:
        mov eax, esi
        inc eax
        push eax
        mov edx, OFFSET prompt
        call WriteString
        pop eax

        lea edx, [array + esi * 4]
        call ReadInt
        mov [edx], eax

        inc esi
        loop InputLoop


    mov ecx, arraySize
    mov esi, 0
    mov sum, 0

    SumLoop:
        lea edx, [array + esi * 4]
        mov eax, [edx]
        add sum, eax
        add esi, 2
        cmp esi, 6
        jl SumLoop


    mov edx, OFFSET resultMsg
    call WriteString
    mov eax, sum
    call WriteInt

    exit
main ENDP

END main



//////////////////////////////////////////////////////////////////////////////////////
INCLUDE Irvine32.inc

.data
    base        DWORD   ?
    exponent    DWORD   ?
    result      DWORD   ?
    promptBase  BYTE    "Enter the base number: ", 0
    promptExp   BYTE    "Enter the exponent: ", 0
    resultMsg   BYTE    "Result: ", 0

.code
main PROC
    mov edx, OFFSET promptBase
    call WriteString
    call ReadInt
    mov base, eax

    mov edx, OFFSET promptExp
    call WriteString
    call ReadInt
    mov exponent, eax

    ; Calculate power
    mov eax, 1
    mov ecx, exponent
    
    powerLoop:
        cmp ecx, 0
        je  done

        imul eax, base
        loop powerLoop

    done:

    mov edx, OFFSET resultMsg
    call WriteString
    call WriteInt

    exit
main ENDP

END main


////////////////////////////////////
INCLUDE Irvine32.inc

.data
    numRows     DWORD   ?       ; Number of rows for the triangle
    row         DWORD   0       ; Current row counter
    col         DWORD   0       ; Current column counter
    prompt      BYTE    "Enter the number of rows for the triangle: ", 0
    asterisk    BYTE    '*'     ; Character to display
    
.code
printTriangle PROC
    mov ecx, numRows ; Initialize ecx with numRows
    
    ; Outer loop for each row
    L1:
        ; Inner loop for spaces before asterisks
        mov ebx, ecx
        L2:
            ; Print space
            call WriteChar ; Print a space

            ; Decrement column counter
            dec ebx
            jnz L2

        ; Inner loop for asterisks
        mov ebx, 0
        L3:
            ; Print asterisk
            mov edx, OFFSET asterisk
            call WriteString

            ; Increment column counter
            inc ebx
            cmp ebx, row ; Check if the column counter reached the row count
            jl L3

        ; Move to the next row
        inc row
        ; Move to the next line
        mov edx, 0
        call Crlf

        ; Decrement row counter
        dec ecx
        jnz L1 ; Repeat for the next row

    ret
printTriangle ENDP

printReverseTriangle PROC
    ; Initialize row counter
    mov ecx, numRows ; Initialize ecx with numRows

    ; Outer loop for each row
    L4:
        ; Inner loop for spaces before asterisks
        mov ebx, 0
        L5:
            ; Print space
            call WriteChar ; Print a space

            ; Increment column counter
            inc ebx
            cmp ebx, row ; Check if the column counter reached the row count
            jl L5

        ; Inner loop for asterisks
        mov ebx, ecx
        L6:
            ; Print asterisk
            mov edx, OFFSET asterisk
            call WriteString

            ; Decrement column counter
            dec ebx
            jnz L6

        ; Move to the next row
        inc row
        ; Move to the next line
        mov edx, 0
        call Crlf

        ; Decrement row counter
        dec ecx
        jnz L4 ; Repeat for the next row

    ret
printReverseTriangle ENDP

main PROC
    ; Get the number of rows for the triangle from the user
    mov edx, OFFSET prompt
    call WriteString
    call ReadInt
    mov numRows, eax

    ; Initialize row and column counters
    mov row, 1 ; Start row and column from 1
    mov col, 0

    ; Call the procedure to print the triangle
    call printTriangle

    ; Call the procedure to print the reverse triangle
    call printReverseTriangle

    ; Exit the program
    exit
main ENDP

END main


//////////////////////////////////////////////////////////////////////////////////////////
INCLUDE Irvine32.inc

.data
    numRows     DWORD   ?       ; Number of rows for the rectangle
    numCols     DWORD   ?       ; Number of columns for the rectangle
    row         DWORD   0       ; Current row counter
    col         DWORD   0       ; Current column counter
    promptRow   BYTE    "Enter the number of rows for the rectangle: ", 0
    promptCol   BYTE    "Enter the number of columns for the rectangle: ", 0
    asterisk    BYTE    '*'     ; Character to display
    
.code
printRectangle PROC
    ; Initialize row counter
    mov ecx, numRows

    ; Outer loop for each row
    L1:
        ; Inner loop for columns
        mov ebx, numCols
        L2:
            ; Print asterisk
            mov edx, OFFSET asterisk
            call WriteString

            ; Increment column counter
            inc col

            ; Load the value of numCols into a register for comparison
            mov eax, numCols

            ; Check if the column counter reached the specified number of columns
            cmp col, eax
            jl L2

        ; Move to the next row
        inc row
        mov col, 0 ; Reset column counter for the next row

        ; Move to the next line
        mov edx, 0
        call Crlf

        ; Decrement row counter
        dec ecx
        jnz L1 ; Repeat for the next row

    ret
printRectangle ENDP

main PROC
    ; Get the number of rows for the rectangle from the user
    mov edx, OFFSET promptRow
    call WriteString
    call ReadInt
    mov numRows, eax

    ; Get the number of columns for the rectangle from the user
    mov edx, OFFSET promptCol
    call WriteString
    call ReadInt
    mov numCols, eax

    ; Initialize row and column counters
    mov row, 1 ; Start row and column from 1
    mov col, 0

    ; Call the procedure to print the rectangle
    call printRectangle

    ; Exit the program
    exit
main ENDP

END main


////////////////////////////////////////////////////////////////////////////////////////
INCLUDE Irvine32.inc

.data
    year        DWORD   ?      ; Variable to store the input year
    prompt      BYTE    "Enter a year: ", 0
    leapYearMsg BYTE    "Leap year", 0
    notLeapMsg  BYTE    "Not a leap year", 0

.code
main PROC
    ; Get the year from the user
    mov edx, OFFSET prompt
    call WriteString
    call ReadInt
    mov year, eax

    ; Check if it's a leap year
    mov eax, year
    call IsLeapYear

    ; Display the result
    cmp eax, 1
    je  leapYear
    jmp notLeapYear

leapYear:
    mov edx, OFFSET leapYearMsg
    jmp displayResult

notLeapYear:
    mov edx, OFFSET notLeapMsg

displayResult:
    call WriteString

    exit
main ENDP

; Function to check if a year is a leap year
IsLeapYear PROC
    ; Input: year in eax
    ; Output: 1 in eax if leap year, 0 otherwise

    ; Check if the year is divisible by 4
    mov edx, 0
    mov ecx, 4
    div ecx
    cmp edx, 0
    jne notLeap

    ; Check if the year is divisible by 100
    mov edx, 0
    mov ecx, 100
    div ecx
    cmp edx, 0
    jne leap

    ; Check if the year is divisible by 400
    mov edx, 0
    mov ecx, 400
    div ecx
    cmp edx, 0
    jne notLeap

leap:
    mov eax, 1
    ret

notLeap:
    xor eax, eax
    ret
IsLeapYear ENDP

END main
