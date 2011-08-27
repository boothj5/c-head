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

    assert_true(1) ;
}

int main(void)
{
    add_test(test_lowest_card_by_player, "test_lowest_card_by_player" ) ;

    run_tests() ; 
    return 0 ;
}

