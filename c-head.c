#include <stdio.h>

void clearscreen() ;
int request_num_players() ;
int request_num_cards_each() ;
int calc_decks_required(int, int) ;

int main(void)
{
    int num_players, num_cards_each, total_cards_needed, decks_required ;

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
