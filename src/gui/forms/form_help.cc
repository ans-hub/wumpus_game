// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: help window for gui windows container

#include "form_help.h"

namespace wumpus_game {

FormHelp::FormHelp ()
: Fl_Window(330, 470, "Help")
, window_{new Fl_Window(330, 470, "Help")}
, box_label_{new Fl_Box(30, 20, 270, 45, "HELP")}
, btn_quit_help_{new Fl_Button(40, 420, 250, 25, "Close")}
{
  TuneAppearance();
  window_->end();
}

FormHelp::~FormHelp()
{
  delete btn_quit_help_;
  delete box_label_;
  delete window_;
}

void FormHelp::TuneAppearance()
{
  window_->set_modal();
  window_->color((Fl_Color)34);
  window_->position((Fl::w() - window_->w())/2, (Fl::h() - window_->h())/2);
  box_label_->color((Fl_Color)84);
  box_label_->box(FL_PLASTIC_UP_FRAME);
  box_label_->color((Fl_Color)84);
  box_label_->labelsize(21);
  box_label_->labelcolor((Fl_Color)115);
}

}  // namespace wumpus_game