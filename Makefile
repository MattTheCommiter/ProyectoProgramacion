CFLAGS=-Wall -ansi -pedantic -g
SRCDIR=./src
OBJDIR=./obj
LIBDIR=./lib
INCDIR=./include
DOCDIR=./doc
INC=-Iinclude
CLIBS=-L$(LIBDIR) -lscreen
TESTS=character_test set_test space_test link_test inventory_test object_test player_test
EXE=juego_hormiga $(TESTS)
vpath %.h $(INCDIR)
vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)

.PHONY: all general tests clean run runV runLog runLog_read1 runLog_read2 set_test_run character_test_run space_test_run inventory_test_run link_test_run object_test_run player_test_run set_test_runV character_test_runV space_test_runV inventory_test_runV link_test_runV object_test_runV player_test_runV docs clean_docs tests test_run commands

#make - compile game 
all: juego_hormiga

#make tests - compile every test
tests: $(TESTS)

#make general - compile both game and tests
general: $(EXE)

###################################################### GAME EXECUTABLE ######################################################
juego_hormiga :  $(OBJDIR)/link.o $(OBJDIR)/inventory.o $(OBJDIR)/game_loop.o $(OBJDIR)/game.o $(OBJDIR)/graphic_engine.o $(OBJDIR)/command.o $(OBJDIR)/game_actions.o $(OBJDIR)/space.o $(OBJDIR)/gameManagement.o $(OBJDIR)/object.o $(OBJDIR)/player.o $(OBJDIR)/character.o $(OBJDIR)/set.o $(OBJDIR)/libscreen.o $(OBJDIR)/cinematics.o
	gcc -g -o $@ $^



