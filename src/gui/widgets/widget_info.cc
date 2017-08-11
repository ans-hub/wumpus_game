// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents info and control table for game window

#include "widget_info.h"

namespace wumpus_game {

WidgetInfo::WidgetInfo (Images& images)
: Fl_Group(10, 70, 90, 90)
, images_{images}
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
  int w = config::level_width(level);
  int offset = config::main_wnd_offset; 

  this->image(
    images_.GetInfoImages(InfoStuff::COVER, level)
  );
  box_arrows_->image(
    images_.GetInfoImages(InfoStuff::ARROWS, level)
  );
  box_wumps_->image(
    images_.GetInfoImages(InfoStuff::WUMPS, level)
  );
  box_bats_->image(
    images_.GetInfoImages(InfoStuff::BATS, level)
  );
  box_pits_->image(
    images_.GetInfoImages(InfoStuff::PITS, level)
  );
  box_level_->image(
    images_.GetInfoImages(InfoStuff::LEVEL, level)
  );
  btn_continue_->image(
    images_.GetInfoImages(InfoStuff::CONTINUE, level)
  );

  resize(offset + (w/2) - (90/2), (90/2)+(w/2), 90, 90);
  redraw();
}

void WidgetInfo::TuneAppearance()
{
  // btn_next_->hide();

  align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_CLIP);
  labelcolor(FL_WHITE);

  box_arrows_->align(Fl_Align(256));
  box_arrows_->labelcolor(FL_WHITE);
  box_pits_->align(Fl_Align(256));
  box_pits_->labelcolor(FL_WHITE);
  box_bats_->align(Fl_Align(256));
  box_bats_->labelcolor(FL_WHITE);
  box_wumps_->align(Fl_Align(256));
  box_wumps_->labelcolor(FL_WHITE);
  box_level_->align(Fl_Align(256));
  box_level_->labelcolor(FL_WHITE);
  btn_continue_->align(Fl_Align(256));
}

}  // namespace wumpus_game