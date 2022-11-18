WIDTH ?= 10
HEIGHT ?= 10
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)

all: project

%.o: %.c
	gcc -c $(CFLAGS) $<

project: # (Add your dependency here, e.g "project.o")
	# (Add your compile command here, e.g "gcc $(CFLAGS) project.o -o project")

test_project: # (Add your dependency here, e.g "test.o")
	gcc -c $(CFLAGS) tst/test.c
	gcc -c $(CFLAGS) src/geometry.c
	gcc -c $(CFLAGS) src/world.c
	gcc -c $(CFLAGS) src/neighbors.c
	gcc $(CFLAGS) test.o geometry.o world.o neighbors.o -o test_project.out
	# (Add your compile command here, e.g "gcc $(CFLAGS) test.o -o test_project")

clean:
	rm -f *.o *~ *.out 
