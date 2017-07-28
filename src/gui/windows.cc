// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: windows container for `gui` view and cotroller

#include "windows.h"

namespace wumpus_game {

Windows::Windows() 
  : wnd_start_ { new FormStart() }
  , wnd_help_ { new FormHelp() }
  , wnd_main_{ new FormMain() }
  , wnd_popup_{ new FormPopup() }
  , wdg_map_ { new FormMap() }
{
  wnd_main_->begin();
  wnd_main_->add(wdg_map_);
  wnd_main_->end();
  SetChildrenCallbacks();
}

Windows::~Windows()
{
  wnd_main_->remove(wdg_map_); // to prevent segmentation fault
  delete wnd_start_;
  delete wnd_help_;
  delete wnd_main_;
  delete wnd_popup_;
  delete wdg_map_;
}

void Windows::SetChildrenCallbacks()
{
  wnd_start_->btn_help_->callback(
    (Fl_Callback*)(gui_helpers::cb_help_button), (void*)this
  );
  wnd_help_->btn_quit_help_->callback(
    (Fl_Callback*)(gui_helpers::cb_quit_help_button), (void*)this
  );
  wnd_main_->callback(
    (Fl_Callback*)(gui_helpers::cb_close_wnd_main_), (void*)this
  );
  wnd_main_->btn_help_->callback(
    (Fl_Callback*)(gui_helpers::cb_help_button), (void*)this
  );
}

void Windows::Show()
{
  wnd_start_->show();
  Fl::run();
}

void Windows::Close()
{
  wnd_start_->hide();
}

void Windows::ShowMain() const
{
  wnd_main_->Show();
} 

void Windows::HideMain() const
{
  wnd_main_->Hide();
}

void Windows::ShowHelp() const
{
  wnd_help_->Show();
}

void Windows::HideHelp() const
{
  wnd_help_->Hide();
}

void Windows::Redraw(int level)
{
  wnd_main_->Redraw(level); 
  wdg_map_->Redraw(level);
}

void Windows::ShowWidget(Fl_Widget* w)
{
  w->show();
}

void Windows::HideWidget(Fl_Widget* w)
{
  w->hide();
}

namespace gui_helpers {

void cb_help_button(void*, void* w)
{
  ((Windows*)w)->ShowHelp();
}

void cb_quit_help_button(void*, void* w)
{
  ((Windows*)w)->HideHelp();
}

void cb_close_wnd_main_(void*, void* w)
{
  fl_message_hotspot(0);
  auto result = fl_choice(
    "Are you want to stop game?", "No", "Yes", 0
  );
  if (result == 1) {
    ((Windows*)w)->HideMain();
  }
}

}  // namespace gui_helpers

}  // namespace wumpus_game