// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group box for main window contains RoomButtons

#include "group_rooms.h"

namespace wumpus_game {

GroupRooms::GroupRooms ()
  : Fl_Group(10, 10, 200, 200, "_")
  , rooms_{}
{ }

GroupRooms::~GroupRooms()
{
  for (auto& v : rooms_) 
  {
    this->remove(v);
    delete v;
  }
}

void GroupRooms::DrawRooms(int level)
{
  for (int i = 0; i < (level+3*4); ++i) {
    RoomButton* btn = new RoomButton(i, (i*25)+20, 20, 30, 30);
    // btn->callback((Fl_Callback*)callback_.target<void>(), command_);
    btn->callback((Fl_Callback*)callback_, command_);
    btn->activate();
    this->add(btn);
    rooms_.push_back(btn);
  }
}

void GroupRooms::ClearRooms()
{
  for (auto& v : rooms_) delete v;
  rooms_.clear();
  rooms_.resize(0);
}

}  // namespace wumpus_game