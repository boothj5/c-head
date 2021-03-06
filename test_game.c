#include <stdio.h>
#include <string.h>
#include <head-unit.h>

#include "game.h"

static char names[MAX_NUM_PLAYERS][MAX_NAME_LEN];
static char types[MAX_NUM_PLAYERS];
static struct game_t game;
static struct player_t *player;
static int choices[4];
static int num_choices;

static void setup_game(void)
{
    strcpy(names[0],"p1");
    types[0] = 'h';
    game = make_game(2, names, types, 3); 
    game.current_player = 0;
    player = &game.players[game.current_player];
}

static void test_ten_on_nothing_burns(void)
{
    setup_game();
    player->hand[0] = make_card(TEN, SPADES);
    player->hand_size = 1;
    choices[0] = 0;
    num_choices = 1;

    make_move(&game, choices, num_choices);

    assert_true(game.pile_size == 0);
}

static void test_ten_on_two_cards_burns(void)
{
    setup_game();
    player->hand[0] = make_card(TEN, HEARTS);
    player->hand_size = 1;
    choices[0] = 0;
    num_choices = 1;

    game.pile[0] = make_card(THREE, DIAMONDS);
    game.pile[1] = make_card(NINE, DIAMONDS);
    game.pile_size = 2;

    make_move(&game, choices, num_choices);

    assert_true(game.pile_size == 0);
}

static void test_four_of_a_kind_burns(void)
{
    setup_game();
    player->hand[0] = make_card(FOUR, DIAMONDS);
    player->hand[1] = make_card(FOUR, HEARTS);
    player->hand[2] = make_card(FOUR, SPADES);
    player->hand[3] = make_card(FOUR, CLUBS);
    player->hand_size = 4;

    choices[0] = 0;
    choices[1] = 1;
    choices[2] = 2;
    choices[3] = 3;
    num_choices = 4;

    game.pile[0] = make_card(TWO, DIAMONDS);
    game.pile[1] = make_card(THREE, DIAMONDS);
    game.pile_size = 2;

    make_move(&game, choices, num_choices);

    assert_true(game.pile_size == 0); 
}

static void test_three_same_on_one_same_burns(void)
{
    setup_game();
    player->hand[0] = make_card(FOUR, DIAMONDS);
    player->hand[1] = make_card(FOUR, HEARTS);
    player->hand[2] = make_card(FOUR, SPADES);
    player->hand_size = 4;

    choices[0] = 0;
    choices[1] = 1;
    choices[2] = 2;
    num_choices = 3;

    game.pile[0] = make_card(TWO, DIAMONDS);
    game.pile[1] = make_card(FOUR, CLUBS);
    game.pile_size = 2;

    make_move(&game, choices, num_choices);

    assert_true(game.pile_size == 0); 
}

static void test_two_same_on_two_same_burns(void)
{
    setup_game();
    player->hand[0] = make_card(FOUR, DIAMONDS);
    player->hand[1] = make_card(FOUR, HEARTS);
    player->hand_size = 4;

    choices[0] = 0;
    choices[1] = 1;
    num_choices = 2;

    game.pile[0] = make_card(TWO, DIAMONDS);
    game.pile[1] = make_card(FOUR, CLUBS);
    game.pile[2] = make_card(FOUR, SPADES);
    game.pile_size = 3;

    make_move(&game, choices, num_choices);

    assert_true(game.pile_size == 0); 
}

static void test_one_same_on_three_same_burns(void)
{
    setup_game();
    player->hand[0] = make_card(FOUR, DIAMONDS);
    player->hand_size = 4;

    choices[0] = 0;
    num_choices = 1;

    game.pile[0] = make_card(TWO, DIAMONDS);
    game.pile[1] = make_card(FOUR, CLUBS);
    game.pile[2] = make_card(FOUR, SPADES);
    game.pile[3] = make_card(FOUR, HEARTS);
    game.pile_size = 4;

    make_move(&game, choices, num_choices);

    assert_true(game.pile_size == 0); 
}

static void test_player_on_last_cards(void) 
{
    setup_game();
    player->hand_size = 0;
    player->face_up_size = 0;
    player->face_down_size = 1;

    assert_true(player_on_last_cards(&game));
}

static void test_not_player_on_last_cards_when_face_up(void)
{
    setup_game();
    player->hand_size = 0;
    player->face_up_size = 1;
    player->face_down_size = 1;

    assert_false(player_on_last_cards(&game));
}

static void test_not_player_on_last_cards_when_hand(void) 
{
    setup_game();
    player->hand_size = 1;
    player->face_up_size = 1;
    player->face_down_size = 1;

    assert_false(player_on_last_cards(&game));
}

void register_game_tests(void)
{
    TEST_MODULE("test_game");
    TEST(test_ten_on_nothing_burns);
    TEST(test_ten_on_two_cards_burns);
    TEST(test_four_of_a_kind_burns);
    TEST(test_three_same_on_one_same_burns);
    TEST(test_two_same_on_two_same_burns);
    TEST(test_one_same_on_three_same_burns);
    TEST(test_player_on_last_cards);
    TEST(test_not_player_on_last_cards_when_face_up);
    TEST(test_not_player_on_last_cards_when_hand);
}

