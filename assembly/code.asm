.MODEL SMALL
.STACK 100H
.DATA 
mainReturnVariable dw ?
val2 dw ?
i2 dw ?
temp0 dw ?
temp1 dw ?
temp2 dw ?
temp3 dw ?
temp4 dw ?
temp5 dw ?
temp6 dw ?
temp7 dw ?
temp8 dw ?
temp9 dw ?
temp10 dw ?
temp11 dw ?
a2 dw 20 dup(?)
.CODE
main PROC
    MOV AX,@DATA
MOV DS,AX 
MOV temp0,0
MOV AX,temp0
MOV i2,AX
;Loop Begin
Label2:
;$4 code Begin
MOV temp1,15
MOV AX,i2
CMP AX,temp1
JL Label0
MOV temp2,0
JMP Label1
Label0:
MOV temp2,1
Label1:
;$4 code End
MOV AX,temp2
CMP AX,0
JE Label3
;$7 code Begin
MOV BX,i2
ADD BX,BX
MOV temp4,1
MOV AX,i2
ADD AX,temp4
MOV temp5,AX
MOV AX,temp5
MOV a2[BX],AX
;$5 code Begin
MOV AX,i2
MOV temp3,AX
INC i2
JMP Label2
Label3:
;Loop END
MOV temp6,0
MOV AX,temp6
MOV i2,AX
;Loop Begin
Label6:
;$4 code Begin
MOV temp7,15
MOV AX,i2
CMP AX,temp7
JL Label4
MOV temp8,0
JMP Label5
Label4:
MOV temp8,1
Label5:
;$4 code End
MOV AX,temp8
CMP AX,0
JE Label7
;$7 code Begin
MOV BX,i2
ADD BX,BX
MOV AX, a2[BX]
MOV temp10,AX
MOV AX,temp10
MOV val2,AX
MOV AX,val2
CALL OUTDEC
;$5 code Begin
MOV AX,i2
MOV temp9,AX
INC i2
JMP Label6
Label7:
;Loop END
MOV temp11,0
MOV AX,temp11
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