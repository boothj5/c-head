#include <stdio.h>
#include <head-unit.h>

#include "card.h"

void test_three_lowest_when_last(void)
{
    struct card_t ten = make_card(TEN, HEARTS) ;
    struct card_t six = make_card(SIX, CLUBS) ;
    struct card_t three = make_card(THREE, DIAMONDS) ;
    struct card_t cards[] = { ten, six, three } ;

    struct card_t lowest = find_lowest_card(cards, 3) ;
    assert_int_equals(THREE, lowest.rank) ;
}

void test_three_lowest_when_middle(void)
{
    struct card_t ten = make_card(TEN, HEARTS) ;
    struct card_t three = make_card(THREE, DIAMONDS) ;
    struct card_t six = make_card(SIX, CLUBS) ;
    struct card_t cards[] = { ten, three, six } ;

    struct card_t lowest =  find_lowest_card(cards, 3) ;
    assert_int_equals(THREE, lowest.rank) ;
}

void test_three_lowest_when_first(void)
{
    struct card_t three = make_card(THREE, DIAMONDS) ;
    struct card_t ten = make_card(TEN, HEARTS) ;
    struct card_t six = make_card(SIX, CLUBS) ;
    struct card_t cards[] = { three, ten, six } ;

    struct card_t lowest =  find_lowest_card(cards, 3) ;
    assert_int_equals(THREE, lowest.rank) ;
}

void test_lowest_one_card(void)
{
    struct card_t ten = make_card(TEN, HEARTS) ;
    struct card_t cards[] = { ten } ;

    struct card_t lowest =  find_lowest_card(cards, 1) ;
    assert_int_equals(TEN, lowest.rank) ;
}   

void test_three_lower_than_two(void)
{
    struct card_t three = make_card(THREE, DIAMONDS) ;
    struct card_t two = make_card(TWO, HEARTS) ;
    struct card_t cards[] = { three, two } ;

    struct card_t lowest = find_lowest_card(cards, 2) ;
    assert_int_equals(THREE, lowest.rank) ;
}

void test_five_lower_than_two(void)
{
    struct card_t five = make_card(FIVE, DIAMONDS) ;
    struct card_t two = make_card(TWO, HEARTS) ;
    struct card_t cards[] = { five, two } ;

    struct card_t lowest = find_lowest_card(cards, 2) ;
    assert_int_equals(FIVE, lowest.rank) ;
}

void test_jack_lower_than_seven(void)
{
    struct card_t jack = make_card(JACK, DIAMONDS) ;
    struct card_t seven = make_card(SEVEN, HEARTS) ;
    struct card_t cards[] = { jack, seven } ;

    struct card_t lowest = find_lowest_card(cards, 2) ;
    assert_int_equals(JACK, lowest.rank) ;
}

void test_two_special(void)
{
    assert_true(special_card(make_card(TWO, DIAMONDS))) ;
}

void test_seven_special(void)
{
    assert_true(special_card(make_card(SEVEN, DIAMONDS))) ;
}

void test_ten_special(void)
{
    assert_true(special_card(make_card(TEN, DIAMONDS))) ;
}

void test_ranks_equal(void)
{
    struct card_t tend = make_card(TEN, DIAMONDS) ;
    struct card_t tenh = make_card(TEN, HEARTS) ;

    assert_true(ranks_equal(tend, tenh)) ;
}

void test_ranks_not_equal(void)
{
    struct card_t ten = make_card(TEN, DIAMONDS) ;
    struct card_t ace = make_card(ACE, HEARTS) ;

    assert_false(ranks_equal(ten, ace)) ;
}

void test_all_ranks_equal(void)
{
    struct card_t threed = make_card(THREE, DIAMONDS) ;     
    struct card_t threes = make_card(THREE, SPADES) ;     
    struct card_t threeh = make_card(THREE, HEARTS) ;     
    struct card_t threec = make_card(THREE, CLUBS) ; 
    struct card_t cards[4] = { threed, threes, threeh, threec } ;

    assert_true(all_ranks_equal(cards, 4)) ;
}

void test_all_ranks_not_equal(void)
{
    struct card_t threed = make_card(THREE, DIAMONDS) ;     
    struct card_t threes = make_card(THREE, SPADES) ;     
    struct card_t threeh = make_card(THREE, HEARTS) ;     
    struct card_t fourc = make_card(FOUR, CLUBS) ; 
    struct card_t cards[4] = { threed, threes, threeh, fourc } ;

    assert_false(all_ranks_equal(cards, 4)) ;
}

void test_remove_card_from_cards_decrements_size(void)
{
    int num_cards = 5 ;
    struct card_t cards[num_cards] ;
    cards[0] = make_card(THREE, DIAMONDS) ;
    cards[1] = make_card(TWO, DIAMONDS) ;
    cards[2] = make_card(NINE, HEARTS) ;
    cards[3] = make_card(SEVEN, SPADES) ;
    cards[4] = make_card(JACK, CLUBS) ;
    remove_card_from_cards(cards, &num_cards, make_card(NINE, HEARTS)) ;

    assert_int_equals(4, num_cards) ;
}

