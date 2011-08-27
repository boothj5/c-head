#include <stdio.h>
#include <head-unit.h>
#include "card.h"

void test_three_lowest_when_last(void)
{
    struct card_t ten = make_card(TEN, HEARTS) ;
    struct card_t six = make_card(SIX, CLUBS) ;
    struct card_t three = make_card(THREE, DIAMONDS) ;
    struct card_t cards[] = { ten, six, three } ;

    struct card_t lowest = find_lowest_card(cards, 3) ;
    assert_true(lowest.rank == THREE) ;
}

void test_three_lowest_when_middle(void)
{
    struct card_t ten = make_card(TEN, HEARTS) ;
    struct card_t three = make_card(THREE, DIAMONDS) ;
    struct card_t six = make_card(SIX, CLUBS) ;
    struct card_t cards[] = { ten, three, six } ;

    struct card_t lowest =  find_lowest_card(cards, 3) ;
    assert_true(lowest.rank == THREE) ;
}

void test_three_lowest_when_first(void)
{
    struct card_t three = make_card(THREE, DIAMONDS) ;
    struct card_t ten = make_card(TEN, HEARTS) ;
    struct card_t six = make_card(SIX, CLUBS) ;
    struct card_t cards[] = { three, ten, six } ;

    struct card_t lowest =  find_lowest_card(cards, 3) ;
    assert_true(lowest.rank == THREE) ;
}

void test_lowest_one_card(void)
{
    struct card_t ten = make_card(TEN, HEARTS) ;
    struct card_t cards[] = { ten } ;

    struct card_t lowest =  find_lowest_card(cards, 1) ;
    assert_true(lowest.rank == TEN) ;
}   

void test_three_lower_than_two(void)
{
    struct card_t three = make_card(THREE, DIAMONDS) ;
    struct card_t two = make_card(TWO, HEARTS) ;
    struct card_t cards[] = { three, two } ;

    struct card_t lowest = find_lowest_card(cards, 2) ;
    assert_true(lowest.rank == THREE) ;
}

void test_five_lower_than_two(void)
{
    struct card_t five = make_card(FIVE, DIAMONDS) ;
    struct card_t two = make_card(TWO, HEARTS) ;
    struct card_t cards[] = { five, two } ;

    struct card_t lowest = find_lowest_card(cards, 2) ;
    assert_true(lowest.rank == FIVE) ;
}

void test_jack_lower_than_seven(void)
{
    struct card_t jack = make_card(JACK, DIAMONDS) ;
    struct card_t seven = make_card(SEVEN, HEARTS) ;
    struct card_t cards[] = { jack, seven } ;

    struct card_t lowest = find_lowest_card(cards, 2) ;
    assert_true(lowest.rank == JACK) ;
}

void test_two_special(void)
{
    assert_true(special_card(make_card(TWO, DIAMONDS))) ;
}

void test_seven_special(void)
{
    assert_true(special_card(make_card(SEVEN, DIAMONDS))) ;
}

void test_ten_special(void)
{
    assert_true(special_card(make_card(TEN, DIAMONDS))) ;
}


int main(void)
{
    add_suite("test_card") ;
    add_test(test_three_lowest_when_last, "test_three_lowest_when_last" ) ;
    add_test(test_three_lowest_when_middle, "test_three_lowest_when_middle") ;
    add_test(test_three_lowest_when_first, "test_three_lowest_when_first") ;
    add_test(test_lowest_one_card, "test_lowest_one_card") ;
    add_test(test_three_lower_than_two, "test_three_lower_than_two") ;
    add_test(test_five_lower_than_two, "test_five_lower_than_two") ;
    add_test(test_jack_lower_than_seven, "test_jack_lower_than_seven") ;
    add_test(test_two_special, "test_two_special") ;
    add_test(test_seven_special, "test_seven_special") ;
    add_test(test_ten_special, "test_ten_special") ;

    run_tests() ; 
    return 0 ;
}

