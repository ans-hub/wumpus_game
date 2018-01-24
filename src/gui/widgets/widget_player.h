// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents player on the map

#ifndef WIDGET_PLAYER_H
#define WIDGET_PLAYER_H

#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_PNG_Image.H>

#include "3rdparty/audio/audio_out.h"

#include "gui/images.h"
#include "gui/helpers/point.h"
#include "gui/helpers/trajectory.h"
#include "config.h"
#include "enums/enums.h"

namespace wumpus_game {

class WidgetPlayer : public Fl_Group
{
public:
  using State = PlayerState;

  WidgetPlayer(AudioOut&, Images&);
  virtual ~WidgetPlayer() { }
  
  void Redraw(int level);
  void SetState(State);
  void SetDefaultState() { SetState(State::STAY); }
  void ShowFeels(bool, bool, bool);
  void SetCurrRoom(int room) { room_ = room; }
  int  GetCurrRoom() const { return room_; }

private:
  void TuneAppearance();

  int         room_;   // used by parent widgets for animate
  int         level_;
  State       state_;
  AudioOut&   audio_;
  Images&     images_;
  
  Fl_Box*     box_player_;
  Fl_Box*     box_wumps_;
  Fl_Box*     box_bats_;
  Fl_Box*     box_pits_;
};

}  // namespace wumpus_game

#endif  // WIDGET_PLAYER_H