WIDTH ?= 10
HEIGHT ?= 10
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)
CC = gcc

all: project

%.o: %.c
	$(CC) -c -I src $(CFLAGS) $^ -o $@

project: src/main.o src/geometry.o src/world.o src/neighbors.o src/sets.o src/pawns.o src/players.o src/world_ext.o src/game.o
	$(CC) $^ -o $@
	rm */*.o

test:
	make test_project

test_project: tst/test.o src/geometry.o src/world.o src/neighbors.o src/sets.o src/pawns.o src/players.o src/world_ext.o src/game.o
	$(CC) -g -O0 $^ -o $@.out
	rm */*.o

clean:
	rm -f project *.o *~ *.out
