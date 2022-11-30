#ifndef __SETS_H__
#define __SETS_H__

#include "geometry.h"
#include "world.h"

/** A struct representing a set of places by their index in the world */
struct sets_t {
    int l[WORLD_SIZE+1];
};

/** Inits an empty set */
void sets_init(struct sets_t* s);

/** Inits a list of empty sets */
void sets_list_init(struct sets_t s[], const int nb);

/** Returns the number places in a set */
int sets_get_nb(const struct sets_t* set);

/** Returns the value at nb */
int sets_get_place_at(const struct sets_t* set, const int nb);

/** Adds a place to a set */
void sets_add(struct sets_t* set, int nb);

/** Returns a random place in a set */
int sets_get_random_place(struct sets_t* set);

/** Sets the sort of all places in a set */
void sets_set_sorts(struct sets_t* set, struct world_t* world, enum sort_t sort);

/** Sets the color of all places in a set */
void sets_set_colors(struct sets_t* set, struct world_t* world, enum color_t color);

/** Sets the initial set for a number of players */
void sets_set_initial_sets(int nb_players, struct sets_t sets[]);

#endif // __SETS_H__
