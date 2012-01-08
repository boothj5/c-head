#include <stdio.h>
#include <string.h>
#include <head-unit.h>

#include "pile.h"

void test_burn_card_on_pile(void)
{
    int pile_size = 1 ;
    struct card_t pile[pile_size] ;
    pile[0] = make_card(TEN, DIAMONDS) ;
    int result = burn_cards_laid(pile, pile_size) ;

    assert_true(result) ;

}

void test_not_burn_card_on_pile(void)
{
    int pile_size = 1 ;
    struct card_t pile[pile_size] ;
    pile[0] = make_card(JACK, DIAMONDS) ;
    int result = burn_cards_laid(pile, pile_size) ;

    assert_false(result) ;
}

void test_burn_four_of_a_kind(void)
{
    int pile_size = 6 ;
    struct card_t pile[pile_size] ;
    pile[0] = make_card(JACK, DIAMONDS) ;
    pile[1] = make_card(THREE, DIAMONDS) ;
    pile[2] = make_card(NINE, DIAMONDS) ;
    pile[3] = make_card(NINE, SPADES) ;
    pile[4] = make_card(NINE, HEARTS) ;
    pile[5] = make_card(NINE, CLUBS) ;
    int result = burn_cards_laid(pile, pile_size) ;

    assert_true(result) ;
}

void test_not_burn_three_of_a_kind(void)
{
    int pile_size = 5 ;
    struct card_t pile[pile_size] ;
    pile[0] = make_card(JACK, DIAMONDS) ;
    pile[1] = make_card(THREE, DIAMONDS) ;
    pile[2] = make_card(NINE, DIAMONDS) ;
    pile[3] = make_card(NINE, SPADES) ;
    pile[4] = make_card(NINE, HEARTS) ;
    int result = burn_cards_laid(pile, pile_size) ;

    assert_false(result) ;
}

void test_not_burn_no_cards(void)
{
    int pile_size = 0 ;
    struct card_t pile[pile_size] ;
    int result = burn_cards_laid(pile, pile_size) ;

    assert_false(result) ;
}

void test_missgo_card_on_pile(void)
{
    int pile_size = 1 ;
    struct card_t pile[pile_size] ;
    pile[0] = make_card(EIGHT, DIAMONDS) ;
    int result = miss_a_go_card_laid(pile, pile_size) ;

    assert_true(result) ;
}

void test_not_missgo_card_on_pile(void)
{
    int pile_size = 1 ;
    struct card_t pile[pile_size] ;
    pile[0] = make_card(JACK, DIAMONDS) ;
    int result = miss_a_go_card_laid(pile, pile_size) ;

    assert_false(result) ;
}


void register_pile_tests(void)
{
    add_suite("test_pile") ;
    add_test(test_burn_card_on_pile, "test_burn_card_on_pile" ) ;
    add_test(test_not_burn_card_on_pile, "test_not_burn_card_on_pile" ) ;
    add_test(test_burn_four_of_a_kind, "test_burn_four_of_a_kind" ) ;
    add_test(test_not_burn_three_of_a_kind, "test_not_burn_three_of_a_kind" ) ;
    add_test(test_not_burn_no_cards, "test_not_burn_no_cards" ) ;
    add_test(test_missgo_card_on_pile, "test_missgo_card_on_pile" ) ;
    add_test(test_not_missgo_card_on_pile, "test_not_missgo_card_on_pile" ) ;
}
