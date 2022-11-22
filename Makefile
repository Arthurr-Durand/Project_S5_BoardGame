WIDTH ?= 10
HEIGHT ?= 10
MANSUBA_FLAGS = -DWIDTH=$(WIDTH) -DHEIGHT=$(HEIGHT)
CFLAGS = -Wall -Wextra -std=c99 -g3 $(MANSUBA_FLAGS)
CC= gcc 

all: project

%.o: %.c
	gcc -c $(CFLAGS) $<

project: # (Add your dependency here, e.g "project.o")
	# (Add your compile command here, e.g "gcc $(CFLAGS) project.o -o project")

test_project: test.o geometry.o world.o neighbors.o   # (Add your dependency here, e.g "test.o")

	$(CC) $(CFLAGS) $^ -o $@
	rm -R *.o
	
clean:
	rm -f *.o *~ *.out 
