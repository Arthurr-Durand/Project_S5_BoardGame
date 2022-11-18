#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#include "world.h"

/** Struct representing a place in a world*/
struct places_t {
    unsigned int index; // The index of the place
    enum color_t color; // The color of the place
    enum sort_t sort; // The sort of the place
};

/** Abstract struct representing the possible places in the world
    These places are indexed from 0 to WORLD_SIZE-1 */
struct world_t {
    struct places_t p[WORLD_SIZE]; // The list of all places in the world
};

struct world_t world;

/** Initializes a world (NO_COLOR, NO_SORT everywhere)
    Always returns the same pointer */
struct world_t* world_init() {
    for (int i = 0; i < WORLD_SIZE; ++i) {
        world.p[i].index = i;
        world.p[i].color = NO_COLOR;
        world.p[i].sort = NO_SORT;
    }
    return &world;
};

/** Return the color at a place */
enum color_t world_get(const struct world_t* b, unsigned int idx)
{
    return b->p[idx].color;
}

/** Sets the color at a place */
void world_set(struct world_t* b, unsigned int idx, enum color_t c)
{
    b->p[idx].color = c;
}

/** Return the sort at a place */
enum sort_t world_get_sort(const struct world_t* b, unsigned int idx)
{
    return b->p[idx].sort;
}

/** Sets the sort at a place */
void world_set_sort(struct world_t* b, unsigned int idx, enum sort_t c)
{
    b->p[idx].sort = c;
}
