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

static void test_valid_card_on_card(struct card_t test_card, struct card_t pile_card)
{
    setup() ;
    num_choices = 1 ;
    game.pile[game.pile_size++] = pile_card;
    player->hand[player->hand_size++] = test_card ;
    choices[0] = 0 ;

    assert_true(valid_move(game, choices, num_choices)) ;
}

static void test_not_valid_card_on_card(struct card_t test_card, struct card_t pile_card)
{
    setup() ;
    num_choices = 1 ;
    game.pile[game.pile_size++] = pile_card;
    player->hand[player->hand_size++] = test_card ;
    choices[0] = 0 ;

    assert_false(valid_move(game, choices, num_choices)) ;
}

void test_not_valid_move_no_cards(void)
{
    setup() ;
    num_choices = 1 ;
    game.pile[game.pile_size++] = make_card(NINE, HEARTS) ;
    player->hand[player->hand_size++] = make_card(FOUR, SPADES) ;

    assert_false(valid_move(game, choices, num_choices)) ;
}

void test_not_valid_more_cards_than_hand(void)
{
    setup() ;
    num_choices = 2 ;
    game.pile[game.pile_size++] = make_card(THREE, HEARTS) ;
    player->hand[player->hand_size++] = make_card(FOUR, SPADES) ;
    choices[0] = 0 ;
    choices[1] = 1 ;

    assert_false(valid_move(game, choices, num_choices)) ;
}

void test_not_valid_when_rank_not_equal(void) 
{   
    setup() ;
    num_choices = 2 ;
    player->hand[player->hand_size++] = make_card(FOUR, SPADES) ;
    player->hand[player->hand_size++] = make_card(SEVEN, DIAMONDS) ;
    choices[0] = 0 ;
    choices[1] = 1 ;

    assert_false(valid_move(game, choices, num_choices)) ;
}

void test_not_valid_when_not_in_hand(void) 
{   
    setup() ;
    num_choices = 2 ;
    game.pile[game.pile_size++] = make_card(THREE, HEARTS) ;
    player->hand[player->hand_size++] = make_card(FOUR, SPADES) ;
    player->hand[player->hand_size++] = make_card(SEVEN, DIAMONDS) ;
    choices[0] = 0 ;
    choices[1] = 4 ;

    assert_false(valid_move(game, choices, num_choices)) ;
}

void test_valid_four_on_three(void)
{
    test_valid_card_on_card(make_card(FOUR, SPADES), make_card(THREE, HEARTS)) ; 
}

void test_valid_three_on_three(void)
{
    test_valid_card_on_card(make_card(THREE, SPADES), make_card(THREE, HEARTS)) ; 
}

void test_not_valid_three_on_four(void)
{
    test_not_valid_card_on_card(make_card(THREE, SPADES), make_card(FOUR, HEARTS)) ; 
}

void test_valid_two_on_nine(void)
{
    test_valid_card_on_card(make_card(TWO, DIAMONDS), make_card(NINE, SPADES)) ; 
}

void test_valid_seven_on_queen(void)
{
    test_valid_card_on_card(make_card(SEVEN, DIAMONDS), make_card(QUEEN, SPADES)) ; 
}

void register_game_tests(void)
{
    add_suite("test_game") ;
    add_test(test_not_valid_move_no_cards, "test_not_valid_move_no_cards" ) ;
    add_test(test_not_valid_more_cards_than_hand, "test_not_valid_more_cards_than_hand" ) ;
    add_test(test_not_valid_when_rank_not_equal, "test_not_valid_when_rank_not_equal" ) ;
    add_test(test_not_valid_when_not_in_hand, "test_not_valid_when_not_in_hand" ) ;
    add_test(test_valid_four_on_three, "test_valid_four_on_three" ) ;
    add_test(test_valid_three_on_three, "test_valid_three_on_three" ) ;
    add_test(test_not_valid_three_on_four, "test_not_valid_three_on_four" ) ;
    add_test(test_valid_two_on_nine, "test_valid_two_on_nine" ) ;
    add_test(test_valid_seven_on_queen, "test_valid_seven_on_queen" ) ;
}

