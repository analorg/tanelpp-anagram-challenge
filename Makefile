ll: main.o
	gcc main.o -o bin/anagram -pg
main.o: main.c
	gcc -I . -c main.c -pg
clean:
	rm -rf *.o
	rm bin/anagram
