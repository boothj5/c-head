#include <stdio.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "card.h"
#include "util.h"
#include "game_rules.h"

static int calc_deck_size(struct game_t game) ;
static void create_deck(struct game_t *game) ;
static void deal(struct game_t *game) ;
static void shuffle(struct game_t *game) ;

static int find_lowest_player(struct game_t *game, struct card_t lowest, 
                                        struct card_t *lowest_by_player) ;

static void add_to_pile(struct game_t *game, struct card_t c) ;

static void add_similar_cards(struct game_t *game, struct card_t lowest, 
    struct player_t *lowest_player, struct card_t *to_lay, int *ncards) ;

static void play_from_hand(struct game_t *game, struct player_t *player,
                                        struct card_t *to_lay, int ncards) ;

static void play_from_face_up(struct game_t *game, struct player_t *player,
                                        struct card_t *to_lay, int ncards) ;

static void play_from_face_down(struct game_t *game, struct player_t *player,
                                        struct card_t *to_lay, int ncards) ;

static void set_last_move(struct game_t *game, char *name, struct card_t *cards, 
                                                                   int ncards) ;

static void set_last_move_was_burn(struct game_t *game, char *name) ;

static int burn_cards_laid(struct game_t *game) ;

static void burn_pile(struct game_t *game) ;

static int miss_a_go_card_laid(struct game_t *game) ;

static void set_last_move_was_miss_a_go(struct game_t *game, char *name) ;

static void set_last_move_pickup(struct game_t *game, char *name) ;

struct game_t make_game(int nplayers, char names[][MAX_NAME_LEN], int ncards)
{
    int i ;    
    struct game_t game ;

    game.num_players = nplayers ;
    game.num_cards_each = ncards ;
    game.pile_size = 0 ;
    game.burnt_size = 0 ;
    game.current_player = 0 ;
    game.miss_a_go = FALSE ;
    for(i = 0 ; i<nplayers ; i++)
        game.players[i] = make_player(names[i], HUMAN) ;
    
    return game ;
}

void init_game(struct game_t *game)
{
    create_deck(game) ;
    shuffle(game) ;
    deal(game) ;
}

void first_move(struct game_t *game)
{
    int num_to_lay = 0 ;
    struct card_t lowest_by_player[game->num_players] ;
    struct card_t lowest ;
    struct card_t to_lay[MAX_HAND_SIZE] ;
    struct player_t *player ;

    find_lowest_card_by_player(game->players, game->num_players, lowest_by_player) ;
    lowest = find_lowest_card(lowest_by_player, game->num_players) ;
    game->current_player = find_lowest_player(game, lowest, lowest_by_player) ;
    player = &(game->players[game->current_player]) ;
    add_similar_cards(game, lowest, player, to_lay, &num_to_lay) ;
    play_from_hand(game, player, to_lay, num_to_lay) ;
    move_to_next_player(game) ;
    set_last_move(game, player->name, to_lay, num_to_lay) ;
}

void make_move(struct game_t *game, int card_choices[], int num_choices)
{
    int i = 0 ;
    struct card_t to_lay[num_choices] ;
    struct player_t *player = &game->players[game->current_player] ;

    if (player->hand_size > 0) {
        for (i = 0 ; i < num_choices ; i++) 
            to_lay[i] = player->hand[card_choices[i]] ;
        play_from_hand(game, player, to_lay, num_choices) ;
    }
    else if (player->face_up_size > 0) {
        for (i = 0 ; i < num_choices ; i++) 
            to_lay[i] = player->face_up[card_choices[i]] ;
        play_from_face_up(game, player, to_lay, num_choices) ;
    }
    else {
        for (i = 0 ; i < num_choices ; i++) 
            to_lay[i] = player->face_down[card_choices[i]] ;
        play_from_face_down(game, player, to_lay, num_choices) ;
    }
    
    if (burn_cards_laid(game)) {
        burn_pile(game) ;
        set_last_move_was_burn(game, player->name) ;
    }
    else if (miss_a_go_card_laid(game)) {
        game->miss_a_go = TRUE ;
        set_last_move_was_miss_a_go(game, player->name) ;
    }
    else {
        set_last_move(game, player->name, to_lay, num_choices) ;
    }
}

int continue_play(struct game_t game)
{
    int i, players_with_cards = 0 ;

    for (i = 0 ; i < game.num_players  ; i++)
        if (has_cards(game.players[i]))
            players_with_cards++ ;
    
    return (players_with_cards > 1) ;
}

struct player_t get_shithead(struct game_t game)
{
    int i ;
    
    for (i = 0 ; i < game.num_players ; i++)
        if (has_cards(game.players[i]))
            return game.players[i] ;

    return game.players[0] ;
}

void move_to_next_player(struct game_t *game) {
    if (game->current_player == game->num_players -1)
        game->current_player = 0 ;
    else
        game->current_player++ ;
    if (game->miss_a_go) {
        if (game->current_player == game->num_players -1)
            game->current_player = 0 ;
        else
            game->current_player++ ;
    }

    game->miss_a_go = FALSE ;
}

void pick_up_pile(struct game_t *game)
{
    struct player_t *player = &game->players[game->current_player] ;
    int i ;

    for (i = 0 ; i < game->pile_size ; i++) 
        deal_to_hand(player, game->pile[i]) ;

    game->pile_size = 0 ;
    set_last_move_pickup(game, player->name) ;
}

