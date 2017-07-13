// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `view` using gui

#include "view.h"

namespace wumpus_game {

bool GuiView::IncomingNotify(Event msg) const
{
  switch(msg)
  {
    case Event::NEW_LEVEL :
      gui_helpers::show_level(gui_, model_);
      gui_helpers::show_intro(gui_, model_);
      gui_helpers::disable_buttons(gui_);
      gui_helpers::show_player_pos(gui_, model_);
      break;
    case Event::MOVE_NOT_NEIGHBOR :
    case Event::SHOT_NOT_NEIGHBOR :
    {
      gui_helpers::show_error_room(gui_);
      gui_helpers::unshown_last_action(gui_, model_);
      break;
    }
    case Event::PLAYER_DOES_MOVE :
      gui_helpers::mark_room_as_visited(gui_, model_);
      gui_helpers::clear_player_pos(gui_);
      gui_helpers::show_player_pos(gui_, model_);  
      break;
    case Event::GAME_OVER :
      gui_helpers::enable_buttons(gui_);
      break;
  }
  return true;
}

namespace gui_helpers {
  
void show_intro(Windows&, const Logic&) { }

void disable_buttons(Windows& gui)
{
  auto* wnd = gui.main_wnd_;
  wnd->btn_start_->deactivate();
}

void show_level(Windows& gui, const Logic& model)
{
  int level = model.CurrentLevel();
  // GroupRooms* rooms = new GroupRooms();
  gui.RedrawRooms(level);
  // gui.AddWidget(rooms);
  gui.Redraw();
  //  gui.ShowWidget(gui.box_rooms_);
  // int level = model.CurrentLevel();
  // GroupRooms* rooms = new GroupRooms();
  // gui.RedrawRooms(level);
  // gui.AddWidget(rooms);
  // gui.Redraw();
}

void enable_buttons(Windows& gui)
{
  auto* wnd = gui.main_wnd_;
  wnd->btn_start_->activate();
}

void unshown_last_action(Windows& gui, const Logic& model)
{
  int room = model.CurrentRequest().room_;
  auto* btn = gui.box_rooms_->rooms_[room];
  if (!btn->visited_) btn->value(0); 
  // Fl::pushed(nullptr);
  gui.Redraw();
}

void show_error_room(Windows& gui)
{
  gui.main_wnd_->output_->insert(
    0, "ERROR: You choose not neighboring room, please repeat\n"
  );
}

void show_player_pos(Windows& gui, const Logic& model)
{
  int room = model.GetLevel().player_->GetCurrRoomNum();
  gui.box_rooms_->rooms_[room]->label("Y");
  gui.box_rooms_->rooms_[room]->value(1);
}

void clear_player_pos(Windows& gui)
{
  auto& rooms = gui.box_rooms_->rooms_;
  for (auto& v : rooms) v->label("");
}

void mark_room_as_visited(Windows& gui, const Logic& model)
{
  int room = model.CurrentRequest().room_;
  auto* btn = gui.box_rooms_->rooms_[room];
  btn->visited_ = true;
}


}  // namespace gui_helpers

}  // namespace wumpus_game