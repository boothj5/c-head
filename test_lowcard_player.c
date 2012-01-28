#include <stdio.h>
#include <head-unit.h>

#include "player.h"
#include "card.h"

static struct card_t fourD = { FOUR, DIAMONDS };
static struct card_t fiveH = { FIVE, HEARTS };
static struct card_t sixH = { SIX, HEARTS };
static struct card_t sixC = { SIX, CLUBS };
static struct card_t aceS = { ACE, SPADES };
static struct card_t aceD = { ACE, DIAMONDS };
static struct card_t twoS = { TWO, SPADES };
static struct card_t tenC = { TEN, CLUBS };

static void test_is_computer(void)
{
    struct player_t low = make_player("Low", 'l');
    assert_true(low.is_computer);
}

static void doesnt_swap_cards(void)
{
    struct player_t low = make_player("Low", 'l');
    assert_false(ask_swap_cards(&low));
}

static void always_chooses_first_face_down(void)
{
    struct player_t low = make_player("Low", 'l');
    assert_int_equals(1, low.ask_face_down_move());
}

static void chooses_low_from_hand_when_empty_pile()
{
    int choices[20];
    int nchoices;
    struct player_t low = make_player("Low", 'l');
    deal_to_hand(&low, fourD);
    deal_to_hand(&low, sixH);
    deal_to_hand(&low, aceS);
    sort_cards(low.hand, low.hand_size);
    
    struct card_t pile[0];
    struct player_helper_t helper = make_helper(pile, 0);
    
    ask_move(&low, &helper, choices, &nchoices);

    assert_int_equals(1, nchoices);
    assert_true(cards_equal(&fourD, &low.hand[choices[0]]));
}

static void chooses_low_from_face_up_when_empty_pile()
{
    int choices[20];
    int nchoices;
    struct player_t low = make_player("Low", 'l');
    deal_to_face_up(&low, sixH);
    deal_to_face_up(&low, fourD);
    deal_to_face_up(&low, aceS);

    struct card_t pile[0];
    struct player_helper_t helper = make_helper(pile, 0);
    
    ask_move(&low, &helper, choices, &nchoices);

    assert_int_equals(1, nchoices);
    assert_true(cards_equal(&fourD, &low.face_up[choices[0]]));
}

static void chooses_lowest_from_hand_on_pile()
{
    int choices[20];
    int nchoices;
    struct player_t low = make_player("Low", 'l');
    deal_to_hand(&low, tenC);
    deal_to_hand(&low, fourD);
    deal_to_hand(&low, sixH);
    deal_to_hand(&low, twoS);
    deal_to_hand(&low, aceS);
    sort_cards(low.hand, low.hand_size);

    struct card_t pile[1];
    pile[0] = aceD;
    struct player_helper_t helper = make_helper(pile, 1);
    
    ask_move(&low, &helper, choices, &nchoices);

    assert_int_equals(1, nchoices);
    assert_true(cards_equal(&aceS, &low.hand[choices[0]]));
}

static void chooses_lowest_from_face_up_on_pile()
{
    int choices[20];
    int nchoices;
    struct player_t low = make_player("Low", 'l');
    deal_to_face_up(&low, tenC);
    deal_to_face_up(&low, fourD);
    deal_to_face_up(&low, sixH);
    deal_to_face_up(&low, twoS);
    deal_to_face_up(&low, aceS);

    struct card_t pile[1];
    pile[0] = sixC;
    struct player_helper_t helper = make_helper(pile, 1);
    
    ask_move(&low, &helper, choices, &nchoices);

    assert_int_equals(1, nchoices);
    assert_true(cards_equal(&sixH, &low.face_up[choices[0]]));
}

static void chooses_two_cards_from_hand_when_can()
{
    int choices[20];
    int nchoices;
    struct player_t low = make_player("Low", 'l');
    deal_to_hand(&low, tenC);
    deal_to_hand(&low, fourD);
    deal_to_hand(&low, sixH);
    deal_to_hand(&low, twoS);
    deal_to_hand(&low, sixC);
    deal_to_hand(&low, aceS);
    sort_cards(low.hand, low.hand_size);
    
    struct card_t pile[1];
    pile[0] = fiveH;
    struct player_helper_t helper = make_helper(pile, 1);
    
    ask_move(&low, &helper, choices, &nchoices);
    
    assert_int_equals(2, nchoices);

    struct card_t first = low.hand[choices[0]];
    struct card_t second = low.hand[choices[1]];

    assert_int_equals(SIX, first.rank);
    assert_int_equals(SIX, second.rank);
    assert_false(cards_equal(&first, &second));
}

static void chooses_two_cards_from_face_up_when_can()
{
    int choices[20];
    int nchoices;
    struct player_t low = make_player("Low", 'l');
    deal_to_face_up(&low, tenC);
    deal_to_face_up(&low, fourD);
    deal_to_face_up(&low, sixH);
    deal_to_face_up(&low, twoS);
    deal_to_face_up(&low, sixC);
    deal_to_face_up(&low, aceS);
    
    struct card_t pile[1];
    pile[0] = fiveH;
    struct player_helper_t helper = make_helper(pile, 1);
    
    ask_move(&low, &helper, choices, &nchoices);
    
    assert_int_equals(2, nchoices);

    struct card_t first = low.face_up[choices[0]];
    struct card_t second = low.face_up[choices[1]];

    assert_int_equals(SIX, first.rank);
    assert_int_equals(SIX, second.rank);
    assert_false(cards_equal(&first, &second));
}

void register_lowcard_player_tests(void)
{
    TEST_MODULE("test_lowcard_player");
    TEST(test_is_computer);
    TEST(doesnt_swap_cards);
    TEST(always_chooses_first_face_down);
    TEST(chooses_low_from_hand_when_empty_pile);
    TEST(chooses_low_from_face_up_when_empty_pile);
    TEST(chooses_lowest_from_hand_on_pile);
    TEST(chooses_lowest_from_face_up_on_pile);
    TEST(chooses_two_cards_from_hand_when_can);
    TEST(chooses_two_cards_from_face_up_when_can);
}


