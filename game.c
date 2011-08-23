#include <stdio.h>
#include <string.h>
#include "game.h"
#include "card.h"

struct game_t {
    int num_players ;
    int num_cards_each ;
    int deck_size ;
    int pile_size ;
    struct player_t players[MAX_NUM_PLAYERS] ;
    struct card_t deck[MAX_DECK_SIZE] ;
    struct card_t pile[MAX_DECK_SIZE] ;
    char last_move[MAX_LAST_MOVE] ;
} ;

static int calc_decks_required(Game game) ;
static void calc_deck_size(Game game) ;
static void add_to_pile(Game game, struct card_t c) ;
static void create_deck(Game game) ;
static void deal(Game game) ;
static void shuffle(Game game) ;
static void play_from_hand(Game game, struct player_t *player, struct card_t *to_lay, int ncards) ;
static void find_lowest_by_player(Game game, struct card_t *lowest_by_player) ;
static struct player_t *find_lowest_player(Game game, struct card_t lowest, 
                                            struct card_t *lowest_by_player) ;
static void add_similar_cards(Game game, struct card_t lowest, 
                                struct player_t *lowest_player, struct card_t *to_lay, int *ncards) ;

Game make_game(int nplayers, char names[MAX_NUM_PLAYERS][MAX_NAME_LEN], int ncards)
{
    int i ;    
    Game game = malloc(sizeof(struct game_t)) ;

    game->num_players = nplayers ;
    game->num_cards_each = ncards ;
    game->pile_size = 0 ;
    
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

struct card_t *pile(Game game)
{
    return game->pile ;
}

int pile_size(Game game)
{
    return game->pile_size ;
}

char *last_move(Game game)
{
    return game->last_move ;
}

struct player_t *players(Game game)
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
    struct card_t lowest_by_player[game->num_players] ;
    struct card_t lowest ;
    struct player_t *lowest_player ;
    struct card_t to_lay[MAX_HAND_SIZE] ;
    int num_to_lay = 0 ;

    find_lowest_by_player(game, lowest_by_player) ;
    lowest = lowest_card(lowest_by_player, game->num_players) ;
    lowest_player = find_lowest_player(game, lowest, lowest_by_player) ;
    add_similar_cards(game, lowest, lowest_player, to_lay, &num_to_lay) ;
    play_from_hand(game, lowest_player, to_lay, num_to_lay) ;
    
    strcpy(game->last_move, "") ;
    strcat(game->last_move, lowest_player->name) ;
    strcat(game->last_move, " laid: ") ;
    for (i = 0 ; i < num_to_lay ; i++) {
        strcat(game->last_move, show_rank(to_lay[i])) ;
        strcat(game->last_move, " of ") ;
        strcat(game->last_move, show_suit(to_lay[i])) ;
        strcat(game->last_move, "\n") ;
    }
}

static void add_similar_cards(Game game, struct card_t lowest, 
                                struct player_t *lowest_player, struct card_t *to_lay, int *ncards)
{
    int i ;
    for (i = 0 ; i < game->num_cards_each ; i++)
        if (lowest.rank == lowest_player->hand[i].rank)
            to_lay[(*ncards)++] = lowest_player->hand[i] ;
}

static struct player_t *find_lowest_player(Game game, struct card_t lowest, struct card_t *lowest_by_player)
{
    struct player_t *result = &(game->players[0]) ;
    int i ;
    for (i = 0 ; i < game->num_players ; i++)
        if (equals(lowest, lowest_by_player[i])) {
            result = &(game->players[i]) ;
            break ;
        }
   
    return result ;
}

static void find_lowest_by_player(Game game, struct card_t *lowest_by_player)
{
    int i ;
    for (i = 0 ; i < game->num_players ; i++)
        lowest_by_player[i] = lowest_card(game->players[i].hand, game->players[i].hand_size) ;
}

static void play_from_hand(Game game, struct player_t *player, struct card_t *to_lay, int ncards)
{
    int i ;
    for (i = 0 ; i < ncards ; i++) {
        add_to_pile(game, to_lay[i]) ;
        remove_from_hand(player, to_lay[i]) ;
        deal_to_hand(player, game->deck[game->deck_size--]) ;
    }
}

static void add_to_pile(Game game, struct card_t c)
{
    game->pile[game->pile_size++] = c ;
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
          struct card_t t = game->deck[j];
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
            struct player_t *player = &(game->players[i]) ;
            deal_to_hand(player, game->deck[--game->deck_size]) ;
            deal_to_face_up(player, game->deck[--game->deck_size]) ;
            deal_to_face_down(player, game->deck[--game->deck_size]) ;
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
