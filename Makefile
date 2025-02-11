CFLAGS = -Wall -ansi -pedantic -c

all : juego_hormiga

juego_hormiga : game_loop.o game.o graphic_engine.o command.o game_actions.o space.o GameReader.o Object.o player.o
	gcc -o $@ $^ -L./ -lscreen

game_loop.o : game_loop.c command.h types.h game.h space.h player.h Object.h game_actions.h graphic_engine.h
	gcc $(CFLAGS) $^

game.o: game.c game.h command.h types.h space.h player.h Object.h GameReader.h
	gcc $(CFLAGS) $^

graphic_engine.o: graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h types.h space.h player.h Object.h libscreen.h
	gcc $(CFLAGS) $^

command.o: command.c command.h types.h
	gcc $(CFLAGS) $^

game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h player.h Object.h
	gcc $(CFLAGS) $^

space.o: space.c space.h types.h
	gcc $(CFLAGS) $^

GameReader.o: GameReader.c GameReader.h types.h game.h command.h space.h player.h Object.h
	gcc $(CFLAGS) $^

Object.o: Object.c Object.h types.h
	gcc $(CFLAGS) $^

player.o: player.c player.h types.h space.h
	gcc $(CFLAGS) $^

.PHONY: clean
clean:
	rm -f *.o juego_hormiga
run:
	./juego_hormiga anthill.dat