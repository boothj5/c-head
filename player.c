#include <string.h>
#include "player.h"
#include "player_types.h"
#include "card.h"

struct player_t make_player(const char *name, const char type)
{
    struct player_t player;
    strcpy(player.name, name);

    if (type == 'h')
        player.is_computer = FALSE;
    else
        player.is_computer = TRUE;

    player.hand_size = 0;
    player.face_up_size = 0;
    player.face_down_size = 0;

    switch(type) {
    case 'l':
        player.ask_swap_cards = lowcardplayer_ask_swap_cards;
        player.ask_swap_choice = lowcardplayer_ask_swap_choice;
        player.ask_move = lowcardplayer_ask_move;
        player.ask_face_down_move = lowcardplayer_ask_face_down_move;
        break;
    case 'h':
        player.ask_swap_cards = human_ask_swap_cards;
        player.ask_swap_choice = human_ask_swap_choice;
        player.ask_move = human_ask_move;
        player.ask_face_down_move = human_ask_face_down_move;
        break;
    default:
        player.ask_swap_cards = NULL;
        player.ask_swap_choice = NULL;
        player.ask_move = NULL;
        player.ask_face_down_move = NULL;
    }

    return player;
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

void find_lowest_card_by_player(const struct player_t *players, 
    const int num_players, struct card_t *cards)
{
    int i;
    for (i = 0 ; i < num_players ; i++)
        cards[i] = find_lowest_card(players[i].hand, players[i].hand_size);
}

void swap(struct player_t *player, const struct swap_choice_t choice)
{
    struct card_t temp;

    temp = player->hand[choice.hand_choice-1];
    player->hand[choice.hand_choice-1] = player->face_up[choice.faceup_choice-1];
    player->face_up[choice.faceup_choice-1] = temp;
    sort_cards(player->hand, player->hand_size);

}

int has_cards(const struct player_t player)
{
    if (player.hand_size > 0)
        return TRUE;
    if (player.face_up_size > 0)
        return TRUE;
    if (player.face_down_size > 0)
        return TRUE;
    return FALSE;
}

int has_cards_in_hand(const struct player_t player)
{
    return player.hand_size > 0;
}

int ask_swap_cards(const struct player_t player)
{
    return player.ask_swap_cards(player);
}

struct swap_choice_t ask_swap_choice(const struct player_t player)
{
    return player.ask_swap_choice(player);
}

void ask_move(const struct player_t player, const struct player_helper_t helper,
    int card_choices[], int *nchoices)
{
    return player.ask_move(player, helper, card_choices, nchoices);
}

int ask_face_down_move(const struct player_t player)
{
    return player.ask_face_down_move();
}
