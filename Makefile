WIDTH ?= 10
HEIGHT ?= 10
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)
CC = gcc

all: project

%.o: %.c
	$(CC) -c -I src $(CFLAGS) $^ -o $@

project: src/main.o src/geometry.o src/world.o src/neighbors.o src/sets.o src/pawns.o src/players.o src/world_ext.o src/game.o
	$(CC) $^ -o $@ -lm

test: test_geometry test_world test_neighbors test_sets test_pawns test_players test_world_ext test_game
	./test_geometry
	./test_world
	./test_neighbors
	./test_sets
	./test_pawns
	./test_players
	./test_world_ext
	./test_game

test_%: src/%.o tst/test_utilities.o tst/test_%.o src/geometry.o src/world.o src/neighbors.o src/sets.o src/pawns.o src/players.o src/world_ext.o src/game.o
	$(CC) -g -O0 $^ -o $@

doc:
	cd doc/ && pdflatex doc/rendu.tex

clean:
	rm -f project test_* */*.o
