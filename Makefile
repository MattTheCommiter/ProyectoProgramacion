CFLAGS=-Wall -ansi -pedantic -g
SRCDIR=./src
OBJDIR=./obj
LIBDIR=./lib
INCDIR=./include
DOCDIR=./doc
INC=-Iinclude
CLIBS=-L$(LIBDIR) -lscreen
EXE=juego_hormiga tests

#make - compile game 
all: juego_hormiga

#make tests - compile every test
tests: character_test set_test space_test inventory_test

#make general - compile both game and tests
general: $(EXE)

###################################################### GAME EXECUTABLE ######################################################
juego_hormiga : $(OBJDIR)/inventory.o $(OBJDIR)/game_loop.o $(OBJDIR)/game.o $(OBJDIR)/graphic_engine.o $(OBJDIR)/command.o $(OBJDIR)/game_actions.o $(OBJDIR)/space.o $(OBJDIR)/gameReader.o $(OBJDIR)/object.o $(OBJDIR)/player.o $(OBJDIR)/character.o $(OBJDIR)/set.o 
	gcc -g -o $@ $^ $(CLIBS)



###################################################### OBJECTS NEEDED FOR GAME ######################################################
$(OBJDIR)/game.o: $(SRCDIR)/game.c $(INCDIR)/game.h $(INCDIR)/command.h $(INCDIR)/types.h $(INCDIR)/space.h $(INCDIR)/player.h $(INCDIR)/object.h $(INCDIR)/gameReader.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/game_loop.o: $(SRCDIR)/game_loop.c $(INCDIR)/command.h $(INCDIR)/types.h $(INCDIR)/game.h $(INCDIR)/space.h $(INCDIR)/player.h $(INCDIR)/object.h $(INCDIR)/game_actions.h $(INCDIR)/graphic_engine.h
	gcc $(INC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/graphic_engine.o: $(SRCDIR)/graphic_engine.c $(INCDIR)/graphic_engine.h $(INCDIR)/game.h $(INCDIR)/command.h $(INCDIR)/types.h $(INCDIR)/space.h $(INCDIR)/player.h $(INCDIR)/object.h $(INCDIR)/libscreen.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/command.o: $(SRCDIR)/command.c $(INCDIR)/command.h $(INCDIR)/types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/game_actions.o: $(SRCDIR)/game_actions.c $(INCDIR)/game_actions.h $(INCDIR)/command.h $(INCDIR)/types.h $(INCDIR)/game.h $(INCDIR)/space.h $(INCDIR)/player.h $(INCDIR)/object.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/space.o: $(SRCDIR)/space.c $(INCDIR)/space.h $(INCDIR)/types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/gameReader.o: $(SRCDIR)/gameReader.c $(INCDIR)/gameReader.h $(INCDIR)/types.h $(INCDIR)/game.h $(INCDIR)/command.h $(INCDIR)/space.h $(INCDIR)/player.h $(INCDIR)/object.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/object.o: $(SRCDIR)/object.c $(INCDIR)/object.h $(INCDIR)/types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/player.o: $(SRCDIR)/player.c $(INCDIR)/player.h $(INCDIR)/types.h $(INCDIR)/space.h $(INCDIR)/inventory.h
	gcc $(INC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/character.o: $(SRCDIR)/character.c $(INCDIR)/character.h $(INCDIR)/types.h 
	gcc $(INC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/set.o: $(SRCDIR)/set.c $(INCDIR)/set.h $(INCDIR)/types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/inventory.o: $(SRCDIR)/inventory.c $(INCDIR)/inventory.h $(INCDIR)/types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@



###################################################### OBJECTS NEEDED FOR TESTS ######################################################
$(OBJDIR)/set_test.o: $(SRCDIR)/set_test.c $(INCDIR)/set.h $(INCDIR)/types.h $(INCDIR)/set_test.h $(INCDIR)/test.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/character_test.o: $(SRCDIR)/character_test.c $(INCDIR)/character.h $(INCDIR)/types.h $(INCDIR)/character_test.h $(INCDIR)/test.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/space_test.o: $(SRCDIR)/space_test.c $(INCDIR)/space.h $(INCDIR)/types.h $(INCDIR)/space_test.h $(INCDIR)/test.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/inventory_test.o: $(SRCDIR)/inventory_test.c $(INCDIR)/inventory.h $(INCDIR)/set.h $(INCDIR)/types.h $(INCDIR)/inventory_test.h $(INCDIR)/test.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

	
###################################################### TEST EXECUTABLES ######################################################
#Set test related 
set_test: $(OBJDIR)/set_test.o $(OBJDIR)/set.o
	gcc -o $@ $^ 

#Character test related
character_test: $(OBJDIR)/character_test.o $(OBJDIR)/character.o
	gcc -o $@ $^ 
	
#Space test related
space_test: $(OBJDIR)/space_test.o $(OBJDIR)/space.o $(OBJDIR)/set.o
	gcc -o $@ $^ 

#Inventory test related
inventory_test: $(OBJDIR)/inventory_test.o $(OBJDIR)/inventory.o $(OBJDIR)/set.o
	gcc -o $@ $^ 



#Additional commands
.PHONY: clean run runV set_test_run character_test_run space_test_run inventory_test_run

clean:
	rm -f $(OBJDIR)/*.o $(EXE)

run:
	./juego_hormiga anthill.dat

runV:
	valgrind --leak-check=full ./juego_hormiga anthill.dat

character_test_run:
	./character_test

space_test_run:
	./space_test

set_test_run:
	./set_test

inventory_test_run:
	./inventory_test
