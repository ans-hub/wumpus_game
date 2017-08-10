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

#include "gui/helpers/point.h"
#include "gui/helpers/trajectory.h"
#include "audio/audio_out.h"
#include "settings/config.h"
#include "settings/enums.h"

namespace wumpus_game {

class WidgetPlayer : public Fl_Group
{
public:
  using State = PlayerState;

  explicit WidgetPlayer(AudioOut&);
  virtual ~WidgetPlayer() { }
  
  void UseAudio(AudioOut& audio) { audio_ = audio; }
  void SetState(State);   // sets image and plays relevant sound
  void SetDefaultState() { SetState(State::STAY); }
  void ShowFeelsIcons(bool, bool, bool);
  void SetCurrRoom(int room) { curr_room_ = room; }
  int  GetCurrRoom() const { return curr_room_; }

private:
  void TuneAppearance();

  int           curr_room_;   // used by parent widgets for animate
  AudioOut&     audio_;
  State         last_state_;  // needs to determine which sound is playing
  
  Fl_Box*       box_player_;
  Fl_Box*       box_wumps_;
  Fl_Box*       box_bats_;
  Fl_Box*       box_pits_;
  Fl_PNG_Image* img_bg_;
  Fl_PNG_Image* img_stay_;
  Fl_PNG_Image* img_shot_;
  Fl_PNG_Image* img_walk_;
  Fl_PNG_Image* img_bats_;
  Fl_PNG_Image* img_kill_wump_;
  Fl_PNG_Image* img_no_arrows_;
  Fl_PNG_Image* img_unknown_;
  Fl_PNG_Image* img_dead_wump_;
  Fl_PNG_Image* img_dead_pits_;
  Fl_PNG_Image* img_feels_box_;
  Fl_PNG_Image* img_feels_bats_;
  Fl_PNG_Image* img_feels_pits_;
  Fl_PNG_Image* img_feels_wumps_;
};

}  // namespace wumpus_game

#endif  // WIDGET_PLAYER_H