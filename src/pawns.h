#ifndef __PAWNS_H__
#define __PAWNS_H__

#include "neighbors.h"
#include "sets.h"

/** A struct representing a piece */
struct pawns_t {
	int player_index;
	int max_dep;
	enum color_t color;
	enum sort_t type;
	int position;
	int captured;
};

/** Inits a pawn */
void pawns_init(struct pawns_t* pawn, int player_index, int max_dep, enum color_t color, enum sort_t type, int position);

/** Returns the index of the player that own the pawn */
int pawns_get_player_index(const struct pawns_t* pawn);

/** Returns the maximum depth of a pawn */
int pawns_get_max_dep(const struct pawns_t* pawn);

/** Returns the color of a pawn */
enum color_t pawns_get_color(const struct pawns_t* pawn);

/** Returns the type of a pawn */
enum sort_t pawns_get_type(const struct pawns_t* pawn);

/** Returns the position of a pawn */
int pawns_get_position(const struct pawns_t* pawn);

/** Returns if a pawn is captured */
int pawns_get_captured(const struct pawns_t* pawn);

/** Returns the numbers of pawn's neighbors */
int pawns_get_neighbors_nb(const struct neighbors_t neighbors);

/** Sets if a pawn is captured or not */
void pawns_set_captured(struct pawns_t* pawn, int captured);

/** Set a new position*/
void pawns_set_position(struct pawns_t* pawn, int new_position);

#endif	// __PAWNS_H__
