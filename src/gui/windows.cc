// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: windows container for `gui` view and cotroller

#include "windows.h"

namespace wumpus_game {

Windows::Windows() 
  : main_wnd_{ new FormMain() }
  , popup_wnd_{ new FormPopup() }
  , box_rooms_ { new GroupRooms() }
{
  AddWidget(box_rooms_);
}

Windows::~Windows()
{
  RemoveWidget(box_rooms_);
  delete main_wnd_;
  delete popup_wnd_;
  delete box_rooms_;
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

void Windows::RedrawRooms(int i)
{
  box_rooms_->ClearRooms();
  box_rooms_->DrawRooms(i);
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
  w->hide();
}

void Windows::HideWidget(Fl_Widget* w)
{
  w->show();
}

}  // namespace wumpus_game