// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents info and control table for game window

#include "widget_info.h"

namespace wumpus_game {

// Make coor put in initialzer list not in Resize() (Redraw())

WidgetInfo::WidgetInfo ()
: Fl_Group(10, 70, 300, 35)
, img_cover_{new Fl_PNG_Image("../src/gui/widgets/img/info_bg.png")}
, img_bg_{new Fl_Tiled_Image(img_cover_, 0, 0)}
, img_level_{new Fl_PNG_Image("../src/gui/widgets/img/info_level.png")}
, img_wumps_{new Fl_PNG_Image("../src/gui/widgets/img/info_wumps.png")}
, img_bats_{new Fl_PNG_Image("../src/gui/widgets/img/info_bats.png")}
, img_pits_{new Fl_PNG_Image("../src/gui/widgets/img/info_pits.png")}
, img_arrows_{new Fl_PNG_Image("../src/gui/widgets/img/info_arrows.png")}
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

void WidgetInfo::Redraw(int level)
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
}

void WidgetInfo::TuneAppearance()
{
  image(img_bg_);
  align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_CLIP);
  box(FL_PLASTIC_UP_FRAME);
  labelcolor(FL_WHITE);
  box_arrows_->image(img_arrows_);
  box_arrows_->align(Fl_Align(256));
  box_arrows_->labelcolor(FL_WHITE);
  box_pits_->image(img_pits_);
  box_pits_->align(Fl_Align(256));
  box_pits_->labelcolor(FL_WHITE);
  box_bats_->image(img_bats_);
  box_bats_->align(Fl_Align(256));
  box_bats_->labelcolor(FL_WHITE);
  box_wumps_->image(img_wumps_);
  box_wumps_->align(Fl_Align(256));
  box_wumps_->labelcolor(FL_WHITE);
  box_level_->image(img_level_);
  box_level_->align(Fl_Align(256));
  box_level_->labelcolor(FL_WHITE);
}

}  // namespace wumpus_game