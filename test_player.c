#include <stdio.h>
#include <head-unit.h>

#include "player.h"
#include "card.h"

void test_lowest_card_by_player(void)
{
    struct player_t steve = make_player("Steve", HUMAN) ;
    struct player_t james = make_player("James", HUMAN) ;
    struct player_t dave = make_player("Dave", HUMAN) ;
    struct player_t mike = make_player("Mike", HUMAN) ;
    struct player_t players[4] ;
    struct card_t lowest_cards[4] ;

    deal_to_hand(&steve, make_card(TEN, DIAMONDS)) ;
    deal_to_hand(&steve, make_card(SEVEN, HEARTS)) ;
    deal_to_hand(&steve, make_card(FOUR, SPADES)) ;

    deal_to_hand(&james, make_card(FOUR, SPADES)) ;
    deal_to_hand(&james, make_card(FIVE, HEARTS)) ;
    deal_to_hand(&james, make_card(NINE, SPADES)) ;   

    deal_to_hand(&dave, make_card(JACK, DIAMONDS)) ;
    deal_to_hand(&dave, make_card(QUEEN, HEARTS)) ;
    deal_to_hand(&dave, make_card(KING, SPADES)) ;   

    deal_to_hand(&mike, make_card(ACE, DIAMONDS)) ;
    deal_to_hand(&mike, make_card(ACE, HEARTS)) ;
    deal_to_hand(&mike, make_card(ACE, SPADES)) ;   

    players[0] = steve ;
    players[1] = james ;
    players[2] = dave ;
    players[3] = mike ;

    find_lowest_card_by_player(players, 4, lowest_cards) ;

    assert_true(cards_equal(lowest_cards[0], make_card(FOUR, SPADES))) ;
    assert_true(cards_equal(lowest_cards[1], make_card(FOUR, SPADES))) ;
    assert_true(cards_equal(lowest_cards[2], make_card(JACK, DIAMONDS))) ;
    assert_int_equals(ACE, lowest_cards[3].rank) ;
}

void swap_first_two_cards(void)
{
    struct player_t james = make_player("James", HUMAN) ;
    deal_to_hand(&james, make_card(FOUR, SPADES)) ;
    deal_to_hand(&james, make_card(TEN, DIAMONDS)) ;
    deal_to_hand(&james, make_card(SEVEN, HEARTS)) ;
    sort_cards(james.hand, james.hand_size) ;
    
    deal_to_face_up(&james, make_card(THREE, DIAMONDS)) ;
    deal_to_face_up(&james, make_card(NINE, DIAMONDS)) ;
    deal_to_face_up(&james, make_card(ACE, CLUBS)) ;

    swap(&james, 1, 1) ;
    
    assert_true(cards_equal(james.hand[0], make_card(THREE, DIAMONDS))) ;
    assert_true(cards_equal(james.face_up[0], make_card(FOUR, SPADES))) ;
}

void swap_last_two_cards(void)
{
    struct player_t james = make_player("James", HUMAN) ;
    deal_to_hand(&james, make_card(FOUR, SPADES)) ;
    deal_to_hand(&james, make_card(ACE, DIAMONDS)) ;
    deal_to_hand(&james, make_card(SEVEN, HEARTS)) ;
    sort_cards(james.hand, james.hand_size) ;
    
    deal_to_face_up(&james, make_card(NINE, DIAMONDS)) ;
    deal_to_face_up(&james, make_card(ACE, CLUBS)) ;
    deal_to_face_up(&james, make_card(TWO, DIAMONDS)) ;

    swap(&james, 3, 3) ;
    
    assert_true(cards_equal(james.hand[2], make_card(TWO, DIAMONDS))) ;
    assert_true(cards_equal(james.face_up[2], make_card(SEVEN, HEARTS))) ;
}

void swap_first_and_last(void)
{
    struct player_t james = make_player("James", HUMAN) ;
    deal_to_hand(&james, make_card(FOUR, SPADES)) ;
    deal_to_hand(&james, make_card(FIVE, DIAMONDS)) ;
    deal_to_hand(&james, make_card(SIX, HEARTS)) ;
    sort_cards(james.hand, james.hand_size) ;
    
    deal_to_face_up(&james, make_card(EIGHT, DIAMONDS)) ;
    deal_to_face_up(&james, make_card(NINE, CLUBS)) ;
    deal_to_face_up(&james, make_card(JACK, DIAMONDS)) ;

    swap(&james, 1, 3) ;
    
    assert_true(cards_equal(james.hand[2], make_card(JACK, DIAMONDS))) ;
    assert_true(cards_equal(james.face_up[2], make_card(FOUR, SPADES))) ;
}

