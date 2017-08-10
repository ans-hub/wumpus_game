// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: windows container for `gui` view and cotroller

#include "windows.h"

namespace wumpus_game {

Windows::Windows(AudioOut& audio) 
  : wnd_start_ { new FormStart() }
  , wnd_help_ { new FormHelp() }
  , wnd_main_{ new FormMain(audio) }
  , wdg_map_ { wnd_main_->wdg_map_ }
  , wdg_info_{ wnd_main_->wdg_info_ }
  , wdg_player_ { wnd_main_->wdg_map_->GetPlayer() }
  , audio_{audio}
{
  wdg_player_->UseAudio(audio_);
  SetFormsCallbacks();
}

Windows::~Windows()
{
  delete wnd_help_;
  delete wnd_start_;
  delete wnd_main_;
}

void Windows::SetFormsCallbacks()
{
  wnd_start_->btn_help_->callback(
    (Fl_Callback*)(cb_help_button), (void*)this
  );
  wnd_start_->btn_quit_->callback(
    (Fl_Callback*)(cb_quit_button), (void*)this
  );
  wnd_help_->btn_quit_help_->callback(
    (Fl_Callback*)(cb_quit_help_button), (void*)this
  );
  wnd_main_->callback(
    (Fl_Callback*)(cb_close_wnd_main_), (void*)this
  );
}

bool Windows::Show()
{
  wnd_start_->show();
  audio_.Play(config::GetBgMusic(1), true);

  return Fl::run();
}

void Windows::Close()
{
  wnd_start_->hide();
}

void Windows::cb_help_button(void*, void* w)
{
  ((Windows*)w)->wnd_help_->show();
}

void Windows::cb_quit_help_button(void*, void* w)
{
  ((Windows*)w)->wnd_help_->hide();
}

void Windows::cb_quit_button(void*, void* w)
{
  ((Windows*)w)->Close();
}

void Windows::cb_close_wnd_main_(void*, void* w)
{
  fl_message_hotspot(0);

  auto result = fl_choice(
    "Are you want to stop game?", "No", "Yes", 0
  );

  if (result == 1) {
    ((Windows*)w)->wnd_main_->hide();
    
  }
}

}  // namespace wumpus_game