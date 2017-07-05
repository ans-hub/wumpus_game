// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game logic (aka `model` in MVC-meaning)

#include "logic.h"

namespace wumpus_game {

Logic::Logic()
: cave_{20}
, wump_{cave_}
, bats_{cave_}
, pit_{cave_}
, player_{cave_}
, game_over_cause_{Person::EMPTY}
{ }

void Logic::Run()
{
  using namespace ::mvc_set;

  NotifyViews(Show::WINDOW);
  // StartGame();
}

void Logic::Rebuild()
{
  wump_.Alive();
  wump_.TeleportRandom();
  player_.Alive();
  player_.TeleportRandom();
  bats_.TeleportRandom();
  pit_.TeleportRandom();
}

void Logic::StartGame()
{
  using namespace ::mvc_set;

  game_over_cause_ = Person::EMPTY;
  NotifyViews(Show::INTRO);
  do {
    NotifyViews(Show::NEIGH_ROOMS);
    NotifyViews(Show::PLAYER_FEELS);
    PlayerTurn();
    Battle();
    EnemyTurn();
  } while(game_over_cause_ == Person::EMPTY);
  
  NotifyViews(Show::GAME_OVER);
}

// PRIVATE REALISATION

void Logic::PlayerTurn()
{
  using namespace ::mvc_set;
  
  Input action = Input::UNKNOWN;
  int room{-1};
  GetUserInput(action, room);

  switch(action) {
    case Input::SHOT : PlayerDoShot(room); break;
    case Input::MOVE : PlayerDoMove(room); break;
    case Input::QUIT : game_over_cause_ = Person::UNKNOWN; break;
    // case Input::HELP : game.SayIntro(); break;
    case Input::UNKNOWN : default : break;
  }
}

void Logic::PlayerDoShot(int room)
{
  using namespace ::mvc_set;
  
  if (player_.Shot(room) == Person::WUMP) {
    wump_.Kill();
    game_over_cause_ = Person::PLAYER;
  }
  else {
    int wump_room = wump_.GetCurrRoomNum();
    int player_room = player_.GetCurrRoomNum();
    if (helpers::is_neighboring_rooms(wump_room, player_room, cave_)) {
      wump_.Worried(true);
    }
  }
}

void Logic::PlayerDoMove(int room)
{
  using namespace ::mvc_set;
  
  std::string msg;
  player_.Move(room, msg);
  NotifyViews(Show::PLAYER_MOVED);
}

void Logic::GetUserInput(::mvc_set::Input& action, int& room)
{
  using namespace ::mvc_set;
  
  do {
    NotifyViews(Show::PROMPT);
    RequestController(action, room);

    if (action == Input::QUIT)
      break;

    int curr_room = player_.GetCurrRoomNum();
    bool correctness{true};

    if (!helpers::is_neighboring_rooms(curr_room, room, cave_)) {
      NotifyViews(Show::ERROR_ROOM);
      correctness = false;
    }
    if (action == Input::UNKNOWN) {
      NotifyViews(Show::ERROR_ACTION);
      correctness = false;
    }
    if (correctness)
      break;
  } while(true);
}


void Logic::EnemyTurn()
{
  using namespace ::mvc_set;
  
  if (wump_.Worried()) {
    wump_.Worried(false);
    wump_.MoveRandom();
  }
  auto wump_sees = wump_.ExamineRoom();
  for(auto const whom : wump_sees) {    
    switch(whom)
    {
      case Person::PLAYER : game_over_cause_ = Person::WUMP; break;
      default : break;
    }
  }
}

void Logic::Battle()
{
  using namespace ::mvc_set;

  auto player_sees = player_.ExamineRoom();
  for(auto const whom : player_sees) {
    switch (whom)
    {
      case Person::WUMP :
        player_.Kill();
        game_over_cause_ = Person::WUMP;
        break;
      case Person::PIT  :
        player_.Kill();
        game_over_cause_ = Person::PIT;
        break;
      case Person::BAT  :
        player_.TeleportRandom();
        bats_.TeleportRandom();
        NotifyViews(Show::MOVED_BATS);
        break;
      default : break;
    }
  }
}

// void Logic::RebuildCave()
// {
//   // cave_ = Labyrinth(20);
//   // wump_(cave_);
//   // bats_(cave_);
//   // pit_(cave_);
//   // player_(cave_);
//   // game_over_ = false;
// }

}  // namespace mvc_set

// Note #1 : interesting thing about initialization https://stackoverflow.com/a/6822479/7489927

// Note #2 : also needs to get_settings in constructor
