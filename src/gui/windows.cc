// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: container of forms and resources

#include "windows.h"

namespace wumpus_game {

Windows::Windows(Images& images, AudioOut& audio)
  : images_{images}
  , audio_{audio}
  , wnd_start_{ new FormStart(images_) }    // see note #1 after code
  , wnd_help_{ new FormHelp(images_) }
  , wnd_main_{ new FormMain(images_, audio_) }
  , wdg_map_ { wnd_main_->wdg_map_ }
  , wdg_info_{ wnd_main_->wdg_map_->wdg_info_ }
  , wdg_player_ { wnd_main_->wdg_map_->wdg_player_ }
{
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
  auto bg_music = config::GetBackgroundMusic(1);
  audio_.Play(bg_music);

  wnd_start_->show();
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

// Note #1 : main reason to set audio through constructor is that audio is
// stored as reference. Since it is changable through object life time, here is
// just one right way to do this - send it throught constructors. The second way 
// is make pointers, but it would entail unnecessary checking inside classes 