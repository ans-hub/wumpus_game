// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: help window for gui windows container

#include "form_help.h"

namespace wumpus_game {

FormHelp::FormHelp ()
  : Fl_Double_Window(330, 470, "Help")
  , box_label_{new Fl_Box(30, 20, 270, 45, "HELP")}
  , btn_quit_help_{new Fl_Button(30, 420, 270, 25, "Close")}
  , display_{new Fl_Text_Display(30, 90, 270, 310) }
  , output_{new Fl_Text_Buffer()}
{
  TuneAppearance();
  FillOutput();
  end();
}

FormHelp::~FormHelp()
{
  display_->buffer(nullptr);
  output_->text("");
  delete output_;
}

void FormHelp::TuneAppearance()
{
  set_modal();
  color((Fl_Color)34);
  position((Fl::w() - this->w())/2, (Fl::h() - this->h())/2);
  box_label_->color((Fl_Color)84);
  box_label_->box(FL_PLASTIC_UP_FRAME);
  box_label_->color((Fl_Color)84);
  box_label_->labelsize(21);
  box_label_->labelcolor((Fl_Color)115);
  display_->textsize(13);
  display_->color((Fl_Color)84);  
  display_->box(FL_PLASTIC_UP_FRAME);
  display_->color((Fl_Color)34);
  display_->labelcolor((Fl_Color)25);
  display_->textcolor((Fl_Color)25);
  display_->buffer(output_);
  display_->wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0);
}

void FormHelp::FillOutput() const
{
  std::stringstream sst{};
  sst << "You are in the dark cave with rooms. Somewhere here lives "
      << "one or more Wumpuses. You have the bow and arrows. Find and kill all"
      << "Wumpus! And be aware about presence of other danger things - the Bats "
      << "and the Bottomless pits\n\n"; 
  sst << "If the Wumpus in the one of the neighboring rooms, you feels its."
      << "When you feels the wind it means that the Bats are near. And if you"
      << "feel the cold its means that the Bottomless Pit is near\n\n";
  sst << "Left mouse button - move to room\n";
  sst << "Right mouse button - shot into the room\n";
  output_->text("");
  output_->append(sst.str().c_str());
}

}  // namespace wumpus_game