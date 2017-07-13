// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: windows container for `gui` view and cotroller

#include "windows.h"

namespace wumpus_game {

Windows::Windows() 
  : main_wnd_{ new FormMain() }
  , popup_wnd_{ new FormPopup() }
  , map_box_ { new FormMap() }
{
  AddWidget(map_box_);
}

Windows::~Windows()
{
  RemoveWidget(map_box_);
  delete main_wnd_;
  delete popup_wnd_;
  delete map_box_;
}

void Windows::Show()
{
  main_wnd_->window_->show();
  Fl::run();
}

void Windows::Close()
{
  main_wnd_->window_->hide();
}

void Windows::Redraw()
{
  main_wnd_->window_->redraw();
}

void Windows::AddWidget(Fl_Widget* w)
{
  main_wnd_->window_->add(w);
}

void Windows::RemoveWidget(Fl_Widget* w)
{
  main_wnd_->window_->remove(w);
}

void Windows::ShowWidget(Fl_Widget* w)
{
  w->show();
}

void Windows::HideWidget(Fl_Widget* w)
{
  w->hide();
}

}  // namespace wumpus_game