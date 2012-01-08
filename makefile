CC=gcc
CFLAGS=-I ~/include -Werror -Wall -Wextra

compile: card.o player.o console.o game.o game_rules.o last_move.o pile.o c-head.o
	$(CC) -o c-head card.o player.o console.o game.o game_rules.o last_move.o pile.o c-head.o

install: compile
	cp c-head ~/bin/c-head

compile-tests: testsuite.o test_card.o test_player.o test_game_rules.o test_pile.o test_last_move.o last_move.o pile.o test_game.o card.o player.o game.o game_rules.o
	$(CC) -lstdc++ testsuite.o test_card.o test_player.o test_game_rules.o test_pile.o test_last_move.o test_game.o pile.o card.o player.o game.o game_rules.o last_move.o -I ~/include -L ~/lib -o testsuite -l headunit

test: compile-tests
	./testsuite

clean:
	rm -f *.o
	rm -f c-head
	rm -f testsuite

run: clean install
	c-head

memcheck: clean install
	valgrind --leak-check=full c-head

