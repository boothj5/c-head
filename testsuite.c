#include <head-unit.h>
#include "testsuite.h"

int main(void)
{
    register_card_tests() ;
    register_player_tests() ;
    register_game_rules_tests() ;
    run_tests() ;
    return 0 ;
}
