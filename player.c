#include <string.h>
#include "player.h"

struct player_t make_player(char *name, int type) 
{
    struct player_t player ;
    strcpy(player.name, name) ;
    player.type = type ;
    player.hand_size = 0 ;
    player.face_up_size = 0 ;
    player.face_down_size = 0 ;
    return player ;
}

void deal_to_hand(struct player_t *p, struct card_t c)
{
    p->hand[p->hand_size++] = c ;
}

void deal_to_face_up(struct player_t *p, struct card_t c)
{
    p->face_up[p->face_up_size++] = c ;
}

void deal_to_face_down(struct player_t *p, struct card_t c)
{
    p->face_down[p->face_down_size++] = c ;
}

void remove_from_hand(struct player_t *p, struct card_t c)
{
    int i, j ;
    for (i = 0 ; i < p->hand_size ; i++)
        if (equals(p->hand[i], c)) {
            for (j = i+1 ; j < p->hand_size ; j++)
                p->hand[j-1] = p->hand[j] ;
            p->hand_size-- ;
            break ;
        }
}

void find_lowest_card_by_player(struct player_t *ps, 
                                int nplayers, 
                                struct card_t *cs)
{
    int i ;
    for (i = 0 ; i < nplayers ; i++)
        cs[i] = find_lowest_card(ps[i].hand, ps[i].hand_size) ;
}

void swap(struct player_t *p, int hand_c, int faceup_c)
{
    struct card_t temp ;

    temp = p->hand[hand_c-1] ;
    p->hand[hand_c-1] = p->face_up[faceup_c-1] ;
    p->face_up[faceup_c-1] = temp ;
}

int has_cards(struct player_t player)
{
    if (player.hand_size > 0)
        return 1 ;
    if (player.face_up_size > 0)
        return 1 ;
    if (player.face_down_size > 0)
        return 1 ;
    return 0 ;
}

