#include <stdio.h>
#include "c-head.h"

void newline()
{
    newlines(1) ;
}

void newlines(int num)
{
    int i ;
    for (i = 0 ; i < num ; i++)
    {
        printf("\n") ;
    }
}

void show_welcome_msg()
{
    printf("Welcome to C-Head!") ;
    newlines(2) ;
}

void show_player(player *p)
{
    printf("Player name : %s, Player type : %d", p->name, p->type) ;
    newline() ;
}

void show_players(player *players, int len) 
{
    int i ;

    for (i = 0 ; i < len ; i++) 
    {
        show_player(&players[i]) ;       
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

void request_player_name(char *name, int num)
{
    printf("Enter name for player %d :", num) ;
    newline() ;
    scanf("%s", name) ;
}

