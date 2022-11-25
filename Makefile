WIDTH ?= 10
HEIGHT ?= 10
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)
CC = gcc

all: project

%.o: %.c
	$(CC) -c -I src $(CFLAGS) $^ -o $@

project: # (Add your dependency here, e.g "project.o")
	# (Add your compile command here, e.g "gcc $(CFLAGS) project.o -o project")

test_project: tst/test.o src/geometry.o src/world.o src/neighbors.o src/sets.o src/pawn.o
	$(CC) $^ -o $@.out
	rm */*.o

clean:
	rm -f *.o *~ *.out
