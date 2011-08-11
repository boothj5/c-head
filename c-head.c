#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "c-head.h" 

void create_players(player *, int) ;
void shuffle(card *, size_t) ;

int main(void)
{
    int num_players, num_cards_each, deck_size ;
    player players[MAX_NUM_PLAYERS] ;
    card deck[MAX_DECK_SIZE] ;

    clearscreen() ;
    show_welcome_msg() ;
    num_players = request_num_players() ;
    num_cards_each = request_num_cards_each() ;
    newline() ;

    deck_size = cards_required(num_players, num_cards_each) ;
 
    create_deck(deck, deck_size) ;
    show_deck(deck, deck_size) ;

    create_players(players, num_players) ;
    show_players(players, num_players) ;

    shuffle(deck, deck_size) ;
    newline() ;
    show_deck(deck, deck_size) ;

}

void create_players(player *players, int num_players)
{
    int i ;
    char name[MAX_NAME_LEN] ;

    for (i = 0 ; i < num_players ; i++) 
    {
        request_player_name(name, i+1) ;
        players[i] = make_player(name, HUMAN) ;
    }
}

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
