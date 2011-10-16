#include <head-unit.h>

#include "testsuite.h"
#include "last_move.h"

void test_last_move_miss_a_go(void)
{
    char last_move[100] = "" ;
    char name[10] = "James" ;

    set_last_move_was_miss_a_go(last_move, name) ;

    assert_string_equals("James layed miss a go card\n", last_move) ;
}

void test_last_move_was_burn(void)
{
    char last_move[100] = "" ;
    char name[10] = "James" ;

    set_last_move_was_burn(last_move, name) ;

    assert_string_equals("James burnt the deck\n", last_move) ;
}   

void test_last_move_pickup(void)
{
    char last_move[100] = "" ;
    char name[10] = "James" ;

    set_last_move_pickup(last_move, name) ;

    assert_string_equals("James picked up\n", last_move) ;
}

void test_last_move_with_cards(void)
{
    char last_move[100] = "" ;
    char name[10] = "James" ;
    int ncards = 3 ;
    struct card_t cards[3] ;
    cards[0] = make_card(ACE, SPADES) ;
    cards[1] = make_card(THREE, DIAMONDS) ;
    cards[2] = make_card(SEVEN, HEARTS) ;

    set_last_move(last_move, name, cards, ncards) ;

    assert_string_equals("James laid: ACE of SPADES, THREE of DIAMONDS, SEVEN of HEARTS, \n", 
                                                                                    last_move) ;
}

void register_last_move_tests(void)
{
    add_suite("test_last_move") ;
    add_test(test_last_move_miss_a_go, "test_last_move_miss_a_go") ;
    add_test(test_last_move_was_burn, "test_last_move_was_burn") ;
    add_test(test_last_move_pickup, "test_last_move_pickup") ;
    add_test(test_last_move_with_cards, "test_last_move_with_cards") ;
}

