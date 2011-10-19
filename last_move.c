#include "string.h"
#include "last_move.h"

void set_last_move(char *last_move, char *name, struct card_t *cards, int num_cards)
{
    int i ;

    strcpy(last_move, "") ;
    strcat(last_move, name) ;
    strcat(last_move, " laid: ") ;
    for (i = 0 ; i < num_cards ; i++) {
        strcat(last_move, show_rank(cards[i])) ;
        strcat(last_move, " of ") ;
        strcat(last_move, show_suit(cards[i])) ;
        strcat(last_move, ", ") ;
    }
    strcat(last_move, "\n") ;
}

void set_last_move_was_burn(char *last_move, char *name)
{
    strcpy(last_move, "") ;
    strcat(last_move, name) ;
    strcat(last_move, " burnt the deck\n") ;
}

void set_last_move_pickup(char *last_move, char *name)
{
    strcpy(last_move, "") ;
    strcat(last_move, name) ;
    strcat(last_move, " picked up\n") ;
}

void set_last_move_was_miss_a_go(char *last_move, char *name)
{
    strcpy(last_move, "") ;
    strcat(last_move, name) ;
    strcat(last_move, " layed miss a go card\n") ;
}

