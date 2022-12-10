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
}

struct world_t* world_ext_get_world(struct world_ext_t* world_ext)
{
    return world_ext->world;
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

void _world_ext_get_all_moves_simple(struct world_ext_t* world_ext, struct sets_t* set, struct pawns_t* pawn)
{
    int idx, d;
    for (int k = 0; k < (pawns_get_neighbors_nb(get_neighbors(pawns_get_position(pawn)))); ++k) {
        idx = get_neighbors(pawns_get_position(pawn)).n[k].i;
        d = get_neighbors(pawns_get_position(pawn)).n[k].d;
        for (int i = 0; i < pawns_get_max_dep(pawn); i++) {
            if (!world_get_sort(world_ext_get_world(world_ext), idx))
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
        switch (d) {
            case EAST:
            case WEST:
            case SOUTH:
            case NORTH:
                for (int i = 0; i < pawns_get_max_dep(pawn); i++) {
                    if (!world_get_sort(world_ext_get_world(world_ext), idx))
                        sets_add(set, idx);
                    idx = get_neighbor(idx,d);
                }
                break;
            default:
                for (int i = 0; i < pawns_get_max_dep(pawn)-1; i++) {
                    if (!world_get_sort(world_ext_get_world(world_ext), idx))
                        sets_add(set, idx);
                    idx = get_neighbor(idx,d);
                }
                break;
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
