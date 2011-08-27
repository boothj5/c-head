#include <stdio.h>
#include <head-unit.h>
#include "player.h"
#include "card.h"

void test_lowest_card_by_player(void)
{
    struct player_t steve = make_player("Steve", HUMAN) ;
    deal_to_hand(&steve, make_card(TEN, DIAMONDS)) ;
    deal_to_hand(&steve, make_card(SEVEN, HEARTS)) ;
    deal_to_hand(&steve, make_card(FOUR, SPADES)) ;   

    struct player_t james = make_player("James", HUMAN) ;
    deal_to_hand(&james, make_card(FOUR, SPADES)) ;
    deal_to_hand(&james, make_card(FIVE, HEARTS)) ;
    deal_to_hand(&james, make_card(NINE, SPADES)) ;   

    struct player_t dave = make_player("Dave", HUMAN) ;
    deal_to_hand(&dave, make_card(JACK, DIAMONDS)) ;
    deal_to_hand(&dave, make_card(QUEEN, HEARTS)) ;
    deal_to_hand(&dave, make_card(KING, SPADES)) ;   

    struct player_t mike = make_player("Mike", HUMAN) ;
    deal_to_hand(&mike, make_card(ACE, DIAMONDS)) ;
    deal_to_hand(&mike, make_card(ACE, HEARTS)) ;
    deal_to_hand(&mike, make_card(ACE, SPADES)) ;   

    struct player_t players[4] = { steve, james, dave, mike } ;
    struct card_t lowest_cards[4] ;

    find_lowest_card_by_player(players, 4, lowest_cards) ;

    assert_true(equals(lowest_cards[0], make_card(FOUR, SPADES))) ;
    assert_true(equals(lowest_cards[1], make_card(FOUR, SPADES))) ;
    assert_true(equals(lowest_cards[2], make_card(JACK, DIAMONDS))) ;
    assert_true(lowest_cards[3].rank == ACE) ;
}

void swap_first_two_cards(void)
{
    struct player_t james = make_player("James", HUMAN) ;
    deal_to_hand(&james, make_card(TEN, DIAMONDS)) ;
    deal_to_hand(&james, make_card(SEVEN, HEARTS)) ;
    deal_to_hand(&james, make_card(FOUR, SPADES)) ;   
    
    deal_to_face_up(&james, make_card(NINE, DIAMONDS)) ;
    deal_to_face_up(&james, make_card(ACE, CLUBS)) ;
    deal_to_face_up(&james, make_card(THREE, DIAMONDS)) ;

    swap(&james, 1, 1) ;
    
    assert_true(equals(james.hand[0], make_card(NINE, DIAMONDS))) ;
    assert_true(equals(james.face_up[0], make_card(TEN, DIAMONDS))) ;
}

int main(void)
{
    add_test(test_lowest_card_by_player, "test_lowest_card_by_player" ) ;
    add_test(swap_first_two_cards, "swap_first_two_cards" ) ;

    run_tests() ; 
    return 0 ;
}

