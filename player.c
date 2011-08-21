#include <string.h>
#include "player.h"

struct player_t {
    char name[MAX_NAME_LEN] ;
    int type ;
    Card hand[MAX_HAND_SIZE] ;
    int hand_size ;
    Card face_up[MAX_TABLE_HAND_SIZE] ;
    int face_up_size ;
    Card face_down[MAX_TABLE_HAND_SIZE] ;
    int face_down_size ;
} ;

Player make_player(char *name, int type) 
{
    Player player = malloc(sizeof(struct player_t)) ;
    strcpy(player->name, name) ;
    player->type = type ;
    player->hand_size = 0 ;
    player->face_up_size = 0 ;
    player->face_down_size = 0 ;
    return player ;
}

void deal_to_hand(Player p, Card c)
{
    p->hand[p->hand_size++] = c ;
}

void deal_to_face_up(Player p, Card c)
{
    p->face_up[p->face_up_size++] = c ;
}

void deal_to_face_down(Player p, Card c)
{
    p->face_down[p->face_down_size++] = c ;
}

char *player_name(Player p) 
{
    return p->name ;
}

int hand_size(Player p)
{
    return p->hand_size ;
}

int face_up_size(Player p)
{
    return p->face_up_size ;
}

int face_down_size(Player p)
{
    return p->face_down_size ;
}

Card *hand(Player p)
{
    return p->hand ;
}

Card *face_up(Player p)
{
    return p->face_up ;
} 

Card *face_down(Player p)
{
    return p->face_down ;
}  

void remove_from_hand(Player p, Card c)
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
