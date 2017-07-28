// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: start window for gui windows container

#ifndef FORM_START_H
#define FORM_START_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Window.H>

namespace wumpus_game {

class FormStart : public Fl_Window 
{
public: 
  FormStart();
  ~FormStart();
  void Show() { show(); }
  void Hide() { hide(); }
  Fl_Box*           box_btns_;
  Fl_Box*           box_label_;
  Fl_Button*        btn_start_;
  Fl_Button*        btn_help_;
  Fl_Button*        btn_quit_;
private:
  void TuneAppearance();
};

}  // namespace wumpus_game

#endif  //FORM_START_H