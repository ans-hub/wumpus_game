// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents map for main window

#ifndef WIDGET_MAP_H
#define WIDGET_MAP_H

#include <vector>
#include <tuple>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Group.H>

#include "gui/widgets/widget_room.h"
#include "gui/widgets/widget_netdraw.h"
#include "gui/widgets/widget_player.h"
#include "audio/audio_out.h"
#include "settings/config.h"

namespace wumpus_game {

class WidgetMap : public Fl_Group
{
public:
  using Marked = bool;
  using Active = bool;
  using Deimaged = bool;
  using CallbackFunc = void;
  using CommandFunc = void;
  
  using VRooms = std::vector<WidgetRoom*>;
  using VRoomsRef = const VRooms&;
  using WPlayer = WidgetPlayer;
  using RoomState = std::tuple<Marked,Active,Deimaged>;
  using WRoomsState = std::vector<RoomState>;
  
  explicit WidgetMap(AudioOut&);
  virtual ~WidgetMap();

  bool      IsReady() const { return ready_; }
  VRoomsRef GetRooms() const { return wdg_rooms_; }
  WPlayer*  GetPlayer() { return wdg_player_; }
  Point     GetRoomCoords(int) const;

  void      Redraw(int);
  void      MovePlayerInstantly(int);
  void      MovePlayerAnimated(int);  
  void      Deactivate(bool d);
  void      Activate();
  
  void      SetCallback(CallbackFunc* cb) { callback_ = cb; }
  void      SetCommand(CommandFunc* cmd) { command_ = cmd; }

private:
  VRooms          wdg_rooms_;     // mess in var names@!
  WidgetNetdraw*  wdg_pathes_;
  WidgetPlayer*   wdg_player_;
  CallbackFunc*   callback_;
  CommandFunc*    command_;
  Trajectory      trajectory_;
  WRoomsState     rooms_state_;
  int             level_;
  bool            ready_;

  void ResizeGroup(int);
  void DrawPlayer();
  void DrawRooms(int);
  void DrawLines(int);
  void SetLinesAngles(int);
  void ClearRooms();
  void SaveRoomsState();
  void LoadRoomsState();
  void RedrawCurrentByRotate();
  void SetRotateCallback();
  void SetRoomsCallback();
  void TuneAppearance();
  
  void RefreshAnimateTrajectory();
  static void cb_move_player_animated(void*);
  static void cb_rotate_map(void*);
};

namespace helpers {
  
  Point get_offset(Fl_Widget*);

}  // namespace helpers

}  // namespace wumpus_game

#endif  //WIDGET_MAP_H