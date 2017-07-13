// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group box for main window contains RoomButtons

#ifndef GROUP_ROOMS_H
#define GROUP_ROOMS_H

#include <FL/Fl.H>
#include <FL/Fl_Group.H>

#include <vector>
#include <functional>

#include "room_button.h"

namespace wumpus_game {

class GroupRooms : public Fl_Group
{
public:
  using RoomButtons = std::vector<RoomButton*>;
  // using Callback = std::function<void(void*,void*)>;
  using Callback = void*;
  
  GroupRooms();
  ~GroupRooms();
  void DrawRooms(int);
  void ClearRooms();
  RoomButtons rooms_;
  // here pointer to function that must be callback
  Callback callback_;
  void* command_;
};

}  // namespace wumpus_game

#endif  //GROUP_ROOMS_H