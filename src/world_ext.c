#include <stdlib.h>
#include <stdio.h>

#include "world_ext.h"

void world_ext_init(struct world_ext_t* world_ext, int nb_players, int starting_position, int max_dep, enum sort_t pawn_type, int format, int formae)
{
    world_ext->world = world_init();
    world_ext->nb_players = nb_players;
    players_init(world_ext->players, nb_players);

    sets_list_init(world_ext->initial_sets, nb_players);
    if (starting_position)
        sets_set_initial_sets_battleground(nb_players, world_ext->initial_sets);
    else
        sets_set_initial_sets(nb_players, world_ext->initial_sets);
    players_set_initial_pawns(world_ext->world, world_ext->players, nb_players, world_ext->initial_sets, max_dep, pawn_type, format, formae);

    sets_list_init(world_ext->current_sets, nb_players);
    for (int p = 0; p < world_ext_get_nb_players(world_ext); p++) {
        for (int i = 0; i < sets_get_nb(world_ext->initial_sets); i++)
            sets_add(&world_ext->current_sets[p], sets_get_place_at(world_ext->initial_sets, i));
    }
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

int _world_ext_test_capture(struct world_ext_t* world_ext, struct players_t* current_player, int new_position)
{
    int current_player_index = players_get_index(current_player);
    if (sets_is_in_set(&world_ext_get_current_sets(world_ext)[current_player_index], new_position)) // 0 si le pion appartient au joueur
        return 0;
    for (int i = 0; i < world_ext_get_nb_players(world_ext); i++) { // 0 si le pion est dans une position de départ
        if ((i != current_player_index) && sets_is_in_set(&world_ext_get_initial_sets(world_ext)[i], new_position))
            return 0;
    }
    return 1;
}

void _world_ext_get_all_moves_simple(struct world_ext_t* world_ext, struct sets_t* set, struct players_t* current_player, struct pawns_t* pawn)
{
    int idx, d;
    for (int k = 0; k < (pawns_get_neighbors_nb(get_neighbors(pawns_get_position(pawn)))); ++k) {
        idx = get_neighbors(pawns_get_position(pawn)).n[k].i;
        d = get_neighbors(pawns_get_position(pawn)).n[k].d;
        for (int i = 0; i < pawns_get_max_dep(pawn); i++) {
            if (!world_get_sort(world_ext_get_world(world_ext), idx) || _world_ext_test_capture(world_ext, current_player, idx))
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
                    if (world_get_sort(world_ext_get_world(world_ext), idx))
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
                    if ((!world_get_sort(world_ext_get_world(world_ext),idx)) && ((i!=0)))
                        sets_add(set, idx);
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

void world_ext_get_all_moves(struct world_ext_t* world_ext, struct sets_t* set, struct players_t* current_player, struct pawns_t* pawn)
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
            _world_ext_get_all_moves_simple(world_ext, set, current_player, pawn);
            break;
    }
}

void world_ext_pawn_moves(struct world_ext_t* world_ext, struct pawns_t* pawn, struct players_t* player, int new_position)
{
    int position = pawns_get_position(pawn);
    struct world_t* world = world_ext_get_world(world_ext);

    /* if (world_get_sort(world, new_position)) { // Capture

    } */

    world_set_sort(world, position, NO_SORT);
    world_set(world, position, NO_COLOR);
    sets_remove(&world_ext_get_current_sets(world_ext)[players_get_index(player)], position);
    pawns_set_position(pawn, new_position);
    world_set_sort(world, new_position, pawns_get_type(pawn));
    world_set(world, new_position, pawn->color);
    sets_add(&world_ext_get_current_sets(world_ext)[players_get_index(player)], new_position);
}
