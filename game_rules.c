#include "game_rules.h"
#include "card.h"
#include "player.h"
#include "util.h"
#include "game.h"

static int can_lay(const struct card_t card, const struct card_t *pile, const int pile_size) ;
static int can_move_with_hand(const struct player_t player, const struct card_t *pile, const int pile_size) ;
static int can_move_with_face_up(const struct player_t player, const struct card_t *pile, const int pile_size) ;
static int valid_move_with_given_hand(const struct game_t game, const int card_choices[], const int num_choices,
        const struct card_t *cards, const int cards_size) ;
static int choice_not_in_cards(const int num_choices, const int card_choices[], const int cards_size) ;
static int cannot_lay_first_card(const struct card_t *cards, const int card_choices[], const struct game_t game) ;
static int empty_pile(const int pile_size) ;
static int two_on_pile(const struct card_t *pile, const int pile_size) ;
static int card_higher_than_pile(const struct card_t card, const struct card_t *pile, const int pile_size) ;
static int seven_on_pile(const struct card_t *pile, const int pile_size) ;

int valid_move(struct game_t game, const int card_choices[], const int num_choices)
{
    const struct player_t *player = &game.players[game.current_player] ;

    if (player->hand_size > 0)
        return valid_move_with_given_hand(game, card_choices, num_choices, player->hand, player->hand_size) ;
    else if (player->face_up_size > 0)
        return valid_move_with_given_hand(game, card_choices, num_choices, player->face_up, player->face_up_size) ;
    else
        return FALSE ;
}

int can_move(const struct game_t game)
{
    const struct player_t player = game.players[game.current_player] ;

    if (player.hand_size > 0) 
        return can_move_with_hand(player, game.pile, game.pile_size) ;
    else if (player.face_up_size > 0) 
        return can_move_with_face_up(player, game.pile, game.pile_size) ;
    else 
        return FALSE ;
}

static int valid_move_with_given_hand(const struct game_t game, const int card_choices[], const int num_choices,
        const struct card_t *cards, const int cards_size)
{
    struct card_t to_lay[50] ;
    int num_to_lay = 0 ;
    int i = 0 ;

    if ((num_choices > cards_size) || (choice_not_in_cards(num_choices, card_choices, cards_size)))
        return FALSE ;

    for (i = 0 ; i < num_choices ; i++)
        to_lay[num_to_lay++] = cards[card_choices[i]] ;
        
    if ((!all_ranks_equal(to_lay, num_to_lay)) || (cannot_lay_first_card(cards, card_choices, game)))
        return FALSE ;

    return TRUE ;
}

static int cannot_lay_first_card(const struct card_t *cards, const int card_choices[], const struct game_t game) {
    return (!can_lay(cards[card_choices[0]], game.pile, game.pile_size)) ;
}

static int choice_not_in_cards(const int num_choices, const int card_choices[], const int cards_size) {
    int i ;
    for (i = 0 ; i < num_choices ; i++)
        if (card_choices[i] >= cards_size)
            return TRUE ;
    return FALSE ;
}

static int can_lay(const struct card_t card, const struct card_t *pile, const int pile_size)
{
    if ((empty_pile(pile_size)) || (special_card(card)) || (two_on_pile(pile, pile_size)) ||
            (ranks_equal(card, pile[pile_size-1])) || (card_higher_than_pile(card, pile, pile_size)))
        return TRUE ;
    else if (seven_on_pile(pile, pile_size))
        return can_lay(card, pile, pile_size-1) ;
    else
        return FALSE ;
}

static int empty_pile(const int pile_size) {
    return (pile_size == 0) ;
}

static int two_on_pile(const struct card_t *pile, const int pile_size) {
    return (pile[pile_size-1].rank == TWO) ;
}

static int card_higher_than_pile(const struct card_t card, const struct card_t *pile, const int pile_size) {
    return (card_cmp(&card, &pile[pile_size-1]) == GT) ;
}

static int seven_on_pile(const struct card_t *pile, const int pile_size) {
    return (pile[pile_size-1].rank == SEVEN) ;
}

static int can_move_with_hand(const struct player_t player, const struct card_t *pile, const int pile_size)
{
    int i ;
    for (i = 0 ; i < player.hand_size ; i++)
        if (can_lay(player.hand[i], pile, pile_size))
            return TRUE ;
    return FALSE ;
}

static int can_move_with_face_up(const struct player_t player, const struct card_t *pile, const int pile_size)
{
    int i ;
    for (i = 0 ; i < player.face_up_size ; i++)
        if (can_lay(player.face_up[i], pile, pile_size))
            return TRUE ;
    return FALSE ;
}
