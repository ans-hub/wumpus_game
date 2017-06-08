// main.cc: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: main game app
// 
// Note #1 : just enum typedefs

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

bool is_debug(int argc, char* argv[])
{
  return ((argc == 2) && (std::string(argv[1]) == "debug")) ? true : false;
}

int main(int argc, char* argv[])
{
  typedef anshub::Subject::Person is;               //  see note #1
  typedef anshub::Interaction::GameOverCause its;
  typedef anshub::Interaction::Actions act;

  constexpr int kCaveSize {20};

  anshub::Interaction game;
  anshub::Labyrinth cave(kCaveSize);
  anshub::Wump wump(&cave);
  anshub::Bat bats(&cave);
  anshub::Pit pit(&cave);
  anshub::Player player(&cave);

  game.SayIntro();

  do {
    if (is_debug(argc, argv)) {
      cave.DebugOutput(std::cout);
    }

    auto curr_room = player.GetCurrRoomNum();
    auto neighbor_rooms = cave.GetNeighbors(curr_room);
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
          if (cave.IsNeighbors(wump_room, player_room)) {
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