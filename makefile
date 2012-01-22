CC = gcc
CFLAGS = -I ~/include -O3 -Wall -Wextra -Werror -Wno-unused-parameter
TESTLIB = -L ~/lib -l headunit
CPPLIB = -lstdc++
OBJS = card.o player.o console.o game.o game_rules.o last_move.o \
	   pile.o c-head.o human_player.o lowcard_player.o
TESTOBJS = test_card.o card.o \
		   test_player.o player.o \
           test_human_player.o human_player.o \
		   test_game_rules.o game_rules.o \
		   test_pile.o pile.o \
		   test_last_move.o last_move.o \
		   test_game.o game.o \
		   lowcard_player.o

c-head: $(OBJS)
	$(CC) -o c-head $(OBJS)

card.o: card.h util.h
player.o: player.h player_types.h card.h util.h
human_player.o: player_types.h player.h util.h
lowcard_player.o: player_types.h player.h util.h
console.o: console.h player.h game.h
game.o: game.h card.h util.h pile.h game_rules.h last_move.h
game_rules.o: game_rules.h card.h player.h util.h game.h
last_move.o: last_move.h
pile.o: pile.h util.h game.h pile.h

c-head.o: player.h card.h game.h game_rules.h console.h

test_card.o: card.h
test_player.o: player.h card.h
test_human_player.o: player.h
test_game_rules.o: game_rules.h game.h player.h
test_pile.o: pile.h
test_last_move.o: last_move.h
test_game.o: game.h

testsuite: testsuite.h $(TESTOBJS)
	$(CC) $(CFLAGS) $(CPPLIB) testsuite.c $(TESTOBJS) -o testsuite $(TESTLIB)

.PHONY: install
install: c-head
	cp c-head ~/bin/c-head

.PHONY: test
test: testsuite
	./testsuite

.PHONY: clean
clean:
	rm -f *.o
	rm -f c-head
	rm -f testsuite

.PHONY: run
run: clean install
	c-head

.PHONY: memcheck
memcheck: clean install
	valgrind --leak-check=full c-head

