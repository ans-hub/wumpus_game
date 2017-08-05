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
#include "gui/helpers/draw_consts.h"

namespace wumpus_game {

class WidgetPlayer : public Fl_Group
{
public:
  enum State
  {
    MOVED_BATS,
    STAY,
    WALK,
    SHOT,
    KILLED_BY_WUMP,
    KILLED_BY_PITS,
    KILL_WUMP,
    HAVENT_ARROWS,
    UNKNOWN_ACTION
  };

  WidgetPlayer();
  ~WidgetPlayer() { }
  
  void SetStateImage(State);
  void ShowFeelsIcons(bool, bool, bool);
  void StaticMove(const Point&);
  void AnimateMove(const Point&, Trajectory::Type);
  bool IsAnimateInProgress() const { return !trajectory_.Empty(); }

private:

  void TuneAppearance();

  void AnimateMoveContinue();
  void AnimateMoveFinish();

  static void cb_animate_move(void*);

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
  
  Trajectory    trajectory_;  
};

}  // namespace wumpus_game

#endif  // WIDGET_PLAYER_H