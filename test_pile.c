#include <stdio.h>
#include <string.h>
#include <head-unit.h>
#include "pile.h"

struct card_t tenD;
struct card_t jackD;
struct card_t threeD;
struct card_t nineD;
struct card_t nineS;
struct card_t nineH;
struct card_t nineC;
struct card_t eightD;

static void setup(void)
{
    tenD = make_card(TEN, DIAMONDS);
    jackD = make_card(JACK, DIAMONDS);
    threeD = make_card(THREE, DIAMONDS);
    nineD = make_card(NINE, DIAMONDS);
    nineS = make_card(NINE, SPADES);
    nineH = make_card(NINE, HEARTS);
    nineC = make_card(NINE, CLUBS);
    eightD = make_card(EIGHT, DIAMONDS);
}

static void test_burn_card_on_pile(void)
{
    int pile_size = 1;
    struct card_t pile[pile_size];
    pile[0] = tenD;
    int result = burn_cards_laid(pile, pile_size);

    assert_true(result);

}

static void test_not_burn_card_on_pile(void)
{
    int pile_size = 1;
    struct card_t pile[pile_size];
    pile[0] = jackD;
    int result = burn_cards_laid(pile, pile_size);

    assert_false(result);
}

static void test_burn_four_of_a_kind(void)
{
    int pile_size = 6;
    struct card_t pile[pile_size];
    pile[0] = jackD;
    pile[1] = threeD;
    pile[2] = nineD;
    pile[3] = nineS;
    pile[4] = nineH;
    pile[5] = nineC;
    int result = burn_cards_laid(pile, pile_size);

    assert_true(result);
}

static void test_not_burn_three_of_a_kind(void)
{
    int pile_size = 5;
    struct card_t pile[pile_size];
    pile[0] = jackD;
    pile[1] = threeD;
    pile[2] = nineD;
    pile[3] = nineS;
    pile[4] = nineH;
    int result = burn_cards_laid(pile, pile_size);

    assert_false(result);
}

static void test_not_burn_no_cards(void)
{
    int pile_size = 0;
    struct card_t pile[pile_size];
    int result = burn_cards_laid(pile, pile_size);

    assert_false(result);
}

static void test_missgo_card_on_pile(void)
{
    int pile_size = 1;
    struct card_t pile[pile_size];
    pile[0] = eightD;
    int result = miss_a_go_card_laid(pile, pile_size);

    assert_true(result);
}

static void test_not_missgo_card_on_pile(void)
{
    int pile_size = 1;
    struct card_t pile[pile_size];
    pile[0] = jackD;
    int result = miss_a_go_card_laid(pile, pile_size);

    assert_false(result);
}


void register_pile_tests(void)
{
    TEST_MODULE("test_pile");
    SETUP(setup);
    TEST(test_burn_card_on_pile);
    TEST(test_not_burn_card_on_pile);
    TEST(test_burn_four_of_a_kind);
    TEST(test_not_burn_three_of_a_kind);
    TEST(test_not_burn_no_cards);
    TEST(test_missgo_card_on_pile);
    TEST(test_not_missgo_card_on_pile);
}
