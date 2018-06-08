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

## Gameplay video on youtube:

<p align="center" width="60%"><a href="https://youtu.be/8MtrtkYhbKU"><img src="screenshot.png"></a></p>

## Controls are:

```
LMB - move to room\n"
RMB - shot into the room\n"
MMB - mark/unmark the room\n";
```

## Installation under the Windows

1. Download game to paricular directory and tune build dir


* download game and unpack it to, i.e., "c:/wump/"
* create directory "build" in "c:/wump/"
* go to "CMake -> Change CMake Settings"
* change `buildRoot` to preffered, i.e. `c:\\wump\\build\\`

`Linux:`

* clone git repository to preffered dir (i.e. "~/wump/")
* make dir "build" inside "~/wump"

### Dependicies:

Game has following dependicies:
* game`s gui based on `FLTK` library
* game`s audio output is provided by `audio_out` library (wrapper to Bass library)

### Install FLTK:

Standart installation of game is provided by `cmake`. Thus to install game using`cmake` we should install `FLTK` library by `cmake` too (since only by this install type we would have all necessary files for `cmake`).

1. Download latest `FLTK` release from (fltk`s site)[http://www.fltk.org/software.php]
2. Install:

`Linux:`
```
  # ...after unpacking downloaded archive
  $ cd build		# created at previous step
  $ cmake ../
  $ make
  # ...move built directory to preffered (i.e. ~/libs/fltk_1.3.4)
```
`Windows:`
```
  ... unpack to directory, i.e. "c:/fltk_1.3.4"
  ... make directory "build" inside
  Open -> Folder -> "c:/fltk_1.3.4"
  CMake->Build All
  ... after build have been completed
  ... move built directory (usually from ~/HOME_DIR/CMakeBuilds/..hash..) to preffered
  ... i.e. "c:/fltk_1.3.4/"
```

### Install BASS:

`Linux:`
```bash
  $ wget http://us.un4seen.com/files/bass24-linux.zip
  $ unzip bass24-linux.zip -d tmp/
  $ sudo cp tmp/mp3free/libbass.so /usr/local/lib/
  $ sudo chmod a+rx /usr/local/lib/libbass.so
  $ sudo ldconfig
  $ rm -rf tmp/ bass24-linux.zip
```

`Windows:`
```
  Download archive from http://www.un4seen.com/download.php?bass24
  Unpack bass.dll and c/bass.lib to the root of build directory
```  

### Build game

`Windows:`

* go to "CMake -> Change CMake Settings"
* add to `cmakeCommandArgs` directory which contains build of FLTK i.e. "cmakeCommandArgs": "-DFLTK_DIR:PATH=\"c:/fltk-1.3.4/build/\"",
cmake ../ -DFLTK_DIR:PATH="~/projects/cpp/_libs/fltk-1.3/build"

## Technical notes:

1. Original game has 20-rooms labirint since its based on plane projection of [regular dodecahedron](https://en.wikipedia.org/wiki/Regular_dodecahedron) using [Schlegel diagram](https://en.wikipedia.org/wiki/Schlegel_diagram). In my implementation this is more than 20 rooms in depends of game level.
2. *(copy of note from labyrinth.h)* Implementation of labyrinth based on directed graph with the degree of valency of all vertexes equal 3 (every vertex is connected by edges with 3 other vertex. In meaning of this app the Labyrinth is the Graph, the Rooms are vertexes and the tunnels are edges, the size is the Rooms count in the Labyrinth.
3. *(copy of note from labyrinth.h)* Connecting of the Rooms is auto-processed and based on plane projection of regular dodecahedron using Schlegel diagram. Neighbors Rooms are called as "left", "right" and "back". As you can see at the plane projection, here are presence three main pathes, called "center", "outer" and "inner". Center path consists of size/2 rooms, outer and inner pathes consists of size/4 rooms. Manually creating was avoided by me as not extentable. Scheme of connecting see in the `/info/graph.uml`
4. This Wumpus implementation use *stl vectors* as containers and *raw pointers*. Since the main goal of implementing of this game was educational purpose, I was used in some places raw pointer, and in some places smart pointers.
5. Possible unreachable memory leaks: FormHelp() while using Fl_Text_Buffer().
6. Of course, FLTK is not good tool for game development, but my purpose was educational. And this way was helpful for me to know principles of interface building using FLTK.
