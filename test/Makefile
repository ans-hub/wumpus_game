CC = clang++

SRC = ../src/
HLP = $(SRC)helpers/
ENT = $(SRC)entities/
CLI = $(SRC)cli/
GUI = $(SRC)gui/
AI = $(SRC)ai/

CFLAGS = -I ../src/ -ansi -pedantic-errors -Wall -Wextra -std=c++11 -g
FLTKFLAGS = `fltk-config --ldflags` -lfltk_images -lpng16 -lz

# note - if library is libpng16.so, just type lpng16 and so on
# a - static lib
# so - dynamic lib

OBJECTS = map.o subject.o enemy.o room.o player.o bat.o pit.o wump.o \
level.o logic.o entities_helpers.o logic_helpers.o test_helpers.o test_cases.o \
cli_view.o cli_controller.o ai_controller.o gui_view.o gui_controller.o \
windows.o form_main.o group_rooms.o

main.out : $(OBJECTS) main.cc
	$(CC) $(CFLAGS) -o0 main.cc $(OBJECTS) $(FLTKFLAGS) -o main.out

room.o : $(ENT)room.h $(ENT)room.cc subject.o
	$(CC) $(CFLAGS) -c $(ENT)room.cc

map.o : $(ENT)map.h $(ENT)map.cc room.o 
	$(CC) $(CFLAGS) -c $(ENT)map.cc

subject.o : $(ENT)subject.h $(ENT)subject.cc map.o entities_helpers.o
	$(CC) $(CFLAGS) -c $(ENT)subject.cc

player.o : $(ENT)player.h $(ENT)player.cc subject.o entities_helpers.o
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

windows.o : $(GUI)windows.h $(GUI)windows.cc $(GUI)forms/form_main.h $(GUI)forms/form_popup.h
	$(CC) $(CFLAGS) -c $(GUI)windows.cc

form_main.o : $(GUI)forms/form_main.h $(GUI)forms/form_main.cc $(GUI)forms/room_button.h
	$(CC) $(CFLAGS) -c $(GUI)forms/form_main.cc

group_rooms.o : $(GUI)forms/group_rooms.h $(GUI)forms/group_rooms.cc $(GUI)forms/room_button.h
	$(CC) $(CFLAGS) -c $(GUI)forms/group_rooms.cc

gui_view.o : $(GUI)view.h $(GUI)view.cc $(SRC)3rdparty/observer.h logic.o $(SRC)events.h $(GUI)windows.h
	$(CC) $(CFLAGS) -c $(GUI)view.cc -o gui_view.o 

gui_controller.o : $(GUI)controller.h $(GUI)controller.cc $(SRC)3rdparty/controller.h logic.o $(GUI)windows.h
	$(CC) $(CFLAGS) -c $(GUI)controller.cc -o gui_controller.o 

cli_view.o : $(CLI)view.h $(CLI)view.cc $(SRC)3rdparty/observer.h logic.o $(SRC)events.h
	$(CC) $(CFLAGS) -c $(CLI)view.cc -o cli_view.o 

cli_controller.o : $(CLI)controller.h $(CLI)controller.cc $(SRC)3rdparty/controller.h logic.o
	$(CC) $(CFLAGS) -c $(CLI)controller.cc -o cli_controller.o 

ai_controller.o : $(AI)controller.h $(AI)controller.cc $(SRC)3rdparty/controller.h logic.o
	$(CC) $(CFLAGS) -c $(AI)controller.cc -o ai_controller.o 

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