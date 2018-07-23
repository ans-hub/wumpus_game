// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: container of forms and resources

#ifndef GUI_WINDOWS_H
#define GUI_WINDOWS_H

#include <memory>

#include "FL/fl_ask.H"

#include "3rdparty/audio/audio_out.h"

#include "gui/images.h"
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
  using AudioOut = anshub::AudioOut;

  Windows(Images&, AudioOut&);
  ~Windows();

  bool Show();
  void Close();

  // Resources
  
  Images&       images_;
  AudioOut&     audio_;

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
