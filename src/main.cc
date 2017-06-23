// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main app of wumpus_game

#include <iostream>
#include <vector>
#include <string>

#include "interaction.h"
#include "room.h"
#include "labyrinth.h"
#include "player.h"
#include "wump.h"
#include "bat.h"
#include "pit.h"
#include "helpers.h"

bool is_debug(int argc, char* argv[])
{
  return ((argc == 2) && (std::string(argv[1]) == "debug")) ? true : false;
}

int main(int argc, char* argv[])
{
  using namespace wumpus_game;
  
  typedef Subject::Person is;               // 
  typedef Interaction::GameOverCause its;   // just enums typedefs
  typedef Interaction::Actions act;         //

  constexpr int kCaveSize {20};

  Interaction game;
  Labyrinth cave(kCaveSize);
  Wump wump(cave);
  Bat bats(cave);
  Pit pit(cave);
  Player player(cave);

  game.SayIntro();

  do {
    if (is_debug(argc, argv)) {
      std::cout << cave << '\n';
    }

    auto curr_room = player.GetCurrRoomNum();
    auto neighbor_rooms = helpers::get_neighboring_rooms(curr_room, cave);
    game.SayRoomNeighbors (curr_room, neighbor_rooms);

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

    auto feels = player.Feels();
    for (auto const feel : feels) {
      switch(feel)
      {
        case is::WUMP : game.Say(wump.FeelsRepresent()); break;
        case is::PIT  : game.Say(pit.FeelsRepresent()); break;
        case is::BAT  : game.Say(bats.FeelsRepresent()); break;
        default : break;
      }
    }

    int room{};
    std::string msg{""};

    switch(game.InputActions(room))
    {
      case act::MOVE :
        player.Move(room, msg);
        game.Say(msg);
        break;
      case act::SHOT :
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
      case act::HELP : game.SayIntro(); break;
      case act::QUIT : game.GameOver(its::USER); break;
    }

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
  } while(!game.GameOver());
  
  game.SayGameOver();
  return 0;
}