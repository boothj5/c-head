#include <head-unit.h>

#include "testsuite.h"
#include "last_move.h"

void test_last_move_miss_a_go(void)
{
    char last_move[100] = "" ;
    char name[10] = "James" ;

    set_last_move_was_miss_a_go(last_move, name) ;

    assert_string_equals("James layed miss a go card\n", last_move) ;
}
    
void register_last_move_tests(void)
{
    add_suite("test_last_move") ;
    add_test(test_last_move_miss_a_go, "test_last_move_miss_a_go") ;
}

