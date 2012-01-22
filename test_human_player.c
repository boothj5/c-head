#include <stdio.h>
#include <head-unit.h>

#include "player.h"

static void test_is_not_computer(void)
{
    struct player_t human = make_player("Human", 'h');
    assert_false(human.is_computer);
}

void register_human_player_tests(void)
{
    TEST_MODULE("test_human_player");
    TEST(test_is_not_computer);
}

