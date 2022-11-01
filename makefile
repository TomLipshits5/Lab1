build: bin/main.o bin/numbers.o bin/add.o
	@echo "linking files"
	gcc -m32 -Wall -g -o bin/main bin/main.o bin/numbers.o bin/add.o
	gcc -m32 -Wall -g -o bin/encoder Task1.c

bin/main.o: main.c
	@echo "compiling main"
	gcc -m32 -Wall -c -g -o bin/main.o main.c

bin/numbers.o: numbers.c
	@echo "compiling numbers"
	gcc -m32 -Wall -c -g -o bin/numbers.o numbers.c

bin/add.o: add.s
	@echo "compiling add"
	nasm -g -f elf -w+all -o bin/add.o add.s

clean:
	@echo "Cleaning"
	rm -f bin/*