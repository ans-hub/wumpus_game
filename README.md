# Game "Hunt the wumpus"

My educational implementation of the game ["Hunt the wumpus"](https://en.wikipedia.org/wiki/Hunt_the_Wumpus), invented by [Gregory Yob](https://en.wikipedia.org/wiki/Gregory_Yob) in 1972 or 1973. 

## Game rules:

1. You are the Hunter starts in the dark cave with rooms. Somewhere here lives one or more Wumpuses - terrible monster.
2. Your main goal is to kill all Wumpuses and return to home through the caves, underwater, dead city and some other places.
3. On the way you will be trapper in danger of two types:
  - things which move you from one room to another room (for example, The Bats);
  - things that kill you (for example, The Bottomless pits "
4. You have only the bow, the limited count of arrows on each level and the device that detects monsters and traps
5. Meeting of the Wumpus and the Hunter means dead of the Hunter.
6. Meeting with The Bats or similar things is means that you moved from meeting room to another one randomly.
7. Meeting with the trap like The Bottomless Pit means dead of the Hunter.
8. To leave the level, you should kill all Wumpuses, find the door and open it. At the first level the door is unhidden.

<p align="center" width="60%"><img src="screenshot.png"></p>

## Controls are:

```
LMB - move to room\n"
RMB - shot into the room\n"
MMB - mark/unmark the room\n";
```

## Install and run:

1. Since I work under the Linux I have not tested this game under the Windows.
2. To start the game you should do the next:
```bash
  $ cd src/
  $ ./main
```
3. The game was tested on Ubuntu 16.04

## Technical notes:

1. Original game has 20-rooms labirint since its based on plane projection of [regular dodecahedron](https://en.wikipedia.org/wiki/Regular_dodecahedron) using [Schlegel diagram](https://en.wikipedia.org/wiki/Schlegel_diagram). In my implementation this is more than 20 rooms in depends of game level.
2. *(copy of note from labyrinth.h)* Implementation of labyrinth based on directed graph with the degree of valency of all vertexes equal 3 (every vertex is connected by edges with 3 other vertex. In meaning of this app the Labyrinth is the Graph, the Rooms are vertexes and the tunnels are edges, the size is the Rooms count in the Labyrinth.
3. *(copy of note from labyrinth.h)* Connecting of the Rooms is auto-processed and based on plane projection of regular dodecahedron using Schlegel diagram. Neighbors Rooms are called as "left", "right" and "back". As you can see at the plane projection, here are presence three main pathes, called "center", "outer" and "inner". Center path consists of size/2 rooms, outer and inner pathes consists of size/4 rooms. Manually creating was avoided by me as not extentable. Scheme of connecting see in the `/info/graph.uml`
4. This Wumpus implementation use *stl vectors* as containers and *raw pointers*. Since the main goal of implementing of this game was educational purpose, I was used in some places raw pointer, and in some places smart pointers.
5. Possible unreachable memory leaks: FormHelp() while using Fl_Text_Buffer().
6. Of course, FLTK is not good tool for game development, but my purpose was educational. And this way was helpful for me to know principles of interface building using FLTK.