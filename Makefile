CFLAGS = -Wall -ansi -pedantic -c

all : juego_hormiga

juego_hormiga : game_loop.o game.o graphic_engine.o command.o game_actions.o space.o GameReader.o object.o player.o character.o
	gcc -o $@ $^ -L./ -lscreen

game.o: game.c game.h command.h types.h space.h player.h object.h GameReader.h
	gcc $(CFLAGS) $^

game_loop.o: game_loop.c command.h types.h game.h space.h player.h object.h game_actions.h graphic_engine.h
	gcc $(CFLAGS) $^
	
graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h types.h space.h player.h object.h libscreen.h
	gcc $(CFLAGS) $^

command.o: command.c command.h types.h
	gcc $(CFLAGS) $^

game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h player.h object.h
	gcc $(CFLAGS) $^

space.o: space.c space.h types.h
	gcc $(CFLAGS) $^

GameReader.o: GameReader.c GameReader.h types.h game.h command.h space.h player.h object.h
	gcc $(CFLAGS) $^

object.o: object.c object.h types.h
	gcc $(CFLAGS) $^

player.o: player.c player.h types.h space.h
	gcc $(CFLAGS) $^
	
caracter.o: character.c character.h types.h 
	gcc $(CFLAGS) $^

.PHONY: clean run runV 

clean:
	rm -f *.o *.gch juego_hormiga set_test_exec
run:
	./juego_hormiga anthill.dat
runV:
	valgrind --leak-check=full ./juego_hormiga anthill.dat

run_test_set: set_test_exec

set_test_exec: set_test.o set.o
	gcc -o $@ $^ 

set_test.o: set_test.c set.h types.h set_test.h test.h
	gcc $(CFLAGS) $^
	
set.o: set.c set.h types.h
	gcc $(CFLAGS) $^
