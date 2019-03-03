ll: main.o
	gcc main.o -o bin/anagram
main.o: main.c
	gcc -I . -c main.c -O3
clean:
	rm -rf *.o
	rm bin/anagram
