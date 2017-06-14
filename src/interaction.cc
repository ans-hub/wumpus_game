// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the class that represents interaction with user

#include "interaction.h"

namespace anshub {

void Interaction::Say(const std::string& msg) const
{
  std::cout << msg << '\n';
}

void Interaction::SayGameOver() const
{
  switch (game_over_cause_)
  {
    case PLAYER:
      this->Say("You have killed the Wumpus! Congratulations!");
      break;
    case WUMP:
      this->Say("You have been killed by Wumpus");
      break;
    case PIT:
      this->Say("The bottomless pit is your perpetual retreat");
      break;
    case USER:
    default:
      this->Say("See you later!");
      break;
  }
}

void Interaction::SayIntro() const
{
  this->Say("\nYou are in the dark cave. Somewhere here lives the Wumpus.");
  this->Say("You have the bow and unlimited count of arrows. Find and kill him!");
  this->Say("And be aware about presence of other danger things - the Bats and the Bottomless pit");
  this->Say("You see the legend on the floor with current room number and directions.");
}

void Interaction::SayRoomNeighbors(int curr_room, std::vector<int> neighbors) const
{
  std::stringstream sst;
  sst << "\nINFO:  You are in room " << curr_room << " with tunnels to ";
  for (auto const r : neighbors) {
    sst << r << ", ";
  }
  sst.seekp(-2, std::ios_base::end);
  sst << " rooms.\n";
  std::cout << sst.str();
}

Interaction::Actions Interaction::InputActions(int& room) const
{ 
  // Input action

  std::string x;
  std::string msg {"INPUT: (m)ove, (s)hot, (h)elp or (q)uit: "};
  std::vector<std::string> list { "m", "move", "s", "shot", "h", "help", "q", "quit"};
  do {
  } while (!cin_get(x, msg, list));
  
  if ((x == "h") || (x == "help")) return HELP;
  if ((x == "q") || (x == "quit")) return QUIT;

  // Input room number to apply action

  int min = 0;
  int max = 19;
  msg = "ROOM:  input room number (0-19): ";
  do {
  } while (!cin_get(room, msg, min, max));

  if ((x == "m") || (x == "move")) return MOVE;
  if ((x == "s") || (x == "shot")) return SHOT;
  
  return QUIT;
}

}  // namespace anshub