// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: form represents map for main window

#ifndef FORM_MAP_H
#define FORM_MAP_H

#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>

#include "../widgets/room_button.h"
#include "../widgets/map_pathes.h"
#include "../helpers/draw_consts.h"

namespace wumpus_game {

class FormMap : public Fl_Group
{
public:
  using VRooms = std::vector<RoomButton*>;
  using VRoomsRef = const VRooms&;
  using CallbackFunc = void;
  using CommandFunc = void;
  
  FormMap();
  ~FormMap();
  void SetCallback(CallbackFunc* cb) { callback_ = cb; }
  void SetCommand(CommandFunc* cmd) { command_ = cmd; }
  void Deactivate() { for (auto& r : rooms_) r->deactivate(); }
  void Activate() { for (auto& r : rooms_) r->activate(); }
  VRoomsRef GetRooms() const { return rooms_; }
  void Redraw(int);

protected:
  void DrawRooms(int);
  void DrawLines(int);
  void ClearRooms();
  void ClearLines() { delete pathes_; }
  void ResizeGroup(int);
  void SetCallbacks();
  
private:
  VRooms        rooms_;
  MapPathes*    pathes_;
  CallbackFunc* callback_;
  CommandFunc*  command_;
};

namespace form_helpers {

  void tune_form(Fl_Group*);
  void tune_button(RoomButton*);

}  // namespace form_helpers

}  // namespace wumpus_game

#endif  //FORM_MAP_H