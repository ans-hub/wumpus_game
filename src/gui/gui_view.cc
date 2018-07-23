// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: gui view of game logic

#include "gui_view.h"

namespace wumpus_game {

GuiView::GuiView(const Logic& model, Windows& gui)
  : model_{model}
  , gui_{gui}
  , events_{}
{
  double k_timeout = 0.02;
  Fl::add_timeout(k_timout, cb_process_next_event, this);
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
      gui_helpers::ShowLevel(gui_, model_);
      gui_helpers::DisableFormButtons(gui_);
      gui_helpers::ShowPlayerPositionInstantly(gui_, model_);
      gui_helpers::ShowGuidePositionAtStart(gui_, model_);      
      gui_helpers::RefreshInfoWidget(gui_, model_);
      break;

    case Event::GAME_OVER :
      gui_helpers::ShowGameOver(gui_, model_);
      gui_helpers::HideLevel(gui_, model_);
      gui_helpers::EnableFormButtons(gui_);
      gui_helpers::RefreshInfoWidget(gui_, model_);      
      break;

    case Event::HAVE_NOT_ARROWS :
      gui_helpers::ShowHaventArrows(gui_);
      gui_helpers::RefreshInfoWidget(gui_, model_);      
      break;

    case Event::READY_TO_INPUT : 
      gui_helpers::ShowFeels(gui_, model_, room);
      gui_helpers::MarkRoomAsVisited(gui_, model_, room);
      gui_helpers::RefreshGuidePosition(gui_, model_);            
      break;

    case Event::ONE_WUMP_KILLED :
      gui_helpers::ShowPlayerShot(gui_);    
      gui_helpers::ShowKilledOneWump(gui_);
      gui_helpers::RefreshGuidePosition(gui_, model_);      
      gui_helpers::RefreshInfoWidget(gui_, model_);
      break;

    case Event::PLAYER_DOES_MOVE :
      gui_helpers::ShowPlayerMovement(gui_, room);
      break;

    case Event::MOVED_BY_BATS :
      gui_helpers::ShowBatsMovement(gui_, room);
      break;

    case Event::PLAYER_DOES_SHOT :
      gui_helpers::ShowPlayerShot(gui_);
      gui_helpers::RefreshInfoWidget(gui_, model_);      
      break;    
    
    case Event::MEETS_GUIDE :
      gui_helpers::ShowGuideMeets(gui_, model_, room);
      break;

    case Event::UNKNOWN_COMMAND :
    case Event::MOVE_NOT_NEIGHBOR :
    case Event::SHOT_NOT_NEIGHBOR :
      gui_helpers::ShowErrorRoom(gui_);
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

void RefreshInfoWidget(Windows& gui, const Logic& model)
{
  auto level_num = std::to_string(model.CurrentLevel());
  gui.wdg_info_->box_level_->copy_label(level_num.c_str());

  const Level& level = model.GetLevel();

  auto wumps = std::to_string(helpers::AliveSubjectsCount(level.wumps_));
  gui.wdg_info_->box_wumps_->copy_label(wumps.c_str());

  auto bats = std::to_string(level.bats_.size());
  gui.wdg_info_->box_bats_->copy_label(bats.c_str());

  auto pits = std::to_string(level.pits_.size());
  gui.wdg_info_->box_pits_->copy_label(pits.c_str());

  auto arrows = std::to_string(level.player_->GetArrows());
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
  gui.wdg_map_->ActivateRooms();
}

void HideLevel(Windows& gui, const Logic& model)
{
  gui.wdg_map_->DeactivateRooms();
  
  RoomState state {};
  if (model.GameOverCause() == Subject::ID::PLAYER) 
    state = RoomState::LIGHT;
  else
    state = RoomState::GATE;
  
  for (auto& r : gui.wdg_map_->wdg_rooms_) 
    r->SetDeimage(state);    
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
  auto  feels = helpers::SubjectsInNeighboringRooms(room, cave);
  
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
      gui.wdg_player_->SetState(PlayerState::LEVEL_WIN);
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

void ShowGuidePositionAtStart(Windows& gui, const Logic& model)
{
  auto level_num  = model.CurrentLevel();
  auto guide_room = model.GetLevel().guide_->GetCurrRoomNum();

  if (config::WhetherToShowGuide(level_num)) {
    auto& wdg_room = gui.wdg_map_->wdg_rooms_[guide_room];

    wdg_room->UnlockImage();
    wdg_room->SetImage(RoomState::GUIDE_CLOSED);
    wdg_room->LockImage();
  }  
}

void RefreshGuidePosition(Windows& gui, const Logic& model)
{
  auto& level_ent = model.GetLevel();
  
  if (!helpers::AliveSubjectsCount(level_ent.wumps_)) {

    int room = level_ent.guide_->GetCurrRoomNum();  
    auto& wdg_room = gui.wdg_map_->wdg_rooms_[room];
    
    if (wdg_room->IsLockedImage()){
      wdg_room->UnlockImage();  
      wdg_room->SetImage(RoomState::GUIDE_OPENED);
      wdg_room->LockImage();
    }
  }
  
}

void ShowGuidePosition(Windows& gui, const Logic& model, bool)
{
  auto  level_num = model.CurrentLevel();
  auto& level_ent = model.GetLevel();

  if (config::WhetherToShowGuide(level_num)) {

    int room = level_ent.guide_->GetCurrRoomNum();
    auto& wdg_room = gui.wdg_map_->wdg_rooms_[room];

    wdg_room->UnlockImage();
    if (!helpers::AliveSubjectsCount(level_ent.wumps_)  ) 
      wdg_room->SetImage(RoomState::GUIDE_OPENED);    
    else 
      wdg_room->SetImage(RoomState::GUIDE_CLOSED);
    wdg_room->LockImage();
  }
}

void ShowGuideMeets(Windows& gui, const Logic& model, int room)
{
  gui.wdg_map_->wdg_rooms_[room]->SetImage(RoomState::GUIDE_CLOSED);
  gui.wdg_map_->wdg_rooms_[room]->LockImage();  

  if (model.GameOverCause() != Subject::ID::PLAYER)
    gui.wdg_player_->SetState(PlayerState::MEETS_CLOSED_GUIDE);
}

void MarkRoomAsVisited(Windows& gui, const Logic& model, int room)
{
  auto level = model.CurrentLevel();

  if (config::WhetherToMarkVisitedRooms(level)) {
    auto& wdg_room = gui.wdg_map_->wdg_rooms_[room];

    wdg_room->SetImage(RoomState::LIGHT);
    wdg_room->SwitchOn();
  }
}

}  // namespace gui_helpers

}  // namespace wumpus_game
