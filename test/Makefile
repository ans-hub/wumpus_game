CC = clang++
SRC = ../src/
CFLAGS = -I ../src/ -ansi -pedantic-errors -Wall -Wextra -std=c++11 -g
OBJECTS = labyrinth.o subject.o enemy.o room.o player.o bat.o pit.o wump.o interaction.o helpers.o test_cases.o

main.out : $(OBJECTS) main.cc
	$(CC) $(CFLAGS) -o0 main.cc -o main.out $(OBJECTS)

room.o : $(SRC)room.h $(SRC)room.cc subject.o
	$(CC) $(CFLAGS) -c $(SRC)room.cc

labyrinth.o : $(SRC)labyrinth.h $(SRC)labyrinth.cc room.o 
	$(CC) $(CFLAGS) -c $(SRC)labyrinth.cc

subject.o : $(SRC)subject.h $(SRC)subject.cc labyrinth.o helpers.o
	$(CC) $(CFLAGS) -c $(SRC)subject.cc

player.o : $(SRC)player.h $(SRC)player.cc subject.o helpers.o
	$(CC) $(CFLAGS) -c $(SRC)player.cc

enemy.o : $(SRC)enemy.h $(SRC)enemy.cc subject.o
	$(CC) $(CFLAGS) -c $(SRC)enemy.cc	

wump.o : $(SRC)wump.h $(SRC)wump.cc enemy.o
	$(CC) $(CFLAGS) -c $(SRC)wump.cc

bat.o : $(SRC)bat.h $(SRC)bat.cc enemy.o
	$(CC) $(CFLAGS) -c $(SRC)bat.cc

pit.o : $(SRC)pit.h $(SRC)pit.cc enemy.o
	$(CC) $(CFLAGS) -c $(SRC)pit.cc

interaction.o : $(SRC)interaction.h $(SRC)interaction.cc
	$(CC) $(CFLAGS) -c $(SRC)interaction.cc

helpers.o : $(SRC)helpers.h $(SRC)helpers.cc
	$(CC) $(CFLAGS) -c $(SRC)helpers.cc

test_cases.o : test_cases.h test_cases.cc helpers.o
	$(CC) $(CFLAGS) -c test_cases.cc

clean : 
	rm ${OBJECTS} main.out