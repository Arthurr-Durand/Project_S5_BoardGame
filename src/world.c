#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#include "world.h"

/** Abstract struct representing the possible places in the world
    These places are indexed from 0 to WORLD_SIZE-1 */
struct world_t {
    enum color_t colors[WORLD_SIZE];
    enum sort_t sorts[WORLD_SIZE];
};

struct world_t world;

/** Initializes a world (NO_COLOR, NO_SORT everywhere)
    Always returns the same pointer */
struct world_t* world_init() {
    for (int i = 0; i < WORLD_SIZE; ++i) {
        world.colors[i] = NO_COLOR;
        world.sorts[i] = NO_SORT;
    }
    return &world;
};

/** Return the color at a place */
enum color_t world_get(const struct world_t* b, unsigned int idx)
{
    return b->colors[idx];
}

/** Sets the color at a place */
void world_set(struct world_t* b, unsigned int idx, enum color_t c)
{
    b->colors[idx] = c;
}

/** Return the sort at a place */
enum sort_t world_get_sort(const struct world_t* b, unsigned int idx)
{
    return b->sorts[idx];
}

/** Sets the sort at a place */
void world_set_sort(struct world_t* b, unsigned int idx, enum sort_t c)
{
    b->sorts[idx] = c;
}
