#include <stdio.h>
#include <head-unit.h>
#include "card.h"

static struct card_t tenH = { TEN, HEARTS };
static struct card_t sixC = { SIX, CLUBS };
static struct card_t threeD = { THREE, DIAMONDS };
static struct card_t threeH = { THREE, HEARTS };
static struct card_t threeS = { THREE, SPADES };
static struct card_t threeC = { THREE, CLUBS };
static struct card_t twoH = { TWO, HEARTS }; 
static struct card_t fiveD = { FIVE, DIAMONDS };
static struct card_t jackD = { JACK, DIAMONDS };
static struct card_t sevenH = { SEVEN, HEARTS };
static struct card_t twoD = { TWO, DIAMONDS };
static struct card_t sevenD = { SEVEN, DIAMONDS };
static struct card_t tenD = { TEN, DIAMONDS };
static struct card_t aceH = { ACE, HEARTS };
static struct card_t fourC = { FOUR, CLUBS };
static struct card_t nineH = { NINE, HEARTS };
static struct card_t sevenS = { SEVEN, SPADES };
static struct card_t jackC = { JACK, CLUBS };
static struct card_t aceD = { ACE, DIAMONDS };
static struct card_t twoS = { TWO, SPADES };
static struct card_t kingC = { KING, CLUBS };
static struct card_t eightS = { EIGHT, SPADES };

static void test_three_lowest_when_last(void)
{
    struct card_t cards[] = { tenH, sixC, threeD };
    struct card_t lowest = find_lowest_card(cards, 3);
    assert_int_equals(THREE, lowest.rank);
}

static void test_three_lowest_when_middle(void)
{
    struct card_t cards[] = { tenH, threeD, sixC };
    struct card_t lowest =  find_lowest_card(cards, 3);
    assert_int_equals(THREE, lowest.rank);
}

static void test_three_lowest_when_first(void)
{
    struct card_t cards[] = { threeD, tenH, sixC };
    struct card_t lowest =  find_lowest_card(cards, 3);
    assert_int_equals(THREE, lowest.rank);
}

static void test_lowest_one_card(void)
{
    struct card_t cards[] = { tenH };
    struct card_t lowest =  find_lowest_card(cards, 1);
    assert_int_equals(TEN, lowest.rank);
}   

static void test_three_lower_than_two(void)
{
    struct card_t cards[] = { threeD, twoH };
    struct card_t lowest = find_lowest_card(cards, 2);
    assert_int_equals(THREE, lowest.rank);
}

static void test_five_lower_than_two(void)
{
    struct card_t cards[] = { fiveD, twoH };
    struct card_t lowest = find_lowest_card(cards, 2);
    assert_int_equals(FIVE, lowest.rank);
}

static void test_jack_lower_than_seven(void)
{
    struct card_t cards[] = { jackD, sevenH };
    struct card_t lowest = find_lowest_card(cards, 2);
    assert_int_equals(JACK, lowest.rank);
}

static void test_two_special(void)
{
    assert_true(special_card(twoH));
}

static void test_seven_special(void)
{
    assert_true(special_card(sevenD));
}

static void test_ten_special(void)
{
    assert_true(special_card(tenD));
}

static void test_ranks_equal(void)
{
    assert_true(ranks_equal(tenD, tenH));
}

static void test_ranks_not_equal(void)
{
    assert_false(ranks_equal(tenD, aceH));
}

static void test_all_ranks_equal(void)
{
    struct card_t cards[4] = { threeD, threeS, threeH, threeC };
    assert_true(all_ranks_equal(cards, 4));
}

static void test_all_ranks_not_equal(void)
{
    struct card_t cards[4] = { threeD, threeS, threeH, fourC };
    assert_false(all_ranks_equal(cards, 4));
}

static void test_remove_card_from_cards_decrements_size(void)
{
    int num_cards = 5;
    struct card_t cards[num_cards];
    cards[0] = threeD;
    cards[1] = twoD;
    cards[2] = nineH;
    cards[3] = sevenS;
    cards[4] = jackC;
    remove_card_from_cards(cards, &num_cards, nineH);

    assert_int_equals(4, num_cards);
}

static void test_remove_card_from_cards_removes_card(void)
{
    int num_cards = 5;
    struct card_t cards[num_cards];
    cards[0] = threeD;
    cards[1] = twoD;
    cards[2] = nineH;
    cards[3] = sevenS;
    cards[4] = jackC;
    remove_card_from_cards(cards, &num_cards, nineH);

    int i;
    int found = 0;
    for (i = 0; i < num_cards; i++) {
        if (cards_equal(cards[i], nineH)) {
            found = 1;
            break;
        }
    }
    assert_false(found);
}

static void test_add_card_to_cards_increments_size(void)
{
    int num_cards = 5;
    struct card_t cards[num_cards];
    cards[0] = threeD;
    cards[1] = twoD;
    cards[2] = nineH;
    cards[3] = sevenS;
    cards[4] = jackC;
    add_card_to_cards(cards, &num_cards, aceH);

    assert_int_equals(6, num_cards);
}

static void test_add_card_to_cards_adds_card(void)
{
    int num_cards = 5;
    struct card_t cards[num_cards];
    cards[0] = threeD;
    cards[1] = twoD;
    cards[2] = nineH;
    cards[3] = sevenS;
    cards[4] = jackC;
    add_card_to_cards(cards, &num_cards, twoS);

    int i;
    int found = 0;
    for (i = 0 ; i < num_cards ; i++) {
        if (cards_equal(cards[i], twoS)) {
            found = 1;
            break;
        }
    }
    assert_true(found);
}

static void test_sort_cards(void) {
    int num_cards = 5;
    struct card_t cards[num_cards];

    cards[0] = aceD;
    cards[1] = threeH;
    cards[2] = twoS;
    cards[3] = kingC;
    cards[4] = eightS;

    sort_cards(cards, num_cards);

    assert_true(cards_equal(cards[0], threeH) &&
                cards_equal(cards[1], eightS) &&
                cards_equal(cards[2], kingC) &&
                cards_equal(cards[3], aceD) &&
                cards_equal(cards[4], twoS));
}

void register_card_tests()
{
    TEST_MODULE("test_card");
    TEST(test_three_lowest_when_last);
    TEST(test_three_lowest_when_middle);
    TEST(test_three_lowest_when_first);
    TEST(test_lowest_one_card);
    TEST(test_three_lower_than_two);
    TEST(test_five_lower_than_two) ;
    TEST(test_jack_lower_than_seven) ;
    TEST(test_two_special) ;
    TEST(test_seven_special) ;
    TEST(test_ten_special);
    TEST(test_ranks_equal);
    TEST(test_ranks_not_equal);
    TEST(test_all_ranks_equal);
    TEST(test_all_ranks_not_equal);
    TEST(test_remove_card_from_cards_decrements_size);
    TEST(test_remove_card_from_cards_removes_card);
    TEST(test_add_card_to_cards_increments_size);
    TEST(test_add_card_to_cards_adds_card);
    TEST(test_sort_cards);
}

