CC = clang++
CFLAGS = -I ../src/ -ansi -pedantic-errors -Wall -Wextra -std=c++1y -g
OBJECTS = labyrinth.o subject.o enemy.o room.o player.o bat.o pit.o wump.o interaction.o

main.out : $(OBJECTS) main.cc
	$(CC) $(CFLAGS) main.cc -o main.out $(OBJECTS)

room.o : ../src/room.h ../src/room.cc ../src/subject.h ../src/subject.cc
	$(CC) $(CFLAGS) -c ../src/room.cc

labyrinth.o : ../src/room.h ../src/room.cc ../src/labyrinth.h ../src/labyrinth.cc 
	$(CC) $(CFLAGS) -c ../src/labyrinth.cc

subject.o : ../src/labyrinth.h ../src/labyrinth.cc ../src/subject.h ../src/subject.cc
	$(CC) $(CFLAGS) -c ../src/subject.cc

enemy.o : ../src/enemy.h ../src/enemy.cc ../src/subject.h ../src/subject.cc
	$(CC) $(CFLAGS) -c ../src/enemy.cc
	
player.o : ../src/player.h ../src/player.cc ../src/subject.h ../src/subject.cc
	$(CC) $(CFLAGS) -c ../src/player.cc

wump.o : ../src/wump.h ../src/wump.cc ../src/enemy.h ../src/enemy.cc
	$(CC) $(CFLAGS) -c ../src/wump.cc

bat.o : ../src/bat.h ../src/bat.cc ../src/enemy.h ../src/enemy.cc
	$(CC) $(CFLAGS) -c ../src/bat.cc

pit.o : ../src/pit.h ../src/pit.cc ../src/enemy.h ../src/enemy.cc
	$(CC) $(CFLAGS) -c ../src/pit.cc

interaction.o : ../src/interaction.h ../src/interaction.cc ../src/3rdparty/cin_wrapper.h
	$(CC) $(CFLAGS) -c ../src/interaction.cc

clean : 
	rm ${OBJECTS} main.out