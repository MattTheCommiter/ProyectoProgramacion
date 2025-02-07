CFLAGS = -Wall -ansi -pedantic -c

all : juego_hormiga

juego_hormiga : game_loop.o game.o graphic_engine.o command.o game_actions.o space.o
	gcc -o $@ $^ -L./ -lscreen

game_loop.o : game_loop.c
	gcc $(CFLAGS) $^

game.o: game.c
	gcc $(CFLAGS) $^

graphic_engine.o: graphic_engine.c
	gcc $(CFLAGS) $^

command.o: command.c
	gcc $(CFLAGS) $^

game_actions.o: game_actions.c
	gcc $(CFLAGS) $^

space.o: space.c
	gcc $(CFLAGS) $^

.PHONY: clean
clean:
	rm -f *.o juego_hormiga