#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#include "world.h"
#include "sets.h"

#define UINT_MAX WORLD_SIZE

struct sets_t;

void sets_init(struct sets_t* s)
{
    s->l[0] = UINT_MAX;
}

void sets_list_init(struct sets_t s[], const int nb)
{
    for (int i = 0; i < nb; ++i) 
        sets_init(&s[i]);
}

int sets_get_nb(const struct sets_t* set)
{
    int i = 0;
    for (; set->l[i] != UINT_MAX; ++i);
    return i;
}

int sets_get_at_nb(const struct sets_t* set, const int nb)
{
    return (nb < sets_get_nb(set)) ? set->l[nb] : UINT_MAX;
}

void sets_add(struct sets_t* s, int p)
{
    int nb = sets_get_nb(s);
    if (nb < UINT_MAX) {
        s->l[nb] = p;
        s->l[nb+1] = UINT_MAX;
    }
}

int sets_get_random(struct sets_t* s)
{
    return s->l[rand()%sets_get_nb(s)];
}

void sets_set_sort(struct sets_t* set, struct world_t* world, enum sort_t sort)
{
    for (int i = 0; i < sets_get_nb(set); ++i)
        world_set_sort(world, i, sort);
}

void sets_set_color(struct sets_t* set, struct world_t* world, enum color_t color) 
{
    for (int i = 0; i < sets_get_nb(set); ++i)
        world_set(world, i, color);
}

void sets_set_initial_sets(int nb_players, struct sets_t sets[])
{
    for(int i = 0; i < nb_players; i++) {
        int p = 0;
        for (int k =((HEIGHT/nb_players)*WIDTH); k < (((HEIGHT/nb_players)+1)*WIDTH); k++) {
            sets_add(&sets[i], ((i*WIDTH*HEIGHT)/nb_players)+p);
            p+=1;
        }
    }
}
