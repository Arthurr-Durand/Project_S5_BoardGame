#ifndef __SETS_H__
#define __SETS_H__

#include "geometry.h"
#include "world.h"

/** A struct representing a set of places by their index in the world */
struct sets_t {
    int l[WORLD_SIZE+1];
};

/** Inits an empty set */
struct sets_t* sets_init();

/** Returns the number places in a set */
int sets_get_nb(const struct sets_t* set);

/** Returns the value at nb */
int sets_get_at_nb(const struct sets_t* set, const int nb);

/** Adds a place to a set */
void sets_add(struct sets_t* set, int nb);

/** Returns a random place in a set */
int sets_get_random(struct sets_t* set);

/** Sets the sort of all places in a set */
void sets_set_sort(struct sets_t* set, struct world_t* world, enum sort_t sort);

/** Sets the color of all places in a set */
void sets_set_color(struct sets_t* set, struct world_t* world, enum color_t color);

#endif // __SETS_H__
