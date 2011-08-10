#include <stdlib.h>
#include "c-head.h"

#define DECK_SIZE 52

void populate_deck(card *, int) ;

void create_deck(card **deck, int num_decks)
{
    int num_cards = cards_required(num_decks) ;
    *deck = (card *) malloc(num_cards * sizeof(card)) ;
    populate_deck(*deck, num_cards) ;
}

int cards_required(int decks)
{
    int result ;
    result = decks * DECK_SIZE ;

    return result ;
}

void populate_deck(card *deck, int num_cards)
{
    int rank, suit ;
    int i = 0 ;
    int j ;

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
