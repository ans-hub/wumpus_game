CC = clang++
SRC = ../src/
ENT = $(SRC)entities/
CFLAGS = -I ../src/ -ansi -pedantic-errors -Wall -Wextra -std=c++11 -g
OBJECTS = map.o subject.o enemy.o room.o player.o bat.o pit.o wump.o \
level.o helpers.o test_helpers.o test_cases.o

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

helpers.o : $(SRC)helpers.h $(SRC)helpers.cc
	$(CC) $(CFLAGS) -c $(SRC)helpers.cc

test_helpers.o : test_helpers.h test_helpers.cc map.o subject.o
	$(CC) $(CFLAGS) -c test_helpers.cc

test_cases.o : test_cases.h test_cases.cc $(OBJECTS)
	$(CC) $(CFLAGS) -c test_cases.cc

clean : 
	rm ${OBJECTS} main.out