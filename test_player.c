#include <stdio.h>
#include <head-unit.h>

#include "player.h"
#include "card.h"

static struct card_t tenD;
static struct card_t sevenH;
static struct card_t fourS;
static struct card_t fiveH;
static struct card_t nineS;
static struct card_t jackD;
static struct card_t queenH;
static struct card_t kingS;
static struct card_t aceD;
static struct card_t aceH;
static struct card_t aceS;
static struct card_t tenD;
static struct card_t threeD;
static struct card_t nineD;
static struct card_t aceC;
static struct card_t twoD;
static struct card_t fiveD;
static struct card_t sixH;
static struct card_t eightD;
static struct card_t nineC;

static void setup(void)
{
    tenD = make_card(TEN, DIAMONDS);
    sevenH = make_card(SEVEN, HEARTS);
    fourS = make_card(FOUR, SPADES);
    fiveH = make_card(FIVE, HEARTS);
    nineS = make_card(NINE, SPADES);
    jackD = make_card(JACK, DIAMONDS);
    queenH = make_card(QUEEN, HEARTS);
    kingS = make_card(KING, SPADES);
    aceD = make_card(ACE, DIAMONDS);
    aceH = make_card(ACE, HEARTS);
    aceS = make_card(ACE, SPADES);
    tenD = make_card(TEN, DIAMONDS);
    threeD = make_card(THREE, DIAMONDS);
    nineD = make_card(NINE, DIAMONDS);
    aceC = make_card(ACE, CLUBS);
    twoD = make_card(TWO, DIAMONDS);
    fiveD = make_card(FIVE, DIAMONDS);
    sixH = make_card(SIX, HEARTS);
    eightD = make_card(EIGHT, DIAMONDS);
    nineC = make_card(NINE, CLUBS);
}

static void test_lowest_card_by_player(void)
{
    struct player_t steve = make_player("Steve", 'h');
    struct player_t james = make_player("James", 'h');
    struct player_t dave = make_player("Dave", 'h');
    struct player_t mike = make_player("Mike", 'h');
    struct player_t players[4];
    struct card_t lowest_cards[4];

    deal_to_hand(&steve, tenD);
    deal_to_hand(&steve, sevenH);
    deal_to_hand(&steve, fourS);

    deal_to_hand(&james, fourS);
    deal_to_hand(&james, fiveH);
    deal_to_hand(&james, nineS);   

    deal_to_hand(&dave, jackD);
    deal_to_hand(&dave, queenH);
    deal_to_hand(&dave, kingS);   

    deal_to_hand(&mike, aceD);
    deal_to_hand(&mike, aceH);
    deal_to_hand(&mike, aceS);   

    players[0] = steve;
    players[1] = james;
    players[2] = dave;
    players[3] = mike;

    find_lowest_card_by_player(players, 4, lowest_cards);

    assert_true(cards_equal(&lowest_cards[0], &fourS));
    assert_true(cards_equal(&lowest_cards[1], &fourS));
    assert_true(cards_equal(&lowest_cards[2], &jackD));
    assert_int_equals(ACE, lowest_cards[3].rank);
}

static void swap_first_two_cards(void)
{
    struct player_t james = make_player("James", 'h');
    struct swap_choice_t choice;
    deal_to_hand(&james, fourS);
    deal_to_hand(&james, tenD);
    deal_to_hand(&james, sevenH);
    sort_cards(james.hand, james.hand_size);
    
    deal_to_face_up(&james, threeD);
    deal_to_face_up(&james, nineD);
    deal_to_face_up(&james, aceC);

    choice.hand_choice = 1;
    choice.faceup_choice = 1;
    swap(&james, &choice);
    
    assert_true(cards_equal(&james.hand[0], &threeD));
    assert_true(cards_equal(&james.face_up[0], &fourS));
}

static void swap_last_two_cards(void)
{
    struct player_t james = make_player("James", 'h');
    struct swap_choice_t choice;
    deal_to_hand(&james, fourS);
    deal_to_hand(&james, aceD);
    deal_to_hand(&james, sevenH);
    sort_cards(james.hand, james.hand_size);
    
    deal_to_face_up(&james, nineD);
    deal_to_face_up(&james, aceC);
    deal_to_face_up(&james, twoD);

    choice.hand_choice = 3;
    choice.faceup_choice = 3;
    swap(&james, &choice);
    
    assert_true(cards_equal(&james.hand[2], &twoD));
    assert_true(cards_equal(&james.face_up[2], &sevenH));
}

