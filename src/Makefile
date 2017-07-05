CC = clang++
# CFLAGS = -ansi -pedantic-errors -Wall -Wextra -std=c++11 -g
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -std=c++11 `fltk-config --cxxflags` -g
OBJECTS = labyrinth.o subject.o enemy.o room.o player.o bat.o pit.o wump.o \
helpers.o cli_controller.o cli_view.o logic.o gui.o
ENT = entities/

main.out : $(OBJECTS) main.cc
	$(CC) $(CFLAGS) main.cc $(OBJECTS) `fltk-config --ldflags` -lfltk_images -lfltk_png -lz -o main.out

# -lz flag for png 
	# $(CC) $(CFLAGS) main.cc -o main.out $(OBJECTS)

# Main game files

room.o : $(ENT)room.h $(ENT)room.cc subject.o
	$(CC) $(CFLAGS) -c $(ENT)room.cc

labyrinth.o : $(ENT)labyrinth.h $(ENT)labyrinth.cc room.o
	$(CC) $(CFLAGS) -c $(ENT)labyrinth.cc

subject.o : $(ENT)subject.h $(ENT)subject.cc labyrinth.o
	$(CC) $(CFLAGS) -c $(ENT)subject.cc

enemy.o : $(ENT)enemy.h $(ENT)enemy.cc subject.o
	$(CC) $(CFLAGS) -c $(ENT)enemy.cc
	
player.o : $(ENT)player.h $(ENT)player.cc subject.o
	$(CC) $(CFLAGS) -c $(ENT)player.cc

wump.o : $(ENT)wump.h $(ENT)wump.cc enemy.o
	$(CC) $(CFLAGS) -c $(ENT)wump.cc

bat.o : $(ENT)bat.h $(ENT)bat.cc enemy.o
	$(CC) $(CFLAGS) -c $(ENT)bat.cc

pit.o : $(ENT)pit.h $(ENT)pit.cc enemy.o
	$(CC) $(CFLAGS) -c $(ENT)pit.cc

logic.o : logic.h logic.cc 3rdparty/observable.h events.h
	$(CC) $(CFLAGS) -c logic.cc

helpers.o : helpers.h helpers.cc
	$(CC) $(CFLAGS) -c helpers.cc

# Interface

cli_controller.o : cli/controller.h cli/controller.cc 3rdparty/observer.h logic.o events.h
	$(CC) $(CFLAGS) -c cli/controller.cc -o cli_controller.o

cli_view.o : cli/view.h cli/view.cc 3rdparty/observer.h logic.o events.h
	$(CC) $(CFLAGS) -c cli/view.cc -o cli_view.o 

gui.o : gui/gui.h gui/gui.cc 3rdparty/observer.h logic.o events.h gui/coords.h gui/room_button.h
	$(CC) $(CFLAGS) -c gui/gui.cc

clean : 
	rm ${OBJECTS} main.out