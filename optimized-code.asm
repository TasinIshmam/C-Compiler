.MODEL SMALL
.STACK 100H
.DATA 
mainReturnVariable dw ?
i2 dw ?
b2 dw ?
a2 dw ?
temp0 dw ?
temp1 dw ?
temp2 dw ?
temp3 dw ?
temp4 dw ?
temp5 dw ?
temp6 dw ?
temp7 dw ?
.CODE
main PROC
    MOV AX,@DATA
MOV DS,AX 
MOV temp0,0
MOV AX,temp0
MOV b2,AX
MOV temp1,0
MOV AX,temp1
MOV i2,AX
;Loop Begin
Label4:
;$4 code Begin
MOV temp2,4
MOV AX,i2
CMP AX,temp2
JL Label0
MOV temp3,0
JMP Label1
Label0:
MOV temp3,1
Label1:
;$4 code End
MOV AX,temp3
CMP AX,0
JE Label5
;$7 code Begin
MOV temp5,3
MOV AX,temp5
MOV a2,AX
Label2:
MOV AX,a2
MOV temp6,AX
DEC a2
MOV AX,temp6
CMP AX,0
JE Label3
MOV AX,b2
MOV temp7,AX
INC b2
JMP Label2
Label3:
;$5 code Begin
MOV AX,i2
MOV temp4,AX
INC i2
JMP Label4
Label5:
;Loop END
MOV AX,a2
CALL OUTDEC
MOV AX,b2
CALL OUTDEC
MOV AX,i2
CALL OUTDEC
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
