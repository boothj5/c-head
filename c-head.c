#include <stdio.h>
#include <stdlib.h>

#define MAXNAMELEN 10

enum ranks { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
             JACK, QUEEN, KING, ACE } ;

enum suits { HEARTS, SPADES, DIAMONDS, CLUBS } ;

enum player_types { HUMAN, COMPUTER } ;

typedef struct {
    int rank ;
    int suit ;
} card ;

typedef struct {
    char name[MAXNAMELEN] ;
    int type ;
} player ;

void clearscreen() ;
int request_num_players() ;
int request_num_cards_each() ;
int calc_decks_required(int, int) ;
void show_player(player *) ;
void show_players(player *, int) ;

int main(void)
{
    int num_players, num_cards_each, total_cards_needed, decks_required ;
    player *players ;

    clearscreen() ;
    printf("Welcome to C-Head!") ;
    printf("\n") ;
    printf("\n") ;
    num_players = request_num_players() ;
    num_cards_each = request_num_cards_each() ;
    printf("\n") ;

    decks_required = calc_decks_required(num_players, num_cards_each) ;
    printf("Total decks needed = %d", decks_required) ;
    printf("\n") ;

    players = (player *) malloc(num_players * sizeof(player)) ;

    int i ;
    for (i = 0 ; i < num_players ; i++) 
    {
        printf("Enter name for player %d :\n", i+1) ;
        scanf("%s", players[i].name) ;
        players[i].type = HUMAN ;
    }
    
    show_players(players, num_players) ;

}

void clearscreen() 
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n") ;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n") ;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n") ;
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

int calc_decks_required(int n_players, int n_cards)
{
    int total_cards, result, div, add ;

    total_cards = n_players * (n_cards * 3) ;
    div = total_cards / 52 ;
    add = ((total_cards % 52) > 0) ;

    result = div + add ;
    return result ;
}

void show_player(player *p)
{
    printf("Player name : %s, Player type : %d\n", p->name, p->type) ;
}

void show_players(player *players, int len) 
{
    int i ;

    for (i = 0 ; i < len ; i++) 
    {
        show_player(&players[i]) ;       
    }
}
