#include <stdio.h>
#include <head-unit.h>

#include "player.h"
#include "card.h"
#include "config.h"

static struct card_t fourD = { FOUR, DIAMONDS };
//static struct card_t fiveH = { FIVE, HEARTS };
static struct card_t sixH = { SIX, HEARTS };
//static struct card_t sixC = { SIX, CLUBS };
static struct card_t aceS = { ACE, SPADES };
//static struct card_t aceD = { ACE, DIAMONDS };
//static struct card_t twoS = { TWO, SPADES };
//static struct card_t tenC = { TEN, CLUBS };

static void test_is_computer(void)
{
    struct player_t low = make_player("Low", 'l');
    assert_true(low.is_computer);
}

static void doesnt_swap_cards(void)
{
    struct player_t low = make_player("Low", 'l');
    assert_false(ask_swap_cards(low));
}

static void always_chooses_first_face_down(void)
{
    struct player_t low = make_player("Low", 'l');
    assert_int_equals(1, low.ask_face_down_move());
}

static void chooses_low_from_hand_when_empty_pile()
{
    struct player_t low = make_player("Low", 'l');
    deal_to_hand(&low, fourD);
    deal_to_hand(&low, sixH);
    deal_to_hand(&low, aceS);
    sort_cards(low.hand, low.hand_size);
    
    struct player_helper_t helper;
    helper.pile_size = 0;

    int choices[20];
    int nchoices;
    
    ask_move(low, helper, choices, &nchoices);

    assert_int_equals(1, nchoices);
    assert_true(cards_equal(fourD, low.hand[choices[0]]));
}

void register_lowcard_player_tests(void)
{
    TEST_MODULE("test_lowcard_player");
    TEST(test_is_computer);
    TEST(doesnt_swap_cards);
    TEST(always_chooses_first_face_down);
    TEST(chooses_low_from_hand_when_empty_pile);
}


