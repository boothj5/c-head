#include <stdio.h>
#include <string.h>
#include "player.h"
#include "game.h"
#include "console.h"

static void show_players(const struct player_t *players, const int num_players) ;
static void show_pile(const struct card_t *cards, const int num_cards) ;
static void show_deck(const int num_cards) ;
static void show_burnt(const int num_cards) ;
static void show_last_move(const char *move) ;
static int parse_choice(char choice[], int card_choices[], int *num_choices) ;
static int str_to_bool(char *choice) ;

void newline()
{
    printf("\n") ;
}

void newlines(const int num)
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

void show_player(struct player_t player)
{
    printf("Player name : %s", player.name) ;
    newline() ;
    if (player.hand_size > 0) {
        printf("HAND     : ") ;
        show_cards(player.hand, player.hand_size) ;
    }
    if (player.face_up_size > 0) {
        printf("FACE UP  : ") ;
        show_cards(player.face_up, player.face_up_size) ;
    }
    if (player.face_down_size > 0) {
        printf("FACE DOWN: ") ;
        show_cards(player.face_down, player.face_down_size) ;
    }
}

static void show_players(const struct player_t *players, const int num_players)
{
    int i ;
    for (i = 0 ; i < num_players ; i++)  {
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

void request_player_names(char names[][MAX_NAME_LEN], const int num_players)
{
    char *name = malloc(sizeof(char) * MAX_NAME_LEN) ;
    int i ;
    
    for (i = 0 ; i < num_players ; i++) {
        printf("Enter name for player %d :", i+1) ;
        newline() ;
        scanf("%s", name) ;
        strcpy(names[i], name) ;
    }
    free(name) ;
    
    newline() ;
}

void show_cards(const struct card_t *cards, const int num_cards)
{
    int i ;
    int j = 1 ;

    for (i = 0 ; i< num_cards ; i++) {
        printf("(%d)%s of %s", j, show_rank(cards[i]), show_suit(cards[i])) ;
        if (j <= (num_cards - 1))
            printf(", ") ;
        else
            newline() ;
        j++ ;
    }
}

static void show_deck(const int num_cards)
{
    printf("%d left on deck", num_cards) ;
    newlines(2) ;
}

static void show_burnt(const int num_cards)
{
    printf("%d burnt", num_cards) ;
    newlines(2) ;
}

static void show_pile(const struct card_t *cards, const int num_cards)
{   
    int i ;
    int j = 1 ;

    printf("%d on pile:", num_cards) ;
    newline() ;
    
    for (i = (num_cards-1) ; i >= 0 ; i--) {
        printf("\t") ;
        if (i == (num_cards-1))
            printf("(*)") ;
        printf("%s of %s", show_rank(cards[i]), show_suit(cards[i])) ;
        newline() ;
        j++ ;
    }
    newline() ;
}

static void show_last_move(const char *move)
{
    printf(move) ;
}

int request_swap_cards(const char *name)
{
    int result ;    
    char *choice = malloc(sizeof(char) * 2) ;
    newline() ;
    printf("%s, would you like to swap cards (y/n) : ", name) ;
    scanf("%s", choice) ; 
    result = str_to_bool(choice) ;
    free(choice) ;
    return result ;
}

int request_swap_more(const char *name)
{
    int result = 0 ;
    char *choice = malloc(sizeof(char) * 2) ;
    newline() ;
    printf("%s, swap more (y/n) : ", name) ;
    scanf("%s", choice) ; 
    result = str_to_bool(choice) ;
    free(choice) ;

    return result ;
}

static int str_to_bool(char *choice)
{
    return ((strcmp(choice, "y") == 0) | (strcmp(choice, "Y") == 0));
}

int request_hand_swap(const int size)
{
    int choice ;
    printf("Hand card to swap (1-%d): ", size) ;
    scanf("%d", &choice) ;
    return choice ;
}

int request_faceup_swap(const int size)
{
    int choice ;
    printf("Face up card to swap (1-%d): ", size) ;
    scanf("%d", &choice) ;
    return choice ;
}

void show_game_summary(const struct game_t game)
{
    show_pile(game.pile, game.pile_size) ;
    show_deck(game.deck_size) ;
    show_burnt(game.burnt_size) ;
    show_players(game.players, game.num_players) ;
    show_last_move(game.last_move) ;
}

void request_move(const struct player_t player, int card_choices[], int *num_choices)
{
    char entered[10] ;
    printf("%s, choose cards to lay: ", player.name) ;
    scanf("%s", entered) ;

    while (!parse_choice(entered, card_choices, num_choices)) {
        *num_choices = 0 ;
        newline() ;
        printf("Enter card choices seperated by commas.") ;
        newlines(2) ;
        printf("%s, choose cards to lay: ", player.name) ;
        scanf("%s", entered) ;
    }
}

void show_shithead(const struct player_t player)
{
    newline() ;
    printf("!!!! GAME OVER !!!!") ;
    newlines(2) ;
    printf("SHITHEAD == %s", player.name) ;
    newlines(2) ;
}

static int parse_choice(char choice[], int card_choices[], int *num_choices)
{
    char *result = NULL;
    int to_int ;
    result = strtok(choice, "," );
    while( result != NULL ) {
        to_int = atoi(result) ;
        if (to_int == 0) {
            return 0 ;
        }
        else {
            card_choices[(*num_choices)++] = to_int-1 ;
            result = strtok( NULL, "," );
        }
    }
    return 1 ;
}

void wait_user()
{
    int ch;
    do
        ch = fgetc(stdin) ; 
    while (ch != EOF && ch != '\n'); 
    clearerr(stdin);
    fflush(stdout);
    getchar() ;
}

void show_bad_move(void)
{
    newline() ;
    printf("You can't do that, try again") ;
    newline() ;
}

void show_pickup(const char *name)
{
    newline() ;
    printf("Oh dear, %s, you must pick up, press enter.", name) ;
    newline() ;
}
