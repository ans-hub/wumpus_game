// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents map for main window
//
// This widget is the main widget, which is container for
// drawed net map, room buttons, player and info widgets

#ifndef WIDGET_MAP_H
#define WIDGET_MAP_H

#include <vector>
#include <tuple>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Group.H>

#include "3rdparty/audio_out.h"

#include "gui/widgets/widget_room.h"
#include "gui/widgets/widget_netdraw.h"
#include "gui/widgets/widget_player.h"
#include "gui/widgets/widget_info.h"
#include "gui/images.h"
#include "config.h"

namespace wumpus_game {

class WidgetMap : public Fl_Group
{
public:
  using Player  = WidgetPlayer;
  using Info    = WidgetInfo;
  using Room    = std::unique_ptr<WidgetRoom>;
  using VRooms  = std::vector<Room>;

  using CallbackFunc = void;
  using CommandFunc = void;
  
  WidgetMap(AudioOut&, Images&);
  virtual ~WidgetMap() { }

  void    Redraw(int level);
  void    MovePlayerInstantly(int to_room);
  void    MovePlayerAnimated(int to_room);  
  void    Deactivate(bool);
  void    Activate();

  // Getters and setters

  bool    IsReady() const { return ready_; }
  Point   GetRoomCoords(int) const;
  void    SetCallback(CallbackFunc* cb) { callback_ = cb; }
  void    SetCommand(CommandFunc* cmd) { command_ = cmd; }

  // Direct access widgets

  Info*   wdg_info_;
  VRooms  wdg_rooms_;
  Player* wdg_player_;

private:
  CallbackFunc*   callback_;
  CommandFunc*    command_;
  WidgetNetdraw*  wdg_pathes_;
  Trajectory      trajectory_;    // needs for animating players movements
  
  int             level_;
  bool            ready_;         // flag to show users that animation is over
  Images&         images_;

  void ResizeGroup(int);
  void DrawPlayer();
  void DrawRooms(int);
  void DrawLines(int);
  void SetLinesAngles(int);
  void RepositionRooms();  
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
  
  Point GetOffset(Fl_Widget*);

}  // namespace helpers

}  // namespace wumpus_game

#endif  //WIDGET_MAP_H