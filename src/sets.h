#ifndef __SETS_H__
#define __SETS_H__

#include "world.h"

/** A struct representing a vector towards a neighbor of a place
    It contains the index of the neighbor, and the direction it's in */
struct sets_t;

/** Inits an empty set */
struct sets_t* sets_init();

/** Returns the number of places pointers in a set */
int sets_get_nb(const struct sets_t* s);

/** Adds a place pointer to a set */
void sets_add(struct sets_t* s, int nb);

/** Returns a random place pointer in a set */
int sets_get_random(struct sets_t* s);

/** Sets the sort of all places in a set */
void sets_set_sort(struct sets_t* s);

/** Sets the color of all places in a set */
void sets_set_color(struct sets_t* s);

#endif // __SETS_H__
