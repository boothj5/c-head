#include <stdio.h>
#include "card.h"
#include "jbtest.h" 

#define NUM_TESTS 2

static void test_three_lowest(void) ;
static void test_three_lowest_fail(void) ;

static void (*tests[NUM_TESTS]) (void)  = { test_three_lowest, 
                                            test_three_lowest_fail } ;

int main(void)
{
    int i ;
    for (i = 0 ; i < NUM_TESTS ; i++)
        (*tests[i])() ;
    
    return 0 ;
}

void test_three_lowest(void)
{
    Card ten = make_card(TEN, HEARTS) ;
    Card six = make_card(SIX, CLUBS) ;
    Card three = make_card(THREE, DIAMONDS) ;

    Card cards[] = { ten, six, three } ;

    Card lowest_card ;
    lowest_card =  lowest(cards, 3) ;

    assert_true(lowest_card.rank == THREE) ;
}

void test_three_lowest_fail(void)
{
    Card ten = make_card(TEN, HEARTS) ;
    Card six = make_card(SIX, CLUBS) ;
    Card three = make_card(THREE, DIAMONDS) ;

    Card cards[] = { ten, six, three } ;

    Card lowest_card ;
    lowest_card =  lowest(cards, 3) ;

    assert_true(lowest_card.rank != THREE) ;
}
