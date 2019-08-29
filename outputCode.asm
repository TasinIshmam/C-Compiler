.MODEL SMALL
.STACK 100H
.DATA 
b2 dw ?
a2 dw ?
t0 dw ?
t1 dw ?
t2 dw ?
t3 dw ?
t4 dw ?
t5 dw ?
t6 dw ?
t7 dw ?
t8 dw ?
t9 dw ?
t10 dw ?
asd2 dw ?
j2 dw ?
t11 dw ?
t12 dw ?
t13 dw ?
t14 dw ?
t15 dw ?
t16 dw ?
c2 dw 53 dup(?)
.CODE
MAIN PROC

MOV AX, @DATA
MOV DS, AX

	MOV t0,1
MOV AX,t0
MOV a2,AX
	MOV t1,2
MOV AX,t1
MOV BX,a2
MUL BX
MOV t2, AX
MOV AX,t2
MOV b2,AX
MOV AX,b2
MOV BX,a2
DIV BX
MOV t3, AX
MOV AX,t3
MOV a2,AX
	MOV t4,0
MOV AX,t4
MOV a2,AX
	MOV t5,0
MOV AX,t5
MOV a2,AX
L2:
	MOV t6,20
MOV AX,a2
CMP AX,t6
JL L0
MOV t7,0
JMP L0
L0:
MOV t7,1
L1:
MOV AX,t7
CMP AX,0
JE L3
	MOV BX,a2
	ADD BX,BX
MOV AX,a2
MOV c2[BX],AX
	MOV BX,a2
	ADD BX,BX
MOV AX, c2[BX]
MOV t10,AX
MOV AX,t10
MOV b2,AX
MOV AX,b2
CALL OUTDEC
	MOV t8,1
MOV AX,a2
ADD AX,t8
MOV t9,AX
MOV AX,t9
MOV a2,AX
JMP L2
L3:
	MOV t11,5
	MOV t12,3
MOV AX,t11
MOV BX,t12
MOV DX,0
DIV BX
MOV t13, DX
MOV AX,t13
MOV j2,AX
MOV AX,j2
ADD AX,j2
MOV t14,AX
MOV AX,t14
MOV a2,AX
	MOV t15,213
MOV AX,t15
MOV asd2,AX
MOV AX,a2
CALL OUTDEC
JMP LReturnmain
LReturnmain:
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
