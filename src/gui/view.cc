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

    case Event::GAME_OVER :
      gui_helpers::show_game_over(gui_, model_);
      gui_helpers::hide_level(gui_);
      gui_helpers::enable_buttons(gui_);
      break;

    case Event::UNKNOWN_COMMAND :
    case Event::MOVE_NOT_NEIGHBOR :
    case Event::SHOT_NOT_NEIGHBOR :
    {
      gui_helpers::show_error_room(gui_);
      gui_helpers::unshown_last_action(gui_, model_);
      break;
    }

    case Event::HAVE_NOT_ARROWS :
      gui_helpers::show_havent_arrows(gui_);
      break;

    case Event::READY_TO_INPUT : 
      gui_helpers::show_feels(gui_, model_);
      break;

    case Event::ONE_WUMP_KILLED :
      gui_helpers::show_killed_one_wump(gui_);
      break;

    case Event::MOVED_BATS :
      gui_helpers::show_moved_bats(gui_);
    case Event::PLAYER_DOES_MOVE :
      gui_helpers::mark_room_as_visited(gui_, model_);
      gui_helpers::clear_player_pos(gui_);
      gui_helpers::show_player_pos(gui_, model_);  
      break;
    
    case Event::PLAYER_DOES_SHOT :
      gui_helpers::unshown_last_action(gui_, model_);
      break;    
    
    case Event::WINDOW : default: break;

  }
  return true;
}

namespace gui_helpers {
  
void show_intro(Windows& gui, const Logic& logic)
{
  auto& level = logic.GetLevel();

  std::stringstream sst{};
  sst << "You are in the dark cave with " << level.cave_->GetSize()
      << " rooms. Somewhere here lives " << level.wumps_.size() 
      << " Wumpus.\n"
      << "You have the bow and " << level.player_->GetArrows() 
      << " arrows. Find and kill all Wumpus!\n"
      << "And be aware about presence of other danger things - "
      << "the " << level.bats_.size() << " Bats "
      << "and the " << level.pits_.size() << " Bottomless pits\n";

  auto& out = gui.main_wnd_->output_;
  out->text("");
  out->append(sst.str().c_str());
}

void disable_buttons(Windows& gui)
{
  auto* wnd = gui.main_wnd_;
  wnd->btn_start_->deactivate();
}

void show_level(Windows& gui, const Logic& model)
{
  int level = model.CurrentLevel();
  gui.Redraw(level);
  gui.map_box_->Activate();
}

void hide_level(Windows& gui)
{
  gui.map_box_->Deactivate();
}

void enable_buttons(Windows& gui)
{
  auto* wnd = gui.main_wnd_;
  wnd->btn_start_->activate();
}

void unshown_last_action(Windows& gui, const Logic& model)
{
  int room = model.CurrentRequest().room_;
  auto* btn = gui.map_box_->GetRooms()[room];
  if (!btn->visited_) btn->value(0);
  // gui.Redraw();
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
  gui.map_box_->GetRooms()[room]->label("Y");
  gui.map_box_->GetRooms()[room]->value(1);
}

void clear_player_pos(Windows& gui)
{
  auto& rooms = gui.map_box_->GetRooms();
  for (auto& v : rooms) v->label("");
}

void mark_room_as_visited(Windows& gui, const Logic& model)
{
  int room = model.CurrentRequest().room_;
  auto* btn = gui.map_box_->GetRooms()[room];
  btn->visited_ = true;
}

void show_moved_bats(Windows& gui)
{
  gui.main_wnd_->output_->insert(
    0, "You have been moved by the Bats to another room\n"
  );
}

void show_havent_arrows(Windows& gui)
{
  gui.main_wnd_->output_->insert(
    0, "ERROR: You have not enought arrays to shot\n"
  );
}

void show_feels(Windows& gui, const Logic& logic)
{
  auto& out = gui.main_wnd_->output_;
  auto feels = logic.GetLevel().player_->Feels();
  
  for (auto const feel : feels) {
    switch(feel)
    {
      case Logic::SubjectID::WUMP :
        out->insert(
          0, "FEELS: It`s smeels like Wumpus (possible the Wumpus is near)\n"
        );
        break;
      case Logic::SubjectID::PIT  :
        out->insert(
          0, "FEELS: You feel the wind (possible the bats is near)\n"
        );
        break;
      case Logic::SubjectID::BAT  :
        out->insert(
          0, "FEELS: You feel the cold (possible the bottomless pit is near)\n"
        );
        break;
      default : break;
    } 
  }
}

void show_game_over(Windows& gui, const Logic& logic)
{
  auto& out = gui.main_wnd_->output_;

  switch (logic.GameOverCause()) {
    case Logic::SubjectID::PLAYER :
      out->insert(0,"***You have killed the Wumpus!***\n");
      break;
    case Logic::SubjectID::WUMP    :
      out->insert(0, "***You have been killed by Wumpus***\n");
      break;
    case Logic::SubjectID::PIT :
      out->insert(0, "***The bottomless pit is your perpetual retreat***\n");
      break;
    case Logic::SubjectID::UNKNOWN :
    default:
      out->insert(0, "***See you later!***\n");
      break;
  }
}

void show_killed_one_wump(Windows& gui)
{
  auto& out = gui.main_wnd_->output_;
  out->insert(0, "INFO: You killed one wumpus\n");
}


}  // namespace gui_helpers

}  // namespace wumpus_game