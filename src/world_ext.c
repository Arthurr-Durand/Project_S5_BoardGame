#include <stdlib.h>
#include <stdio.h>

#include "world_ext.h"

#define UINT_MAX WORLD_SIZE

void world_ext_init(struct world_ext_t* world_ext, int nb_players, int starting_position, int max_dep, enum sort_t pawn_type, int format, int formae)
{
    world_ext->world = world_init();
    world_ext->nb_players = nb_players;
    players_init(world_ext->players, nb_players);

    sets_list_init(world_ext->initial_sets, nb_players);
    sets_list_init(world_ext->current_sets, nb_players);
    if (starting_position)
        sets_set_initial_sets_battleground(nb_players, world_ext->initial_sets, world_ext->current_sets);
    else
        sets_set_initial_sets(nb_players, world_ext->initial_sets, world_ext->current_sets);
    players_set_initial_pawns(world_ext->world, world_ext->players, nb_players, world_ext->initial_sets, max_dep, pawn_type, format, formae);

    world_ext->nb_captured_pawns = 0;
}

struct world_t* world_ext_get_world(struct world_ext_t* world_ext)
{
    return world_ext->world;
}

int world_ext_get_nb_players(const struct world_ext_t* world_ext)
{
    return world_ext->nb_players;
}

struct players_t* world_ext_get_player_nb(struct world_ext_t* world_ext, int nb)
{
    return &world_ext->players[nb];
}

struct sets_t* world_ext_get_initial_sets(struct world_ext_t* world_ext)
{
    return world_ext->initial_sets;
}

struct sets_t* world_ext_get_current_sets(struct world_ext_t* world_ext)
{
    return world_ext->current_sets;
}


int world_ext_get_nb_captured_pawns(const struct world_ext_t* world_ext)
{
    return world_ext->nb_captured_pawns;
}

struct pawns_t* world_ext_get_captured_pawn_at_index(const struct world_ext_t* world_ext, int index)
{
    return world_ext->captured_pawns[index];
}

void world_ext_add_captured_pawn(struct world_ext_t* world_ext, struct pawns_t* pawn)
{
    world_ext->captured_pawns[world_ext->nb_captured_pawns] = pawn;
    world_ext->nb_captured_pawns++;
}

struct pawns_t* world_ext_get_pawn_at_position(struct world_ext_t* world_ext, int position)
{
    struct players_t* player;
    for (int p = 0; p < world_ext_get_nb_players(world_ext); p++) { // Get player
        if (sets_is_in_set(&world_ext_get_current_sets(world_ext)[p], position))
            player = world_ext_get_player_nb(world_ext, p);
    }
    for (int i = 0; i < players_get_nb_pawns(player); i++) { // Get pawn
        if (pawns_get_position(players_get_pawn_at_index(player, i)) == position)
            return players_get_pawn_at_index(player, i);
    }
    return players_get_pawn_at_index(world_ext_get_player_nb(world_ext, 0), 0);
}

int _world_ext_test_capture(struct world_ext_t* world_ext, int current_player_index, int new_position)
{
    if (sets_is_in_set(&world_ext_get_current_sets(world_ext)[current_player_index], new_position)) // 0 si le pion appartient au joueur
        return 0;
    for (int i = 0; i < world_ext_get_nb_players(world_ext); i++) { // 0 si le pion est dans une position de départ
        if ((i != current_player_index) && sets_is_in_set(&world_ext_get_initial_sets(world_ext)[i], new_position))
            return 0;
    }
    return 1;
}

void _world_ext_get_all_moves_simple(struct world_ext_t* world_ext, struct sets_t* set, struct pawns_t* pawn)
{
    int idx, d;
    for (int k = 0; k < (pawns_get_neighbors_nb(get_neighbors(pawns_get_position(pawn)))); ++k) {
        idx = get_neighbors(pawns_get_position(pawn)).n[k].i;
        d = get_neighbors(pawns_get_position(pawn)).n[k].d;
        for (int i = 0; i < pawns_get_max_dep(pawn); i++) {
            if (!world_get_sort(world_ext_get_world(world_ext), idx) || _world_ext_test_capture(world_ext, pawns_get_player_index(pawn), idx))
                sets_add(set, idx);
            idx = get_neighbor(idx,d);
        }
    }
}

