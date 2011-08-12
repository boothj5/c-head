#include "card.h"

void shuffle(card *deck, size_t n)
{
    if (n > 1)
    {
        srand((unsigned)time(NULL)) ;
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          card t = deck[j];
          deck[j] = deck[i];
          deck[i] = t;
        }
    }
}

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

char* show_rank(card *c)
{
    switch(c->rank)
    {
        case TWO:
            return "TWO" ;
        case THREE:
            return "THREE" ;
        case FOUR:
            return "FOUR" ;
        case FIVE:
            return "FIVE" ;
        case SIX:
            return "SIX" ;
        case SEVEN:
            return "SEVEN" ;
        case EIGHT:
            return "EIGHT" ;
        case NINE:
            return "NINE" ;
        case TEN:
            return "TEN" ;
        case JACK:
            return "JACK" ;
        case QUEEN:
            return "QUEEN" ;
        case KING:
            return "KING" ;
        case ACE:
            return "ACE" ;
        default:
            return "ERROR!!!" ;
    }
}

char* show_suit(card *c)
{
    switch(c->suit)
    {
        case HEARTS:
            return "HEARTS" ;
        case DIAMONDS:
            return "DIAMONDS" ;
        case CLUBS:
            return "CLUBS" ;
        case SPADES:
            return "SPADES" ;
        default:
            return "ERROR!!!!" ;
    } 
}
