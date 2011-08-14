#include <stdio.h>
#include "card.h"

int main(void)
{
    Card ten = make_card(TEN, HEARTS) ;
    Card six = make_card(SIX, CLUBS) ;
    Card three = make_card(THREE, DIAMONDS) ;

    Card cards[] = { ten, six, three } ;

    Card lowest_card ;
    lowest_card =  lowest(cards, 3) ;
    
    if (lowest_card.rank = THREE)
        printf("SUCCESS\n") ;
    else
        printf("FAILURE\n") ;
    
    return 0 ;
}
