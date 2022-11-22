#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#include "world.h"
#include "sets.h"

#define UINT_MAX WORLD_SIZE

struct sets_t {
    int l[WORLD_SIZE+1];
};

struct sets_t* sets_init() {
    static struct sets_t s;
    s.l[0] = UINT_MAX;
    return &s;
}

int sets_get_nb(const struct sets_t* set) {
    int i = 0;
    for (; set->l[i] != UINT_MAX; ++i);
    return i;
}

int sets_get_at_nb(const struct sets_t* set, const int nb) {
    return (nb < sets_get_nb(set)) ? set->l[nb] : UINT_MAX;
}


void sets_add(struct sets_t* s, int p) {
    int nb = sets_get_nb(s);
    if (nb < UINT_MAX) {
        s->l[nb] = p;
        s->l[nb+1] = UINT_MAX;
    }
}

int sets_get_random(struct sets_t* s);

void sets_set_sort(struct sets_t* set, struct world_t* world, enum sort_t sort) {
    for (int i = 0; i < sets_get_nb(set); ++i)
        world_set_sort(world, i, sort);
}

void sets_set_color(struct sets_t* set, struct world_t* world, enum color_t color) {
    for (int i = 0; i < sets_get_nb(set); ++i)
        world_set(world, i, color);
}
