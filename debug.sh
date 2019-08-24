bison -d -y -v   1605115_parser.y
echo '1'
g++ -c -o y.o y.tab.c -g
echo '2'
flex 1605115_scanner.l
echo '3'
g++ -c -o l.o lex.yy.c -g
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo '4'
g++ -o a.out y.o l.o -lfl -ly -g
echo '5'
 gdb ./a.out
run input.c

 #commands - backtrace, bt full, where, list