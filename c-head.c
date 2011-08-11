#include <stdio.h>
#include <stdlib.h>
#include "c-head.h" 

void create_players(player *, int) ;

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

    create_players(players, num_players) ;

    shuffle(deck, deck_size) ;
    newline() ;
    printf("Initial deck\n") ;
    show_cards(deck, deck_size) ;
    newline() ;

    int i ;
    for (i = 0 ; i < num_players ; i++)
    {
        int j ;
        for (j = 0 ; j < num_cards_each ; j++)
        {
            deal_to_hand(&players[i], deck[--deck_size]) ;
            deal_to_face_up(&players[i], deck[--deck_size]) ;
            deal_to_face_down(&players[i], deck[--deck_size]) ;
        }
    }

    show_players(players, num_players) ;
    newline() ;
    printf("Deck after dealing\n") ;
    show_cards(deck, deck_size) ;
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


