#include <stdio.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "card.h"
#include "config.h"
#include "pile.h"
#include "util.h"
#include "game_rules.h"
#include "last_move.h"

static int calc_deck_size(const struct game_t *game)
{
    int decks_required, total_cards, div, add;
    
    total_cards = game->num_players * (game->num_cards_each * 3);
    div = total_cards / DECK_SIZE;
    add = ((total_cards % DECK_SIZE) > 0);
    decks_required = div + add;

    return (decks_required * DECK_SIZE);
}

static void create_deck(struct game_t *game)
{
    int num_decks;
    enum cardrank rank;
    enum cardsuit suit;
    int i = 0;
    int j;

    game->deck_size = calc_deck_size(game);
    num_decks = game->deck_size / DECK_SIZE;
    
    for (j = 0; j < num_decks; j++)
        for (suit = HEARTS; suit <= CLUBS; suit++)
            for (rank = TWO; rank <= ACE; rank++)
                game->deck[i++] = make_card(rank, suit);
}

static void deal(struct game_t *game)
{
    int i, j;
    struct player_t *player = NULL;
    struct card_t *deck = game->deck;
    int *deck_size = &game->deck_size;

    for (i = 0; i < game->num_players; i++) {
        player = &game->players[i];
        for (j = 0; j < game->num_cards_each; j++) {
            deal_to_hand(player, deck[*deck_size]);
            (*deck_size)--;
            deal_to_face_up(player, deck[*deck_size]);
            (*deck_size)--;
            deal_to_face_down(player, deck[*deck_size]);
            (*deck_size)--;
        }
        sort_cards(player->hand, player->hand_size);
    }
}

static void shuffle(struct game_t *game)
{
    int i, j;
    struct card_t t;

    if (game->deck_size > 1) {
        for (i = 0; i < game->deck_size; i++) {
            j = rand() / (RAND_MAX / game->deck_size + 1);
            t = game->deck[j];
            game->deck[j] = game->deck[i];
            game->deck[i] = t;
        }
    }
}

static void play_from_hand(struct game_t *game, const struct card_t *to_lay, 
    const int num_cards)
{
    int i;
    struct player_t *player = &game->players[game->current_player];

    for (i = 0; i < num_cards; i++) {
        add_to_pile(game->pile, &game->pile_size, to_lay[i]);
        remove_from_hand(player, &to_lay[i]);
        
        if (game->deck_size > 0 && (player->hand_size < game->num_cards_each)) {
            deal_to_hand(player, game->deck[game->deck_size-1]);
            game->deck_size--;
        }
    }

    sort_cards(player->hand, player->hand_size);
}

static void play_from_face_up(struct game_t *game, struct player_t *player,
    const struct card_t *to_lay, const int num_cards)
{
    int i;

    for (i = 0; i < num_cards; i++) {
        add_to_pile(game->pile, &game->pile_size, to_lay[i]);
        remove_from_face_up(player, &to_lay[i]);
    }
}

static void play_from_face_down(struct game_t *game, struct player_t *player,
    const struct card_t *to_lay, const int num_cards)
{
    int i;
    
    for (i = 0; i < num_cards; i++) {
        add_to_pile(game->pile, &game->pile_size, to_lay[i]);
        remove_from_face_down(player, &to_lay[i]);
    }
}

static void burn_pile(struct game_t *game)
{
    game->burnt += game->pile_size;
    game->pile_size = 0;
    game->current_player--;
}

static void update_last_move(struct game_t *game, struct card_t *cards,
    const int num_cards)
{
    struct player_t *player = &game->players[game->current_player];

    if (burn_cards_laid(game->pile, game->pile_size)) {
        burn_pile(game);
        set_last_move_was_burn(game->last_move, player->name);
    }
    else if (miss_a_go_card_laid(game->pile, game->pile_size)) {
        game->miss_a_go = TRUE;
        set_last_move_was_miss_a_go(game->last_move, player->name);
    }
    else {
        set_last_move(game->last_move, player->name, cards, num_cards);
    }
}

struct game_t make_game(const int num_players, char names[][MAX_NAME_LEN], char types[],
    const int num_cards)
{
    int i;    
    struct game_t game;

    game.num_players = num_players;
    game.num_cards_each = num_cards;
    game.pile_size = 0; 
    game.deck_size = 0;
    game.burnt = 0;
    game.current_player = 0;
    game.miss_a_go = FALSE;

    for(i = 0; i<num_players; i++)
        game.players[i] = make_player(names[i], types[i]);
    
    return game;
}

