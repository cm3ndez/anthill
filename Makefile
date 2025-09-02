CC= gcc
#DEBUG=  -DDEBUG   #Uncomment -DDEBUG here for debugging 
CFLAGS= -Wall -pedantic -ansi -g -Iinclude $(DEBUG)
TEST_LIST= set_test character_test space_test inventory_test link_test player_test object_test

.PHONY: clean_objs clean_execs clean_doc clean_all execute test_build test_execute gen_doc

anthill: obj/game.o obj/command.o obj/game_actions.o obj/game_loop.o obj/graphic_engine.o lib/libscreen.a obj/space.o obj/player.o obj/object.o obj/game_management.o obj/set.o obj/character.o obj/inventory.o obj/link.o obj/game_rules.o
	$(CC) -o anthill obj/game.o obj/game_management.o obj/command.o obj/game_actions.o obj/game_loop.o obj/graphic_engine.o obj/space.o obj/player.o obj/object.o obj/set.o obj/character.o obj/inventory.o obj/link.o obj/game_rules.o -lscreen -L lib

obj/game_loop.o: src/game_loop.c include/command.h include/types.h include/game.h include/space.h include/player.h include/object.h include/character.h include/game_actions.h include/graphic_engine.h
	$(CC) $(CFLAGS) -c src/game_loop.c -o obj/game_loop.o

obj/game_actions.o: src/game_actions.c include/game_actions.h include/command.h include/types.h include/game.h include/space.h include/player.h include/object.h include/character.h 
	$(CC) $(CFLAGS) -c src/game_actions.c -o obj/game_actions.o

obj/command.o: src/command.c include/command.h include/types.h
	$(CC) $(CFLAGS) -c src/command.c -o obj/command.o

obj/game.o: src/game.c include/game.h include/command.h include/types.h include/space.h include/player.h include/object.h include/character.h include/game_management.h	
	$(CC) $(CFLAGS) -c src/game.c -o obj/game.o

obj/space.o: src/space.c include/space.h include/types.h include/set.h
	$(CC) $(CFLAGS) -c src/space.c -o obj/space.o

obj/graphic_engine.o: src/graphic_engine.c include/graphic_engine.h include/game.h include/command.h include/types.h include/space.h include/player.h include/object.h include/character.h include/libscreen.h	
	$(CC) $(CFLAGS) -c src/graphic_engine.c -o obj/graphic_engine.o

obj/player.o: src/player.c include/player.h include/types.h include/inventory.h
	$(CC) $(CFLAGS) -c src/player.c -o obj/player.o

obj/object.o: src/object.c include/object.h include/types.h	
	$(CC) $(CFLAGS) -c src/object.c -o obj/object.o

obj/game_management.o: src/game_management.c include/game_management.h include/game.h include/command.h include/types.h include/space.h include/player.h include/object.h include/character.h	
	$(CC) $(CFLAGS) -c src/game_management.c -o obj/game_management.o

obj/set.o: src/set.c include/set.h include/types.h	
	$(CC) $(CFLAGS) -c src/set.c -o obj/set.o

obj/character.o: src/character.c include/character.h include/types.h	
	$(CC) $(CFLAGS) -c src/character.c -o obj/character.o

obj/inventory.o: src/inventory.c include/inventory.h include/set.h include/types.h	
	$(CC) $(CFLAGS) -c src/inventory.c -o obj/inventory.o

obj/link.o: src/link.c include/link.h include/types.h	
	$(CC) $(CFLAGS) -c src/link.c -o obj/link.o

obj/game_rules.o: src/game_rules.c include/game_rules.h include/types.h	include/game.h
	$(CC) $(CFLAGS) -c src/game_rules.c -o obj/game_rules.o

execute:
	./anthill anthill_final.dat

clean_all: clean_objs clean_execs clean_docs
	@echo "Done."

clean_objs:
	rm obj/* 

clean_execs:
	rm anthill $(TEST_LIST) 

clean_docs:
	rm -rf doc/*

test_build: $(TEST_LIST)
	@echo "Compilation completed."

character_test: obj/character_test.o obj/character.o
	$(CC) obj/character_test.o obj/character.o -o character_test 

set_test: obj/set_test.o obj/set.o
	$(CC) obj/set_test.o obj/set.o -o set_test 

inventory_test: obj/inventory_test.o obj/inventory.o obj/set.o
	$(CC) obj/inventory_test.o obj/inventory.o obj/set.o -o inventory_test 

space_test: obj/space_test.o obj/space.o obj/set.o
	$(CC) obj/space_test.o obj/space.o obj/set.o -o space_test 

link_test: obj/link_test.o obj/link.o
	$(CC) obj/link_test.o obj/link.o -o link_test 

player_test: obj/player_test.o obj/player.o obj/inventory.o obj/set.o
	$(CC) obj/player_test.o obj/player.o obj/inventory.o obj/set.o -o player_test 

object_test: obj/object_test.o obj/object.o
	$(CC) obj/object_test.o obj/object.o -o object_test 

obj/character_test.o: src/character_test.c include/character_test.h include/character.h include/types.h include/test.h
	$(CC) $(CFLAGS) -c src/character_test.c -o obj/character_test.o

obj/set_test.o: src/set_test.c include/set_test.h include/set.h include/types.h include/test.h
	$(CC) $(CFLAGS) -c src/set_test.c -o obj/set_test.o 

obj/space_test.o: src/space_test.c include/space_test.h include/space.h include/types.h include/test.h
	$(CC) $(CFLAGS) -c src/space_test.c -o obj/space_test.o 

obj/inventory_test.o: src/inventory_test.c include/inventory_test.h include/set.h include/inventory.h include/types.h include/test.h
	$(CC) $(CFLAGS) -c src/inventory_test.c -o obj/inventory_test.o 
	
obj/link_test.o: src/link_test.c include/link_test.h include/link.h include/types.h include/test.h
	$(CC) $(CFLAGS) -c src/link_test.c -o obj/link_test.o 

obj/player_test.o: src/player_test.c include/player.h include/types.h include/player_test.h include/test.h
	$(CC) $(CFLAGS) -c src/player_test.c -o obj/player_test.o 

obj/object_test.o: src/object_test.c include/object.h include/types.h include/object_test.h include/test.h
	$(CC) $(CFLAGS) -c src/object_test.c -o obj/object_test.o 
	
test_execute: $(TEST_LIST) 
	@echo "\n>>>>>>>>>>>>>>>>>>Executing character_test:\n"
	./character_test
	@echo "\n>>>>>>>>>>>>>>>>>>Executing set_test:\n"
	./set_test
	@echo "\n>>>>>>>>>>>>>>>>>>Executing space_test:\n"
	./space_test
	@echo "\n>>>>>>>>>>>>>>>>>>Executing inventory_test:\n"
	./inventory_test
	@echo "\n>>>>>>>>>>>>>>>>>>Executing link_test:\n"
	./link_test
	@echo "\n>>>>>>>>>>>>>>>>>>Executing player_test:\n"
	./player_test
	@echo "\n>>>>>>>>>>>>>>>>>>Executing object_test:\n"
	./object_test
	

gen_doc:
	doxygen Doxyfile
