// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `controller` using ai

#include "controller.h"

namespace wumpus_game {

bool AiController::RunModel()
{
  int i{0};
  do {

    model_.NewLevel(level_);
    const Level& level = model_.GetLevel();
    do {
      int curr_room = level.player_->GetCurrRoomNum();
      auto rooms = helpers::get_neighboring_rooms(curr_room, level.cave_.get());
      auto feels = level.player_->Feels();
      
      bool wump = false;
      for (auto& feel : feels) {
          if (feel == Subject::WUMP) wump = true;
      }
      int cell = rand_toolkit::get_rand(0,2);
      model_.Turn(static_cast<int>(wump), rooms[cell]);
    } while (!model_.GameOver());

  } while (++i <= steps_);

  return true;
}

}  // namespace wumpus_game