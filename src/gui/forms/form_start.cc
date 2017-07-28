// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: start window for gui windows container

#include "form_start.h"

namespace wumpus_game {

FormStart::FormStart ()
: Fl_Window(330, 270, "Hunt the Wumpus")
// , window_{new Fl_Window(330, 270, "Hunt the Wumpus")}
, box_btns_{new Fl_Box(30, 80, 270, 170)}
, box_label_{new Fl_Box(30, 20, 270, 45, "HUNT THE WUMPUS")}
, btn_start_{new Fl_Button(90, 100, 150, 25, "Start new")}
, btn_help_{new Fl_Button(90, 150, 150, 25, "Help")}
, btn_quit_{new Fl_Button(90, 200, 150, 25, "Quit")}
{
  TuneAppearance();
  end();
  // window_->end();
}

FormStart::~FormStart()
{
  delete btn_quit_;
  delete btn_help_;
  delete btn_start_;
  delete box_label_;
  delete box_btns_; 
  // delete window_;
}

void FormStart::TuneAppearance()
{
  color((Fl_Color)34);
  position((Fl::w() - w())/2, (Fl::h() - h())/2);
  // window_->color((Fl_Color)34);
  // window_->position((Fl::w() - window_->w())/2, (Fl::h() - window_->h())/2);
  box_btns_->box(FL_PLASTIC_UP_FRAME);
  box_btns_->color((Fl_Color)84);
  box_label_->color((Fl_Color)84);
  box_label_->box(FL_PLASTIC_UP_FRAME);
  box_label_->color((Fl_Color)84);
  box_label_->labelsize(21);
  box_label_->labelcolor((Fl_Color)115);
}

}  // namespace wumpus_game