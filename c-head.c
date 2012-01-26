#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "player.h"
#include "player_types.h"
#include "game.h"
#include "console.h"
#include "player_interaction.h"

#define THRESHOLD 10000

static void shuffle(struct player_type_t *players, int nplayers)
{
    int i, r;
    struct player_type_t t;

    if (nplayers > 1) {
        clock_t c = clock();
        srand(c) ;
        for (i = 0; i < nplayers; i++) {
            r = rand() / ( RAND_MAX / nplayers + 1 );
            t = players[i];
            players[i] = players[r];
            players[r] = t;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        struct game_t game;
        int nplayers, ncards;
        char names[MAX_NUM_PLAYERS][MAX_NAME_LEN];
        char types[MAX_NUM_PLAYERS];
        struct player_t shithead;
    
        clearscreen();
        show_welcome_msg();
        nplayers = request_num_players();
        ncards = request_num_cards_each();
        request_player_details(names, types, nplayers);

        game = make_game(nplayers, names, types, ncards);
        init_game(&game);
        perform_swap(&game);
        first_move(&game);

        while (continue_play(game)) {
            clearscreen();
            show_game_summary(game);
            if (player_on_last_cards(&game))
                perform_last_cards_move(&game);
            else
                perform_move(&game);
        }

        shithead = get_shithead(game);
        show_shithead(shithead);

        return 0;
    }
    else if (argc == 2) {
        int ngames = 0;
        int game = 0;
        int nplayers = 3;
        int ncards = 3;
        int stalemates = 0;

        ngames = atoi(argv[1]); 

        struct player_type_t ptypes[nplayers];

        struct player_type_t random;
        random.type = 'r';
        strcpy(random.name, "Random");

        struct player_type_t low;
        low.type = 'l';
        strcpy(low.name, "Low");

        struct player_type_t pyro;
        pyro.type = 'p';
        strcpy(pyro.name, "Pyro");

        ptypes[0] = random;
        ptypes[1] = low;
        ptypes[2] = pyro;

        clock_t start = clock();

        for (game = 0; game < ngames; game++) {
            char names[MAX_NUM_PLAYERS][MAX_NAME_LEN];
            char types[MAX_NUM_PLAYERS];

            shuffle(ptypes, 3); 
    
            int i;
            for (i = 0; i < nplayers; i++) {
                strcpy(names[i], ptypes[i].name);
                types[i] = ptypes[i].type;
            }
   
            struct game_t game = make_game(nplayers, names, types, ncards);
            //struct player_t shithead;

            init_game(&game);
            perform_swap(&game);
            first_move(&game);

            int moves = 0;
            while (continue_play(game) && moves < THRESHOLD) {
                if (player_on_last_cards(&game))
                    perform_last_cards_move(&game);
                else
                    perform_move(&game);
                moves++;
            }
        
            if (moves == THRESHOLD) {
                stalemates++;
            }

            //shithead = get_shithead(game);
    
            for (i = 0; i < nplayers; i++) {
                printf("%c", types[i]);
            }
            printf("\n");
        }

        clock_t end = clock();

        double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("TIME : %f\n", elapsed);

        return 0;
    } else {
        printf("Usage: c-head <num_games>\n");
        printf("    Omit num_games for interactive mode.\n");

        return 1;
    }
}