void _world_ext_get_all_moves_tower(struct world_ext_t* world_ext, struct sets_t* set, struct pawns_t* pawn)
{
    int idx, d;
    for (int k = 0; k < (pawns_get_neighbors_nb(get_neighbors(pawns_get_position(pawn)))); ++k) {
        idx = get_neighbors(pawns_get_position(pawn)).n[k].i;
        d = get_neighbors(pawns_get_position(pawn)).n[k].d;
        switch (d) {
            case EAST:
            case WEST:
            case SOUTH:
            case NORTH:
                for (int i = 0; i < pawns_get_max_dep(pawn); i++) {
                    if (world_get_sort(world_ext_get_world(world_ext), idx) && !_world_ext_test_capture(world_ext, pawns_get_player_index(pawn), idx))
                        break;
                    else
                        sets_add(set, idx);
                    idx = get_neighbor(idx,d);
                }
                break;
            default:
                break;
        }
    }
}

void _world_ext_get_all_moves_elefun(struct world_ext_t* world_ext, struct sets_t* set, struct pawns_t* pawn)
{
    int idx, d;
    for (int k = 0; k < (pawns_get_neighbors_nb(get_neighbors(pawns_get_position(pawn)))); ++k) {
        idx = get_neighbors(pawns_get_position(pawn)).n[k].i;
        d = get_neighbors(pawns_get_position(pawn)).n[k].d;
        for (int i = 0; i < pawns_get_max_dep(pawn); i++) {
            switch (d) {
                case EAST:
                case WEST:
                case SOUTH:
                case NORTH:
                    // if ((!world_get_sort(world_ext_get_world(world_ext),idx)) && ((i!=0) || ((pawns_get_max_dep(pawn)%2)!=0)))
                    
                    // if ((!world_get_sort(world_ext_get_world(world_ext),idx)) && ((i!=0)))
                    if (i!=0) {
                        if ((!world_get_sort(world_ext_get_world(world_ext),idx)) || _world_ext_test_capture(world_ext, pawns_get_player_index(pawn), idx))
                            sets_add(set, idx);
                    }
                    idx = get_neighbor(idx,d);
                break;
            default:
                break;
        }
        }
    }
}

void _world_ext_get_all_moves_king1st(struct world_ext_t* world_ext, struct sets_t* set, struct pawns_t* pawn)
{
    int r;
    for (int idx = 1; idx < WORLD_SIZE; idx++) {
        r = 0;
        for (int i = 1; i <= idx; i++) {
            if ((idx%i)==0)
                r++;
        }
        if ((r == 2) && (idx != pawns_get_position(pawn))) {
            if (!world_get_sort(world_ext_get_world(world_ext), idx))
            sets_add(set, idx);
        }
    }
}

void world_ext_get_all_moves(struct world_ext_t* world_ext, struct sets_t* set, struct pawns_t* pawn)
{
    switch (pawns_get_type(pawn)) {
        case PAWN_TOWER:
            _world_ext_get_all_moves_tower(world_ext, set, pawn);
            break;
        case PAWN_ELEFUN:
            _world_ext_get_all_moves_elefun(world_ext, set, pawn);
            break;
        case PAWN_KING1ST:
            _world_ext_get_all_moves_king1st(world_ext, set, pawn);
            break;
        default:
            _world_ext_get_all_moves_simple(world_ext, set, pawn);
            break;
    }
}

void world_ext_pawn_moves(struct world_ext_t* world_ext, struct pawns_t* pawn, int new_position)
{
    int position = pawns_get_position(pawn);
    struct world_t* world = world_ext_get_world(world_ext);
    int current_player_index = pawns_get_player_index(pawn);

    if (world_get_sort(world, new_position)) { // Capture
        struct pawns_t* captured_pawn = world_ext_get_pawn_at_position(world_ext, new_position);
        int captured_player_index = pawns_get_player_index(captured_pawn);
        world_set_sort(world, new_position, NO_SORT);
        world_set(world, new_position, NO_COLOR);
        pawns_set_position(captured_pawn, UINT_MAX);
        sets_remove(&world_ext_get_current_sets(world_ext)[captured_player_index], new_position);
        world_ext_add_captured_pawn(world_ext, captured_pawn);
    }

    world_set_sort(world, position, NO_SORT);
    world_set(world, position, NO_COLOR);
    sets_remove(&world_ext_get_current_sets(world_ext)[current_player_index], position);
    pawns_set_position(pawn, new_position);
    world_set_sort(world, new_position, pawns_get_type(pawn));
    world_set(world, new_position, pawn->color);
    sets_add(&world_ext_get_current_sets(world_ext)[current_player_index], new_position);
}

struct pawns_t* word_ext_get_random_pawn(struct world_ext_t* world_ext, int current_player_index)
{
    int rd = rand()%sets_get_nb(&world_ext_get_current_sets(world_ext)[current_player_index]);
    return world_ext_get_pawn_at_position(world_ext, sets_get_place_at(&world_ext_get_current_sets(world_ext)[current_player_index], rd));
}