void test_remove_card_from_cards_removes_card(void)
{
    int num_cards = 5 ;
    struct card_t cards[num_cards] ;
    cards[0] = make_card(THREE, DIAMONDS) ;
    cards[1] = make_card(TWO, DIAMONDS) ;
    cards[2] = make_card(NINE, HEARTS) ;
    cards[3] = make_card(SEVEN, SPADES) ;
    cards[4] = make_card(JACK, CLUBS) ;
    remove_card_from_cards(cards, &num_cards, make_card(NINE, HEARTS)) ;

    int i ;
    int found = 0 ;
    for (i = 0 ; i < num_cards ; i++) {
        if (cards_equal(cards[i], make_card(NINE, HEARTS))) {
            found = 1 ;
            break ;
        }
    }
    assert_false(found) ;
}

void test_add_card_to_cards_increments_size(void)
{
    int num_cards = 5 ;
    struct card_t cards[num_cards] ;
    cards[0] = make_card(THREE, DIAMONDS) ;
    cards[1] = make_card(TWO, DIAMONDS) ;
    cards[2] = make_card(NINE, HEARTS) ;
    cards[3] = make_card(SEVEN, SPADES) ;
    cards[4] = make_card(JACK, CLUBS) ;
    add_card_to_cards(cards, &num_cards, make_card(ACE, HEARTS)) ;

    assert_int_equals(6, num_cards) ;
}

void test_add_card_to_cards_adds_card(void)
{
    int num_cards = 5 ;
    struct card_t cards[num_cards] ;
    cards[0] = make_card(THREE, DIAMONDS) ;
    cards[1] = make_card(TWO, DIAMONDS) ;
    cards[2] = make_card(NINE, HEARTS) ;
    cards[3] = make_card(SEVEN, SPADES) ;
    cards[4] = make_card(JACK, CLUBS) ;
    add_card_to_cards(cards, &num_cards, make_card(TWO, SPADES)) ;

    int i ;
    int found = 0 ;
    for (i = 0 ; i < num_cards ; i++) {
        if (cards_equal(cards[i], make_card(TWO, SPADES))) {
            found = 1 ;
            break ;
        }
    }
    assert_true(found) ;
}

void test_sort_cards(void) {
    int num_cards = 5 ;
    struct card_t cards[num_cards] ;

    cards[0] = make_card(ACE, DIAMONDS) ;
    cards[1] = make_card(THREE, HEARTS) ;
    cards[2] = make_card(TWO, SPADES) ;
    cards[3] = make_card(KING, CLUBS) ;
    cards[4] = make_card(EIGHT, SPADES) ;

    sort_cards(cards, num_cards) ;

    assert_true(cards_equal(cards[0], make_card(THREE, HEARTS)) &&
                cards_equal(cards[1], make_card(EIGHT, SPADES)) &&
                cards_equal(cards[2], make_card(KING, CLUBS)) &&
                cards_equal(cards[3], make_card(ACE, DIAMONDS)) &&
                cards_equal(cards[4], make_card(TWO, SPADES)) ) ;
}

void register_card_tests()
{
    add_suite("test_card") ;
    add_test(test_three_lowest_when_last, "test_three_lowest_when_last" ) ;
    add_test(test_three_lowest_when_middle, "test_three_lowest_when_middle") ;
    add_test(test_three_lowest_when_first, "test_three_lowest_when_first") ;
    add_test(test_lowest_one_card, "test_lowest_one_card") ;
    add_test(test_three_lower_than_two, "test_three_lower_than_two") ;
    add_test(test_five_lower_than_two, "test_five_lower_than_two") ;
    add_test(test_jack_lower_than_seven, "test_jack_lower_than_seven") ;
    add_test(test_two_special, "test_two_special") ;
    add_test(test_seven_special, "test_seven_special") ;
    add_test(test_ten_special, "test_ten_special") ;
    add_test(test_ranks_equal, "test_ranks_equal") ;
    add_test(test_ranks_not_equal, "test_ranks_not_equal") ;
    add_test(test_all_ranks_equal, "test_all_ranks_equal") ;
    add_test(test_all_ranks_not_equal, "test_all_ranks_not_equal") ;
    add_test(test_remove_card_from_cards_decrements_size, "test_remove_card_from_cards_decrements_size") ;
    add_test(test_remove_card_from_cards_removes_card, "test_remove_card_from_cards_removes_card") ;
    add_test(test_add_card_to_cards_increments_size, "test_add_card_to_cards_increments_size") ;
    add_test(test_add_card_to_cards_adds_card, "test_add_card_to_cards_adds_card") ;
    add_test(test_sort_cards, "test_sort_cards") ;
}

