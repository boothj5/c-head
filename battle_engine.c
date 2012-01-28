#include <time.h>
#include <stdio.h>
#include <string.h>
#include "engines.h"
#include "player_types.h"
#include "game.h"
#include "player_interaction.h"
#include "util.h"

#define THRESHOLD 10000

struct sh_count_t {
    struct player_type_t player;
    int count;
};

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

static void init_sh_counts(struct player_type_t ptypes[], struct sh_count_t counts[])
{
    struct sh_count_t random;
    random.player = ptypes[0];
    random.count = 0;
    counts[0] = random;
    
    struct sh_count_t low;
    low.player = ptypes[1];
    low.count = 0;
    counts[1] = low;
    
    struct sh_count_t pyro;
    pyro.player = ptypes[2];
    pyro.count = 0;
    counts[2] = pyro;
}

static void add_sh(char *name, struct sh_count_t counts[])
{
    if (strcmp(name, "Random") == 0)
        counts[0].count++;
    else if (strcmp(name, "Low") == 0)
        counts[1].count++;
    else
        counts[2].count++;
}

static int score_order(const void *count1, const void *count2)
{
    const struct sh_count_t *icount1 = (const struct sh_count_t *) count1;
    const struct sh_count_t *icount2 = (const struct sh_count_t *) count2;

    return icount1->count > icount2->count;
}

static void show_counts(struct sh_count_t counts[], int ngames)
{
    float percent;

    qsort(counts, 3, sizeof(struct sh_count_t), score_order);

    int i;
    for (i = 0; i < 3; i++) {
        percent = (double)counts[i].count / (double)ngames * 100.0;
        printf("%-20s%-10d%.0f%%\n", counts[i].player.name, counts[i].count, percent);
    }    
}

void run_battle_engine(int ngames)
{
    int game = 0;
    int nplayers = 3;
    int ncards = 3;
    int stalemates = 0;
    struct player_type_t ptypes[nplayers];
    struct sh_count_t sh_counts[nplayers];

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

    init_sh_counts(ptypes, sh_counts);
    
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
        while (continue_play(&game) && moves < THRESHOLD) {
            if (player_on_last_cards(&game))
                perform_last_cards_move(&game);
            else
                perform_move(&game);
            moves++;
        }
    
        if (moves == THRESHOLD) {
            stalemates++;
        }

        get_shithead(&game, shithead);

        add_sh(shithead, sh_counts);

    }

    clock_t end = clock();
    double totalmillis = ((double) (end - start)) / (CLOCKS_PER_SEC / 1000);
    char fmt_elapsed[100];
    format_millis(totalmillis, fmt_elapsed);
    
    float avg_game_millis = totalmillis / ngames;
    float stalemate_percent = (double)stalemates / (double)ngames * 100.0;

    printf("\n");
    printf("SUMMARY\n");
    printf("Total games : %d\n", ngames);
    printf("Total time : ");
    printf("%s\n", fmt_elapsed);
    printf("Average game: %.2f milliseconds\n", avg_game_millis);
    printf("Stalemates : %d, %.2f%%\n", stalemates, stalemate_percent);

    printf("\n");
    printf("SCORES\n");
    printf("%-20s%-10s%s\n", "Name", "Shithead", "Lose rate");
    printf("------------------------------------------\n");
    
    show_counts(sh_counts, ngames);

    printf("\n");
}
