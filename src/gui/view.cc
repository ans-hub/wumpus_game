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
      gui_helpers::disable_buttons(gui_);
      gui_helpers::show_player_movement(gui_, model_);
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
      gui_helpers::show_moved_bats(gui_, model_);
      break;

    case Event::PLAYER_DOES_MOVE :  
      gui_helpers::show_player_movement(gui_, model_);  
      break;
    
    case Event::PLAYER_DOES_SHOT :
      gui_helpers::show_player_shot(gui_);
      break;    
    
    case Event::WINDOW : default: break;

  }
  return true;
}

namespace gui_helpers {

void enable_buttons(Windows& gui)
{
  gui.wnd_main_->btn_start_->activate();
}

void disable_buttons(Windows& gui)
{
  gui.wnd_main_->btn_start_->deactivate();
}

void show_level(Windows& gui, const Logic& model)
{
  int level = model.CurrentLevel();
  gui.ShowMain();
  gui.Redraw(level);
  gui.wdg_map_->Activate();
}

void hide_level(Windows& gui)
{
  gui.wdg_map_->Deactivate();
}

void show_error_room(Windows& gui)
{
  gui.wdg_map_->GetPlayer()->UnknownAction();
  gui.wnd_main_->redraw();   
}

void show_player_movement(Windows& gui, const Logic& model)
{
  int room = model.GetLevel().player_->GetCurrRoomNum();
  int x = gui.wdg_map_->GetRoomCoordX(room);
  int y = gui.wdg_map_->GetRoomCoordY(room);
  gui.wdg_map_->GetPlayer()->Move(x,y);
  gui.wnd_main_->redraw();
}

void show_player_shot(Windows& gui)
{
  gui.wdg_map_->GetPlayer()->Shot();
  gui.wnd_main_->redraw();   
}

void show_moved_bats(Windows& gui, const Logic& model)
{
  int room = model.GetLevel().player_->GetCurrRoomNum();
  int to_x = gui.wdg_map_->GetRoomCoordX(room);
  int to_y = gui.wdg_map_->GetRoomCoordY(room);
  gui.wdg_map_->GetPlayer()->AnimateBegin(to_x, to_y);
  gui.wnd_main_->redraw();
}

void show_havent_arrows(Windows& gui)
{
  gui.wnd_main_->output_->insert(
    0, "ERROR: You have not enought arrays to shot\n"
  );
}

void show_feels(Windows& gui, const Logic& model)
{  
  bool wumps {false};
  bool bats {false};  
  bool pits {false};

  auto feels = model.GetLevel().player_->Feels();

  for (auto const feel : feels) {
    switch(feel)
    {
      case Logic::SubjectID::WUMP :
        wumps = true;
        break;
      case Logic::SubjectID::BAT  :
        bats = true;
        break;
      case Logic::SubjectID::PIT  :
        pits = true;
        break;
      default : break;
    } 
  }
  gui.wdg_map_->GetPlayer()->ShowFeels(wumps, bats, pits);
  gui.wnd_main_->redraw();   
}

void show_game_over(Windows& gui, const Logic& logic)
{
  auto& out = gui.wnd_main_->output_;

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
  auto& out = gui.wnd_main_->output_;
  out->insert(0, "INFO: You killed one wumpus\n");
}


}  // namespace gui_helpers

}  // namespace wumpus_game