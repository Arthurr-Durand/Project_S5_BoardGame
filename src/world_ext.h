#ifndef __WORLD_EXT_H__
#define __WORLD_EXT_H__

#include "players.h"

struct world_ext_t {
	struct world_t* world;
	int nb_players;
	struct players_t players[MAX_PLAYERS];
	struct sets_t initial_sets[MAX_PLAYERS];
	struct sets_t current_sets[MAX_PLAYERS];
	int nb_captured_pawns;
	struct pawns_t* captured_pawns[WORLD_SIZE];
};

void world_ext_init(struct world_ext_t* world_ext, int nb_players, int starting_position, int max_dep, enum sort_t pawn_type, int format, int formae);

struct world_t* world_ext_get_world(struct world_ext_t* world_ext);

int world_ext_get_nb_players(const struct world_ext_t* world_ext);

struct players_t* world_ext_get_player_nb(struct world_ext_t* world_ext, int nb);

struct sets_t* world_ext_get_initial_sets(struct world_ext_t* wold_ext);

struct sets_t* world_ext_get_current_sets(struct world_ext_t* wold_ext);

void world_ext_get_all_moves(struct world_ext_t* world_ext, struct sets_t* set, struct pawns_t* pawn);

int world_ext_pawn_moves(struct world_ext_t* world_ext, struct pawns_t* pawn, int new_position);

int world_ext_get_nb_captured_pawns(const struct world_ext_t* world_ext);

struct pawns_t* world_ext_get_captured_pawn_at_index(const struct world_ext_t* world_ext, int index);

void world_ext_add_captured_pawn(struct world_ext_t* world_ext, struct pawns_t* pawn);

void world_ext_remove_captured_pawn(struct world_ext_t* world_ext, int index);

struct pawns_t* world_ext_get_pawn_at_position(struct world_ext_t* world_ext, int position);

struct pawns_t* word_ext_get_random_pawn(struct world_ext_t* world_ext, int current_player_index);

void world_ext_try_release(struct world_ext_t* world_ext, int chances);

#endif	// __WORLD_EXT_H__
