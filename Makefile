all:
	make bin;
	make rshell;
	make ls;
	make cp;
bin:
	mkdir bin;
rshell:
	g++ src/rshell.cpp -Wall -Werror -ansi -pedantic -o bin/rshell
ls:
	g++ src/ls.cpp -Wall -Werror -ansi -pedantic -o bin/ls
cp:
	g++ src/cp.cpp -Wall -Werror -ansi -pedantic -o bin/cp

