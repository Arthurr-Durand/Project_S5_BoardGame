#ifndef __WORLD_EXT_H__
#define __WORLD_EXT_H__

#include "players.h"

struct world_ext_t {
    struct world_t* world;
    int nb_players;
    struct players_t players[WORLD_SIZE];
    struct sets_t initial_sets[WORLD_SIZE];
    struct sets_t current_sets[WORLD_SIZE];
};

void world_ext_init(struct world_ext_t* world_ext, int nb_players, int starting_position, int max_dep, enum sort_t pawn_type, int format, int formae);

struct world_t* world_ext_get_world(struct world_ext_t* world_ext);

struct players_t* world_ext_get_player_nb(struct world_ext_t* world_ext, int nb);

struct sets_t* world_ext_get_initial_sets(struct world_ext_t* wold_ext);

struct sets_t* world_ext_get_current_sets(struct world_ext_t* wold_ext);

void world_ext_get_all_moves(struct world_ext_t* world_ext, struct sets_t* set, struct pawns_t* pawn);

#endif // __WORLD_EXT_H__