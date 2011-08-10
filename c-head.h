// player contants
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
} player ;

// card functions
void create_deck(card *, int) ;
int cards_required(int) ;

// player functions
player make_player(char *, int) ;

// game functions
int calc_decks_required(int, int) ;

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
void show_deck(card *, int) ;
