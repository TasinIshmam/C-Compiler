
echo 'Generating executables for compiler'
sh bin/script.sh
echo 'Starting debugger'
echo 'To run a file through debugger type "run <filename>" '
gdb ./out/a.out 