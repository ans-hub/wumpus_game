// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: help window for gui windows container

#ifndef FORM_HELP_H
#define FORM_HELP_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Window.H>

namespace wumpus_game {

class FormHelp : public Fl_Window 
{
public: 
  FormHelp();
  ~FormHelp();
  Fl_Window*        window_;
  Fl_Box*           box_label_;
  Fl_Button*        btn_quit_help_;
  void Show() const { window_->show(); }
  void Hide() const { window_->hide(); }
private:
  void TuneAppearance();
};

}  // namespace wumpus_game

#endif  //FORM_HELP_H