#include <stdio.h>
#include <string.h>
#include <head-unit.h>

#include "game.h"
#include "player.h"
#include "game_rules.h"

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

// helper tests
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

// basic tests
void test_valid_on_no_cards(void)
{
    setup() ;
    num_choices = 1 ;
    player->hand[player->hand_size++] = make_card(THREE, SPADES) ;
    
    assert_true(valid_move(game, choices, num_choices)) ;
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

// normal order tests
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

void test_valid_three_on_two(void)
{
    test_valid_card_on_card(make_card(THREE, SPADES), make_card(TWO, HEARTS)) ; 
}

// test two on anything
void test_valid_two_on_nine(void)
{
    test_valid_card_on_card(make_card(TWO, DIAMONDS), make_card(NINE, SPADES)) ; 
}

void test_valid_two_on_seven(void)
{
    test_valid_card_on_card(make_card(TWO, HEARTS), make_card(SEVEN, CLUBS)) ;
}

// test seven on anything
void test_valid_seven_on_queen(void)
{
    test_valid_card_on_card(make_card(SEVEN, DIAMONDS), make_card(QUEEN, SPADES)) ; 
}

void test_valid_seven_on_two(void)
{
    test_valid_card_on_card(make_card(SEVEN, HEARTS), make_card(TWO, SPADES)) ;
}

//test ten on anything
void test_valid_ten_on_jack(void)
{
    test_valid_card_on_card(make_card(TEN, CLUBS), make_card(JACK, DIAMONDS)) ;
}

void test_valid_ten_on_two(void)
{
    test_valid_card_on_card(make_card(TEN, CLUBS), make_card(TWO, DIAMONDS)) ;
}

// test laying on invisible
void test_valid_six_on_seven_on_nothing(void)
{
    setup() ;
    num_choices = 1 ;
    game.pile[game.pile_size++] = make_card(SEVEN, HEARTS) ;
    player->hand[player->hand_size++] = make_card(SIX, HEARTS) ;
    choices[0] = 0 ;
    
    assert_true(valid_move(game, choices, num_choices)) ;
}

void test_valid_five_on_seven_on_three(void)
{
    setup() ;
    num_choices = 1 ;
    game.pile[game.pile_size++] = make_card(THREE, DIAMONDS) ;
    game.pile[game.pile_size++] = make_card(SEVEN, HEARTS) ;
    player->hand[player->hand_size++] = make_card(FIVE, HEARTS) ;
    choices[0] = 0 ;
    
    assert_true(valid_move(game, choices, num_choices)) ;
}

void register_game_rules_tests(void)
{
    TEST_MODULE("test_game_rules");
    TEST(test_valid_on_no_cards);
    TEST(test_not_valid_move_no_cards);
    TEST(test_not_valid_more_cards_than_hand);
    TEST(test_not_valid_when_rank_not_equal);
    TEST(test_not_valid_when_not_in_hand);
    TEST(test_valid_four_on_three);
    TEST(test_valid_three_on_three);
    TEST(test_valid_three_on_two);
    TEST(test_not_valid_three_on_four);
    TEST(test_valid_two_on_nine);
    TEST(test_valid_seven_on_queen);
    TEST(test_valid_seven_on_two);
    TEST(test_valid_ten_on_jack);
    TEST(test_valid_ten_on_two);
    TEST(test_valid_two_on_seven);
    TEST(test_valid_six_on_seven_on_nothing);
    TEST(test_valid_five_on_seven_on_three);
}

