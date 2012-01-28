#include <stdio.h>
#include <head-unit.h>

#include "player.h"

static void test_is_computer(void)
{
    struct player_t random = make_player("Random", 'r');
    assert_true(random.is_computer);
}

static void doesnt_swap_cards(void)
{
    struct player_t random = make_player("Random", 'r');
    assert_false(ask_swap_cards(&random));
}

static void always_chooses_first_face_down(void)
{
    struct player_t random = make_player("Random", 'r');
    assert_int_equals(1, random.ask_face_down_move());
}

void register_random_player_tests(void)
{
    TEST_MODULE("test_random_player");
    TEST(test_is_computer);
    TEST(doesnt_swap_cards);
    TEST(always_chooses_first_face_down);
}


