CC=gcc
CFLAGS=-I ~/include -Werror -Wall -Wextra

make-c-head: card.o player.o console.o game.o c-head.o
	$(CC) -o c-head card.o player.o console.o game.o c-head.o

install: make-c-head
	cp c-head ~/bin/c-head

make-tests: testsuite.o test_card.o test_player.o card.o player.o
	$(CC) testsuite.o test_card.o test_player.o card.o player.o -I ~/include -L ~/lib -o testsuite -l headunit

test: make-tests
	./testsuite

clean:
	rm -f *.o
	rm -f c-head
	rm -f ~/bin/c-head
	rm -f testsuite
