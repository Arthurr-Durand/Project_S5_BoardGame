#ifndef __SETS_H__
#define __SETS_H__

#include "world.h"

/** A struct representing a vector towards a neighbor of a place
    It contains the index of the neighbor, and the direction it's in */
struct sets_t;

struct sets_t set_init(); // Inits an empty set

void get_nb_in_set(const struct sets_t s); // Returns the number of places pointers in a set

// void add_to_set(struct sets_t, struct places_t* p); // Adds a place pointer to a set

// struct place_t* random_in_set(struct sets_t s, struct places_t p); // Returns a random place pointer in a set

#endif // __SETS_H__
