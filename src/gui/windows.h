// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: container of forms and resources

#ifndef GUI_WINDOWS_H
#define GUI_WINDOWS_H

#include "FL/fl_ask.H"

#include "gui/images.h"
#include "audio/audio_out.h"
#include "gui/forms/form_start.h"
#include "gui/forms/form_help.h"
#include "gui/forms/form_main.h"
#include "gui/widgets/widget_info.h"
#include "gui/widgets/widget_map.h"
#include "config.h"

namespace wumpus_game {

class Windows
{
public:
  Windows(Images&, AudioOut&);
  ~Windows();

  bool Show();
  void Close();
  void PlayBackgroundMusic(int level = 1);

  // Resources
  
  Images&       images_;
  AudioOut&     audio_;     // see note #3 after code

  // Form of all game

  FormStart*    wnd_start_;
  FormHelp*     wnd_help_;
  FormMain*     wnd_main_;
  
  // Widgets that are aliases for simple access
  
  WidgetMap*    wdg_map_;
  WidgetInfo*   wdg_info_;
  WidgetPlayer* wdg_player_;

private:

  void  SetFormsCallbacks();    // see note #1

  static void cb_help_button(void*, void*);
  static void cb_quit_help_button(void*, void*);
  static void cb_quit_button(void*, void*);
  static void cb_close_wnd_main_(void*, void*);
};

}  // namespace wumpus_game

#endif  // GUI_WINDOWS_H

// Note #1 : Windows sets callbacks that not depends on game logic,
// but only based on the appearance logic. Callbacks based on game
// logic sets in the GuiController

// Note #2 : Reason of separating media.h and windows.h was in logic,
// that controller needs to have as member windows.h, to sets callbacks
// to some gui elements. If media.h and windows.h would be as one class,
// this would be a mess, since controller shouldn`t know about view.

// Note #3 : However audio_ data member is not needed, AudioOut entitie
// needs only to set its as data member of some form and widgets. But
// if I delete it here as data member, the code reader may be confused.