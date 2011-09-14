#include <stdio.h>
#include <string.h>

#include "player.h"
#include "game.h"
#include "console.h"

static void show_players(struct player_t *players, int len) ;
static void show_pile(struct card_t *cards, int ncards) ;
static void show_deck(int num_cards) ;
static void show_last_move(char *move) ;

void newline()
{
    printf("\n") ;
}

void newlines(int num)
{
    int i ;
    for (i = 0 ; i < num ; i++)
        newline() ;
}

void show_welcome_msg()
{
    printf("Welcome to C-Head!") ;
    newlines(2) ;
}

void show_player(struct player_t p)
{
    printf("Player name : %s", p.name) ;
    newline() ;
    if (p.hand_size > 0) {
        printf("HAND     : ") ;
        show_cards(p.hand, p.hand_size) ;
    }
    if (p.face_up_size > 0) {
        printf("FACE UP  : ") ;
        show_cards(p.face_up, p.face_up_size) ;
    }
    if (p.face_down_size > 0) {
        printf("FACE DOWN: ") ;
        show_cards(p.face_down, p.face_down_size) ;
    }
}

static void show_players(struct player_t *players, int len) 
{
    int i ;
    for (i = 0 ; i < len ; i++)  {
        show_player(players[i]) ;
        newline() ;
    }
}

void clearscreen() 
{
    newlines(100) ;
}

int request_num_players()
{
    int result ;
    printf("Enter number of players : ") ;
    scanf("%d", &result) ;
    return result ;
}

int request_num_cards_each()
{
    int result ;
    printf("Enter number of cards each : ") ;
    scanf("%d", &result) ;
    return result ;
}

void request_player_names(char names[][MAX_NAME_LEN], int nplayers)
{
    char *name = malloc(sizeof(char) * MAX_NAME_LEN) ;
    int i ;
    
    for (i = 0 ; i < nplayers ; i++) {
        printf("Enter name for player %d :", i+1) ;
        newline() ;
        scanf("%s", name) ;
        strcpy(names[i], name) ;
    }
    free(name) ;
    
    newline() ;
}

void show_cards(struct card_t *cards, int num_cards) 
{
    int i ;
    int j = 1 ;

    for (i = 0 ; i< num_cards ; i++) {
        printf("(%d)%s of %s", j, show_rank(cards[i]), show_suit(cards[i])) ;
        if (j <= (num_cards - 1))
            printf(", ") ;
        else
            printf("\n") ;
        j++ ;
    }
}

static void show_deck(int num_cards) 
{
    printf("%d left on deck", num_cards) ;
    newlines(2) ;
}

static void show_pile(struct card_t *cards, int ncards)
{   
    int i ;
    int j = 1 ;

    printf("%d on pile:\n", ncards) ;
    
    for (i = (ncards-1) ; i >= 0 ; i--) {
        printf("\t") ;
        if (i == (ncards-1))
            printf("(*)") ;
        printf("%s of %s", show_rank(cards[i]), show_suit(cards[i])) ;
        if (j <= (ncards - 1))
            printf("\n") ;
        else
            printf("\n") ;
        j++ ;
    }
    newline() ;
}

static void show_last_move(char *move) 
{
    printf(move) ;
}

int request_swap_cards(char *name)
{
    int result ;    
    char *choice = malloc(sizeof(char) * 2) ;
    newline() ;
    printf("%s, would you like to swap cards (y/n) : ", name) ;
    scanf("%s", choice) ; 
    result = ((strcmp(choice, "y") == 0) | (strcmp(choice, "Y") == 0)) ;
    free(choice) ;
    return result ;
}

int request_swap_more(char *name)
{
    int result = 0 ;
    char *choice = malloc(sizeof(char) * 2) ;
    newline() ;
    printf("%s, swap more (y/n) : ", name) ;
    scanf("%s", choice) ; 
    result = ((strcmp(choice, "y") == 0) | (strcmp(choice, "Y") == 0)) ;
    free(choice) ;

    return result ;
}

int request_hand_swap(int size)
{
    int choice ;
    printf("Hand card to swap (1-%d): ", size) ;
    scanf("%d", &choice) ;
    return choice ;
}

int request_faceup_swap(int size)
{
    int choice ;
    printf("Face up card to swap (1-%d): ", size) ;
    scanf("%d", &choice) ;
    return choice ;
}

void show_game_summary(struct game_t game)
{
    show_pile(game.pile, game.pile_size) ;
    show_deck(game.deck_size) ;
    show_players(game.players, game.num_players) ;
    show_last_move(game.last_move) ;
}

int request_move(struct player_t player)
{
    int choice ;
    printf("%s, choose cards to lay: ", player.name) ;
    scanf("%d", &choice) ;
    return choice ;
}

void show_shithead(struct player_t player)
{
    printf("\n!!!! GAME OVER !!!!\n") ;
    printf("\nSHITHEAD == %s\n\n", player.name) ;
}
