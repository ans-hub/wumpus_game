CC = clang++
SRC = ../src/
HLP = $(SRC)helpers/
ENT = $(SRC)entities/
CLI = $(SRC)cli/
CFLAGS = -I ../src/ -ansi -pedantic-errors -Wall -Wextra -std=c++11 -g
OBJECTS = map.o subject.o enemy.o room.o player.o bat.o pit.o wump.o \
level.o logic.o entities_helpers.o logic_helpers.o test_helpers.o test_cases.o \
cli_view.o cli_controller.o

main.out : $(OBJECTS) main.cc
	$(CC) $(CFLAGS) -o0 main.cc -o main.out $(OBJECTS)

room.o : $(ENT)room.h $(ENT)room.cc subject.o
	$(CC) $(CFLAGS) -c $(ENT)room.cc

map.o : $(ENT)map.h $(ENT)map.cc room.o 
	$(CC) $(CFLAGS) -c $(ENT)map.cc

subject.o : $(ENT)subject.h $(ENT)subject.cc map.o helpers.o
	$(CC) $(CFLAGS) -c $(ENT)subject.cc

player.o : $(ENT)player.h $(ENT)player.cc subject.o helpers.o
	$(CC) $(CFLAGS) -c $(ENT)player.cc

enemy.o : $(ENT)enemy.h $(ENT)enemy.cc subject.o
	$(CC) $(CFLAGS) -c $(ENT)enemy.cc	

wump.o : $(ENT)wump.h $(ENT)wump.cc enemy.o
	$(CC) $(CFLAGS) -c $(ENT)wump.cc

bat.o : $(ENT)bat.h $(ENT)bat.cc enemy.o
	$(CC) $(CFLAGS) -c $(ENT)bat.cc

pit.o : $(ENT)pit.h $(ENT)pit.cc enemy.o
	$(CC) $(CFLAGS) -c $(ENT)pit.cc

level.o : $(ENT)level.h $(ENT)level.cc map.o wump.o bat.o pit.o
	$(CC) $(CFLAGS) -c $(ENT)level.cc

logic.o : $(SRC)logic.h $(SRC)logic.cc level.o $(SRC)events.h $(SRC)3rdparty/observable.h
	$(CC) $(CFLAGS) -c $(SRC)logic.cc

cli_view.o : $(CLI)view.h $(CLI)view.cc $(SRC)3rdparty/observer.h logic.o $(SRC)events.h
	$(CC) $(CFLAGS) -c $(CLI)view.cc -o cli_view.o 

cli_controller.o : $(CLI)controller.h $(CLI)controller.cc $(SRC)3rdparty/controller.h logic.o
	$(CC) $(CFLAGS) -c $(CLI)controller.cc -o cli_controller.o 

entities_helpers.o : $(HLP)entities_helpers.h $(HLP)entities_helpers.cc
	$(CC) $(CFLAGS) -c $(HLP)entities_helpers.cc

logic_helpers.o : $(HLP)logic_helpers.h $(HLP)logic_helpers.cc
	$(CC) $(CFLAGS) -c $(HLP)logic_helpers.cc

test_helpers.o : test_helpers.h test_helpers.cc map.o subject.o
	$(CC) $(CFLAGS) -c test_helpers.cc

test_cases.o : test_cases.h test_cases.cc $(OBJECTS)
	$(CC) $(CFLAGS) -c test_cases.cc

clean : 
	rm ${OBJECTS} main.out