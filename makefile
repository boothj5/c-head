CC = gcc
CFLAGS = -I ~/include -O3 -Wall -Wextra -Werror -Wno-unused-parameter
TESTLIB = -L ~/lib -l headunit
CPPLIB = -lstdc++
OBJS = card.o player.o console.o game.o game_rules.o last_move.o \
	   pile.o c-head.o human_player.o lowcard_player.o random_player.o \
       pyromaniac.o player_interaction.o cli_engine.o battle_engine.o util.o \
	   card_choosers.o
TESTOBJS = test_card.o card.o \
		   test_player.o player.o \
           test_human_player.o human_player.o \
           test_lowcard_player.o lowcard_player.o \
		   test_game_rules.o game_rules.o \
		   test_pile.o pile.o \
		   test_last_move.o last_move.o \
		   test_game.o game.o \
		   test_random_player.o random_player.o \
           pyromaniac.o util.o card_choosers.o

c-head: $(OBJS)
	$(CC) -o c-head $(OBJS)

card.o: card.h config.h
player.o: player.h player_types.h card.h config.h game.h
human_player.o: player_types.h player.h config.h
lowcard_player.o: player_types.h config.h card_choosers.h player.h
pyromaniac.o: player_types.h player.h config.h card_choosers.h
random_player.o: player_types.h player.h config.h util.h card_choosers.h
player_interaction.o: player_interaction.h game.h player.h console.h game_rules.h
console.o: console.h player.h game.h
game.o: game.h card.h pile.h game_rules.h last_move.h config.h util.h
game_rules.o: game_rules.h card.h player.h config.h game.h
last_move.o: last_move.h
pile.o: pile.h config.h game.h pile.h
cli_engine.o: game.h console.h player_interaction.h config.h engines.h
battle_engine.o: engines.h player_types.h game.h player_interaction.h util.h
util.o: util.h

c-head.o: player.h game.h console.h player_interaction.h player_types.h \
		  engines.h

test_card.o: card.h
test_player.o: player.h card.h
test_human_player.o: player.h
test_lowcard_player.o: player.h card.h
test_random_player.o: player.h
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

