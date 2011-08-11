#include <stdlib.h>
#include <stdio.h>
#include "c-head.h"

void create_deck(card *deck, int num_cards)
{
    int num_decks ;
    int rank, suit ;
    int i = 0 ;
    int j ;

    num_decks = num_cards / DECK_SIZE ;

    for (j = 0 ; j < num_decks ; j++)
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
