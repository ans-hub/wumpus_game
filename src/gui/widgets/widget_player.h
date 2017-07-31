// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents player on the map

#ifndef WIDGET_PLAYER_H
#define WIDGET_PLAYER_H

#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Group.H>

#include "../helpers/point.h"
#include "../helpers/trajectory.h"

namespace wumpus_game {

class WidgetPlayer : public Fl_Group
{
public:
  WidgetPlayer();
  ~WidgetPlayer();
  
  void DoesMove(int x, int y);
  void DoesShot();
  void DoesKillWump();
  void DoesKilledByWump();
  void DoesKilledByPits();
  void DoesUnknownAction();
  void DoesFeels(bool, bool, bool);
  void AnimateBegin(int x, int y);
  void AnimateContinue();
  void AnimateFinish();

private:
  Fl_Group*     grp_player_;
  Fl_Group*     grp_feels_;
  Fl_Box*       box_wumps_;  
  Fl_Box*       box_bats_;  
  Fl_Box*       box_pits_;  
  Fl_PNG_Image* img_stay_;
  Fl_PNG_Image* img_shot_;
  Fl_PNG_Image* img_bats_; 
  Fl_PNG_Image* img_kill_wump_;
  Fl_PNG_Image* img_unknown_;
  Fl_PNG_Image* img_dead_wump_;
  Fl_PNG_Image* img_dead_pits_;
  Fl_PNG_Image* img_feels_box_;
  Fl_PNG_Image* img_feels_bats_;
  Fl_PNG_Image* img_feels_pits_;
  Fl_PNG_Image* img_feels_wumps_;
  Trajectory    trajectory_;
  
  void TuneAppearance();

  static void cb_move_bats(void*);
  static void cb_stop_bats(void*);
};

}  // namespace wumpus_game

#endif  // WIDGET_PLAYER_H