#include <stdio.h>
#include <string.h>

#include "player.h"
#include "game.h"
#include "console.h"

void newline()
{
    printf("\n") ;
}

void newlines(int num)
{
    int i ;
    for (i = 0 ; i < num ; i++)
        newline() ;
}

void show_welcome_msg()
{
    printf("Welcome to C-Head!") ;
    newlines(2) ;
}

void show_player(struct player_t p)
{
    printf("Player name : %s", p.name) ;
    newline() ;
    if (p.hand_size > 0) {
        printf("HAND     : ") ;
        show_cards(p.hand, p.hand_size) ;
    }
    if (p.face_up_size > 0) {
        printf("FACE UP  : ") ;
        show_cards(p.face_up, p.face_up_size) ;
    }
    if (p.hand_size > 0) {
        printf("FACE DOWN: ") ;
        show_cards(p.face_down, p.face_down_size) ;
    }
}

void show_players(struct player_t *players, int len) 
{
    int i ;
    for (i = 0 ; i < len ; i++)  {
        show_player(players[i]) ;
        newline() ;
    }
}

void clearscreen() 
{
    newlines(100) ;
}

int request_num_players()
{
    int result ;
    printf("Enter number of players : ") ;
    scanf("%d", &result) ;
    return result ;
}

int request_num_cards_each()
{
    int result ;
    printf("Enter number of cards each : ") ;
    scanf("%d", &result) ;
    return result ;
}

void request_player_names(char names[MAX_NUM_PLAYERS][MAX_NAME_LEN], int nplayers)
{
    char name[MAX_NAME_LEN] ;
    int i ;
    
    for (i = 0 ; i < nplayers ; i++) {
        printf("Enter name for player %d :", i+1) ;
        newline() ;
        scanf("%s", &name) ;
        strcpy(names[i], name) ;
    }
    
    newline() ;
}

void show_cards(struct card_t *cards, int num_cards) 
{
    int i ;
    int j = 1 ;

    for (i = (num_cards-1) ; i >= 0 ; i--) {
        printf("(%d)%s of %s", j, show_rank(cards[i]), show_suit(cards[i])) ;
        if (j <= (num_cards - 1))
            printf(", ") ;
        else
            printf("\n") ;
        j++ ;
    }
}

void show_deck(int num_cards) 
{
    printf("%d left on deck", num_cards) ;
    newlines(2) ;
}

void show_pile(struct card_t *cards, int ncards)
{
    printf("Pile : ") ;
    show_cards(cards, ncards) ;
}

void show_last_move(char *move) 
{
    printf(move) ;
}
