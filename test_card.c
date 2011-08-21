#include <stdio.h>
#include <head-unit.h>
#include "card.h"

void test_three_lowest_when_last(void)
{
    Card ten = make_card(TEN, HEARTS) ;
    Card six = make_card(SIX, CLUBS) ;
    Card three = make_card(THREE, DIAMONDS) ;

    Card cards[] = { ten, six, three } ;

    Card lowest_card ;
    lowest_card =  lowest(cards, 3) ;

    assert_true(rank(lowest_card) == THREE) ;
}

void test_three_lowest_when_middle(void)
{
    Card ten = make_card(TEN, HEARTS) ;
    Card three = make_card(THREE, DIAMONDS) ;
    Card six = make_card(SIX, CLUBS) ;

    Card cards[] = { ten, three, six } ;

    Card lowest_card ;
    lowest_card =  lowest(cards, 3) ;

    assert_true(rank(lowest_card) == THREE) ;
}

void test_three_lowest_when_first(void)
{
    Card three = make_card(THREE, DIAMONDS) ;
    Card ten = make_card(TEN, HEARTS) ;
    Card six = make_card(SIX, CLUBS) ;

    Card cards[] = { three, ten, six } ;

    Card lowest_card ;
    lowest_card =  lowest(cards, 3) ;

    assert_true(rank(lowest_card) == THREE) ;
}

void test_lowest_one_card(void)
{
    Card ten = make_card(TEN, HEARTS) ;

    Card cards[] = { ten } ;

    Card lowest_card ;
    lowest_card =  lowest(cards, 1) ;

    assert_true(rank(lowest_card) == TEN) ;
}   

void test_three_lower_than_two(void)
{
    Card three = make_card(THREE, DIAMONDS) ;
    Card two = make_card(TWO, HEARTS) ;

    Card cards[] = { three, two } ;

    Card lowest_card ;
    lowest_card = lowest(cards, 2) ;
    
    assert_true(rank(lowest_card) == THREE) ;
}

void test_five_lower_than_two(void)
{
    Card five = make_card(FIVE, DIAMONDS) ;
    Card two = make_card(TWO, HEARTS) ;

    Card cards[] = { five, two } ;

    Card lowest_card ;
    lowest_card = lowest(cards, 2) ;
    
    assert_true(rank(lowest_card) == FIVE) ;
}

void test_jack_lower_than_seven(void)
{
    Card jack = make_card(JACK, DIAMONDS) ;
    Card seven = make_card(SEVEN, HEARTS) ;

    Card cards[] = { jack, seven } ;

    Card lowest_card ;
    lowest_card = lowest(cards, 2) ;
    
    assert_true(rank(lowest_card) == JACK) ;
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