static int burn_cards_laid(struct game_t *game)
{
    struct card_t cards_on_pile[4] ;
    int num_cards = 0 ;
    int i ;
    
    if (game->pile_size > 0) {
        if (game->pile[game->pile_size-1].rank == BURN) {
            return TRUE ;
        }

        for (i = 0 ; i < 4 ; i++)
            if (game->pile_size > i) {
                cards_on_pile[i] = game->pile[game->pile_size-(i+1)] ;
                num_cards++ ;
            }

        if (num_cards == 4 && all_ranks_equal(cards_on_pile, num_cards)) {
            return TRUE ;
        }
    }
    
    return FALSE ;
}

static int miss_a_go_card_laid(struct game_t *game)
{
    if (game->pile_size > 0)
        if (game->pile[game->pile_size-1].rank == MISSAGO)
            return TRUE ;
    return FALSE ;
}

static void burn_pile(struct game_t *game)
{
    int i ;

    for (i = 0 ; i < game->pile_size ; i++)
        game->burnt[game->burnt_size++] = game->pile[i] ;
    game->pile_size = 0 ;
    game->current_player-- ;
}

static void set_last_move(struct game_t *game, char *name, 
                            struct card_t *cards, int ncards)
{
    int i ;
    
    strcpy(game->last_move, "") ;
    strcat(game->last_move, name) ;
    strcat(game->last_move, " laid: ") ;
    for (i = 0 ; i < ncards ; i++) {
        strcat(game->last_move, show_rank(cards[i])) ;
        strcat(game->last_move, " of ") ;
        strcat(game->last_move, show_suit(cards[i])) ;
        strcat(game->last_move, ", ") ;
    }
    strcat(game->last_move, "\n") ;
}

static void set_last_move_was_burn(struct game_t *game, char *name)
{
    strcpy(game->last_move, "") ;
    strcat(game->last_move, name) ;
    strcat(game->last_move, " burnt the deck\n") ;
}

static void set_last_move_pickup(struct game_t *game, char *name)
{
    strcpy(game->last_move, "") ;
    strcat(game->last_move, name) ;
    strcat(game->last_move, " picked up\n") ;
}

static void set_last_move_was_miss_a_go(struct game_t *game, char *name)
{
    strcpy(game->last_move, "") ;
    strcat(game->last_move, name) ;
    strcat(game->last_move, " layed miss a go card\n") ;
}

static void add_similar_cards(struct game_t *game, struct card_t lowest, 
        struct player_t *lowest_player, struct card_t *to_lay, int *ncards)
{
    int i ;

    for (i = 0 ; i < game->num_cards_each ; i++)
        if (lowest.rank == lowest_player->hand[i].rank)
            to_lay[(*ncards)++] = lowest_player->hand[i] ;
}

static int find_lowest_player(struct game_t *game, struct card_t lowest,
                                            struct card_t *lowest_by_player)
{
    int i ;
    int result = 0 ;

    for (i = 0 ; i < game->num_players ; i++)
        if (equals(lowest, lowest_by_player[i])) {
            result = i ;
            break ;
        }
    return result ;
}

static void play_from_hand(struct game_t *game, struct player_t *player, 
                                        struct card_t *to_lay, int ncards)
{
    int i ;
    for (i = 0 ; i < ncards ; i++) {
        add_to_pile(game, to_lay[i]) ;
        remove_from_hand(player, to_lay[i]) ;
        if (game->deck_size > 0 && player->hand_size < game->num_cards_each)
            deal_to_hand(player, game->deck[game->deck_size--]) ;
    }
}

static void play_from_face_up(struct game_t *game, struct player_t *player, 
                                        struct card_t *to_lay, int ncards)
{
    int i ;
    for (i = 0 ; i < ncards ; i++) {
        add_to_pile(game, to_lay[i]) ;
        remove_from_face_up(player, to_lay[i]) ;
    }
}

static void play_from_face_down(struct game_t *game, struct player_t *player, 
                                        struct card_t *to_lay, int ncards)
{
    int i ;
    for (i = 0 ; i < ncards ; i++) {
        add_to_pile(game, to_lay[i]) ;
        remove_from_face_down(player, to_lay[i]) ;
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

    game->deck_size = calc_deck_size(*game) ;
    num_decks = game->deck_size / DECK_SIZE ;
    
    for (j = 0 ; j < num_decks ; j++)
        for (suit = HEARTS ; suit <= CLUBS ; suit++)
            for (rank = TWO ; rank <= ACE ; rank++)
                game->deck[i++] = make_card(rank, suit) ;
}

static void shuffle(struct game_t *game)
{
    int i, j ;
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
    int i, j ;

    for (i = 0 ; i < game->num_players ; i++) {
        for (j = 0 ; j < game->num_cards_each ; j++) {
            struct player_t *player = &(game->players[i]) ;
            deal_to_hand(player, game->deck[--game->deck_size]) ;
            deal_to_face_up(player, game->deck[--game->deck_size]) ;
            deal_to_face_down(player, game->deck[--game->deck_size]) ;
        }
    }
}

static int calc_deck_size(struct game_t game)
{
    int decks_required, total_cards, div, add ;
    total_cards = game.num_players * (game.num_cards_each * 3) ;
    div = total_cards / DECK_SIZE ;
    add = ((total_cards % DECK_SIZE) > 0) ;
    decks_required = div + add ;
    return (decks_required * DECK_SIZE) ;
}
