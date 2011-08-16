#include <stdio.h>
#include <head-unit.h>
#include "card.h"

#define NUM_TESTS 10

void test_three_lowest_when_last(void)
{
    Card ten = make_card(TEN, HEARTS) ;
    Card six = make_card(SIX, CLUBS) ;
    Card three = make_card(THREE, DIAMONDS) ;

    Card cards[] = { ten, six, three } ;

    Card lowest_card ;
    lowest_card =  lowest(cards, 3) ;

    assert_true(lowest_card.rank == THREE) ;
}

void test_three_lowest_when_middle(void)
{
    Card ten = make_card(TEN, HEARTS) ;
    Card three = make_card(THREE, DIAMONDS) ;
    Card six = make_card(SIX, CLUBS) ;

    Card cards[] = { ten, three, six } ;

    Card lowest_card ;
    lowest_card =  lowest(cards, 3) ;

    assert_true(lowest_card.rank == THREE) ;
}

void test_three_lowest_when_first(void)
{
    Card three = make_card(THREE, DIAMONDS) ;
    Card ten = make_card(TEN, HEARTS) ;
    Card six = make_card(SIX, CLUBS) ;

    Card cards[] = { three, ten, six } ;

    Card lowest_card ;
    lowest_card =  lowest(cards, 3) ;

    assert_true(lowest_card.rank == THREE) ;
}

void test_lowest_one_card(void)
{
    Card ten = make_card(TEN, HEARTS) ;

    Card cards[] = { ten } ;

    Card lowest_card ;
    lowest_card =  lowest(cards, 1) ;

    assert_true(lowest_card.rank == TEN) ;
}   

void test_three_lower_than_two(void)
{
    Card three = make_card(THREE, DIAMONDS) ;
    Card two = make_card(TWO, HEARTS) ;

    Card cards[] = { three, two } ;

    Card lowest_card ;
    lowest_card = lowest(cards, 2) ;
    
    assert_true(lowest_card.rank == THREE) ;
}

void test_five_lower_than_two(void)
{
    Card five = make_card(FIVE, DIAMONDS) ;
    Card two = make_card(TWO, HEARTS) ;

    Card cards[] = { five, two } ;

    Card lowest_card ;
    lowest_card = lowest(cards, 2) ;
    
    assert_true(lowest_card.rank == FIVE) ;
}

void test_jack_lower_than_seven(void)
{
    Card jack = make_card(JACK, DIAMONDS) ;
    Card seven = make_card(SEVEN, HEARTS) ;

    Card cards[] = { jack, seven } ;

    Card lowest_card ;
    lowest_card = lowest(cards, 2) ;
    
    assert_true(lowest_card.rank == JACK) ;
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

Test tests[NUM_TESTS] = 
        { { test_three_lowest_when_last, "test_three_lowest_when_last" } ,
          { test_three_lowest_when_middle, "test_three_lowest_when_middle" } ,
          { test_three_lowest_when_first, "test_three_lowest_when_first" } ,
          { test_lowest_one_card, "test_lowest_one_card" } ,
          { test_three_lower_than_two, "test_three_lower_than_two" } ,
          { test_five_lower_than_two, "test_five_lower_than_two" } ,
          { test_jack_lower_than_seven, "test_jack_lower_than_seven" } ,
          { test_two_special, "test_two_special" } ,
          { test_seven_special, "test_seven_special" } ,
          { test_ten_special, "test_ten_special" } } ;


int main(void)
{
    run_tests(tests, NUM_TESTS) ; 
    return 0 ;
}

