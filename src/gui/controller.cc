// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `controller` using gui

#include "controller.h"

namespace wumpus_game {

GuiController::GuiController(Windows& gui, Logic& model)
  : Controller() 
  , gui_{gui}
  , model_{model}
{
  SetLogicCommandsCallbacks();
  SetLevelProcessingCallbacks();
}

void GuiController::SetLogicCommandsCallbacks()
{
  gui_.wdg_map_->SetCallback((void*)cb_rooms_button);
  gui_.wdg_map_->SetCommand((void*)this);
}

void GuiController::SetLevelProcessingCallbacks()
{
  gui_.wnd_start_->btn_start_->callback(
    (Fl_Callback*)(cb_start_button), (void*)this
  );
  gui_.wdg_info_->btn_next_->callback(
    (Fl_Callback*)(cb_next_button), (void*)this
  );
  gui_.wdg_info_->btn_continue_->callback(
    (Fl_Callback*)(cb_continue_button), (void*)this
  );
}

bool GuiController::RunModel()
{
  gui_.Show();
  return true;
}

void GuiController::StopModel()
{
  gui_.Close();
}

void GuiController::CommandStart()
{
  model_.NewLevel(1);
}

void GuiController::CommandContinue()
{
  model_.NewLevel();
}

void GuiController::CommandLevel()
{
  int level = model_.CurrentLevel();
  model_.NewLevel(++level);
}

void GuiController::CommandAction(int room)
{
  auto e = Fl::event_button();
  if (e == FL_LEFT_MOUSE) {
    model_.Turn(0, room);
  }
  if (e == FL_RIGHT_MOUSE) {
    model_.Turn(1, room);
  }
}

void GuiController::cb_start_button(void*, void* c)
{
  ((GuiController*)c)->CommandStart();
}

void GuiController::cb_continue_button(void*, void* c)
{
  ((GuiController*)c)->CommandContinue();
}

void GuiController::cb_next_button(void*, void* c)
{
  ((GuiController*)c)->CommandLevel();  
}

void GuiController::cb_rooms_button(void* b, void* c)
{
  ((GuiController*)c)->CommandAction(((WidgetRoom*)b)->num_); // called by WidgetRoom
}

}  // namespace wumpus_game