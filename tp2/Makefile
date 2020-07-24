#Variables
CC = gcc
CFLAGS = -Wall -g
SRC = archivos.c binario.c cache.c main.c
OBJ = main.o game.o archivos.o neighbors.o
FNAME = cache

#Rules
tp.c: $(SRC) $(SRC_C)
	$(CC) $(CFLAGS) -o $(FNAME) $(SRC) $(SRC_C)

clean:
	rm -f cache *.o