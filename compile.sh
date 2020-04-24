echo 'Enter C file (full path)'
read filename
sudo sh bin/script.sh
echo 'Generating Assembly Code'
./out/a.out "$filename"

mv code.asm ./assembly/
mv optimized-code.asm ./assembly/
mv log.txt ./logs/

echo 'Compilation Complete.'
echo 'Code can be found in assembly folder.'
echo 'Detected compile time errors can be seen in log/log.txt'