#include <stdio.h>
#include <string.h>
#include <head-unit.h>

#include "testsuite.h"
#include "game.h"

char names [MAX_NUM_PLAYERS][MAX_NAME_LEN] ;
struct game_t game ;
struct player_t *player ;
int choices[2] ;
int num_choices ;

static void setup(void)
{
    strcpy(names[0],"James") ;
    game = make_game(1, names, 3) ; 
    game.current_player = 0 ;
    player = &game.players[game.current_player] ;
}

void test_ten_on_nothing_burns(void)
{
    setup() ;
    player->hand[0] = make_card(TEN, SPADES) ;
    player->hand_size = 1 ;
    choices[0] = 0 ;
    num_choices = 1 ;

    make_move(&game, choices, num_choices) ;

    assert_true(game.pile_size == 0) ;
}

void test_ten_on_two_cards_burns(void)
{
    setup() ;
    player->hand[0] = make_card(TEN, HEARTS) ;
    player->hand_size = 1 ;
    choices[0] = 0 ;
    num_choices = 1 ;

    game.pile[0] = make_card(THREE, DIAMONDS) ;
    game.pile[1] = make_card(NINE, DIAMONDS) ;
    game.pile_size = 2 ;

    make_move(&game, choices, num_choices) ;

    assert_true(game.pile_size == 0) ;
}

void test_four_of_a_kind_burns(void)
{
    setup() ;
    player->hand[0] = make_card(FOUR, DIAMONDS) ;
    player->hand[1] = make_card(FOUR, HEARTS) ;
    player->hand[2] = make_card(FOUR, SPADES) ;
    player->hand[3] = make_card(FOUR, CLUBS) ;
    player->hand_size = 4 ;

    choices[0] = 0 ;
    choices[1] = 1 ;
    choices[2] = 2 ;
    choices[3] = 3 ;
    num_choices = 4 ;

    game.pile[0] = make_card(TWO, DIAMONDS) ;
    game.pile[1] = make_card(THREE, DIAMONDS) ;
    game.pile_size = 2 ;

    make_move(&game, choices, num_choices) ;

    assert_true(game.pile_size == 0) ; 
}

void test_three_same_on_one_same_burns(void)
{
    setup() ;
    player->hand[0] = make_card(FOUR, DIAMONDS) ;
    player->hand[1] = make_card(FOUR, HEARTS) ;
    player->hand[2] = make_card(FOUR, SPADES) ;
    player->hand_size = 4 ;

    choices[0] = 0 ;
    choices[1] = 1 ;
    choices[2] = 2 ;
    num_choices = 3 ;

    game.pile[0] = make_card(TWO, DIAMONDS) ;
    game.pile[1] = make_card(FOUR, CLUBS) ;
    game.pile_size = 2 ;

    make_move(&game, choices, num_choices) ;

    assert_true(game.pile_size == 0) ; 
}

void test_two_same_on_two_same_burns(void)
{
    setup() ;
    player->hand[0] = make_card(FOUR, DIAMONDS) ;
    player->hand[1] = make_card(FOUR, HEARTS) ;
    player->hand_size = 4 ;

    choices[0] = 0 ;
    choices[1] = 1 ;
    num_choices = 2 ;

    game.pile[0] = make_card(TWO, DIAMONDS) ;
    game.pile[1] = make_card(FOUR, CLUBS) ;
    game.pile[2] = make_card(FOUR, SPADES) ;
    game.pile_size = 3 ;

    make_move(&game, choices, num_choices) ;

    assert_true(game.pile_size == 0) ; 
}

void test_one_same_on_three_same_burns(void)
{
    setup() ;
    player->hand[0] = make_card(FOUR, DIAMONDS) ;
    player->hand_size = 4 ;

    choices[0] = 0 ;
    num_choices = 1 ;

    game.pile[0] = make_card(TWO, DIAMONDS) ;
    game.pile[1] = make_card(FOUR, CLUBS) ;
    game.pile[2] = make_card(FOUR, SPADES) ;
    game.pile[3] = make_card(FOUR, HEARTS) ;
    game.pile_size = 4 ;

    make_move(&game, choices, num_choices) ;

    assert_true(game.pile_size == 0) ; 
}

void register_game_tests(void)
{
    add_suite("test_game") ;
    add_test(test_ten_on_nothing_burns, "test_ten_on_nothing_burns" ) ;
    add_test(test_ten_on_two_cards_burns, "test_ten_on_two_cards_burns" ) ;
    add_test(test_four_of_a_kind_burns, "test_four_of_a_kind_burns" ) ;
    add_test(test_three_same_on_one_same_burns, "test_three_same_on_one_same_burns" ) ;
    add_test(test_two_same_on_two_same_burns, "test_two_same_on_two_same_burns" ) ;
    add_test(test_one_same_on_three_same_burns, "test_one_same_on_three_same_burns" ) ;
}

