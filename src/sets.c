#include <stdio.h>
#include <stdlib.h>

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
	for (; set->l[i] != UINT_MAX; ++i)
		;
	return i;
}

int sets_get_place_at(const struct sets_t* set, const int nb)
{
	return (nb < sets_get_nb(set)) ? set->l[nb] : UINT_MAX;
}

int sets_get_position_of(const struct sets_t* set, const int place)
{
	if (sets_is_in_set(set, place)) {
		for (int i = 0; sets_get_place_at(set, i) != UINT_MAX; ++i) {
			if (sets_get_place_at(set, i) == place)
				return i;
		}
	}
	return -1;
}

void sets_add(struct sets_t* s, int p)
{
	int nb = sets_get_nb(s);
	if (nb < UINT_MAX) {
		s->l[nb] = p;
		s->l[nb + 1] = UINT_MAX;
	}
}

void sets_remove(struct sets_t* set, int place)
{
	int max_nb = sets_get_nb(set);
	for (int position = sets_get_position_of(set, place); position <= max_nb; position++) {
		set->l[position] = set->l[position + 1];
	}
}

int sets_is_in_set(const struct sets_t* set, const int idx)
{
	for (int i = 0; sets_get_place_at(set, i) != UINT_MAX; ++i)
		if (sets_get_place_at(set, i) == idx)
			return 1;
	return 0;
}

int sets_get_random_place(struct sets_t* s)
{
	return s->l[rand() % sets_get_nb(s)];
}

void sets_set_sorts(struct sets_t* set, struct world_t* world, enum sort_t sort)
{
	for (int i = 0; i < sets_get_nb(set); ++i)
		world_set_sort(world, i, sort);
}

void sets_set_colors(struct sets_t* set, struct world_t* world, enum color_t color)
{
	for (int i = 0; i < sets_get_nb(set); ++i)
		world_set(world, i, color);
}

void sets_set_initial_sets(int nb_players, struct sets_t initial_sets[], struct sets_t current_sets[])
{
	for (int i = 0; i < nb_players; i++) {
		int p = 0;
		for (int k = ((HEIGHT / nb_players) * WIDTH); k < (((HEIGHT / nb_players) + 1) * WIDTH); k++) {
			sets_add(&initial_sets[i], ((i * WIDTH * HEIGHT) / nb_players) + p);
			sets_add(&current_sets[i], ((i * WIDTH * HEIGHT) / nb_players) + p);
			p += 1;
		}
	}
}

void sets_set_initial_sets_battleground(int nb_players, struct sets_t initial_sets[], struct sets_t current_sets[])
{
	for (int i = 0; i < nb_players; i++) {
		int p = 1;
		for (int k = ((HEIGHT / nb_players) * WIDTH) + 1; k < (((HEIGHT / nb_players) + 1) * WIDTH) - 1; k++) {
			for (int j = 1; j < ((WIDTH - (2 * nb_players)) / nb_players) + 1; j++) {
				sets_add(&initial_sets[i], ((i * WIDTH * HEIGHT) / nb_players) + p + WIDTH * j);
				sets_add(&current_sets[i], ((i * WIDTH * HEIGHT) / nb_players) + p + WIDTH * j);
			}
			p += 1;
		}
	}
}

// void sets_get_good_places(struct sets_t* set, struct sets_t initial_sets[])
// {
//     int a;
//     //int b=a;
//     int list[sets_get_nb(set)];
//     for(int i=0;i<sets_get_nb(set);i++){
//         a=abs(set->l[i]-initial_sets->l[0]);
//         for(int k=0;k<sets_get_nb(initial_sets);k++){
//             if (a>abs(set->l[i]-initial_sets->l[k])){
//                 a=abs(set->l[i]-initial_sets->l[k]);
//                 printf("coucou %d\n",k);
//             }
//         }
//         list[i]=a;
//         printf("%d\n",list[i]);
//         // //printf("a=%d\n",a);
//         // printf("place %d\n",set->l[i]);
//         // if (a>b){
//         //     sets_remove(set,i-1);
//         //     a=b;
//         // }
//         // if ((b>a) && (i!=0)){
//         //     sets_remove(set,i);
//         //     b=a;
//         // }
//     }
// }