all: ls

ls: ls.c helpers.c
	gcc -Wall -pedantic -std=gnu17 -o ls ls.c helpers.c

clean:
	rm ls
