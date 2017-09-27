# Game "Hunt the wumpus"

My educational implementation of the game ["Hunt the wumpus"](https://en.wikipedia.org/wiki/Hunt_the_Wumpus), invented by [Gregory Yob](https://en.wikipedia.org/wiki/Gregory_Yob) in 1972 or 1973. 

## Historical game rules:

1. The Labirint - 20 rooms connected to each others by tunnels. Every room has three tunnels to the neighbor rooms.
2. The Player, the Wumpus, the Bats and the Bottomless pit are placed randomly in a different rooms.
3. The Player feels presence of the Wumpus, the Bats and/or the Bottomless in the adjancet rooms. This feels recieves to the Player by the messages, but in which room the danger is hidden is unknown.
4. The Bats - when the player goes in to the room with the Bats, the Bats carry the player in other randomly room. Feeling of the Bats is recieved to the Player by the message "I feel the wind".
5. The Bottomless pit - when the player goes in to the room with the pit, he dies and the game is over. Feeling of the Bottomless pit is recieved to the Player by the message "I feel the cold".
6. The Wumpus - the player must kill the Wumpus by shooting the adjacent room. If the Wumpus was not in that room where the Player was shooted, the Wumpus moved randomly to one of three rooms. Feeling of the Wumpus is recieved to the Player by the message "It`s smeels like Wumpus".
7. Meeting of the Wumpus and the Player means dead of the Player.

## Addon rules to my implementation:

1. To enter new level you shall kill all Wumpuses.

## Technical notes:

1. Original game has 20-rooms labirint since its based on plane projection of [regular dodecahedron](https://en.wikipedia.org/wiki/Regular_dodecahedron) using [Schlegel diagram](https://en.wikipedia.org/wiki/Schlegel_diagram). In my implementation this is more than 20 rooms in depends of game level.
2. *(copy of note from labyrinth.h)* Implementation of labyrinth based on directed graph with the degree of valency of all vertexes equal 3 (every vertex is connected by edges with 3 other vertex. In meaning of this app the Labyrinth is the Graph, the Rooms are vertexes and the tunnels are edges, the size is the Rooms count in the Labyrinth.
3. *(copy of note from labyrinth.h)* Connecting of the Rooms is auto-processed and based on plane projection of regular dodecahedron using Schlegel diagram. Neighbors Rooms are called as "left", "right" and "back". As you can see at the plane projection, here are presence three main pathes, called "center", "outer" and "inner". Center path consists of size/2 rooms, outer and inner pathes consists of size/4 rooms. Manually creating was avoided by me as not extentable. Scheme of connecting see in the `/info/graph.uml`
4. This Wumpus implementation use *stl vectors* as containers and *raw pointers*. Since the main goal of implementing of this game was educational purpose, I was used in some places raw pointer, and in some places smart pointers.
5. Possible unreachable memory leaks: FormHelp() while using Fl_Text_Buffer().
6. Of course, FLTK is not good tool for game development, but my purpose was educational. And this way was helpful for me to know principles of interface building using FLTK.