#include <stdio.h>
#include <string.h>
#include <head-unit.h>

#include "testsuite.h"
#include "game.h"

void test_not_valid_move_no_cards(void)
{
    char names [MAX_NUM_PLAYERS][MAX_NAME_LEN] ;
    struct game_t game ;
    struct player_t *player ;
    int choices[0] ;
    int num_choices = 0 ;

    strcpy(names[0],"James") ;
    game = make_game(1, names, 3) ; 
    game.current_player = 0 ;
    player = &game.players[game.current_player] ;

    game.pile[game.pile_size++] = make_card(NINE, HEARTS) ;
    player->hand[player->hand_size++] = make_card(FOUR, SPADES) ;

    assert_false(valid_move(game, choices, num_choices)) ;
}

void register_game_tests(void)
{
    add_suite("test_game") ;
    add_test(test_not_valid_move_no_cards, "test_not_valid_move_no_cards" ) ;
}

