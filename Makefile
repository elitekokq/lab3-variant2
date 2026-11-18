lab3: main.o input.o program.o operations.o
	clang main.o input.o program.o operations.o -o lab3

main.o: main.c lab3.h
	clang -c main.c

input.o: input.c lab3.h
	clang -c input.c

program.o: program.c lab3.h
	clang -c program.c

operations.o: operations.c lab3.h
	clang -c operations.c

clean:
	rm -f *.o lab3
