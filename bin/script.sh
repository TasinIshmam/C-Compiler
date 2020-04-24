cd $(dirname $0)
echo '::---->Installing Flex & Bison'
sudo apt-get install flex bison
echo '::---->Installed Flex & Bison'
which flex
which bison

echo 'Parsing with Bison'
bison -d -y -v   1605115.y
g++ -std=c++11  -c -o y.o y.tab.c
echo 'Scanning wtih Flex'
flex 1605115.l
g++ -std=c++11  -c -o l.o lex.yy.c
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo 'Moving executables to out folder'
mv y.o ../out/
mv l.o ../out/
echo 'Linking Scanner and Parser Files'
g++ -std=c++11  -o ../out/a.out ../out/y.o ../out/l.o -lfl -ly
