CC = g++
CFLAGS = -I  -ansi -pedantic-errors -Wall -Wextra -std=c++11 -g
# CFLAGS = -I  -ansi -pedantic-errors -Wall -Wextra -std=c++11 `fltk-config --cxxflags` -g
OBJECTS = labyrinth.o subject.o enemy.o room.o player.o bat.o pit.o wump.o \
helpers.o cli_controller.o cli_view.o logic.o

main.out : $(OBJECTS) main.cc
	$(CC) $(CFLAGS) main.cc -o main.out $(OBJECTS)

	# $(CC) $(CFLAGS) main.cc -o main.out $(OBJECTS) `fltk-config --ldflags`

# Main game files

room.o : room.h room.cc subject.o
	$(CC) $(CFLAGS) -c room.cc

labyrinth.o : labyrinth.h labyrinth.cc room.o
	$(CC) $(CFLAGS) -c labyrinth.cc

subject.o : subject.h subject.cc labyrinth.o
	$(CC) $(CFLAGS) -c subject.cc

enemy.o : enemy.h enemy.cc subject.o
	$(CC) $(CFLAGS) -c enemy.cc
	
player.o : player.h player.cc subject.o
	$(CC) $(CFLAGS) -c player.cc

wump.o : wump.h wump.cc enemy.o
	$(CC) $(CFLAGS) -c wump.cc

bat.o : bat.h bat.cc enemy.o
	$(CC) $(CFLAGS) -c bat.cc

pit.o : pit.h pit.cc enemy.o
	$(CC) $(CFLAGS) -c pit.cc

logic.o : logic.h logic.cc ui/abc/observable.h
	$(CC) $(CFLAGS) -c logic.cc

# interaction.o : interaction.h interaction.cc 3rdparty/cin_wrapper.h
	# $(CC) $(CFLAGS) -c interaction.cc

helpers.o : helpers.h helpers.cc
	$(CC) $(CFLAGS) -c helpers.cc

# Interface

cli_controller.o : ui/cli/controller.h ui/cli/controller.cc ui/abc/observer.h
	$(CC) $(CFLAGS) -c ui/cli/controller.cc -o cli_controller.o

cli_view.o : ui/cli/view.h ui/cli/view.cc ui/abc/observer.h
	$(CC) $(CFLAGS) -c ui/cli/view.cc -o cli_view.o

clean : 
	rm ${OBJECTS} main.out