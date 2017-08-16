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
      helpers::ShowLevel(gui_, model_);
      helpers::DisableFormButtons(gui_);
      helpers::ShowPlayerPositionInstantly(gui_, model_);
      helpers::RefreshInfoWidget(gui_, model_);
      break;

    case Event::GAME_OVER :
      helpers::ShowGameOver(gui_, model_);
      helpers::HideLevel(gui_, model_);
      helpers::EnableFormButtons(gui_);
      helpers::RefreshInfoWidget(gui_, model_);      
      break;

    case Event::HAVE_NOT_ARROWS :
      helpers::ShowHaventArrows(gui_);
      helpers::RefreshInfoWidget(gui_, model_);      
      break;

    case Event::READY_TO_INPUT : 
      helpers::ShowFeels(gui_, model_, room);
      helpers::MarkRoomAsVisited(gui_, model_, room);
      break;

    case Event::ONE_WUMP_KILLED :
      helpers::ShowPlayerShot(gui_);    
      helpers::ShowKilledOneWump(gui_);
      helpers::RefreshInfoWidget(gui_, model_);
      break;

    case Event::PLAYER_DOES_MOVE :
      helpers::ShowPlayerMovement(gui_, room);
      break;

    case Event::MOVED_BY_BATS :
      helpers::ShowBatsMovement(gui_, room);
      break;

    case Event::PLAYER_DOES_SHOT :
      helpers::ShowPlayerShot(gui_);
      helpers::RefreshInfoWidget(gui_, model_);      
      break;    
    
    case Event::UNKNOWN_COMMAND :
    case Event::MOVE_NOT_NEIGHBOR :
    case Event::SHOT_NOT_NEIGHBOR :
      helpers::ShowErrorRoom(gui_);
      break;

    case Event::MODEL_READY : default: break;
  }
}

void GuiView::cb_process_next_event(void* w)
{
  ((GuiView*)w)->ProcessNextEvent();
  Fl::repeat_timeout(0.02, cb_process_next_event, w);
}

namespace helpers {

void RefreshInfoWidget(Windows& gui, const Logic& model)
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

void EnableFormButtons(Windows& gui)
{
  gui.wdg_info_->btn_continue_->activate();
}

void DisableFormButtons(Windows& gui)
{
  gui.wdg_info_->btn_continue_->deactivate();
}

void ShowLevel(Windows& gui, const Logic& model)
{
  int level = model.CurrentLevel();
  
  gui.wnd_main_->show();
  gui.wnd_main_->Redraw(level);
  gui.wdg_map_->Activate();
}

void HideLevel(Windows& gui, const Logic& model)
{
  if (model.GameOverCause() == Subject::ID::PLAYER)
    gui.wdg_map_->Deactivate(false);
  else
    gui.wdg_map_->Deactivate(true);    
}

void ShowErrorRoom(Windows& gui)
{
  gui.wdg_player_->SetState(PlayerState::UNKNOWN_STATE);
  gui.wnd_main_->redraw();
}

void ShowPlayerPositionInstantly(Windows& gui, const Logic& model)
{
  int to_room = model.GetLevel().player_->GetCurrRoomNum();
  gui.wdg_player_->SetState(PlayerState::STAY);
  gui.wdg_map_->MovePlayerInstantly(to_room);
}

void ShowPlayerMovement(Windows& gui, int to_room)
{
  gui.wdg_player_->SetState(PlayerState::WALK);
  gui.wdg_map_->MovePlayerAnimated(to_room);
}

void ShowBatsMovement(Windows& gui, int to_room)
{
  gui.wdg_player_->SetState(PlayerState::MOVED_BY_BATS);
  gui.wdg_map_->MovePlayerAnimated(to_room);
}

void ShowPlayerShot(Windows& gui)
{
  gui.wdg_player_->SetState(PlayerState::SHOT);
  gui.wnd_main_->redraw();   
}

void ShowHaventArrows(Windows& gui)
{
  gui.wdg_player_->SetState(PlayerState::HAVENT_ARROWS);
  gui.wnd_main_->redraw();
}

void ShowFeels(Windows& gui, const Logic& model, int room)
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

void ShowGameOver(Windows& gui, const Logic& logic)
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

void ShowKilledOneWump(Windows& gui)
{
  gui.wdg_player_->SetState(PlayerState::KILL_WUMP);
}

void MarkRoomAsVisited(Windows& gui, const Logic& model, int room)
{
  auto level = model.CurrentLevel();
  if (config::WhetherToMarkVisitedRooms(level))
    gui.wdg_map_->wdg_rooms_[room]->SetMarked();
}

}  // namespace helpers

}  // namespace wumpus_game