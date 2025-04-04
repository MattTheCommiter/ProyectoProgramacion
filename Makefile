CFLAGS=-Wall -ansi -pedantic -g
SRCDIR=./src
OBJDIR=./obj
LIBDIR=./lib
INCDIR=./include
DOCDIR=./doc
INC=-Iinclude
CLIBS=-L$(LIBDIR) -lscreen
TESTS=character_test set_test space_test link_test inventory_test object_test
EXE=juego_hormiga $(TESTS)
vpath %.h $(INCDIR)
vpath %.c $(SRCDIR)
vpath %.o $(OBJDIR)

#make - compile game 
all: juego_hormiga

#make tests - compile every test
tests: $(TESTS)

#make general - compile both game and tests
general: $(EXE)

###################################################### GAME EXECUTABLE ######################################################
juego_hormiga :  $(OBJDIR)/link.o $(OBJDIR)/inventory.o $(OBJDIR)/game_loop.o $(OBJDIR)/game.o $(OBJDIR)/graphic_engine.o $(OBJDIR)/command.o $(OBJDIR)/game_actions.o $(OBJDIR)/space.o $(OBJDIR)/gameReader.o $(OBJDIR)/object.o $(OBJDIR)/player.o $(OBJDIR)/character.o $(OBJDIR)/set.o 
	gcc -g -o $@ $^ $(CLIBS)



###################################################### OBJECTS NEEDED FOR GAME ######################################################
$(OBJDIR)/game.o: game.c game.h command.h types.h space.h player.h object.h gameReader.h link.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/game_loop.o: game_loop.c command.h types.h game.h space.h player.h object.h game_actions.h graphic_engine.h
	gcc $(INC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/graphic_engine.o: graphic_engine.c graphic_engine.h game.h command.h types.h space.h player.h object.h libscreen.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/command.o: command.c command.h types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/game_actions.o: game_actions.c game_actions.h command.h types.h game.h space.h player.h object.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/space.o: space.c space.h types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/gameReader.o: gameReader.c gameReader.h types.h game.h command.h space.h player.h object.h link.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/object.o: object.c object.h types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/player.o: player.c player.h types.h space.h inventory.h
	gcc $(INC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/character.o: character.c character.h types.h 
	gcc $(INC) $(CFLAGS) -c $< -o $@
	
$(OBJDIR)/set.o: set.c set.h types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/inventory.o: inventory.c inventory.h types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@


$(OBJDIR)/link.o: link.c link.h types.h
	gcc $(INC) $(CFLAGS) -c $< -o $@



###################################################### OBJECTS NEEDED FOR TESTS ######################################################
$(OBJDIR)/set_test.o: set_test.c set.h types.h set_test.h test.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/character_test.o: character_test.c character.h types.h character_test.h test.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/space_test.o: space_test.c space.h types.h space_test.h test.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/inventory_test.o: inventory_test.c inventory.h set.h types.h inventory_test.h test.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/link_test.o: link_test.c link_test.h types.h link.h test.h
	gcc $(INC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/object_test.o: $(SRCDIR)/object_test.c $(INCDIR)/object_test.h $(INCDIR)/types.h $(INCDIR)/link.h $(INCDIR)/test.h
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

object_test: $(OBJDIR)/object_test.o $(OBJDIR)/object.o 
	gcc -o $@ $^

#Additional commands
.PHONY: clean run runV set_test_run character_test_run space_test_run inventory_test_run link_test_run docs clean_docs

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
	./juego_hormiga anthill.dat

runLog:
	./juego_hormiga anthill.dat -l Logfile

runLog_read:
	./juego_hormiga anthill.dat -l Logfile < game1.cmd

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

link_test_run:
	./link_test

object_test_run:
	./object_test

