CC=gcc

c-head-make: card.o player.o console.o game.o c-head.o
	$(CC) -o ~/bin/c-head card.o player.o console.o game.o c-head.o