static void swap_first_and_last(void)
{
    struct player_t james = make_player("James", 'h');
    struct swap_choice_t choice;
    deal_to_hand(&james, fourS);
    deal_to_hand(&james, fiveD);
    deal_to_hand(&james, sixH);
    sort_cards(james.hand, james.hand_size);
    
    deal_to_face_up(&james, eightD);
    deal_to_face_up(&james, nineC);
    deal_to_face_up(&james, jackD);

    choice.hand_choice = 1;
    choice.faceup_choice = 3;
    swap(&james, &choice);
    
    assert_true(cards_equal(&james.hand[2], &jackD));
    assert_true(cards_equal(&james.face_up[2], &fourS));
}

static void swap_middle_cards(void)
{
    struct player_t james = make_player("James", 'h');
    struct swap_choice_t choice;
    deal_to_hand(&james, fourS);
    deal_to_hand(&james, fiveD);
    deal_to_hand(&james, sixH);
    sort_cards(james.hand, james.hand_size);
    
    deal_to_face_up(&james, eightD);
    deal_to_face_up(&james, nineC);
    deal_to_face_up(&james, jackD);

    choice.hand_choice = 2;
    choice.faceup_choice = 2;
    swap(&james, &choice);
    
    assert_true(cards_equal(&james.hand[2], &nineC));
    assert_true(cards_equal(&james.face_up[1], &fiveD));
}

static void test_has_cards_when_hand_does(void)
{
    struct player_t james = make_player("James", 'h');    
    deal_to_hand(&james, tenD);
    deal_to_hand(&james, sevenH);
    deal_to_hand(&james, fourS);   

    assert_true(has_cards(&james));
} 

static void test_has_cards_when_face_up_does(void)
{
    struct player_t james = make_player("James", 'h');    
    deal_to_face_up(&james, tenD);
    deal_to_face_up(&james, sevenH);
    deal_to_face_up(&james, fourS);   

    assert_true(has_cards(&james));
}

static void test_has_cards_when_face_down_does(void)
{
    struct player_t james = make_player("James", 'h');    
    deal_to_face_down(&james, tenD);
    deal_to_face_down(&james, sevenH);
    deal_to_face_down(&james, fourS);   

    assert_true(has_cards(&james));
}

static void test_has_cards_when_one(void)
{
    struct player_t james = make_player("James", 'h');
    deal_to_hand(&james, tenD);

    assert_true(has_cards(&james));
}

static void test_not_has_cards_when_none(void)
{
    struct player_t james = make_player("James", 'h');

    assert_false(has_cards(&james));
}

static void test_remove_from_hand(void)
{
    struct player_t james = make_player("James", 'h');
    deal_to_hand(&james, tenD);
    deal_to_hand(&james, sevenH);
    deal_to_hand(&james, fourS);   
    remove_from_hand(&james, &tenD);   

    assert_int_equals(james.hand_size, 2);
    assert_false(cards_equal(&james.hand[0], &tenD));
    assert_false(cards_equal(&james.hand[1], &tenD));
}

static void test_remove_from_face_up(void)
{
    struct player_t james = make_player("James", 'h');
    deal_to_face_up(&james, tenD);
    deal_to_face_up(&james, sevenH);
    deal_to_face_up(&james, fourS);   
    remove_from_face_up(&james, &tenD);   

    assert_int_equals(james.face_up_size, 2);
    assert_false(cards_equal(&james.face_up[0], &tenD));
    assert_false(cards_equal(&james.face_up[1], &tenD));
}

static void test_remove_from_face_down(void)
{
    struct player_t james = make_player("James", 'h');
    deal_to_face_down(&james, tenD);
    deal_to_face_down(&james, sevenH);
    deal_to_face_down(&james, fourS);
    remove_from_face_down(&james, &tenD);

    assert_int_equals(james.face_down_size, 2);
    assert_false(cards_equal(&james.face_down[0], &tenD));
    assert_false(cards_equal(&james.face_down[1], &tenD));
}

void register_player_tests(void)
{
    TEST_MODULE("test_player");
    SETUP(setup);
    TEST(test_lowest_card_by_player);
    TEST(swap_first_two_cards);
    TEST(swap_last_two_cards);
    TEST(swap_first_and_last);
    TEST(swap_middle_cards);
    TEST(test_has_cards_when_hand_does);
    TEST(test_has_cards_when_face_up_does);
    TEST(test_has_cards_when_face_down_does);
    TEST(test_has_cards_when_one);
    TEST(test_not_has_cards_when_none);
    TEST(test_remove_from_hand);
    TEST(test_remove_from_face_up);
    TEST(test_remove_from_face_down);
}

