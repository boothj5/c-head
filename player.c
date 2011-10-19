#include <string.h>
#include "player.h"
#include "util.h"
#include "card.h"

struct player_t make_player(const char *name, const int type)
{
    struct player_t player ;
    strcpy(player.name, name) ;
    player.type = type ;
    player.hand_size = 0 ;
    player.face_up_size = 0 ;
    player.face_down_size = 0 ;
    return player ;
}

void deal_to_hand(struct player_t *player, const struct card_t card)
{
    add_card_to_cards(player->hand, &player->hand_size, card);
}

void deal_to_face_up(struct player_t *player, const struct card_t card)
{
    add_card_to_cards(player->face_up, &player->face_up_size, card);
}

void deal_to_face_down(struct player_t *player, const struct card_t card)
{
    add_card_to_cards(player->face_down, &player->face_down_size, card);
}

void remove_from_hand(struct player_t *player, const struct card_t card)
{
    remove_card_from_cards(player->hand, &player->hand_size, card);
}

void remove_from_face_up(struct player_t *player, const struct card_t card)
{
    remove_card_from_cards(player->face_up, &player->face_up_size, card);
}

void remove_from_face_down(struct player_t *player, const struct card_t card)
{
    remove_card_from_cards(player->face_down, &player->face_down_size, card);
}

void find_lowest_card_by_player(const struct player_t *players, const int num_players,
        struct card_t *cards)
{
    int i ;
    for (i = 0 ; i < num_players ; i++)
        cards[i] = find_lowest_card(players[i].hand, players[i].hand_size) ;
}

void swap(struct player_t *player, const int hand_index, const int faceup_index)
{
    struct card_t temp ;

    temp = player->hand[hand_index-1] ;
    player->hand[hand_index-1] = player->face_up[faceup_index-1] ;
    player->face_up[faceup_index-1] = temp ;
}

int has_cards(const struct player_t player)
{
    if (player.hand_size > 0)
        return TRUE ;
    if (player.face_up_size > 0)
        return TRUE ;
    if (player.face_down_size > 0)
        return TRUE ;
    return FALSE ;
}

