CC=gcc
CFLAGS=-I ~/include -Werror -Wall -Wextra

compile: card.o player.o console.o game.o c-head.o
	$(CC) -o c-head card.o player.o console.o game.o c-head.o

install: compile
	cp c-head ~/bin/c-head

compile-tests: testsuite.o test_card.o test_player.o test_game.o card.o player.o game.o
	$(CC) testsuite.o test_card.o test_player.o test_game.o card.o player.o game.o -I ~/include -L ~/lib -o testsuite -l headunit

test: compile-tests
	./testsuite

clean:
	rm -f *.o
	rm -f c-head
	rm -f ~/bin/c-head
	rm -f testsuite

run: clean install
	c-head

memcheck: clean install
	valgrind --leak-check=full c-head

