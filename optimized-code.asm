.MODEL SMALL
.STACK 100H
.DATA 
t0 dw ?
t1 dw ?
a4 dw ?
t2 dw ?
t3 dw ?
t4 dw ?
t5 dw ?
t6 dw ?
t7 dw ?
.CODE
MAIN PROC
MOV AX, @DATA
MOV DS, AX
MOV t2,1
MOV t3,2
MOV AX,t2
ADD AX,t3
MOV t4,AX
MOV t5,3
MOV AX,t4
ADD AX,t5
MOV t6,AX
;Line Omitted for optimization
MOV a4,AX
MOV t7,0
MOV AX,t7
JMP RETURNMAIN
RETURNMAIN:
MOV AH, 4CH 
INT 21H
 
OUTDEC PROC  
    PUSH AX 
    PUSH BX 
    PUSH CX 
    PUSH DX  
    CMP AX,0 
    JGE BEGIN 
    PUSH AX 
    MOV DL,'-' 
    MOV AH,2 
    INT 21H 
    POP AX 
    NEG AX 
    
    BEGIN: 
    XOR CX,CX 
    MOV BX,10 
    
    REPEAT: 
    XOR DX,DX 
    DIV BX 
    PUSH DX 
    INC CX 
    OR AX,AX 
    JNE REPEAT 
    MOV AH,2 
    
    PRINT_LOOP: 
    POP DX 
    ADD DL,30H 
    INT 21H 
    LOOP PRINT_LOOP 
    
    MOV AH,2
    MOV DL,10
    INT 21H
    
    MOV DL,13
    INT 21H
	
    POP DX 
    POP CX 
    POP BX 
    POP AX 
    ret 
OUTDEC ENDP
END MAIN
