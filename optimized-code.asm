.MODEL SMALL
.STACK 100H
.DATA 
t0 dw ?
a2 dw ?
t1 dw ?
t2 dw ?
t3 dw ?
t4 dw ?
t5 dw ?
t6 dw ?
.CODE
MAIN PROC
MOV AX, @DATA
MOV DS, AX
MOV t1,1
MOV t2,2
MOV AX,t1
ADD AX,t2
MOV t3,AX
MOV t4,3
MOV AX,t3
ADD AX,t4
MOV t5,AX
;Line Omitted for optimization
MOV a2,AX
MOV t6,0
MOV AX,t6
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
