#Variables
CC = gcc
CFLAGS = -Wall -g
SRC = main.c game.c archivos.c neighbors.c
OBJ = main.o game.o archivos.o neighbors.o
FNAME = conway

#Rules
$(FNAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(FNAME) $(OBJ)

$(OBJ): $(SRC)
	$(CC) -c $(SRC)

clean:
	rm -f conway *.o *.PBM