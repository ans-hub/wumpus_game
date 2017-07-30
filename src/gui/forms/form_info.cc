// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: form represents info table for game window

#include "form_info.h"

namespace wumpus_game {

// Make coor put in initialzer list not in Resize() (Redraw())

FormInfo::FormInfo ()
: Fl_Group(10, 70, 300, 35)
, img_cover_{new Fl_PNG_Image("../src/gui/forms/img/info_bg.png")}
, img_level_{new Fl_PNG_Image("../src/gui/forms/img/info_level.png")}
, img_wumps_{new Fl_PNG_Image("../src/gui/forms/img/info_wumps.png")}
, img_bats_{new Fl_PNG_Image("../src/gui/forms/img/info_bats.png")}
, img_pits_{new Fl_PNG_Image("../src/gui/forms/img/info_pits.png")}
, img_arrows_{new Fl_PNG_Image("../src/gui/forms/img/info_arrows.png")}
, box_level_{new Fl_Box(x()+10, y()+25, 15, 15)}
, box_wumps_{new Fl_Box(1,1,1,1)}
, box_bats_{new Fl_Box(1,1,1,1)}
, box_pits_{new Fl_Box(1,1,1,1)}
, box_arrows_{new Fl_Box(1,1,1,1)}
, btn_next_{new Fl_Button(x()+10, y()+10, 15, 15, "!")}
, btn_continue_{new Fl_Button(x()+40, y()+10, 15, 15, ">")}
, btn_help_{new Fl_Button(x()+70, y()+10, 15, 15, "?")}
{
  TuneAppearance();
  end();
}

FormInfo::~FormInfo()
{
  delete btn_next_;
  delete btn_help_;
  delete btn_continue_;
  delete box_arrows_;
  delete box_pits_;
  delete box_bats_;
  delete box_wumps_;
  delete box_level_;
  delete img_arrows_;
  delete img_pits_;
  delete img_bats_;
  delete img_wumps_;
  delete img_level_;
  delete img_cover_;
}

void FormInfo::Redraw(int level)
{
  int w = draw_consts::level_width(level);
  int offset = draw_consts::main_wnd_offset; 
  
  resize(offset + (w/2) - (90/2), (90/2)+(w/2), 90, 90);
  
  btn_next_->resize(x()+10, y()+10, 15, 15);
  btn_continue_->resize(x()+40, y()+10, 15, 15);
  btn_help_->resize(x()+70, y()+10, 15, 15);

  box_level_->resize(x()+10, y()+25, 15, 15);
  box_wumps_->resize(x()+35, y()+25, 15, 15);
  box_bats_->resize(x()+60, y()+25, 15, 15);
  box_pits_->resize(x()+10, y()+40, 15, 15);
  box_arrows_->resize(x()+35, y()+40, 15, 15);
  
  redraw();
  // int offset = 30;
  // int w = draw_consts::level_width(level) + offset * 2;
  // int h = w + 100;
  
  // resize(1, 1, w, h);
  // position((Fl::w() - this->w())/2, (Fl::h() - this->h())/2);
  // box_cover_->resize(-5, 0, this->w(), this->h());
  // box_level_->resize(2, 54, this->w(), this->h()/2);
  // box_label_->resize(30, 20, this->w()-60, 45);
  // // btn_restart_->resize(this->w()-50-270, this->h()-40, 90, 25);
  // btn_help_->resize(this->w()-40-180, this->h()-40, 90, 25);
  // btn_continue_->resize(this->w()-30-90, this->h()-40, 90, 25);

//   // redraw();
}

void FormInfo::TuneAppearance()
{
  // set_modal();
  // color((Fl_Color)34);
  // position((Fl::w() - this->w())/2, (Fl::h() - this->h())/2);
  // // box_cover_->image(img_bg_);
  // // box_cover_->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_CLIP);
  // image(img_bg_);
  // btn_continue_->resizable(0);
  // btn_help_->resizable(0);
  image(img_cover_);
  align(Fl_Align(513));
  box_arrows_->image(img_arrows_);
  box_arrows_->align(Fl_Align(256));
  box_pits_->image(img_pits_);
  box_pits_->align(Fl_Align(256));
  box_bats_->image(img_bats_);
  box_bats_->align(Fl_Align(256));
  box_wumps_->image(img_wumps_);
  box_wumps_->align(Fl_Align(256));
  box_level_->image(img_level_);
  box_level_->align(Fl_Align(256));
  box(FL_PLASTIC_UP_FRAME);
  // redraw();
  // box_label_->color((Fl_Color)84);
  // box_label_->labelsize(28);
  // box_label_->labelcolor((Fl_Color)115);
}

}  // namespace wumpus_game