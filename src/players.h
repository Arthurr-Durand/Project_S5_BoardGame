#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include "geometry.h"
#include "pawn.h"
#include "sets.h"

struct players_t {
    int index;
    struct pawns_t pawns[WORLD_SIZE+1];
    struct sets_t initial_set;
};

#endif // __PLAYERS_H__