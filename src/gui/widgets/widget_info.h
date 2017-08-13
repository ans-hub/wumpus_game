// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents info and control table for game window

#ifndef WIDGET_INFO_H
#define WIDGET_INFO_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_PNG_Image.H>

#include "gui/images.h"
#include "enums/enums.h"
#include "config.h"

namespace wumpus_game {

class WidgetInfo : public Fl_Group
{
public:
  explicit WidgetInfo(Images&);
  virtual ~WidgetInfo() { }
  void Show() { show(); }
  void Hide() { hide(); }
  void Redraw(int level);

  Images&     images_;
  Fl_Box*     box_level_;
  Fl_Box*     box_wumps_;
  Fl_Box*     box_bats_;
  Fl_Box*     box_pits_;
  Fl_Box*     box_arrows_;
  Fl_Button*  btn_continue_;
  Fl_Button*  btn_next_;  

private:
  void TuneAppearance();
};


}  // namespace wumpus_game

#endif  //WIDGET_INFO_H