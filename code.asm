.MODEL SMALL
.STACK 100H
.DATA 
arg12 dw ?
funcOneParamReturnVariable dw ?
temp0 dw ?
temp1 dw ?
arg3 dw ?
voidfunctionReturnVariable dw ?
arg34 dw ?
arg24 dw ?
funcVoidTwoParamReturnVariable dw ?
temp2 dw ?
funcNoparamReturnVariable dw ?
temp3 dw ?
mainReturnVariable dw ?
b6 dw ?
a6 dw ?
temp4 dw ?
temp5 dw ?
temp6 dw ?
a7 dw ?
temp7 dw ?
temp8 dw ?
temp9 dw ?
temp10 dw ?
temp11 dw ?
temp12 dw ?
temp13 dw ?
.CODE
funcOneParam PROC
PUSH AX
PUSH BX 
PUSH CX 
PUSH DX
PUSH arg12
MOV temp0,2
MOV AX,arg12
ADD AX,temp0
MOV temp1,AX
MOV AX,temp1
MOV funcOneParamReturnVariable,AX
JMP LabelReturnfuncOneParam
LabelReturnfuncOneParam:
POP arg12
POP DX
POP CX
POP BX
POP AX
ret
funcOneParam ENDP
voidfunction PROC
PUSH AX
PUSH BX 
PUSH CX 
PUSH DX
PUSH arg3
MOV AX,arg3
CALL OUTDEC
LabelReturnvoidfunction:
POP arg3
POP DX
POP CX
POP BX
POP AX
ret
voidfunction ENDP
funcVoidTwoParam PROC
PUSH AX
PUSH BX 
PUSH CX 
PUSH DX
PUSH arg34
PUSH arg24
MOV AX,arg24
ADD AX,arg34
MOV temp2,AX
MOV AX,temp2
MOV funcVoidTwoParamReturnVariable,AX
JMP LabelReturnfuncVoidTwoParam
LabelReturnfuncVoidTwoParam:
POP arg24
POP arg34
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
MOV temp3,5
MOV AX,temp3
MOV funcNoparamReturnVariable,AX
JMP LabelReturnfuncNoparam
LabelReturnfuncNoparam:
POP DX
POP CX
POP BX
POP AX
ret
funcNoparam ENDP
main PROC
    MOV AX,@DATA
MOV DS,AX 
MOV temp4,1
MOV AX,temp4
MOV a6,AX
MOV temp5,7
MOV AX,temp5
MOV arg12,AX
CALL funcOneParam
MOV AX,funcOneParamReturnVariable
MOV temp6,AX
MOV AX,temp6
MOV b6,AX
MOV AX,b6
CALL OUTDEC
MOV temp7,6
MOV AX,temp7
MOV a7,AX
MOV AX,a7
MOV arg12,AX
CALL funcOneParam
MOV AX,funcOneParamReturnVariable
MOV temp8,AX
MOV AX,temp8
MOV a7,AX
MOV AX,a7
CALL OUTDEC
MOV AX,a7
MOV arg12,AX
CALL funcOneParam
MOV AX,funcOneParamReturnVariable
MOV temp9,AX
MOV AX,temp9
MOV arg3,AX
CALL voidfunction
MOV AX,voidfunctionReturnVariable
MOV temp10,AX
CALL funcNoparam
MOV AX,funcNoparamReturnVariable
MOV temp11,AX
MOV AX,temp11
MOV a6,AX
MOV AX,a6
MOV arg24,AX
MOV AX,b6
MOV arg34,AX
CALL funcVoidTwoParam
MOV AX,funcVoidTwoParamReturnVariable
MOV temp12,AX
MOV AX,temp12
MOV a6,AX
MOV temp13,0
MOV AX,temp13
MOV mainReturnVariable,AX
JMP LabelReturnmain
LabelReturnmain:
MOV AH,4CH
INT 21H
outdec proc
push ax
push bx
push cx
push dx
or ax,ax
jge END_IF1
push ax
mov dl,'-'
mov ah,2
int 21h
pop ax
neg ax
END_IF1:
xor cx,cx
mov bx,10d
REPEAT1:
xor dx,dx
div bx
push dx
inc cx
or ax,ax
jne REPEAT1
mov ah,2
PRINT_LOOP:
pop dx
or dl,30h
int 21h
loop PRINT_LOOP
mov dx,13
mov ah,2
int 21h 
mov dx,10
mov ah,2
int 21h
pop dx
pop cx
pop bx
pop ax
ret
outdec endp
END MAIN