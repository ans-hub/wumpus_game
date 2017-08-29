CC = g++

SRC = ./
ENT = $(SRC)entities/
CFG = $(SRC)settings/
AUD = $(SRC)3rdparty/
HLP = $(ENT)helpers/
CLI = $(SRC)cli/
GUI = $(SRC)gui/
ENM = $(SRC)enums/
AI = $(SRC)ai/

CFLAGS = -I $(SRC) -ansi -pedantic-errors -Wall -Wextra -std=c++14 -g \
				 -L $(SRC)3rdparty -lbass

FLTKFLAGS = `fltk-config --use-images --ldflags`

OBJECTS = map.o subject.o enemy.o room.o player.o bat.o pit.o wump.o \
					guide.o level.o logic.o helpers.o cli_view.o \
					cli_controller.o ai_controller.o gui_view.o gui_controller.o \
					windows.o form_start.o form_help.o form_main.o widget_info.o \
					widget_map.o widget_netdraw.o widget_player.o trajectory.o \
					scores.o config.o audio_out.o images.o math_helpers.o music.o

release : $(OBJECTS) main.cc
	$(CC) $(CFLAGS) -o2 main.cc $(OBJECTS) $(FLTKFLAGS) $(SRC)3rdparty/libbass.so -o main.out

main.out : $(OBJECTS) main.cc
	$(CC) $(CFLAGS) -o0 main.cc $(OBJECTS) $(FLTKFLAGS) $(SRC)3rdparty/libbass.so -o main.out

room.o : $(ENT)room.h $(ENT)room.cc subject.o
	$(CC) $(CFLAGS) -c $(ENT)room.cc

map.o : $(ENT)map.h $(ENT)map.cc room.o 
	$(CC) $(CFLAGS) -c $(ENT)map.cc

subject.o : $(ENT)subject.h $(ENT)subject.cc map.o helpers.o
	$(CC) $(CFLAGS) -c $(ENT)subject.cc

player.o : $(ENT)player.h $(ENT)player.cc subject.o helpers.o
	$(CC) $(CFLAGS) -c $(ENT)player.cc

guide.o : $(ENT)guide.h $(ENT)guide.cc subject.o helpers.o
	$(CC) $(CFLAGS) -c $(ENT)guide.cc

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

logic.o : $(ENT)logic.h $(ENT)logic.cc level.o $(ENM)enums.h $(SRC)3rdparty/observable.h config.o
	$(CC) $(CFLAGS) -c $(ENT)logic.cc

images.o : $(GUI)images.h $(GUI)images.cc $(ENM)enums.h config.o
	$(CC) $(CFLAGS) -c $(GUI)images.cc

music.o : $(SRC)music/music.h $(SRC)music/music.cc $(ENM)enums.h config.o logic.o
	$(CC) $(CFLAGS) -c $(SRC)music/music.cc

windows.o : $(GUI)windows.h $(GUI)windows.cc form_main.o widget_map.o form_help.o form_start.o config.o
	$(CC) $(CFLAGS) -c $(GUI)windows.cc

form_start.o : $(GUI)forms/form_start.h $(GUI)forms/form_start.cc
	$(CC) $(CFLAGS) -c $(GUI)forms/form_start.cc

form_help.o : $(GUI)forms/form_help.h $(GUI)forms/form_help.cc
	$(CC) $(CFLAGS) -c $(GUI)forms/form_help.cc

form_main.o : $(GUI)forms/form_main.h $(GUI)forms/form_main.cc
	$(CC) $(CFLAGS) -c $(GUI)forms/form_main.cc

widget_info.o : $(GUI)widgets/widget_info.h $(GUI)widgets/widget_info.cc
	$(CC) $(CFLAGS) -c $(GUI)widgets/widget_info.cc

widget_map.o : $(GUI)widgets/widget_map.h $(GUI)widgets/widget_map.cc $(GUI)widgets/widget_room.h widget_netdraw.o widget_player.o
	$(CC) $(CFLAGS) -c $(GUI)widgets/widget_map.cc

widget_netdraw.o : $(GUI)widgets/widget_netdraw.h $(GUI)widgets/widget_netdraw.cc $(GUI)helpers/point.h math_helpers.o
	$(CC) $(CFLAGS) -c $(GUI)widgets/widget_netdraw.cc

trajectory.o : $(GUI)helpers/trajectory.h $(GUI)helpers/trajectory.cc $(GUI)helpers/point.h math_helpers.o
	$(CC) $(CFLAGS) -c $(GUI)helpers/trajectory.cc

math_helpers.o : $(GUI)helpers/math_helpers.h $(GUI)helpers/math_helpers.cc $(GUI)helpers/point.h 
	$(CC) $(CFLAGS) -c $(GUI)helpers/math_helpers.cc

widget_player.o : $(GUI)widgets/widget_player.h $(GUI)widgets/widget_player.cc $(GUI)helpers/point.h trajectory.o
	$(CC) $(CFLAGS) -c $(GUI)widgets/widget_player.cc

gui_view.o : $(GUI)view.h $(GUI)view.cc $(SRC)3rdparty/observer.h logic.o $(ENM)enums.h $(GUI)windows.h config.o audio_out.o
	$(CC) $(CFLAGS) -c $(GUI)view.cc -o gui_view.o 

gui_controller.o : $(GUI)controller.h $(GUI)controller.cc $(SRC)3rdparty/controller.h logic.o $(GUI)windows.h
	$(CC) $(CFLAGS) -c $(GUI)controller.cc -o gui_controller.o 

cli_view.o : $(CLI)view.h $(CLI)view.cc $(SRC)3rdparty/observer.h logic.o $(ENM)enums.h
	$(CC) $(CFLAGS) -c $(CLI)view.cc -o cli_view.o 

cli_controller.o : $(CLI)controller.h $(CLI)controller.cc $(SRC)3rdparty/controller.h logic.o
	$(CC) $(CFLAGS) -c $(CLI)controller.cc -o cli_controller.o 

ai_controller.o : $(AI)controller.h $(AI)controller.cc $(SRC)3rdparty/controller.h logic.o
	$(CC) $(CFLAGS) -c $(AI)controller.cc -o ai_controller.o 

helpers.o : $(ENT)helpers.h $(ENT)helpers.cc wump.o map.o room.o subject.o
	$(CC) $(CFLAGS) -c $(ENT)helpers.cc

audio_out.o : $(AUD)audio_out.h $(AUD)audio_out.cc
	$(CC) $(CFLAGS) -c $(AUD)audio_out.cc

scores.o : $(SRC)scores/scores.h $(SRC)scores/scores.cc logic.o $(ENM)enums.h $(SRC)3rdparty/observer.h config.o
	$(CC) $(CFLAGS) -c $(SRC)scores/scores.cc

config.o : $(SRC)config.h $(SRC)config.cc
	$(CC) $(CFLAGS) -c $(SRC)config.cc

clean : 
	rm ${OBJECTS} main.out main