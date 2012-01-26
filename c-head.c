#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "player.h"
#include "player_types.h"
#include "game.h"
#include "console.h"
#include "player_interaction.h"
#include "engines.h"

#define THRESHOLD 10000

int main(int argc, char *argv[])
{
    if (argc == 1) {
        run_cli_engine();
        return 0;
    }
    else if (argc == 2) {
        int ngames = atoi(argv[1]);
        run_battle_engine(ngames);
        return 0;
    } else {
        printf("Usage: c-head <num_games>\n");
        printf("    Omit num_games for interactive mode.\n");
        return 1;
    }
}
