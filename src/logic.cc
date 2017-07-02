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
, game_over_cause_{NONE}    // see notes #1,2 after code // here we only gets settings
{ }

void Logic::Run()
{
  StartGame();
}

void Logic::StartGame()
{
  game_over_cause_ = NONE;
  NotifyViews(SHOW_INTRO);
  do {
    NotifyViews(SHOW_NEIGH_ROOMS);
    WhomPlayerSees();
    ShowPlayerFeels();
    PlayerTurn();
    EnemyTurn();
  } while(!game_over_cause_);
  NotifyViews(SHOW_GAME_OVER);
}

// PRIVATE REALISATION

void Logic::PlayerTurn()
{
  NotifyViews(SHOW_REQ_INPUT);
  
  Message msg;
  int room{};

  switch(RequestController(msg, room))
  {
    case msg::MOVE :
      player.Move(room, msg);
      game.Say(msg);
      break;
    case msg::SHOT :
      if (player.Shot(room) == is::WUMP) {
        wump.Kill();
        game.GameOver(its::PLAYER);
      }
      else {
        int wump_room = wump.GetCurrRoomNum();
        int player_room = player.GetCurrRoomNum();
        if (helpers::is_neighboring_rooms(wump_room, player_room, cave)) {
          wump.Worried(true);
        }
      }
      break;
    // case msg::HELP : game.SayIntro(); break;
    // case msg::QUIT : game.GameOver(its::USER); break;
  }
}

void Logic::EnemyTurn()
{
  if (wump.Worried()) {
    wump.Worried(false);
    wump.MoveRandom();
  }
  auto wump_sees = wump.ExamineRoom();
  for(auto const whom : wump_sees) {    
    switch(whom)
    {
      case is::PLAYER : game.GameOver(its::WUMP); break;
      default : break;
    }
  }
}

void IfBattle()
{
  auto player_sees = player.ExamineRoom();
  for(auto const whom : player_sees) {
    switch (whom)
    {
      case is::WUMP : player.Kill(); game.GameOver(its::WUMP); break;
      case is::PIT  : player.Kill(); game.GameOver(its::PIT); break;
      case is::BAT  : player.TeleportRandom(); bats.TeleportRandom(); break;
      default : break;
    }
  }
}

void Logic::RebuildCave()
{
  // cave_ = Labyrinth(20);
  // wump_(cave_);
  // bats_(cave_);
  // pit_(cave_);
  // player_(cave_);
  // game_over_ = false;
}

}  // namespace mvc_set

// VIEW METHODS

void ShowNeighborRooms()
{   
  // move in the view
  // auto curr_room = player_.GetCurrRoomNum();
  // auto neighbor_rooms = helpers::get_neighboring_rooms(curr_room, cave_);
  // game.SayRoomNeighbors (curr_room, neighbor_rooms);
}

void ShowPlayerFeels()
{
 auto feels = player_.Feels();
  for (auto const feel : feels) {
    switch(feel)
    {
      case is::WUMP : NotifyViews(FEEL_WUMP); break;
      case is::PIT  : NotifyViews(FEEL_PIT); break;
      case is::BAT  : NotifyViews(FEEL_BAT); break;
      // case is::BAT  : game.Say(bats.FeelsRepresent()); break;
      default : break;
    }
  }
}

// Note #1 : interesting thing about initialization https://stackoverflow.com/a/6822479/7489927

// Note #2 : also needs to get_settings in constructor
