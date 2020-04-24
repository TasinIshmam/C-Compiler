### C Compiler

A simple compiler for a subset of the C Programming Language.  Generates x86 Assembly. Written in C++ 

**Sustem Compatibility:** **Linux** 
*This software was written and tested on Ubuntu/Debian environment. I cannot guarantee full compatilibty with other distros without proper testing.*

**Output:** Assembly Code that targets Intel 8086 Processor (x86 Assembly)
**Dependencies:** Flex, Bison


#### Usage
**1.** Clone this repository

**2.** Run compile.sh in the root. It will prompt you to provide the 'C' file name. This compiles your input file, checks compile errors (lexical/syntax/symantic) which are written in log.txt inside the 'logs' folder. In case of a successful compilation,the generated assembly code can be found in the assembly folder.
**3.** In order to run the generated assembly, use a *8086 Microprocessor emulator. Example: [emu8086](https://emu8086-microprocessor-emulator.en.softonic.com/)
**4.** Use debug.sh to use gdb debugger for any issues.



#### Known Issues

- This implementation of compiler uses static allocation and therefore, doesn't support Recursion.

- Does not come with a linker. So does not support include statements

- Support for structs not yet included.

#### Sample Output
##### Input C code:
```c
int fact(int n){
    int f,i;
    f = 1;
    for(i=n;i>0;i--){
    f = f * i;
    }
    return f;
}


int main(){

    int n,f;
    n = 6;
    f = fact(n);
    println(f);
    return 0;
}

```
##### Generated x86 Assembly
```asm
.MODEL SMALL
.STACK 100H
.DATA 
n2 dw ?
factReturnVariable dw ?
i2 dw ?
f2 dw ?
temp0 dw ?
temp1 dw ?
temp2 dw ?
temp3 dw ?
temp4 dw ?
mainReturnVariable dw ?
f4 dw ?
n4 dw ?
temp5 dw ?
temp6 dw ?
temp7 dw ?
.CODE
fact PROC
PUSH AX
PUSH BX 
PUSH CX 
PUSH DX
PUSH n2
MOV temp0,1
MOV AX,temp0
MOV f2,AX
MOV AX,n2
MOV i2,AX
;Loop Begin
Label2:
;$4 code Begin
MOV temp1,0
MOV AX,i2
CMP AX,temp1
JG Label0
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
MOV AX,f2
MOV BX,i2
MUL BX
MOV temp4, AX
MOV f2,AX
;$5 code Begin
MOV AX,i2
MOV temp3,AX
DEC i2
JMP Label2
Label3:
;Loop END
MOV AX,f2
MOV factReturnVariable,AX
JMP LabelReturnfact
LabelReturnfact:
POP n2
POP DX
POP CX
POP BX
POP AX
ret
fact ENDP
main PROC
    MOV AX,@DATA
MOV DS,AX 
MOV temp5,6
MOV AX,temp5
MOV n4,AX
MOV n2,AX
CALL fact
MOV AX,factReturnVariable
MOV temp6,AX
MOV f4,AX
CALL OUTDEC
MOV temp7,0
MOV AX,temp7
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


```