###################################################### OBJECTS NEEDED FOR GAME ######################################################
$(OBJDIR)/game.o: game.c game.h command.h types.h space.h set.h character.h \
  player.h inventory.h object.h gameManagement.h link.h cinematics.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/game_loop.o: src/game_loop.c include/graphic_engine.h include/game.h \
  command.h types.h space.h set.h player.h character.h inventory.h object.h link.h libscreen.h cinematics.h
	gcc $(INC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/graphic_engine.o: graphic_engine.c graphic_engine.h \
  game.h command.h types.h space.h \
  set.h player.h character.h inventory.h \
  object.h link.h libscreen.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/command.o: command.c command.h types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/game_actions.o: game_actions.c game_actions.h command.h types.h \
  gameManagement.h game.h space.h set.h player.h character.h inventory.h object.h \
  link.h graphic_engine.h libscreen.h 
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/space.o: space.c space.h types.h set.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/gameManagement.o: gameManagement.c gameManagement.h types.h game.h \
  command.h space.h set.h player.h object.h link.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/object.o: object.c object.h types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/player.o: player.c player.h types.h set.h \
  character.h inventory.h
	gcc $(INC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/character.o: character.c character.h types.h 
	gcc $(INC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/set.o: set.c set.h types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/inventory.o: inventory.c inventory.h types.h set.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/libscreen.o: libscreen.c libscreen.h types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/link.o: link.c link.h types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/cinematics.o: cinematics.c cinematics.h types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

###################################################### OBJECTS NEEDED FOR TESTS ######################################################
$(OBJDIR)/set_test.o: set_test.c set_test.h set.h \
  types.h test.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/character_test.o: character_test.c character_test.h \
  test.h character.h types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/space_test.o: space_test.c space_test.h space.h \
  types.h set.h test.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/inventory_test.o: inventory_test.c inventory_test.h \
  set.h types.h inventory.h test.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/link_test.o: link_test.c link_test.h link.h \
  types.h test.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/object_test.o: object_test.c object_test.h types.h \
  test.h object.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/player_test.o: player_test.c player_test.h \
  inventory.h types.h set.h test.h \
  player.h character.h
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

#Link test related
link_test: $(OBJDIR)/link_test.o $(OBJDIR)/link.o 
	gcc -o $@ $^
	
#Object test related
object_test: $(OBJDIR)/object_test.o $(OBJDIR)/object.o 
	gcc -o $@ $^


#player test related
player_test: $(OBJDIR)/player_test.o $(OBJDIR)/player.o $(OBJDIR)/inventory.o $(OBJDIR)/set.o
	gcc -o $@ $^


##General clean target 
clean:
	rm -f $(OBJDIR)/*.o $(EXE) $(TESTS)

## Clean docs: finds subdirectories inside ./doc and removes their files, then removes empty directories
clean_docs:
	@echo "Cleaning in root..."
	@rm -rf *.html *.js *.css *.map *.md5 *.png *.svg
	@SUBDIRS=$$(find ./doc -type d); \
	for dir in $$SUBDIRS; do \
		echo "Cleaning in $$dir..."; \
		(cd $$dir && rm -rf *.html *.js *.css *.map *.md5 *.png *.svg); \
	done

	@echo "Removing empty directories..."
	@find ./doc -type d -empty -delete
##Generate doxygen docuentation using the project's config file 
docs: 
	doxygen Doxyfile 


#Various run commmands
run:
	./juego_hormiga house.dat

runLog:
	./juego_hormiga house.dat -l Logfile

runLog_read1:
	./juego_hormiga house.dat -l Logfile < game1.cmd

runLog_read2:
	./juego_hormiga house.dat -l Logfile < game2.cmd

runV:
	valgrind --leak-check=full ./juego_hormiga house.dat

character_test_run:
	@echo ">>>>>>Running character_test:"
	./character_test

space_test_run:
	@echo ">>>>>>Running space_test:"
	./space_test

set_test_run:
	@echo ">>>>>>Running set_test:"
	./set_test

inventory_test_run:
	@echo ">>>>>>Running inventory_test:"
	./inventory_test

link_test_run:
	@echo ">>>>>>Running link_test:"
	./link_test

object_test_run:
	@echo ">>>>>>Running object_test:"
	./object_test

player_test_run:
	@echo ">>>>>>Running player_test:"
	./player_test

test_run:
	@echo ">>>>>>Running all tests:"
	@echo ">>>>>>Running character_test:"
	./character_test
	@echo ">>>>>>Running set_test:"
	./set_test
	@echo ">>>>>>Running space_test:"
	./space_test
	@echo ">>>>>>Running inventory_test:"
	./inventory_test
	@echo ">>>>>>Running link_test:"
	./link_test
	@echo ">>>>>>Running object_test:"                                                      
	./object_test
	@echo ">>>>>>Running player_test:"                            
	./player_test

character_test_runV:
	@echo ">>>>>>Running character_test with Valgrind:"
	valgrind --leak-check=full ./character_test

space_test_runV:
	@echo ">>>>>>Running space_test with Valgrind:"
	valgrind --leak-check=full ./space_test

set_test_runV:
	@echo ">>>>>>Running set_test with Valgrind:"
	valgrind --leak-check=full ./set_test

inventory_test_runV:
	@echo ">>>>>>Running inventory_test with Valgrind:"
	valgrind --leak-check=full ./inventory_test

link_test_runV:
	@echo ">>>>>>Running link_test with Valgrind:"
	valgrind --leak-check=full ./link_test

object_test_runV:
	@echo ">>>>>>Running object_test with Valgrind:"
	valgrind --leak-check=full ./object_test

player_test_run_V:
	@echo ">>>>>>Running player_test with Valgrind:"
	valgrind --leak-check=full ./player_test

test_runV:
	@echo ">>>>>>Running all tests with Valgrind:"
	@echo ">>>>>>Running character_test with Valgrind:"
	valgrind --leak-check=full ./character_test
	@echo ">>>>>>Running set_test with Valgrind:"
	valgrind --leak-check=full ./set_test
	@echo ">>>>>>Running space_test with Valgrind:"
	valgrind --leak-check=full ./space_test
	@echo ">>>>>>Running inventory_test with Valgrind:"
	valgrind --leak-check=full ./inventory_test
	@echo ">>>>>>Running link_test with Valgrind:"
	valgrind --leak-check=full ./link_test
	@echo ">>>>>>Running object_test with Valgrind:"
	valgrind --leak-check=full ./object_test
	@echo ">>>>>>Running player_test with Valgrind:"
	valgrind --leak-check=full ./player_test

commands:
	@echo ">>>>>>The possible commands are:"
	@echo ">>>>>>tests: creates an executable for each one of the tests"
	@echo ">>>>>>run: Runs the game"
	@echo ">>>>>>runV: Runs the game with valgrind"
	@echo ">>>>>>runLog: Runs the game and logs the output to Logfile"
	@echo ">>>>>>runLog_read1: Runs the game with input from game1.cmd and logs the output to Logfile"
	@echo ">>>>>>runLog_read2: Runs the game with input from game2.cmd and logs the output to Logfile"
	@echo ">>>>>>character_test_run: Runs the character_test executable"
	@echo ">>>>>>space_test_run: Runs the space_test executable"
	@echo ">>>>>>set_test_run: Runs the set_test executable"
	@echo ">>>>>>inventory_test_run: Runs the inventory_test executable"
	@echo ">>>>>>link_test_run: Runs the link_test executable"
	@echo ">>>>>>object_test_run: Runs the object_test executable"
	@echo ">>>>>>player_test_run: Runs the player_test executable"
	@echo ">>>>>>test_run: Runs all test executables"
	@echo ">>>>>>character_test_runV: Runs the character_test executable with Valgrind"
	@echo ">>>>>>space_test_runV: Runs the space_test executable with Valgrind"
	@echo ">>>>>>set_test_runV: Runs the set_test executable with Valgrind"
	@echo ">>>>>>inventory_test_runV: Runs the inventory_test executable with Valgrind"
	@echo ">>>>>>link_test_runV: Runs the link_test executable with Valgrind"
	@echo ">>>>>>object_test_runV: Runs the object_test executable with Valgrind"
	@echo ">>>>>>player_test_run_V: Runs the player_test executable with Valgrind"
	@echo ">>>>>>test_runV: Runs all test executables with Valgrind"
	@echo ">>>>>>docs: Generates documentation using Doxygen"
	@echo ">>>>>>clean: Removes all object files and executables"
	@echo ">>>>>>clean_docs: Cleans up documentation files and removes empty directories"


