#include <stdlib.h>
#include "c-head.h"

#define DECK_SIZE 52

void create_deck(card *deck, int num_decks)
{
    int rank, suit ;
    int i = 0 ;
    int j ;
    int num_cards = cards_required(num_decks) ;

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

int cards_required(int decks)
{
    int result ;
    result = decks * DECK_SIZE ;

    return result ;
}
