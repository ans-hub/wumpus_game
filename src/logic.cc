
#include "model.h"

namespace mvc_set {

Model::Model()    // see notes #1,2 after code
// here we only gets settings
{
  RestartGame();
}

void Model::RestartGame()
{
  cave_ = Labyrinth(20);
  wump_(cave_);
  bats_(cave_);
  pit_(cave_);
  player_(cave_);
  game_over_ = false;
}

void Model::PlayerTurn()
{
  
}

void Model::EnemyTurn()
{
  
}

}  // namespace mvc_set

// Note #1 : interesting thing about initialization https://stackoverflow.com/a/6822479/7489927

// Note #2 : also needs to get_settings in constructor
