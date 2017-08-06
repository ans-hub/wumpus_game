// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents info and control table for game window

#include "widget_info.h"

namespace wumpus_game {

WidgetInfo::WidgetInfo ()
: Fl_Group(10, 70, 90, 90)
, img_cover_{new Fl_PNG_Image("gui/widgets/img/info_bg.png")}
, img_level_{new Fl_PNG_Image("gui/widgets/img/info_level.png")}
, img_wumps_{new Fl_PNG_Image("gui/widgets/img/info_wumps.png")}
, img_bats_{new Fl_PNG_Image("gui/widgets/img/info_bats.png")}
, img_pits_{new Fl_PNG_Image("gui/widgets/img/info_pits.png")}
, img_arrows_{new Fl_PNG_Image("gui/widgets/img/info_arrows.png")}
, img_continue_{new Fl_PNG_Image("gui/widgets/img/info_continue.png")}
, img_repeat_{new Fl_PNG_Image("gui/widgets/img/info_repeat.png")}
, img_repeat_na_{new Fl_PNG_Image("gui/widgets/img/info_repeat_na.png")}
, box_level_{new Fl_Box(x()+55, y()+10, 20, 20)}
, box_wumps_{new Fl_Box(x()+15, y()+10, 20, 20)}
, box_bats_{new Fl_Box(x()+15, y()+60, 20, 20)}
, box_pits_{new Fl_Box(x()+15, y()+35, 20, 20)}
, box_arrows_{new Fl_Box(x()+55, y()+35, 20, 20)}
, btn_continue_{new Fl_Button(x()+50, y()+60, 28, 20)}
, btn_next_{new Fl_Button(x()+15, y()+60, 20, 20)}
{
  TuneAppearance();
  end();
}

void WidgetInfo::Redraw(int level)
{
  int w = draw_consts::level_width(level);
  int offset = draw_consts::main_wnd_offset; 

  resize(offset + (w/2) - (90/2), (90/2)+(w/2), 90, 90);
  redraw();
}

void WidgetInfo::TuneAppearance()
{
  // btn_next_->hide();

  image(img_cover_);
  align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_CLIP);
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
  btn_continue_->image(img_repeat_na_);
  btn_continue_->align(Fl_Align(256));
}

}  // namespace wumpus_game