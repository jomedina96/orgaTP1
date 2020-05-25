#Variables
CC = gcc
CFLAGS = -Wall -g
CFLAGS_ASM = -mno-mips16 -mgp32 -mfp32 -gpubnames -mlong32 -mips1 -mabicalls -mlong-calls -mframe-header-opt -march=r2k
SRC = main.c game.c archivos.c
SRC_C = neighbors.c
SRC_ASM = neighbors.S
OBJ = main.o game.o archivos.o neighbors.o
FNAME = conway

#Rules
asm: $(SRC) $(SRC_ASM)
	$(CC) $(CFLAGS) $(CFLAGS_ASM) -o $(FNAME) $(SRC) $(SRC_ASM)

c: $(SRC) $(SRC_C)
	$(CC) $(CFLAGS) -o $(FNAME) $(SRC) $(SRC_C)

clean:
	rm -f conway *.o *.PBM