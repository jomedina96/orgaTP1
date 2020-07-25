#Variables
CC = gcc
CFLAGS = -Wall -g
SRC = archivos.c binario.c cache.c main.c
OBJ = main.o game.o archivos.o neighbors.o
FNAME = tp2
FILES = 10

#Rules
tp.c: $(SRC) $(SRC_C)
	$(CC) $(CFLAGS) -o $(FNAME) $(SRC) $(SRC_C)

run: tp2
	for i in $$(seq 1 $(FILES)); \
	do \
		echo " "; \
		echo " "; \
		echo "-------------------------------------------------"; \
		echo "RUNNING TP2 WITH PRUEBA$$i.MEM FILE"; \
		./tp2 prueba$$i.mem; \
		echo " "; \
	done

clean:
	rm -f tp2 *.o