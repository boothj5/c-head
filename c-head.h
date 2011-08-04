// player
#define MAX_NAME_LEN 10

enum player_types { HUMAN, COMPUTER } ;

typedef struct {
    char name[MAX_NAME_LEN] ;
    int type ;
} player ;

player make_player(char *, int) ;

// console
void clearscreen() ;
int request_num_players() ;
int request_num_cards_each() ;
void show_player(player *) ;
void show_players(player *, int) ;

