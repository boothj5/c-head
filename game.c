#include <stdio.h>
#include "game.h"
#include "card.h"

struct game_t {
    int num_players ;
    int num_cards_each ;
    int deck_size ;
    Player players[MAX_NUM_PLAYERS] ;
    Card deck[MAX_DECK_SIZE] ;
} ;

static int calc_decks_required(Game game) ;
static void calc_deck_size(Game game) ;
static void create_deck(Game game) ;
static void deal(Game game) ;
static void shuffle(Game game) ;

Game make_game(int nplayers, char names[MAX_NUM_PLAYERS][MAX_NAME_LEN], int ncards)
{
    int i ;    
    Game game = malloc(sizeof(struct game_t)) ;

    game->num_players = nplayers ;
    game->num_cards_each = ncards ;
    
    for(i = 0 ; i<nplayers ; i++) {
        game->players[i] = make_player(names[i], HUMAN) ;
    }
    
    create_deck(game) ;
    shuffle(game) ;
    deal(game) ;
    
    return game ;
}

int deck_size(Game game) 
{
    return game->deck_size ;
}

Player *players(Game game)
{
    return game->players ;
}

int num_players(Game game)
{
    return game->num_players ;
}

void first_move(Game game)
{
    int i ;
    Card lowest_by_player[game->num_players] ;
    Card lowest_card ;
    Player lowest_player ;
    Card to_lay[MAX_HAND_SIZE] ;
    int num_to_lay = 0 ;

    for (i = 0 ; i < game->num_players ; i++)
        lowest_by_player[i] = lowest(hand(game->players[i]), hand_size(game->players[i])) ;

    lowest_card = lowest(lowest_by_player, game->num_players) ;
    for (i = 0 ; i < game->num_players ; i++)
        if (equals(lowest_card, lowest_by_player[i]))
            lowest_player = game->players[i] ;
    
    for (i = 0 ; i < game->num_cards_each ; i++)
        if (rank(lowest_card) == rank(hand(lowest_player)[i]))
            to_lay[num_to_lay++] = hand(lowest_player)[i] ;

    printf("Lowest player = %s\n", player_name(lowest_player)) ;
    for (i = 0 ; i < num_to_lay ; i++)
        printf("\tCard = %s of %s\n", show_rank(to_lay[i]), show_suit(to_lay[i])) ;
}

static void create_deck(Game game)
{
    int num_decks ;
    enum cardrank rank ;
    enum cardsuit suit ;
    int i = 0 ;
    int j ;

    calc_deck_size(game) ;

    num_decks = game->deck_size / DECK_SIZE ;

    for (j = 0 ; j < num_decks ; j++)
        for (suit = HEARTS ; suit <= CLUBS ; suit++)
            for (rank = TWO ; rank <= ACE ; rank++) {
                game->deck[i] = make_card(rank, suit) ;
                i++ ;
            }
}

static void shuffle(Game game)
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

static void deal(Game game)
{
    int i ;
    int k ;
    for (i = 0 ; i < game->num_players ; i++) {
        int j ;
        for (j = 0 ; j < game->num_cards_each ; j++) {
            deal_to_hand(game->players[i], game->deck[--game->deck_size]) ;
            deal_to_face_up(game->players[i], game->deck[--game->deck_size]) ;
            deal_to_face_down(game->players[i], game->deck[--game->deck_size]) ;
        }
    }

}

static int calc_decks_required(Game game)
{
    int total_cards, result, div, add ;

    total_cards = game->num_players * (game->num_cards_each * 3) ;
    div = total_cards / DECK_SIZE ;
    add = ((total_cards % DECK_SIZE) > 0) ;
    result = div + add ;

    return result ;
}

static void calc_deck_size(Game game)
{
    int decks_required;
    decks_required = calc_decks_required(game) ;
    game->deck_size = decks_required * DECK_SIZE ;
}
