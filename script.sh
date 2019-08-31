bison -d -y -v   1605115.y
echo '1'
g++ -std=c++11  -c -o y.o y.tab.c
echo '2'
flex 1605115.l
echo '3'
g++ -std=c++11  -c -o l.o lex.yy.c
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo '4'
g++ -std=c++11  -o a.out y.o l.o -lfl -ly
echo '5'
./a.out input.c