void swap_middle_cards(void)
{
    struct player_t james = make_player("James", HUMAN) ;
    deal_to_hand(&james, make_card(FOUR, SPADES)) ;
    deal_to_hand(&james, make_card(FIVE, DIAMONDS)) ;
    deal_to_hand(&james, make_card(SIX, HEARTS)) ;
    sort_cards(james.hand, james.hand_size) ;
    
    deal_to_face_up(&james, make_card(EIGHT, DIAMONDS)) ;
    deal_to_face_up(&james, make_card(NINE, CLUBS)) ;
    deal_to_face_up(&james, make_card(JACK, DIAMONDS)) ;

    swap(&james, 2, 2) ;
    
    assert_true(cards_equal(james.hand[2], make_card(NINE, CLUBS))) ;
    assert_true(cards_equal(james.face_up[1], make_card(FIVE, DIAMONDS))) ;
}

void test_has_cards_when_hand_does(void)
{
    struct player_t james = make_player("James", HUMAN) ;    
    deal_to_hand(&james, make_card(TEN, DIAMONDS)) ;
    deal_to_hand(&james, make_card(SEVEN, HEARTS)) ;
    deal_to_hand(&james, make_card(FOUR, SPADES)) ;   

    assert_true(has_cards(james)) ;
} 

void test_has_cards_when_face_up_does(void)
{
    struct player_t james = make_player("James", HUMAN) ;    
    deal_to_face_up(&james, make_card(TEN, DIAMONDS)) ;
    deal_to_face_up(&james, make_card(SEVEN, HEARTS)) ;
    deal_to_face_up(&james, make_card(FOUR, SPADES)) ;   

    assert_true(has_cards(james)) ;
}

void test_has_cards_when_face_down_does(void)
{
    struct player_t james = make_player("James", HUMAN) ;    
    deal_to_face_down(&james, make_card(TEN, DIAMONDS)) ;
    deal_to_face_down(&james, make_card(SEVEN, HEARTS)) ;
    deal_to_face_down(&james, make_card(FOUR, SPADES)) ;   

    assert_true(has_cards(james)) ;
}

void test_has_cards_when_one(void)
{
    struct player_t james = make_player("James", HUMAN) ;    
    deal_to_hand(&james, make_card(TEN, DIAMONDS)) ;

    assert_true(has_cards(james)) ;
}

void test_not_has_cards_when_none(void)
{
    struct player_t james = make_player("James", HUMAN) ;    

    assert_false(has_cards(james)) ;
}

void test_remove_from_hand(void)
{
    struct player_t james = make_player("James", HUMAN) ;    
    deal_to_hand(&james, make_card(TEN, DIAMONDS)) ;
    deal_to_hand(&james, make_card(SEVEN, HEARTS)) ;
    deal_to_hand(&james, make_card(FOUR, SPADES)) ;   
    remove_from_hand(&james, make_card(TEN, DIAMONDS)) ;   

    assert_int_equals(james.hand_size, 2) ;
    assert_false(cards_equal(james.hand[0], make_card(TEN, DIAMONDS))) ;
    assert_false(cards_equal(james.hand[1], make_card(TEN, DIAMONDS))) ;
}

void test_remove_from_face_up(void)
{
    struct player_t james = make_player("James", HUMAN) ;    
    deal_to_face_up(&james, make_card(TEN, DIAMONDS)) ;
    deal_to_face_up(&james, make_card(SEVEN, HEARTS)) ;
    deal_to_face_up(&james, make_card(FOUR, SPADES)) ;   
    remove_from_face_up(&james, make_card(TEN, DIAMONDS)) ;   

    assert_int_equals(james.face_up_size, 2) ;
    assert_false(cards_equal(james.face_up[0], make_card(TEN, DIAMONDS))) ;
    assert_false(cards_equal(james.face_up[1], make_card(TEN, DIAMONDS))) ;
}

void test_remove_from_face_down(void)
{
    struct player_t james = make_player("James", HUMAN) ;    
    deal_to_face_down(&james, make_card(TEN, DIAMONDS)) ;
    deal_to_face_down(&james, make_card(SEVEN, HEARTS)) ;
    deal_to_face_down(&james, make_card(FOUR, SPADES)) ;   
    remove_from_face_down(&james, make_card(TEN, DIAMONDS)) ;   

    assert_int_equals(james.face_down_size, 2) ;
    assert_false(cards_equal(james.face_down[0], make_card(TEN, DIAMONDS))) ;
    assert_false(cards_equal(james.face_down[1], make_card(TEN, DIAMONDS))) ;
}

void register_player_tests(void)
{
    TEST_MODULE("test_player");
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

