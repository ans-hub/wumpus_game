CC = g++

SRC = ../src/
ENT = $(SRC)entities/
AUD = $(SRC)audio/
HLP = $(ENT)helpers/
CLI = $(SRC)cli/
AI = $(SRC)ai/

CFLAGS = -I $(SRC) -ansi -pedantic-errors -Wall -Wextra -std=c++11 -g -L $(SRC)3rdparty -lbass
FLTKFLAGS = `fltk-config --use-images --ldflags`

OBJECTS = map.o subject.o enemy.o room.o player.o bat.o pit.o wump.o \
level.o logic.o map_helpers.o logic_helpers.o test_helpers.o test_cases.o \
cli_view.o cli_controller.o ai_controller.o

main.out : $(OBJECTS) main.cc
	$(CC) $(CFLAGS) -o0 main.cc $(OBJECTS) $(FLTKFLAGS) $(SRC)3rdparty/libbass.so -o main.out

room.o : $(ENT)room.h $(ENT)room.cc subject.o
	$(CC) $(CFLAGS) -c $(ENT)room.cc

map.o : $(ENT)map.h $(ENT)map.cc room.o 
	$(CC) $(CFLAGS) -c $(ENT)map.cc

subject.o : $(ENT)subject.h $(ENT)subject.cc map.o map_helpers.o
	$(CC) $(CFLAGS) -c $(ENT)subject.cc

player.o : $(ENT)player.h $(ENT)player.cc subject.o map_helpers.o
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

logic.o : $(ENT)logic.h $(ENT)logic.cc level.o $(ENT)events.h $(SRC)3rdparty/observable.h
	$(CC) $(CFLAGS) -c $(ENT)logic.cc

draw_consts.o : $(GUI)helpers/draw_consts.h $(GUI)helpers/draw_consts.cc
	$(CC) $(CFLAGS) -c $(GUI)helpers/draw_consts.cc

cli_view.o : $(CLI)view.h $(CLI)view.cc $(SRC)3rdparty/observer.h logic.o $(ENT)events.h
	$(CC) $(CFLAGS) -c $(CLI)view.cc -o cli_view.o 

cli_controller.o : $(CLI)controller.h $(CLI)controller.cc $(SRC)3rdparty/controller.h logic.o
	$(CC) $(CFLAGS) -c $(CLI)controller.cc -o cli_controller.o 

ai_controller.o : $(AI)controller.h $(AI)controller.cc $(SRC)3rdparty/controller.h logic.o
	$(CC) $(CFLAGS) -c $(AI)controller.cc -o ai_controller.o 

map_helpers.o : $(HLP)map_helpers.h $(HLP)map_helpers.cc
	$(CC) $(CFLAGS) -c $(HLP)map_helpers.cc

logic_helpers.o : $(HLP)logic_helpers.h $(HLP)logic_helpers.cc
	$(CC) $(CFLAGS) -c $(HLP)logic_helpers.cc

test_helpers.o : test_helpers.h test_helpers.cc map.o subject.o
	$(CC) $(CFLAGS) -c test_helpers.cc

test_cases.o : test_cases.h test_cases.cc $(OBJECTS)
	$(CC) $(CFLAGS) -c test_cases.cc

clean : 
	rm ${OBJECTS} main.out