// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: gui view of game logic

#include "view.h"

namespace wumpus_game {

GuiView::GuiView(const Logic& model, Windows& gui)
  : model_{model}
  , gui_{gui}
  , events_{}
{
  Fl::add_timeout(0.02, cb_process_next_event, this);
}

bool GuiView::IncomingNotify(Event msg)
{
  int room = model_.GetLevel().player_->GetCurrRoomNum();
  events_.push(std::make_pair(msg, room));
  return true;
}

void GuiView::ProcessNextEvent()
{
  if (!events_.empty() && gui_.wdg_map_->IsReady()) {
    Event msg = events_.front().first;
    int room = events_.front().second;

    ExecuteEvent(msg, room);
    events_.pop();
  }
}

void GuiView::ExecuteEvent(Event msg, int room)
{
  switch(msg)
  {
    case Event::NEW_LEVEL :
      gui_helpers::play_bg_music(gui_, model_); // see note #1 after code
      gui_helpers::show_level(gui_, model_);
      gui_helpers::disable_buttons(gui_);
      gui_helpers::show_player_position_instantly(gui_, model_);
      gui_helpers::refresh_info_widget(gui_, model_);
      break;

    case Event::GAME_OVER :
      gui_helpers::show_game_over(gui_, model_);
      gui_helpers::hide_level(gui_, model_);
      gui_helpers::enable_buttons(gui_);
      gui_helpers::refresh_info_widget(gui_, model_);      
      break;

    case Event::HAVE_NOT_ARROWS :
      gui_helpers::show_havent_arrows(gui_);
      gui_helpers::refresh_info_widget(gui_, model_);      
      break;

    case Event::READY_TO_INPUT : 
      gui_helpers::show_feels(gui_, model_, room);
      gui_helpers::mark_room_as_wisited(gui_, model_, room);
      break;

    case Event::ONE_WUMP_KILLED :
      gui_helpers::show_player_shot(gui_);    
      gui_helpers::show_killed_one_wump(gui_);
      gui_helpers::refresh_info_widget(gui_, model_);
      break;

    case Event::PLAYER_DOES_MOVE :
      gui_helpers::show_player_movement(gui_, room);
      break;

    case Event::MOVED_BY_BATS :
      gui_helpers::show_bats_movement(gui_, room);
      break;

    case Event::PLAYER_DOES_SHOT :
      gui_helpers::show_player_shot(gui_);
      gui_helpers::refresh_info_widget(gui_, model_);      
      break;    
    
    case Event::UNKNOWN_COMMAND :
    case Event::MOVE_NOT_NEIGHBOR :
    case Event::SHOT_NOT_NEIGHBOR :
      gui_helpers::show_error_room(gui_);
      break;

    case Event::MODEL_READY : default: break;
  }
}

void GuiView::cb_process_next_event(void* w)
{
  ((GuiView*)w)->ProcessNextEvent();
  Fl::repeat_timeout(0.02, cb_process_next_event, w);
}

namespace gui_helpers {

// This function is needs here to simplify searching and non confusing

void play_bg_music(Windows& gui, const Logic& model)
{
  auto level = model.CurrentLevel();
  auto prev_level_music = config::GetBackgroundMusic(level - 1);
  auto curr_level_music = config::GetBackgroundMusic(level);

  if (prev_level_music != curr_level_music) {
    gui.audio_.Stop(prev_level_music); 
    gui.audio_.Play(curr_level_music);
  }
}

void refresh_info_widget(Windows& gui, const Logic& model)
{
  auto level = std::to_string(model.CurrentLevel());
  gui.wdg_info_->box_level_->copy_label(level.c_str());

  auto wumps = std::to_string(model.GetLevel().WumpsCountLive());
  gui.wdg_info_->box_wumps_->copy_label(wumps.c_str());

  auto bats = std::to_string(model.GetLevel().bats_.size());
  gui.wdg_info_->box_bats_->copy_label(bats.c_str());

  auto pits = std::to_string(model.GetLevel().pits_.size());
  gui.wdg_info_->box_pits_->copy_label(pits.c_str());

  auto arrows = std::to_string(model.GetLevel().player_->GetArrows());
  gui.wdg_info_->box_arrows_->copy_label(arrows.c_str());
}

void enable_buttons(Windows& gui)
{
  gui.wdg_info_->btn_continue_->activate();
}

void disable_buttons(Windows& gui)
{
  gui.wdg_info_->btn_continue_->deactivate();
}

void show_level(Windows& gui, const Logic& model)
{
  int level = model.CurrentLevel();
  
  gui.wnd_main_->show();
  gui.wnd_main_->Redraw(level);
  gui.wdg_map_->Activate();
}

void hide_level(Windows& gui, const Logic& model)
{
  if (model.GameOverCause() == Subject::ID::PLAYER)
    gui.wdg_map_->Deactivate(true);
  else
    gui.wdg_map_->Deactivate(false);    
}

void show_error_room(Windows& gui)
{
  gui.wdg_player_->SetState(PlayerState::UNKNOWN_STATE);
  gui.wnd_main_->redraw();
}

void show_player_position_instantly(Windows& gui, const Logic& model)
{
  int to_room = model.GetLevel().player_->GetCurrRoomNum();
  gui.wdg_player_->SetState(PlayerState::STAY);
  gui.wdg_map_->MovePlayerInstantly(to_room);
}

void show_player_movement(Windows& gui, int to_room)
{
  gui.wdg_player_->SetState(PlayerState::WALK);
  gui.wdg_map_->MovePlayerAnimated(to_room);
}

void show_bats_movement(Windows& gui, int to_room)
{
  gui.wdg_player_->SetState(PlayerState::MOVED_BY_BATS);
  gui.wdg_map_->MovePlayerAnimated(to_room);
}

void show_player_shot(Windows& gui)
{
  gui.wdg_player_->SetState(PlayerState::SHOT);
  gui.wnd_main_->redraw();   
}

void show_havent_arrows(Windows& gui)
{
  gui.wdg_player_->SetState(PlayerState::HAVENT_ARROWS);
  gui.wnd_main_->redraw();
}

void show_feels(Windows& gui, const Logic& model, int room)
{  
  bool wumps {false};
  bool bats {false};  
  bool pits {false};

  auto* cave = model.GetLevel().cave_.get();
  auto  feels = helpers::subjects_in_neighboring_rooms(room, cave);
  
  for (auto const feel : feels) {
    switch(feel)
    {
      case Logic::SubjectID::WUMP : wumps = true; break;
      case Logic::SubjectID::BAT  : bats = true; break;
      case Logic::SubjectID::PIT  : pits = true; break;
      default : break;
    }
  }
  gui.wdg_player_->ShowFeels(wumps, bats, pits);
  gui.wnd_main_->redraw();
}

void show_game_over(Windows& gui, const Logic& logic)
{
  switch (logic.GameOverCause()) {
    case Logic::SubjectID::PLAYER :
      gui.wdg_player_->SetState(PlayerState::KILL_WUMP);
      break;
    case Logic::SubjectID::WUMP :
      gui.wdg_player_->SetState(PlayerState::KILLED_BY_WUMP);
      break;
    case Logic::SubjectID::PIT :
      gui.wdg_player_->SetState(PlayerState::KILLED_BY_PITS);
      break;
    case Logic::SubjectID::UNKNOWN :
    default:
      gui.wnd_main_->hide();
      break;
  }
  gui.wdg_player_->redraw();     
  gui.wnd_main_->redraw();     
}

void show_killed_one_wump(Windows& gui)
{
  gui.wdg_player_->SetState(PlayerState::KILL_WUMP);
}

void mark_room_as_wisited(Windows& gui, const Logic& model, int room)
{
  auto level = model.CurrentLevel();
  if (config::WhetherToMarkVisitedRooms(level))
    gui.wdg_map_->wdg_rooms_[room]->SetMarked(true);
}

}  // namespace gui_helpers

}  // namespace wumpus_game