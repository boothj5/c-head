#include "game.h"

static int calc_decks_required(Game *game) ;
static void calc_deck_size(Game *game) ;

void create_deck(Game *game)
{
    int num_decks ;
    int rank, suit ;
    int i = 0 ;
    int j ;

    calc_deck_size(game) ;

    num_decks = game->deck_size / DECK_SIZE ;

    for (j = 0 ; j < num_decks ; j++) {
        for (suit = 0 ; suit <= 3 ; suit++) {
            for (rank = 2 ; rank <= 14 ; rank++) {
                game->deck[i] = make_card(rank, suit) ;
                //Card a_card ;
                //a_card.rank = rank ;
                //a_card.suit = suit ;
                //game->deck[i] = a_card ;
                i++ ;
            }
        }
    }
}

void shuffle(Game *game)
{
    if (game->deck_size > 1) {
        srand((unsigned)time(NULL)) ;
        size_t i;
        for (i = 0; i < game->deck_size - 1; i++) {
          size_t j = i + rand() / (RAND_MAX / (game->deck_size - i) + 1);
          Card t = game->deck[j];
          game->deck[j] = game->deck[i];
          game->deck[i] = t;
        }
    }
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

static void calc_deck_size(Game *game)
{
    int decks_required;
    decks_required = calc_decks_required(game) ;
    game->deck_size = decks_required * DECK_SIZE ;
}
