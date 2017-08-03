// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `view` using gui

#include "view.h"

namespace wumpus_game {

GuiView::GuiView(Windows& gui, Logic& model)
  : gui_{gui}
  , model_{model}
  , events_{}
  , ready_{true}
{
  Fl::add_timeout(0.02, cb_process_next_event, this);
  Fl::add_timeout(0.02, cb_check_ready_to_next_event, this);
}

bool GuiView::IncomingNotify(Event msg)
{
  int room = model_.GetLevel().player_->GetCurrRoomNum();
  events_.push(std::make_pair(msg, room));
  return true;
}

void GuiView::ProcessNextEvent()
{
  if (!events_.empty() && ready_) {
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
      gui_helpers::show_level(gui_, model_);
      gui_helpers::disable_buttons(gui_);
      gui_helpers::show_player_position_instantly(gui_, model_);
      gui_helpers::refresh_info_widget(gui_, model_);
      break;

    case Event::GAME_OVER :
      gui_helpers::show_game_over(gui_, model_);
      gui_helpers::hide_level(gui_);
      gui_helpers::enable_buttons(gui_);
      gui_helpers::refresh_info_widget(gui_, model_);      
      break;


    case Event::HAVE_NOT_ARROWS :
      gui_helpers::show_havent_arrows(gui_);
      gui_helpers::refresh_info_widget(gui_, model_);      
      break;

    case Event::READY_TO_INPUT : 
      gui_helpers::show_feels(gui_, model_);
      break;

    case Event::ONE_WUMP_KILLED :
      gui_helpers::show_killed_one_wump(gui_);
      gui_helpers::refresh_info_widget(gui_, model_);
      break;

    case Event::MOVED_BATS :
      gui_helpers::show_bats_movement(gui_, room);
      this->DoNotDistrubeWhileAnimate(); 
      break;

    case Event::PLAYER_DOES_MOVE :  
      gui_helpers::show_player_movement(gui_, room);
      this->DoNotDistrubeWhileAnimate();
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

void GuiView::CheckReadyToNextEvent()
{ 
  if (!gui_.wdg_player_->IsAnimateInProgress())
    ready_ = true;
}

void GuiView::cb_process_next_event(void* w)
{
  ((GuiView*)w)->ProcessNextEvent();
  Fl::repeat_timeout(0.02, cb_process_next_event, w);
}

void GuiView::cb_check_ready_to_next_event(void* w)
{
  ((GuiView*)w)->CheckReadyToNextEvent();
  Fl::repeat_timeout(0.02, cb_check_ready_to_next_event, w);  
}

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

void hide_level(Windows& gui)
{
  gui.wdg_map_->Deactivate();
}

void show_error_room(Windows& gui)
{
  gui.wdg_player_->SetStateImage(WidgetPlayer::UNKNOWN_ACTION);
  gui.wnd_main_->redraw();   
}

Point get_offsetted_point_of_room(Windows& gui, int room)
{
  int offset_x = (gui.wdg_player_->w()) / 2;
  int offset_y = (gui.wdg_player_->h()) / 2;

  double to_x = gui.wdg_map_->GetRoomCoordX(room)-offset_x;
  double to_y = gui.wdg_map_->GetRoomCoordY(room)-offset_y;
  
  return Point{to_x, to_y}; 
}

void show_player_position_instantly(Windows& gui, const Logic& model)
{
  int room = model.GetLevel().player_->GetCurrRoomNum();
  Point to_point = get_offsetted_point_of_room(gui, room);
  
  gui.wdg_player_->SetStateImage(WidgetPlayer::STAY);
  gui.wdg_player_->StaticMove(to_point);
}

void show_player_movement(Windows& gui, int room)
{
  Point to_point = get_offsetted_point_of_room(gui, room);

  gui.wdg_player_->SetStateImage(WidgetPlayer::WALK);
  gui.wdg_player_->AnimateMove(to_point, Trajectory::LINE);
}

void show_bats_movement(Windows& gui, int room)
{
  Point to_point = get_offsetted_point_of_room(gui, room);
    
  gui.wdg_player_->SetStateImage(WidgetPlayer::MOVED_BATS);
  gui.wdg_player_->AnimateMove(to_point, Trajectory::LINE);
}

void show_player_shot(Windows& gui)
{
  gui.wdg_player_->SetStateImage(WidgetPlayer::SHOT);
  // gui.wnd_main_->redraw();   
}

void show_havent_arrows(Windows&)
{
  // gui.wnd_main_->output_->insert(
  //   0, "ERROR: You have not enought arrays to shot\n"
  // );
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
  gui.wdg_map_->GetPlayer()->ShowFeelsIcons(wumps, bats, pits);
  gui.wnd_main_->redraw();
}

void show_game_over(Windows& gui, const Logic& logic)
{
  switch (logic.GameOverCause()) {
    case Logic::SubjectID::PLAYER :
      gui.wdg_player_->SetStateImage(WidgetPlayer::KILL_WUMP);
      break;
    case Logic::SubjectID::WUMP :
      gui.wdg_player_->SetStateImage(WidgetPlayer::KILLED_BY_WUMP); 
      break;
    case Logic::SubjectID::PIT :
      gui.wdg_player_->SetStateImage(WidgetPlayer::KILLED_BY_PITS);  
      break;
    case Logic::SubjectID::UNKNOWN :
    default:
      gui.wnd_main_->hide();
      break;
  }

  gui.wnd_main_->redraw();     
}

void show_killed_one_wump(Windows&)
{
  // auto& out = gui.wnd_main_->output_;
  // out->insert(0, "INFO: You killed one wumpus\n");
}

}  // namespace gui_helpers

}  // namespace wumpus_game