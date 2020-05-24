#include <regdef.h>

#define NEIGHBORS_PERIMETER_SIZE 8
#define SIDES_SIZE 2
#define ALIVE_CELL 1

.data
centralSides:           .space SIDES_SIZE
topSides:               .space SIDES_SIZE
bottomSides:            .space SIDES_SIZE
neighborsPerimeter:     .space NEIGHBORS_PERIMETER_SIZE

.text
.align 2
.globl vecinos
.ent vecinos

vecinos:
    subu sp, sp, 48                                     # ----- Building stack -----
    sw ra, 40(sp)
    sw fp, 36(sp)
    .cprestore 32                                       # sw gp, 32(sp)
    move fp, sp
    lw t0, 64(fp)                                       # t0 = N
    sw t0, 16(fp)
    sw a3, 12(fp)
    sw a2, 8(fp)
    sw a1, 4(fp)
    sw a0, 0(fp)
    mul t1, t0, a1                                      # ----- Function body -----
    add t1, t1, a2                                      # t1 = i * N + j (referencePoint)
    sw t1, 28(fp)
    la t3, neighborsPerimeter
    sw t3, 24(fp)
    move a0, t1
    jal findNeighbors
    li t0, 0                                            # t0 = neighborCounter
    li t1, 0                                            # t1 = position
for:                                                    # ----- Contabiliza la cantidad de vecinos vivos -----
    bge t1, NEIGHBORS_PERIMETER_SIZE, exitVecinos
    la t2, neighborsPerimeter                           # t2 = neighborsPerimeter
    lw t3, 0(fp)                                        # t3 = a
    mul t4, t1, 4                                       # t4 = position*4 (offset)
    add t4, t2, t4
    lw t4, (t4)                                         # t4 = neighborsPerimeter[position]
    mul t4, t4, 4
    add t4, t3, t4
    lw t4, (t4)
    add t0, t0, t4
    addi t1, t1, 1                                      # t1 = position + 1
exitVecinos:
    move v0, t0
    lw ra, 40(sp)                                       # Disarming stack
    lw fp, 36(sp)
    lw gp, 32(sp)
    lw a3, 12(sp)
    lw a2, 8(sp)
    lw a1, 4(sp)
    lw a0, 0(sp)
    addu sp, sp, 48
    jr ra
.end vecinos


.text
.align 2
.globl findNeighbors
.ent findNeighbors

findNeighbors:                      # ----- Función que se encarga de encontrar a todos los vecinos del perímetro -----
    subu sp, sp, 56                 # ----- Building stack -----
    sw ra, 48(sp)
    sw fp, 44(sp)
    .cprestore 40                   # sw gp, 40(sp)
    move fp, sp
    sw a3, 12(fp)
    sw a2, 8(fp)
    sw a1, 4(fp)
    sw a0, 0(fp)
    la t0, centralSides
    sw t0, 24(fp)
    la t0, topSides
    sw t0, 20(fp)
    la t0, bottomSides
    sw t0, 16(fp)
    move a1, a2                     # ----- Function body -----
    move a2, a3
    la a3, centralSides
    jal findSides
    lw t0, 4(fp)                    # ----- Analiza si el punto no esta en el borde superior o inferior -----
    ble t0, 0, isEdge
    lw t1, 12(fp)                   # t1 = rowSize
    subi t1, t1, 1                  # t1 = rowSize - 1
    bge t0, t1, isEdge
    lw t0, 72(fp)                   # t0 = columnSize
    sub t1, a0, t0                  # t1 = top
    sw t1, 32(fp)
    add t2, a0, t0                  # t2 = bottom
    sw t2, 28(fp)
    move a0, t1
    move a2, t0
    la a3, topSides
    jal findSides
    move a0, t2
    la a3, bottomSides
    jal findSides
    b exitFindNeighbors
isEdge:
    bne t0, 0, bottomEdge           # ----- Analiza si está o no en el borde superior -----
topEdge:                            # ----- En el borde superior -----
    lw t0, 72(fp)                   # t0 = columnSize
    lw t1, 12(fp)                   # t1 = rowSize
    subi t1, t1, 1                  # t1 = rowSize - 1
    mul t1, t1, t0                  # t1 = columnSize*(rowSize - 1)
    add t3, a0, t1                  # t3 = top
    sw t1, 32(fp)
    add t4, a0, t0                  # t4 = bottom
    sw t2, 28(fp)
    move a0, t3
    move a2, t0
    la a3, topSides
    jal findSides
    move a0, t4
    la a3, bottomSides
    jal findSides
    b exitFindNeighbors
bottomEdge:                         # ----- En el borde inferior -----
    lw t0, 72(fp)                   # t0 = columnSize
    lw t1, 12(fp)                   # t1 = rowSize
    subi t1, t1, 1                  # t1 = rowSize - 1
    mul t1, t1, t0                  # t1 = columnSize*(rowSize - 1)
    sub t3, a0, t0                  # t3 = top
    sw t1, 32(fp)
    sub t4, a0, t1                  # t4 = bottom
    sw t2, 28(fp)
    move a0, t3
    move a2, t0
    la a3, topSides
    jal findSides
    move a0, t4
    la a3, bottomSides
    jal findSides
exitFindNeighbors:
    lw t0, 76(fp)                   # t0 = neighborsPerimeter
    lw t1, 32(fp)                   # t1 = top
    sw t1, 0(t0)
    lw t1, 28(fp)                   # t1 = bottom
    sw t1, 4(t0)
    la t1, centralSides
    lw t2, 0(t1)
    sw t2, 8(fp)
    lw t2, 4(t1)
    sw t2, 12(fp)
    la t1, topSides
    lw t2, 0(t1)
    sw t2, 16(fp)
    lw t2, 4(t1)
    sw t2, 20(fp)
    la t1, bottomSides
    lw t2, 0(t1)
    sw t2, 24(fp)
    lw t2, 4(t1)
    sw t2, 28(fp)
    lw ra, 48(sp)                   # Disarming stack
    lw fp, 44(sp)
    lw gp, 40(sp)
    lw a3, 12(sp)
    lw a2, 8(sp)
    lw a1, 4(sp)
    lw a0, 0(sp)
    addu sp, sp, 56
    jr ra
.end findNeighbors


.text
.align 2
.globl findSides
.ent findSides

findSides:                          # ----- Funcion que busque los laterales dado un punto -----
    subu sp, sp, 8                  # ----- Building stack -----
    sw fp, 4(sp)
    .cprestore 0                    # sw gp, 0(sp)
    beq a1, 0, isSide               # ----- Function body: Analiza que no este en el borde derecho o izquierdo -----
    subi t0, a2, 1
    beq a1, t0, isSide
    subi t0, a0, 1
    addi t1, a0, 1
    sw t0, (a3)
    sw t1, 4(a3)
    b exitFindSides
isSide:
    beq a1, 0, leftSide             # ----- Si está en un borde, analiza si es el izquierdo -----
rightSide:                          # ----- En el borde derecho -----
    subi t0, a0, 1
    sub t1, a0, a2
    addi t1, t1, 1
    sw t0, (a3)
    sw t1, 4(a3)
    b exitFindSides
leftSide:                           # ----- En el borde izquierdo -----
    add t0, a0, a2
    subi t0, t0, 1
    addi, t1, a0, 1
    sw t0, (a3)
    sw t1, 4(a3)
exitFindSides:
    lw gp, 0(sp)                    # ----- Disarming stack -----
    lw fp, 4(sp)
    addu sp, sp, 8
    jr ra
.end findSides
