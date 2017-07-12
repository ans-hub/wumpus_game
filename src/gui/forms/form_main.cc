// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main window for gui windows container

#include "form_main.h"

namespace wumpus_game {

FormMain::FormMain ()
: Fl_Window(200, 200, "_")
, rooms_{}
, window_{new Fl_Window(425, 700, "Hunt the Wumpus")}
, img_level_{(new Fl_PNG_Image("gui/forms/data/level.png"))}
, img_cover_{(new Fl_PNG_Image("gui/forms/data/cover.png"))}
, box_cover_{new Fl_Box(-5, 0, 435, 625)}
, box_level_{new Fl_Box(2, 54, 425, 390)}
, box_label_{new Fl_Box(30, 20, 370, 45, "HUNT THE WUMPUS")}
, btn_start_{new Fl_Button(27, 655, 105, 25, "Start new")}
, btn_help_{new Fl_Button(165, 655, 105, 25, "Help")}
, btn_quit_{new Fl_Button(297, 655, 105, 25, "Quit")}
, output_{new Fl_Text_Buffer()}
, display_{new Fl_Text_Display(26, 435, 375, 200, "Output")}
{
  TuneAppearance();
  window_->end();
}

FormMain::~FormMain()
{
  for (auto v : rooms_) delete v;
  delete display_;
  delete output_;
  delete btn_quit_;
  delete btn_help_;
  delete btn_start_;
  delete box_label_;
  delete box_level_;
  delete box_cover_;
  delete img_cover_;
  delete img_level_;
  delete window_;
}

void FormMain::TuneAppearance()
{
  // windows_size
  window_->color((Fl_Color)34);
  box_cover_->image(img_cover_);
  box_cover_->align(Fl_Align(192));
  box_level_->image(img_level_);
  box_level_->align(Fl_Align(192));
  box_label_->box(FL_PLASTIC_UP_FRAME);
  box_label_->color((Fl_Color)84);
  box_label_->labelsize(28);
  box_label_->labelcolor((Fl_Color)115);
  display_->box(FL_PLASTIC_UP_FRAME);
  display_->color(FL_BLACK);
  display_->labelcolor((Fl_Color)25);
  display_->textcolor((Fl_Color)25);
  display_->align(FL_ALIGN_TOP);
  display_->buffer(output_);
  display_->wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0);
}

}  // namespace wumpus_game