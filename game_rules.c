#include "game_rules.h"
#include "card.h"
#include "player.h"
#include "util.h"
#include "game.h"

static int can_lay(struct card_t card, struct card_t *pile, int pile_size) ;

static int can_move_with_hand(struct player_t player, struct card_t *pile, int pile_size) ;

static int can_move_with_face_up(struct player_t player, struct card_t *pile, int pile_size) ;

int valid_move(struct game_t game, int card_choices[], int num_choices)
{
    struct card_t to_lay[50] ;
    int num_to_lay = 0 ;
    int i ;
    struct player_t *player = &game.players[game.current_player] ;

    // return false if no choices
    if (num_choices == 0) 
        return FALSE ;

    // return false if number chosen greater than hand size
    if (num_choices > player->hand_size) 
        return FALSE ;
    // return false if any of the choices are bigger than the hand size    
    for (i = 0 ; i < num_choices ; i++) 
        if (card_choices[i] >= player->hand_size)
            return FALSE ;
    
    // get the cards to lay
    for (i = 0 ; i < num_choices ; i++)
        to_lay[num_to_lay++] = player->hand[card_choices[i]] ;
    
    // return false if the cards are not of the same rank
    if (!all_ranks_equal(to_lay, num_to_lay))
        return FALSE ;

    // return false if the first card cannot be laid
    if (!can_lay(player->hand[card_choices[0]], game.pile, game.pile_size))
        return FALSE ;
  
    // return true otherwise    
    return TRUE ;
}

int can_move(struct game_t game)
{
    struct player_t player = game.players[game.current_player] ;

    if (player.hand_size > 0) 
        if (can_move_with_hand(player, game.pile, game.pile_size))
            return TRUE ;
        else
            return FALSE ;
    else if (player.face_up_size > 0) 
        if (can_move_with_face_up(player, game.pile, game.pile_size))
            return TRUE ;
        else
            return FALSE ;
    else 
        return FALSE ;
}

static int can_lay(struct card_t card, struct card_t *pile, int pile_size)
{
    if (pile_size == 0)
        return TRUE ;
    else if (special_card(card))
        return TRUE ;
    else if (pile[pile_size-1].rank == TWO)
        return TRUE ;
    else if (pile[pile_size-1].rank == INVISIBLE)
        return can_lay(card, pile, pile_size-1) ;
    else if (card_cmp(card, pile[pile_size-1]) == EQ )
        return TRUE ;
    else if (card_cmp(card, pile[pile_size-1]) == GT)
        return TRUE ;
    else
        return FALSE ;
}

static int can_move_with_hand(struct player_t player, struct card_t *pile, int pile_size)
{
    int i ;

    for (i = 0 ; i < player.hand_size ; i++)
        if (can_lay(player.hand[i], pile, pile_size))
            return TRUE ;

    return FALSE ;
}

static int can_move_with_face_up(struct player_t player, struct card_t *pile, int pile_size)
{
    int i ;

    for (i = 0 ; i < player.face_up_size ; i++)
        if (can_lay(player.face_up[i], pile, pile_size))
            return TRUE ;

    return FALSE ;
}
