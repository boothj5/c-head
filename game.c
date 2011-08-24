#include <stdio.h>
#include <string.h>
#include "game.h"
#include "card.h"

static int calc_decks_required(struct game_t *game) ;
static void calc_deck_size(struct game_t *game) ;
static void add_to_pile(struct game_t *game, struct card_t c) ;
static void create_deck(struct game_t *game) ;
static void deal(struct game_t *game) ;
static void shuffle(struct game_t *game) ;
static void play_from_hand(struct game_t *game, struct player_t *player, struct card_t *to_lay, int ncards) ;
static void find_lowest_by_player(struct game_t *game, struct card_t *lowest_by_player) ;
static struct player_t *find_lowest_player(struct game_t *game, struct card_t lowest, 
                                            struct card_t *lowest_by_player) ;
static void add_similar_cards(struct game_t *game, struct card_t lowest, 
                                struct player_t *lowest_player, struct card_t *to_lay, int *ncards) ;
static void set_last_move(struct game_t *game, char *name, struct card_t *cards, int ncards) ;

struct game_t *make_game(int nplayers, char names[MAX_NUM_PLAYERS][MAX_NAME_LEN], int ncards)
{
    int i ;    
    struct game_t *game = malloc(sizeof(struct game_t)) ;

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

void first_move(struct game_t *game)
{
    int i ;
    int num_to_lay = 0 ;
    struct card_t lowest_by_player[game->num_players] ;
    struct card_t lowest ;
    struct card_t to_lay[MAX_HAND_SIZE] ;
    struct player_t *lowest_player ;

    find_lowest_by_player(game, lowest_by_player) ;
    lowest = lowest_card(lowest_by_player, game->num_players) ;
    lowest_player = find_lowest_player(game, lowest, lowest_by_player) ;
    add_similar_cards(game, lowest, lowest_player, to_lay, &num_to_lay) ;
    play_from_hand(game, lowest_player, to_lay, num_to_lay) ;
    set_last_move(game, lowest_player->name, to_lay, num_to_lay) ;
}

static void set_last_move(struct game_t *game, char *name, struct card_t *cards, int ncards)
{
    int i ;
    
    strcpy(game->last_move, "") ;
    strcat(game->last_move, name) ;
    strcat(game->last_move, " laid: ") ;
    for (i = 0 ; i < ncards ; i++) {
        strcat(game->last_move, show_rank(cards[i])) ;
        strcat(game->last_move, " of ") ;
        strcat(game->last_move, show_suit(cards[i])) ;
        strcat(game->last_move, "\n") ;
    }
}

static void add_similar_cards(struct game_t *game, struct card_t lowest, 
                                struct player_t *lowest_player, struct card_t *to_lay, int *ncards)
{
    int i ;

    for (i = 0 ; i < game->num_cards_each ; i++)
        if (lowest.rank == lowest_player->hand[i].rank)
            to_lay[(*ncards)++] = lowest_player->hand[i] ;
}

static struct player_t *find_lowest_player(struct game_t *game, struct card_t lowest,
                                            struct card_t *lowest_by_player)
{
    int i ;
    struct player_t *result = &(game->players[0]) ;

    for (i = 0 ; i < game->num_players ; i++)
        if (equals(lowest, lowest_by_player[i])) {
            result = &(game->players[i]) ;
            break ;
        }
    return result ;
}

static void find_lowest_by_player(struct game_t *game, struct card_t *lowest_by_player)
{
    int i ;
    for (i = 0 ; i < game->num_players ; i++)
        lowest_by_player[i] = lowest_card(game->players[i].hand, game->players[i].hand_size) ;
}

static void play_from_hand(struct game_t *game, struct player_t *player, struct card_t *to_lay, int ncards)
{
    int i ;
    for (i = 0 ; i < ncards ; i++) {
        add_to_pile(game, to_lay[i]) ;
        remove_from_hand(player, to_lay[i]) ;
        deal_to_hand(player, game->deck[game->deck_size--]) ;
    }
}

static void add_to_pile(struct game_t *game, struct card_t c)
{
    game->pile[game->pile_size++] = c ;
}

static void create_deck(struct game_t *game)
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
            for (rank = TWO ; rank <= ACE ; rank++)
                game->deck[i++] = make_card(rank, suit) ;
}

static void shuffle(struct game_t *game)
{
    size_t i, j ;
    struct card_t t ;

    if (game->deck_size > 1) {
        srand((unsigned)time(NULL)) ;
        for (i = 0; i < game->deck_size - 1; i++) {
            j = i + rand() / (RAND_MAX / (game->deck_size - i) + 1);
            t = game->deck[j];
            game->deck[j] = game->deck[i];
            game->deck[i] = t;
        }
    }
}

static void deal(struct game_t *game)
{
    int i, j, k ;

    for (i = 0 ; i < game->num_players ; i++) {
        for (j = 0 ; j < game->num_cards_each ; j++) {
            struct player_t *player = &(game->players[i]) ;
            deal_to_hand(player, game->deck[--game->deck_size]) ;
            deal_to_face_up(player, game->deck[--game->deck_size]) ;
            deal_to_face_down(player, game->deck[--game->deck_size]) ;
        }
    }
}

static int calc_decks_required(struct game_t *game)
{
    int total_cards, result, div, add ;

    total_cards = game->num_players * (game->num_cards_each * 3) ;
    div = total_cards / DECK_SIZE ;
    add = ((total_cards % DECK_SIZE) > 0) ;
    result = div + add ;

    return result ;
}

static void calc_deck_size(struct game_t *game)
{
    int decks_required;

    decks_required = calc_decks_required(game) ;
    game->deck_size = decks_required * DECK_SIZE ;
}
