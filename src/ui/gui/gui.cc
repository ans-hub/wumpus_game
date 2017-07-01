// Package: mvc_set
// Description: https://github.com/ans-hub/mvc_set
// Author: Anton Novoselov, 2017
// File: realisation of `gui`

#include "gui.h"

namespace mvc_set {

Gui::Gui (Model& model)
: Fl_Window(200, 200, "Examples")
, model_{model}
, window_{new Fl_Window(200, 200, "Example")}
, btn_start_{new Fl_Button(20, 20, 160, 20, "Start new")}
, btn_send_{new Fl_Button(130, 80, 50, 20, "Send")}
, output_{new Fl_Output(60, 110, 120, 20, "Model")}
, input_{new Fl_Value_Input(60, 80, 50, 20, "Ctrl")}
{
  btn_start_->callback((cb_btnstart), (void*)this);
  btn_send_->deactivate();
  input_->value(0);
  window_->end();
  window_->show();
}

Gui::~Gui()
{
  delete btn_start_;
  delete btn_send_;
  delete output_;
  delete input_;
  delete window_;
}

// // `CONTROLLER` ROLE FUNCTIONS

bool Gui::IncomingNotify(int& n, int& m) const
{
  do {
    if (btn_send_->value()) {
      btn_send_->value(0);
      n = input_->value();
      m = n;
      return true;
    }
    if (!window_->shown()) {
      break;
    }
  } while(Fl::wait());
  return false;
}

// `VIEW` ROLE FUNCTIONS

bool Gui::IncomingNotify(Messages::Actions n) const
{
  switch(n)
  {
    case Messages::SHOW_WINDOW:
      Fl::run();
      break;
    case Messages::SHOW_INTRO:
      output_->value("Wait for input...");
      Fl::flush();
      break;
    case Messages::GAME_OVER:
      output_->value("GameOver");
      DisableButtons();
      Fl::flush();             
      break;
    case Messages::SHOW_DATA:
      std::stringstream sst;
      sst << model_.a_;
      output_->value(sst.str().c_str());
      Fl::flush();      
      break;
  }
  return true;
}

// REALISATION DETAILS

void Gui::StartGame()
{
  model_.StartGame();
}

void Gui::EnableButtons()
{
  btn_send_->activate();
}

void Gui::DisableButtons() const
{
  btn_send_->deactivate();
}

}  // namespace mvc_set