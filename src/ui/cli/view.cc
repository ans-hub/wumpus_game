
#include "view.h"

namespace mvc_set {

bool CliView::IncomingNotify(Messages::Actions n) const
{
  switch(n)
  {
    case Messages::SHOW_WINDOW:
      ostream_ << "GameStarted\n";
      model_.StartGame();
      break;
    case Messages::SHOW_INTRO:
      ostream_ << "Wait for input...\n";
      break;  
    case Messages::GAME_OVER:
      ostream_ << "GameOver\n";
      // model_.Stop();
      break;
    case Messages::SHOW_DATA:
      ostream_ << "Data: " << model_.a_ << '\n';
      break;
  }
  return true;
}

}  // namespace mvc_set