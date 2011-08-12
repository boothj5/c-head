#include "game.h"

static int calc_decks_required(Game *game) ;

void calc_cards_required(Game *game)
{
    int decks_required;
    decks_required = calc_decks_required(game) ;
    game->deck_size = decks_required * DECK_SIZE ;
}

void deal(Game *game)
{
    int i ;
    int k ;
    for (i = 0 ; i < game->num_players ; i++) {
        int j ;
        for (j = 0 ; j < game->num_cards_each ; j++) {
            deal_to_hand(&game->players[i], game->deck[--game->deck_size]) ;
            deal_to_face_up(&game->players[i], game->deck[--game->deck_size]) ;
            deal_to_face_down(&game->players[i], game->deck[--game->deck_size]) ;
        }
    }

}


static int calc_decks_required(Game *game)
{
    int total_cards, result, div, add ;

    total_cards = game->num_players * (game->num_cards_each * 3) ;
    div = total_cards / DECK_SIZE ;
    add = ((total_cards % DECK_SIZE) > 0) ;
    result = div + add ;

    return result ;
}
