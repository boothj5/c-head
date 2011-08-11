#include <stdlib.h>

// game constants
#define MAX_NUM_PLAYERS 20
#define MAX_DECK_SIZE 260
#define MAX_HAND_SIZE 100
#define MAX_TABLE_HAND_SIZE 10
#define DECK_SIZE 52

// player constants
#define MAX_NAME_LEN 10

// card data types
enum ranks { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
             JACK, QUEEN, KING, ACE } ;

enum suits { HEARTS, SPADES, DIAMONDS, CLUBS } ;

typedef struct {
    int rank ;
    int suit ;
} card ;

// player data types
enum player_types { HUMAN, COMPUTER } ;

typedef struct {
    char name[MAX_NAME_LEN] ;
    int type ;
    card hand[MAX_HAND_SIZE] ;
    int hand_size ;
    card face_up[MAX_TABLE_HAND_SIZE] ;
    int face_up_size ;
    card face_down[MAX_TABLE_HAND_SIZE] ;
    int face_down_size ;

} player ;

// card functions
void shuffle(card *, size_t) ;
void create_deck(card *, int) ;
char* show_rank(int) ;
char* show_suit(int) ;

// player functions
player make_player(char *, int) ;
void deal_to_hand(player *, card) ;
void deal_to_face_up(player *, card) ;
void deal_to_face_down(player *, card) ; 

// game functions
int cards_required(int, int) ;

// console functions
void show_welcome_msg();
void newline() ;
void newlines(int) ;
void clearscreen() ;
int request_num_players() ;
int request_num_cards_each() ;
void show_player(player *) ;
void show_players(player *, int) ;
void request_player_name(char *, int) ;
void show_cards(card *, int) ;
