// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `view` using gui

#include "media.h"

namespace wumpus_game {

Media::Media(
  const Config& conf, const Logic& model, Windows& gui, const AudioOut& audio)
  : conf_{conf}
  , model_{model}
  , gui_{gui}
  , audio_{audio}
  , events_{}
  // , ready_{true}
{
  Fl::add_timeout(0.02, cb_process_next_event, this);
  // Fl::add_timeout(0.02, cb_check_ready_to_next_event, this);
}

bool Media::IsReady() const
{
  if (!gui_.wdg_player_->IsReady()) return false;
  // if (!wdg_map_.IsReady())
  return true;
}

bool Media::IncomingNotify(Event msg)
{
  int room = model_.GetLevel().player_->GetCurrRoomNum();
  events_.push_back(std::make_pair(msg, room));
  return true;
}

void Media::ProcessNextEvent()
{
  if (!events_.empty() && IsReady()) {
    Event msg = events_.front().first;
    int room = events_.front().second;

    ExecuteEvent(msg, room);
    events_.pop_front();
  }
}

void Media::ExecuteEvent(Event msg, int room)
{
  switch(msg)
  {
    case Event::NEW_LEVEL :
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
      break;

    case Event::ONE_WUMP_KILLED :
      gui_helpers::show_killed_one_wump(gui_);
      gui_helpers::refresh_info_widget(gui_, model_);
      break;

    case Event::PLAYER_DOES_MOVE :
      if (gui_helpers::show_player_movement(gui_, room)) {
        // this->DoNotDistrubeWhileAnimate();
        this->ReturnEventBack(Event::PLAYER_DOES_MOVE, room); 
      }
      break;

    case Event::MOVED_BATS :
      if (gui_helpers::show_bats_movement(gui_, room)) {
        // this->DoNotDistrubeWhileAnimate();
        this->ReturnEventBack(Event::PLAYER_DOES_MOVE, room); 
      }
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

// void Media::CheckReadyToNextEvent()
// { 
//   if (!gui_.wdg_player_->IsAnimateInProgress())
//     ready_ = true;
// }

void Media::ReturnEventBack(Event msg, int room)
{
  events_.push_front(std::make_pair(msg, room));
}

void Media::cb_process_next_event(void* w)
{
  ((Media*)w)->ProcessNextEvent();
  Fl::repeat_timeout(0.02, cb_process_next_event, w);
}

// void Media::cb_check_ready_to_next_event(void* w)
// {
//   ((Media*)w)->CheckReadyToNextEvent();
//   Fl::repeat_timeout(0.02, cb_check_ready_to_next_event, w);  
// }

namespace gui_helpers {

void refresh_info_widget(Windows& gui, const Logic& model)
{
  auto level = std::to_string(model.CurrentLevel());
  gui.wdg_info_->box_level_->copy_label(level.c_str());

  auto wumps = std::to_string(model.GetLevel().WumpsCountLive());
  gui.wdg_info_->box_wumps_->copy_label(wumps.c_str());

  auto bats = std::to_string(model.GetLevel().BatsCount());
  gui.wdg_info_->box_bats_->copy_label(bats.c_str());

  auto pits = std::to_string(model.GetLevel().PitsCount());
  gui.wdg_info_->box_pits_->copy_label(pits.c_str());

  auto arrows = std::to_string(model.GetLevel().ArrowsCount());
  gui.wdg_info_->box_arrows_->copy_label(arrows.c_str());

  if (model.GameOverCause() != Logic::SubjectID::PLAYER)
    gui.wdg_info_->btn_continue_->image(gui.wdg_info_->img_repeat_);
  else
    gui.wdg_info_->btn_continue_->image(gui.wdg_info_->img_continue_); 
   
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
  gui.wnd_main_->Redraw(level);//Redraw(level);
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
  gui.wdg_player_->SetStateImage(WidgetPlayer::UNKNOWN_ACTION);
  gui.audio_.Play(gui.conf_.snd_click_);
  gui.audio_.Play(gui.conf_.snd_unknown_act_);  
  gui.wnd_main_->redraw();   
}

Point get_offsetted_point_of_room(Windows& gui, int room)
{
  int offset_x = (gui.wdg_player_->w()) / 2;
  int offset_y = (gui.wdg_player_->h()) / 2;

  int to_x = gui.wdg_map_->GetRoomCoordX(room)-offset_x;
  int to_y = gui.wdg_map_->GetRoomCoordY(room)-offset_y;
  
  return Point{to_x, to_y}; 
}

void show_player_position_instantly(Windows& gui, const Logic& model)
{
  int room = model.GetLevel().player_->GetCurrRoomNum();
  Point to_point = get_offsetted_point_of_room(gui, room);
  
  gui.wdg_player_->SetStateImage(WidgetPlayer::STAY);
  gui.wdg_player_->StaticMove(to_point);
  // gui.wdg_player_->curr_room_ = room;  
}

// Returns true if movement has been animated, and false if points
// from and to is equal

bool show_player_movement(Windows& gui, int room)
{
  Point to_point = get_offsetted_point_of_room(gui, room);
  Point this_point {gui.wdg_player_->x(), gui.wdg_player_->y()};

  if (to_point != this_point) {
    gui.wdg_player_->SetStateImage(WidgetPlayer::WALK);
    gui.wdg_player_->AnimatePrepare(to_point, Trajectory::LINE);
    gui.wdg_player_->AnimateMove();
    // gui.wdg_player_->curr_room_ = room;
    gui.audio_.Play(gui.conf_.snd_steps_, true);
    return true;
  }
  else {
    gui.audio_.Stop(gui.conf_.snd_steps_);
    return false;
  }
}

// Returns true if movement has been animated, and false if points
// from and to is equal

bool show_bats_movement(Windows& gui, int room)
{
  Point to_point = get_offsetted_point_of_room(gui, room);
  Point this_point {gui.wdg_player_->x(), gui.wdg_player_->y()};
    
  if (to_point != this_point) {
    gui.wdg_player_->SetStateImage(WidgetPlayer::MOVED_BATS);
    gui.wdg_player_->AnimatePrepare(to_point, Trajectory::LINE);
    gui.wdg_player_->AnimateMove();
    // gui.wdg_player_->curr_room_ = room;    
    gui.audio_.Play(gui.conf_.snd_bats_, true);
    return true;
  }
  else {
    gui.audio_.Stop(gui.conf_.snd_bats_);
    return false;        
  }
}

void show_player_shot(Windows& gui)
{
  gui.wdg_player_->SetStateImage(WidgetPlayer::SHOT);
  gui.audio_.Play(gui.conf_.snd_shot_);
  gui.wnd_main_->redraw();   
}

void show_havent_arrows(Windows& gui)
{
  gui.wdg_player_->SetStateImage(WidgetPlayer::HAVENT_ARROWS);
  gui.audio_.Play(gui.conf_.snd_unknown_act_);
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
      case Logic::SubjectID::WUMP :
        wumps = true;
        gui.audio_.Play(gui.conf_.snd_wump_feels_);              
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
  gui.wdg_map_->GetPlayer()->ShowFeelsIcons(wumps, bats, pits);
  gui.wnd_main_->redraw();
}

void show_game_over(Windows& gui, const Logic& logic)
{
  switch (logic.GameOverCause()) {
    case Logic::SubjectID::PLAYER :
      gui.wdg_player_->SetStateImage(WidgetPlayer::KILL_WUMP);
      gui.audio_.Play(gui.conf_.snd_wump_killed_);      
      break;
    case Logic::SubjectID::WUMP :
      gui.wdg_player_->SetStateImage(WidgetPlayer::KILLED_BY_WUMP);
      gui.audio_.Play(gui.conf_.snd_wump_attack_);       
      break;
    case Logic::SubjectID::PIT :
      gui.wdg_player_->SetStateImage(WidgetPlayer::KILLED_BY_PITS);
      gui.audio_.Play(gui.conf_.snd_pits_);
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
  gui.wdg_player_->SetStateImage(WidgetPlayer::KILL_WUMP);
  gui.audio_.Play(gui.conf_.snd_wump_killed_);
}

}  // namespace gui_helpers

}  // namespace wumpus_game