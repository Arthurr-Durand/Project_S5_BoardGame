#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "test_utilities.h"

void test_game_winning_cond()
{
	puts("\ttest_game_winning_cond :");
	struct world_ext_t world_ext;
	world_ext_init(&world_ext, 3, 0, 1, PAWN_SIMPLE, 0, 0);
	struct players_t* player0 = world_ext_get_player_nb(&world_ext, 0);
	struct players_t* player1 = world_ext_get_player_nb(&world_ext, 1);
	int_test(game_winning_cond(player1, &world_ext_get_initial_sets(&world_ext)[0], players_get_pawn_at_index(player1, 0), 3), 0);
	world_ext_pawn_moves(&world_ext, players_get_pawn_at_index(player0, 0), 1);
	world_ext_pawn_moves(&world_ext, players_get_pawn_at_index(player1, 0), 0);
	int_test(game_winning_cond(player1, &world_ext_get_initial_sets(&world_ext)[0], players_get_pawn_at_index(player1, 0), 3), 1);
}

int main()
{
	puts("test_game.c :");
	test_game_winning_cond();

	return 0;
}
