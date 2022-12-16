#ifndef __SETS_H__
#define __SETS_H__

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

/** Returns the position of place in a set */
int sets_get_position_of(const struct sets_t* set, const int place);

/** Adds a place to a set */
void sets_add(struct sets_t* set, int nb);

/** Removes a place to a set */
void sets_remove(struct sets_t* set, int place);

/**  Return Bool  */
int sets_is_in_set(const struct sets_t* set, const int idx);

/** Returns a random place in a set */
int sets_get_random_place(struct sets_t* set);

/** Sets the sort of all places in a set */
void sets_set_sorts(struct sets_t* set, struct world_t* world, enum sort_t sort);

/** Sets the color of all places in a set */
void sets_set_colors(struct sets_t* set, struct world_t* world, enum color_t color);

/** Sets the initial set for a number of players */
void sets_set_initial_sets(int nb_players, struct sets_t initial_sets[], struct sets_t current_sets[]);

/** Sets the initial battle ground set for a number of player <4 */
void sets_set_initial_sets_battleground(int nb_players, struct sets_t sets[], struct sets_t current_sets[]);

void sets_get_good_places(struct sets_t* set, struct sets_t iniset[]);

#endif // __SETS_H__
