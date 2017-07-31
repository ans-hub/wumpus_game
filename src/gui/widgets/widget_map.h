// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents map for main window

#ifndef WIDGET_MAP_H
#define WIDGET_MAP_H

#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>

#include "../widgets/widget_room.h"
#include "../widgets/widget_netdraw.h"
#include "../widgets/widget_player.h"
#include "../helpers/draw_consts.h"

namespace wumpus_game {

class WidgetMap : public Fl_Group
{
public:
  using VRooms = std::vector<WidgetRoom*>;
  using VRoomsRef = const VRooms&;
  // using Player = WidgetPlayer;
  using CallbackFunc = void;
  using CommandFunc = void;
  
  WidgetMap();
  ~WidgetMap();
  void SetCallback(CallbackFunc* cb) { callback_ = cb; }
  void SetCommand(CommandFunc* cmd) { command_ = cmd; }
  void Deactivate() { for (auto& r : rooms_) r->deactivate(); }
  void Activate() { for (auto& r : rooms_) r->activate(); }
  void RedrawRooms() { Deactivate(); Activate(); }
  VRoomsRef  GetRooms() const { return rooms_; }
  WidgetPlayer* GetPlayer() { return player_; }
  int GetRoomCoordX(int) const;
  int GetRoomCoordY(int) const;
  void Redraw(int);

protected:
  void ResizeGroup(int);
  void DrawPlayer();
  void DrawRooms(int);
  void DrawLines(int);
  void ClearRooms();
  void ClearPlayer();
  void ClearLines();
  void SetCallbacks();
  
private:
  VRooms          rooms_;     // mess in var names@!
  WidgetNetdraw*  pathes_;
  WidgetPlayer*   player_;
  CallbackFunc*   callback_;
  CommandFunc*    command_;
};

namespace form_helpers {

  void tune_form(Fl_Group*);
  void tune_button(WidgetRoom*);

}  // namespace form_helpers

}  // namespace wumpus_game

#endif  //WIDGET_MAP_H