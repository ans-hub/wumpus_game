// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: help window for gui windows container

#ifndef FORM_HELP_H
#define FORM_HELP_H

#include <sstream>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Double_Window.H>

#include "config.h"
#include "gui/images.h"

namespace wumpus_game {

class FormHelp : public Fl_Double_Window 
{
public: 
  explicit FormHelp(Images&);
  virtual ~FormHelp();
  
  Images&           images_;

  Fl_Box*           box_label_;
  Fl_Button*        btn_quit_help_;
  Fl_Text_Display*  display_;
  Fl_Text_Buffer*   output_;

private:
  void TuneAppearance();
  void FillOutput() const;
};

}  // namespace wumpus_game

#endif  //FORM_HELP_H