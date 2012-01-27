#include <time.h>
#include <stdio.h>
#include <string.h>
#include "engines.h"
#include "player_types.h"
#include "game.h"
#include "player_interaction.h"
#include "util.h"

#define THRESHOLD 10000

static void shuffle(struct player_type_t *players, int nplayers)
{
    int i, r;
    struct player_type_t t;

    if (nplayers > 1) {
        srand(rdtsc()) ;
        for (i = 0; i < nplayers; i++) {
            r = rand() / ( RAND_MAX / nplayers + 1 );
            t = players[i];
            players[i] = players[r];
            players[r] = t;
        }
    }
}

static void initShMap(int shMap[])
{
    shMap[0] = 0;
    shMap[1] = 0;
    shMap[2] = 0;
}

static void addSh(char *name, int shMap[])
{
    if (strcmp(name, "Random") == 0)
        shMap[0]++;
    else if (strcmp(name, "Low") == 0)
        shMap[1]++;
    else
        shMap[2]++;
}

static void showSh(int shMap[], int ngames)
{
    float percent;

    percent = (double)shMap[0] / (double)ngames * 100.0;
    printf("%-20s%-10d%.2f%%\n", "Random", shMap[0], percent);
    
    percent = (double)shMap[1] / (double)ngames * 100.0;
    printf("%-20s%-10d%.2f%%\n", "Low", shMap[1], percent);
    
    percent = (double)shMap[2] / (double)ngames * 100.0;
    printf("%-20s%-10d%.2f%%\n", "Pyro", shMap[2], percent);
}

void run_battle_engine(int ngames)
{
    int game = 0;
    int nplayers = 3;
    int ncards = 3;
    int stalemates = 0;
    struct player_type_t ptypes[nplayers];
    int shMap[nplayers];

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

    initShMap(shMap);
    
    clock_t start = clock();

    for (game = 0; game < ngames; game++) {
        char names[MAX_NUM_PLAYERS][MAX_NAME_LEN];
        char types[MAX_NUM_PLAYERS];
        char shithead[MAX_NAME_LEN];

        shuffle(ptypes, 3); 

        int i;
        for (i = 0; i < nplayers; i++) {
            strcpy(names[i], ptypes[i].name);
            types[i] = ptypes[i].type;
        }

        struct game_t game = make_game(nplayers, names, types, ncards);

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

        get_shithead(game, shithead);

        addSh(shithead, shMap);

    }

    clock_t end = clock();
    double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;

    
    float stalemate_percent = (double)stalemates / (double)ngames * 100.0;

    printf("\n");
    printf("SUMMARY\n");
    printf("Total games : %d\n", ngames);
    printf("Total time : %f seconds\n", elapsed);
    printf("Stalemates : %d, %.2f%%\n", stalemates, stalemate_percent);

    printf("\n");
    printf("SCORES\n");
    printf("%-20s%-10s%s\n", "Name", "Shithead", "Lose rate");
    printf("------------------------------------------\n");
    
    showSh(shMap, ngames);

}
