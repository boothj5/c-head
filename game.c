#include <stdio.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "card.h"
#include "util.h"
#include "pile.h"

#include "game_rules.h"
#include "last_move.h"

static int calc_deck_size(const struct game_t game) ;
static void create_deck(struct game_t *game) ;
static void deal(struct game_t *game) ;
static void shuffle(struct game_t *game) ;
static int find_lowest_player(const struct game_t *game, const struct card_t lowest,
        const struct card_t *lowest_by_player) ;
static void add_similar_cards(const struct game_t *game, const struct card_t lowest,
        const struct player_t *lowest_player, struct card_t *to_lay, int *ncards) ;
static void play_from_hand(struct game_t *game, struct player_t *player, const struct card_t *to_lay,
        const int num_cards) ;
static void play_from_face_up(struct game_t *game, struct player_t *player, const struct card_t *to_lay,
        const int num_cards) ;
static void play_from_face_down(struct game_t *game, struct player_t *player, const struct card_t *to_lay,
        const int num_cards) ;
static void burn_pile(struct game_t *game) ;
static void update_last_move(struct game_t *game, struct card_t *cards, const int num_cards) ;

struct game_t make_game(const int num_players, char names[][MAX_NAME_LEN], const int num_cards)
{
    int i ;    
    struct game_t game ;

    game.num_players = num_players ;
    game.num_cards_each = num_cards ;
    game.pile_size = 0 ;
    game.burnt_size = 0 ;
    game.current_player = 0 ;
    game.miss_a_go = FALSE ;
    for(i = 0 ; i<num_players ; i++)
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
    set_last_move(game->last_move, player->name, to_lay, num_to_lay) ;
}

void make_move(struct game_t *game, const int card_choices[], const int num_choices)
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
   
    update_last_move(game, to_lay, num_choices) ;
}

static void update_last_move(struct game_t *game, struct card_t *cards, const int num_cards)
{
    struct player_t *player = &game->players[game->current_player] ;

    if (burn_cards_laid(game->pile, game->pile_size)) {
        burn_pile(game) ;
        set_last_move_was_burn(game->last_move, player->name) ;
    }
    else if (miss_a_go_card_laid(game->pile, game->pile_size)) {
        game->miss_a_go = TRUE ;
        set_last_move_was_miss_a_go(game->last_move, player->name) ;
    }
    else {
        set_last_move(game->last_move, player->name, cards, num_cards) ;
    }
}

int continue_play(const struct game_t game)
{
    int i, players_with_cards = 0 ;

    for (i = 0 ; i < game.num_players  ; i++)
        if (has_cards(game.players[i]))
            players_with_cards++ ;
    
    return (players_with_cards > 1) ;
}

struct player_t get_shithead(const struct game_t game)
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
    sort_cards(player->hand, player->hand_size) ;

    game->pile_size = 0 ;
    set_last_move_pickup(game->last_move, player->name) ;
}

static void burn_pile(struct game_t *game)
{
    int i ;

    for (i = 0 ; i < game->pile_size ; i++)
        game->burnt[game->burnt_size++] = game->pile[i] ;
    game->pile_size = 0 ;
    game->current_player-- ;
}

static void add_similar_cards(const struct game_t *game, const struct card_t lowest, const struct player_t *lowest_player,
        struct card_t *to_lay, int *num_cards)
{
    int i ;

    for (i = 0 ; i < game->num_cards_each ; i++)
        if (lowest.rank == lowest_player->hand[i].rank)
            to_lay[(*num_cards)++] = lowest_player->hand[i] ;
}

static int find_lowest_player(const struct game_t *game, const struct card_t lowest, const struct card_t *lowest_by_player)
{
    int i ;
    int result = 0 ;

    for (i = 0 ; i < game->num_players ; i++)
        if (cards_equal(lowest, lowest_by_player[i])) {
            result = i ;
            break ;
        }
    return result ;
}

static void play_from_hand(struct game_t *game, struct player_t *player, const struct card_t *to_lay, const int num_cards)
{
    int i ;
    for (i = 0 ; i < num_cards ; i++) {
        add_to_pile(game->pile, &game->pile_size, to_lay[i]) ;
        remove_from_hand(player, to_lay[i]) ;
        if (game->deck_size > 0 && player->hand_size < game->num_cards_each)
            deal_to_hand(player, game->deck[game->deck_size--]) ;
    }
    sort_cards(player->hand, player->hand_size) ;
}

static void play_from_face_up(struct game_t *game, struct player_t *player, const struct card_t *to_lay,
        const int num_cards)
{
    int i ;
    for (i = 0 ; i < num_cards ; i++) {
        add_to_pile(game->pile, &game->pile_size, to_lay[i]) ;
        remove_from_face_up(player, to_lay[i]) ;
    }
}

static void play_from_face_down(struct game_t *game, struct player_t *player, const struct card_t *to_lay,
        const int num_cards)
{
    int i ;
    for (i = 0 ; i < num_cards ; i++) {
        add_to_pile(game->pile, &game->pile_size, to_lay[i]) ;
        remove_from_face_down(player, to_lay[i]) ;
    }
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
    for (i = 0 ; i < game->num_players ; i++) {
        sort_cards(game->players[i].hand, game->players[i].hand_size) ;
    }

}

static int calc_deck_size(const struct game_t game)
{
    int decks_required, total_cards, div, add ;
    total_cards = game.num_players * (game.num_cards_each * 3) ;
    div = total_cards / DECK_SIZE ;
    add = ((total_cards % DECK_SIZE) > 0) ;
    decks_required = div + add ;
    return (decks_required * DECK_SIZE) ;
}
