// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to gui of wumpus_game

#ifndef GUI_H
#define GUI_H

#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>

#include "labyrinth.h"

namespace wumpus_game {

namespace gui {

  void build_user_interface(const std::string&);
  void draw_cave(const Labyrinth&);
  void refresh_cave(const Labyrinth&);

}  // gui

}  // namespace wumpus_game

#endif  // GUI_H