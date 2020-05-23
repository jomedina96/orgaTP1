#Variables
CC = gcc
CFLAGS = -Wall -g
SRC = main.c juego.c archivos.c
OBJ = main.o juego.o archivos.o
FNAME = conway

#Rules
$(FNAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(FNAME) $(OBJ)

$(OBJ): $(SRC)
	$(CC) -c $(SRC)

clean:
	rm -f conway *.o