void init_game(struct game_t *game)
{
    create_deck(game);
    shuffle(game);
    deal(game);
}

void first_move(struct game_t *game)
{
    int num_to_lay = 0;
    struct card_t lowest;
    struct card_t to_lay[MAX_HAND_SIZE];

    game->current_player = 0;
    struct card_t current_lowest = game->players[game->current_player].hand[0];
    int i;
    for (i = 1; i < game->num_players; i++) {
        struct card_t player_lowest = game->players[i].hand[0];
        if (card_cmp(&player_lowest, &current_lowest) == LT)
            game->current_player = i;
    }

    lowest = game->players[game->current_player].hand[0];
    for (i = 0; i < game->num_cards_each; i++)
        if (lowest.rank == game->players[game->current_player].hand[i].rank)
            to_lay[num_to_lay++] = game->players[game->current_player].hand[i];

    play_from_hand(game, to_lay, num_to_lay);
    set_last_move(game->last_move, game->players[game->current_player].name, 
        to_lay, num_to_lay);
    move_to_next_player(game);
}

void make_move(struct game_t *game, const int card_choices[], const int num_choices)
{
    int i = 0;
    struct card_t to_lay[num_choices];
    struct player_t *player = &game->players[game->current_player];

    if (player->hand_size > 0) {
        for (i = 0 ; i < num_choices ; i++) 
            to_lay[i] = player->hand[card_choices[i]];

        play_from_hand(game, to_lay, num_choices);
    }
    else if (player->face_up_size > 0) {
        for (i = 0; i < num_choices; i++) 
            to_lay[i] = player->face_up[card_choices[i]];

        play_from_face_up(game, player, to_lay, num_choices);
    }
    else {
        for (i = 0; i < num_choices; i++)
            to_lay[i] = player->face_down[card_choices[i]];

        play_from_face_down(game, player, to_lay, num_choices);
    }

    update_last_move(game, to_lay, num_choices);
}

void make_move_from_face_down(struct game_t *game, const int face_down_choice)
{
    struct card_t to_lay[1];
    struct player_t *player = &game->players[game->current_player];

    to_lay[0] = player->face_down[face_down_choice];
    play_from_face_down(game, player, to_lay, 1);
    update_last_move(game, to_lay, 1);
}

int continue_play(const struct game_t *game)
{
    int i, players_with_cards = 0;

    for (i = 0; i < game->num_players; i++)
        if (has_cards(&game->players[i]))
            players_with_cards++;
    
    return (players_with_cards > 1);
}

void get_shithead(const struct game_t *game, char *name)
{
    int i;
    
    for (i = 0; i < game->num_players; i++)
        if (has_cards(&game->players[i])) {
            strcpy(name, game->players[i].name);
            return;
        }
    strcpy(name, game->players[0].name);
}

void move_to_next_player(struct game_t *game) 
{
    game->current_player++;
    if (game->current_player == game->num_players)
        game->current_player = 0;
    while (!has_cards(&game->players[game->current_player])) {
        game->current_player++;
        if (game->current_player == game->num_players)
            game->current_player = 0;
    }

    if (game->miss_a_go) {
        game->current_player++;
        if (game->current_player == game->num_players)
            game->current_player = 0;
        while (!has_cards(&game->players[game->current_player])) {
            game->current_player++;
            if (game->current_player == game->num_players)
                game->current_player = 0;
        }
    }

    game->miss_a_go = FALSE;
}

void pick_up_pile(struct game_t *game)
{
    struct player_t *player = &game->players[game->current_player];
    int i;

    for (i = 0; i < game->pile_size; i++) 
        deal_to_hand(player, game->pile[i]);
    
    sort_cards(player->hand, player->hand_size);

    game->pile_size = 0;
    set_last_move_pickup(game->last_move, player->name);
}

void pick_up_pile_and_face_down(struct game_t *game, const int face_down_choice)
{
    struct player_t *player = &game->players[game->current_player];
    const struct card_t card = player->face_down[face_down_choice];

    pick_up_pile(game);
    deal_to_hand(player, card);
    sort_cards(player->hand, player->hand_size);
    remove_from_face_down(player, &card);
}

int player_on_last_cards(const struct game_t *game)
{
    const struct player_t player = game->players[game->current_player];

    return ((player.hand_size == 0) && (player.face_up_size == 0));
}

struct player_helper_t get_player_helper(const struct game_t *game)
{
    struct player_helper_t helper = make_helper(game->pile, game->pile_size);

    return helper;
}
