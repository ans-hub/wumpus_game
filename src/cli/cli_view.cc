// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `view` using ostream routines

#include "cli_view.h"

namespace wumpus_game {

bool CliView::IncomingNotify(Event msg)
{
  switch(msg)
  {
    case Event::NEW_LEVEL :
      cli_helpers::PrintIntro(ostream_, model_);
      break;
    
    case Event::GAME_OVER :
      cli_helpers::PrintGameOver(ostream_, model_.GameOverCause());
      break;
    
    case Event::MOVED_BY_BATS :
      cli_helpers::PrintMovedBats(ostream_);
      break;
    
    case Event::HAVE_NOT_ARROWS :
      cli_helpers::PrintShotNoArrows(ostream_);
      break;

    case Event::SHOT_NOT_NEIGHBOR :
      cli_helpers::PrintShotNotNeighboring(ostream_);
      break;

    case Event::MOVE_NOT_NEIGHBOR :
      cli_helpers::PrintErrorRoom(ostream_);
      break;
    
    case Event::ONE_WUMP_KILLED :
      cli_helpers::PrintKilledOneWump(ostream_);
      break;
    
    case Event::READY_TO_INPUT :
      cli_helpers::PrintNeighbors(ostream_, model_);  
      cli_helpers::PrintFeels(ostream_, model_);    
      cli_helpers::PrintPrompt(ostream_);
      break;

    case Event::UNKNOWN_COMMAND : 
      cli_helpers::PrintUnknownCommand(ostream_);
      break;

    case Event::MODEL_READY : default: break;
  }
  return true;
}

// HELPERS

namespace cli_helpers {

void PrintPrompt(std::ostream& ostream)
{
  ostream << "What to do? Move or shot? In which room? > ";
}

void PrintErrorRoom(std::ostream& ostream)
{
  ostream << "ERROR: You input not neighbor room to move, please repeat\n";
}

void PrintErrorActions(std::ostream& ostream)
{
  ostream << "ERROR: You have not enought arrays to show\n";
}

void PrintShotNotNeighboring(std::ostream& ostream)
{
  ostream << "ERROR: You shot not neighboring room, please repeat\n";
}

void PrintIntro(std::ostream& ostream, const Logic& logic)
{
  auto& level = logic.GetLevel();
  ostream << "You are in the dark cave with " << level.cave_->GetSize()
          << " rooms. Somewhere here lives " << level.wumps_.size() 
          << " Wumpus.\n"
          << "You have the bow and " << level.player_->GetArrows() 
          << " arrows. Find and kill all Wumpus!\n"
          << "And be aware about presence of other danger things - "
          << "the " << level.bats_.size() << " Bats "
          << "and the " << level.pits_.size() << " Bottomless pits\n";
}

void PrintShotNoArrows(std::ostream& ostream)
{
  ostream << "ERROR: You have not enought arrows to shot\n";  
}

void PrintGameOver(std::ostream& ostream, Logic::SubjectID person)
{
  switch (person) {
    case Logic::SubjectID::PLAYER:
      ostream << "***You have clean the cave from Wumpuses! Congratulations!***\n";
      break;
    case Logic::SubjectID::WUMP:
      ostream << "***You have been killed by Wumpus***\n";
      break;
    case Logic::SubjectID::PIT:
      ostream << "***The bottomless pit is your perpetual retreat***\n";
      break;
    case Logic::SubjectID::UNKNOWN:
    default:
      ostream << "***See you later!***\n";
      break;
  }
}

void PrintFeels(std::ostream& ostream, const Logic& logic)
{
  auto feels = logic.GetLevel().player_->Feels();
  for (auto const feel : feels) {
    switch(feel)
    {
      case Logic::SubjectID::WUMP :
        ostream << "FEELS: It`s smeels like Wumpus (possible the Wumpus is near)\n";
        break;
      case Logic::SubjectID::BAT  :
        ostream << "FEELS: You feel the wind (possible the bats is near)\n";
        break;
      case Logic::SubjectID::PIT  :
        ostream << "FEELS: You feel the cold (possible the bottomless pit is near)\n";
        break;
      default : break;
    } 
  }
}

void PrintNeighbors(std::ostream& ostream, const Logic& model)
{
  auto current { model.GetLevel().player_->GetCurrRoomNum() };
  auto neighbor = map_helpers::GetNeighboringRooms
  (
    current,
    model.GetLevel().cave_.get()
  );

  ostream << "-\nYou see the legend on the floor with current room "
          << "number and directions:\n";
  ostream << "*** Room # " << current
          << ", tunnels to " << helpers::VintToString(neighbor, ", ")
          << " rooms ***\n";
}

void PrintMovedBats(std::ostream& ostream)
{
  ostream << "INFO: You have been moved by the Bats to another room\n";
}

void PrintKilledOneWump(std::ostream& ostream)
{
  ostream << "INFO: You killed one wumpus\n";
}

void PrintUnknownCommand(std::ostream& ostream)
{
  ostream << "ERROR: Your input is not recognized\n";  
}

}  // namespace cli_helpers

}  // namespace wumpus_game
