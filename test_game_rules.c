#include <stdio.h>
#include <string.h>
#include <head-unit.h>

#include "game.h"
#include "player.h"
#include "game_rules.h"

char names [MAX_NUM_PLAYERS][MAX_NAME_LEN];
struct game_t game;
struct player_t *player;
int choices[2];
int num_choices;
struct card_t threeS;
struct card_t threeH;
struct card_t nineH;
struct card_t fourS;
struct card_t sevenD;
struct card_t fourH;
struct card_t twoH;
struct card_t twoD;
struct card_t nineS;
struct card_t sevenC;
struct card_t queenS;
struct card_t sevenH;
struct card_t twoS;
struct card_t tenC;
struct card_t jackD;
struct card_t sixH;
struct card_t threeD;
struct card_t fiveH;

static void setup(void)
{
    threeS = make_card(THREE, SPADES);
    threeH = make_card(THREE, HEARTS);
    nineH = make_card(NINE, HEARTS);
    fourS = make_card(FOUR, SPADES);
    sevenD = make_card(SEVEN, DIAMONDS);
    fourH = make_card(FOUR, HEARTS);
    twoH = make_card(TWO, HEARTS);
    twoD = make_card(TWO, DIAMONDS);
    nineS = make_card(NINE, SPADES);
    sevenC = make_card(SEVEN, CLUBS);
    queenS = make_card(QUEEN, SPADES);
    sevenH = make_card(SEVEN, HEARTS);
    twoS = make_card(TWO, SPADES);
    tenC = make_card(TEN, CLUBS);
    jackD = make_card(JACK, DIAMONDS);
    sixH = make_card(SIX, HEARTS);
    threeD = make_card(THREE, DIAMONDS);
    fiveH = make_card(FIVE, HEARTS);
}

static void setup_game(void)
{
    strcpy(names[0],"James");
    game = make_game(1, names, 3); 
    game.current_player = 0;
    player = &game.players[game.current_player];
}

// helper tests
static void test_valid_card_on_card(struct card_t test_card, struct card_t pile_card)
{
    setup_game();
    num_choices = 1;
    game.pile[game.pile_size++] = pile_card;
    player->hand[player->hand_size++] = test_card;
    choices[0] = 0;

    assert_true(valid_move(game, choices, num_choices));
}

static void test_not_valid_card_on_card(struct card_t test_card, struct card_t pile_card)
{
    setup_game();
    num_choices = 1;
    game.pile[game.pile_size++] = pile_card;
    player->hand[player->hand_size++] = test_card;
    choices[0] = 0;

    assert_false(valid_move(game, choices, num_choices));
}

// basic tests
static void test_valid_on_no_cards(void)
{
    setup_game();
    num_choices = 1;
    player->hand[player->hand_size++] = threeS;
    
    assert_true(valid_move(game, choices, num_choices));
}

static void test_not_valid_move_no_cards(void)
{
    setup_game();
    num_choices = 1;
    game.pile[game.pile_size++] = nineH;
    player->hand[player->hand_size++] = fourS;

    assert_false(valid_move(game, choices, num_choices));
}

static void test_not_valid_more_cards_than_hand(void)
{
    setup_game();
    num_choices = 2;
    game.pile[game.pile_size++] = threeH;
    player->hand[player->hand_size++] = fourS;
    choices[0] = 0;
    choices[1] = 1;

    assert_false(valid_move(game, choices, num_choices));
}

static void test_not_valid_when_rank_not_equal(void) 
{   
    setup_game();
    num_choices = 2;
    player->hand[player->hand_size++] = fourS;
    player->hand[player->hand_size++] = sevenD; 
    choices[0] = 0;
    choices[1] = 1;

    assert_false(valid_move(game, choices, num_choices));
}

static void test_not_valid_when_not_in_hand(void) 
{   
    setup_game();
    num_choices = 2;
    game.pile[game.pile_size++] = threeH;
    player->hand[player->hand_size++] = fourS;
    player->hand[player->hand_size++] = sevenD;
    choices[0] = 0;
    choices[1] = 4;

    assert_false(valid_move(game, choices, num_choices));
}

// normal order tests
static void test_valid_four_on_three(void)
{
    test_valid_card_on_card(fourS, threeH); 
}

static void test_valid_three_on_three(void)
{
    test_valid_card_on_card(threeS, threeH); 
}

static void test_not_valid_three_on_four(void)
{
    test_not_valid_card_on_card(threeS, fourH); 
}

static void test_valid_three_on_two(void)
{
    test_valid_card_on_card(threeS, twoH); 
}

// test two on anything
static void test_valid_two_on_nine(void)
{
    test_valid_card_on_card(twoD, nineS); 
}

static void test_valid_two_on_seven(void)
{
    test_valid_card_on_card(twoH, sevenC);
}

// test seven on anything
static void test_valid_seven_on_queen(void)
{
    test_valid_card_on_card(sevenD, queenS); 
}

static void test_valid_seven_on_two(void)
{
    test_valid_card_on_card(sevenH, twoS);
}

//test ten on anything
static void test_valid_ten_on_jack(void)
{
    test_valid_card_on_card(tenC, jackD);
}

static void test_valid_ten_on_two(void)
{
    test_valid_card_on_card(tenC, twoD);
}

// test laying on invisible
static void test_valid_six_on_seven_on_nothing(void)
{
    setup_game();
    num_choices = 1;
    game.pile[game.pile_size++] = sevenH;
    player->hand[player->hand_size++] = sixH;
    choices[0] = 0;
    
    assert_true(valid_move(game, choices, num_choices));
}

static void test_valid_five_on_seven_on_three(void)
{
    setup_game();
    num_choices = 1;
    game.pile[game.pile_size++] = threeD;
    game.pile[game.pile_size++] = sevenH;
    player->hand[player->hand_size++] = fiveH;
    choices[0] = 0;
    
    assert_true(valid_move(game, choices, num_choices));
}

void register_game_rules_tests(void)
{
    TEST_MODULE("test_game_rules");
    SETUP(setup);
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

