#include <head-unit.h>
#include "testsuite.h"

int main(void)
{
    register_card_tests() ;
    register_player_tests() ;
    register_game_rules_tests() ;
    register_game_tests() ;
    register_last_move_tests() ;
    register_pile_tests() ; ;
    run_suite() ;
    return 0 ;
}
