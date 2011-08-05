#include <stdlib.h>
#include "c-head.h"

void create_deck(card *deck, int num_decks)
{
    int rank, suit ;
    int i = 0 ;
    int j ;
    int num_cards = 52 * num_decks ;

    for (j = 0 ; j < num_cards ; j++)
    {
        for (suit = 0 ; suit <= 3 ; suit++)
        {
            for (rank = 2 ; rank <= 14 ; rank++)
            {
                card a_card ;
                a_card.rank = rank ;
                a_card.suit = suit ;
                deck[i] = a_card ;
                i++ ;
            }
        }
    }
}
