#include <stdio.h>
#include <head-unit.h>
#include "card.h"

#define NUM_TESTS 4

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

    Card cards[] = { ten, } ;

    Card lowest_card ;
    lowest_card =  lowest(cards, 1) ;

    assert_true(lowest_card.rank == TEN) ;
}   

static Test tests[NUM_TESTS]  = 
    { { test_three_lowest_when_last, "test_three_lowest_when_last" } ,  
      { test_three_lowest_when_middle, "test_three_lowest_when_middle" } ,
      { test_three_lowest_when_first, "test_three_lowest_when_first" } , 
      { test_lowest_one_card, "test_lowest_one_card" } } ;

int main(void)
{
    run_tests(tests, NUM_TESTS) ; 
    return 0 ;
}

