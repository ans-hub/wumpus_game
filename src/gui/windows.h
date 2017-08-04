// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: windows container for `gui` view and cotroller

#ifndef GUI_WINDOWS_H
#define GUI_WINDOWS_H

#include "FL/fl_ask.H"

#include "gui/forms/form_start.h"
#include "gui/forms/form_help.h"
#include "gui/forms/form_main.h"
#include "gui/widgets/widget_info.h"
#include "gui/widgets/widget_map.h"
#include "settings/config.h"

namespace wumpus_game {

class Windows
{
public:
  explicit Windows(const Config&);
  ~Windows();

  void Show();
  void Close();
  
  // Form of all game

  FormStart*    wnd_start_;
  FormHelp*     wnd_help_;
  FormMain*     wnd_main_;
  
  // Widgets that are aliases for simple access
  
  WidgetMap*    wdg_map_;
  WidgetInfo*   wdg_info_;
  WidgetPlayer* wdg_player_;

private:
  const Config& conf_;
  void  SetFormsCallbacks();    // see note #1
};

namespace gui_helpers {

  void cb_help_button(void*, void*);
  void cb_quit_help_button(void*, void*);
  void cb_quit_button(void*, void* c);
  void cb_close_wnd_main_(void*, void*);

}  // namespace gui_helpers

}  // namespace wumpus_game

#endif  // GUI_WINDOWS_H

// Note #1 : Windows sets callbacks that not depends on game logic,
// but only based on form appearance logic. Callbacks based on game
// logic sets in the GuiController