#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#include "sets.h"

#define UINT_MAX WORLD_SIZE

struct sets_t {
    int l[WORLD_SIZE+1];
};

/** Inits an empty set */
struct sets_t* sets_init() {
    static struct sets_t s;
    s.l[0] = UINT_MAX;
    return &s;
}

/** Returns the number of places pointers in a set */
int sets_get_nb(const struct sets_t* s) {
    int i = 0;
    for (; s->l[i] != UINT_MAX; ++i);
    return i;
}

/** Adds a place pointer to a set */
void sets_add(struct sets_t* s, int p) {
    int nb = sets_get_nb(s);
    if (nb < UINT_MAX) {
        s->l[nb] = p;
        s->l[nb+1] = UINT_MAX;
    }
}

/** Returns a random place pointer in a set */
int sets_get_random(struct sets_t* s);

/** Sets the sort of all places in a set */
void sets_set_sort(struct sets_t* s);

/** Sets the color of all places in a set */
void sets_set_color(struct sets_t* s);
