.MODEL SMALL
.STACK 100H
.DATA 
arg12 dw ?
funcOneParam_return dw ?
t0 dw ?
t1 dw ?
arg33 dw ?
arg23 dw ?
funcVoidTwoParam_return dw ?
t2 dw ?
funcNoparam_return dw ?
t3 dw ?
main_return dw ?
b5 dw ?
a5 dw ?
t4 dw ?
t5 dw ?
t6 dw ?
t7 dw ?
t8 dw ?
t9 dw ?
.CODE
funcOneParam PROC
PUSH AX
PUSH BX 
PUSH CX 
PUSH DX
PUSH arg12
MOV t0,2
MOV AX,arg12
ADD AX,t0
MOV t1,AX
;Line Omitted for optimization
MOV funcOneParam_return,AX
JMP LReturnfuncOneParam
LReturnfuncOneParam:
POP arg12
POP DX
POP CX
POP BX
POP AX
ret
funcOneParam ENDP
funcVoidTwoParam PROC
PUSH AX
PUSH BX 
PUSH CX 
PUSH DX
PUSH arg33
PUSH arg23
MOV AX,arg23
ADD AX,arg33
MOV t2,AX
;Line Omitted for optimization
MOV funcVoidTwoParam_return,AX
JMP LReturnfuncVoidTwoParam
LReturnfuncVoidTwoParam:
POP arg23
POP arg33
POP DX
POP CX
POP BX
POP AX
ret
funcVoidTwoParam ENDP
funcNoparam PROC
PUSH AX
PUSH BX 
PUSH CX 
PUSH DX
MOV t3,5
MOV AX,t3
MOV funcNoparam_return,AX
JMP LReturnfuncNoparam
LReturnfuncNoparam:
POP DX
POP CX
POP BX
POP AX
ret
funcNoparam ENDP
main PROC
    MOV AX,@DATA
MOV DS,AX 
MOV t4,1
MOV AX,t4
MOV a5,AX
MOV t5,7
MOV AX,t5
MOV arg12,AX
CALL funcOneParam
MOV AX,funcOneParam_return
MOV t6,AX
;Line Omitted for optimization
MOV b5,AX
;Line Omitted for optimization
CALL OUTDEC
CALL funcNoparam
MOV AX,funcNoparam_return
MOV t7,AX
;Line Omitted for optimization
MOV a5,AX
;Line Omitted for optimization
CALL OUTDEC
MOV AX,a5
MOV arg23,AX
MOV AX,b5
MOV arg33,AX
CALL funcVoidTwoParam
MOV AX,funcVoidTwoParam_return
MOV t8,AX
;Line Omitted for optimization
MOV a5,AX
;Line Omitted for optimization
CALL OUTDEC
MOV t9,0
MOV AX,t9
MOV main_return,AX
JMP LReturnmain
LReturnmain:
MOV AH,4CH
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
