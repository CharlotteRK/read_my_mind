CC = gcc
FLAGS = -Wall -Wextra -ggdb
CFLAGS =  -c -Wall -Wextra -ggdb -std=c99


all: array linked comp

clean:
	rm -f *.o

array: readmymind_array.c
	${CC} ${CFLAGS} readmymind_array.c -o readmymind_array.o

array: array_deck.c
	${CC} ${CFLAGS} array_deck.c -o array_deck.o

array: readmymind_array.o array_deck.o
	${CC} ${FLAGS} readmymind_array.o array_deck.o -o readmymind_array

comp: array_deck.c
	${CC} ${CFLAGS} array_deck.c -o array_deck.o

comp: comparison.c
	${CC} ${CFLAGS} comparison.c -o comparison.o

comp: linked_deck.c
	${CC} ${CFLAGS} linked_deck.c -o linked_deck.o

comp: comparison.o array_deck.o linked_deck.o
	${CC} ${FLAGS} comparison.o array_deck.o linked_deck.o -o comparison

linked: readmymind.c
	${CC} ${CFLAGS} readmymind.c -o readmymind.o

linked: linked_deck.c
	${CC} ${CFLAGS} linked_deck.c -o linked_deck.o

linked: readmymind.o linked_deck.o
	${CC} ${FLAGS} readmymind.o linked_deck.o -o readmymind
