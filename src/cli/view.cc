// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `view` using ostream routines

#include "view.h"

namespace wumpus_game {

bool CliView::IncomingNotify(Event msg) const
{
  switch(msg)
  {
    case Event::NEW_LEVEL :
      cli_helpers::print_intro(ostream_, model_);
      break;
    
    case Event::GAME_OVER :
      cli_helpers::print_game_over(ostream_, model_.game_over_cause_);
      break;
    
    case Event::MOVED_BATS :
      cli_helpers::print_moved_bats(ostream_);
      break;
    
    case Event::HAVE_NOT_ARROWS :
      cli_helpers::print_shot_no_arrays(ostream_);
      break;

    case Event::SHOT_NOT_NEIGHBOR :
      cli_helpers::print_shot_not_neighboring(ostream_);
      break;

    case Event::MOVE_NOT_NEIGHBOR :
      cli_helpers::print_error_room(ostream_);
      break;
    
    case Event::ONE_WUMP_KILLED :
      cli_helpers::print_killed_one_wump(ostream_);
      break;
    
    case Event::READY_TO_INPUT :
      cli_helpers::print_neighbors(ostream_, model_);  
      cli_helpers::print_feels(ostream_, model_);    
      cli_helpers::print_prompt(ostream_);
      break;
    case Event::UNKNOWN_COMMAND : 
      cli_helpers::print_unknown_command(ostream_);
      break;
    // case Event::ERROR_ACTION :
    //   cli_helpers::print_error_action(ostream_);
    //   break;
    
    // case Event::ERROR_ROOM :
    //   cli_helpers::print_error_room(ostream_);
    //   break;
    case Event::WINDOW : default: break;
  }
  return true;
}

// HELPERS

namespace cli_helpers {

void print_prompt(std::ostream& ostream)
{
  ostream << "What to do? Move or shot? In which room? > ";
}

void print_error_room(std::ostream& ostream)
{
  ostream << "ERROR: You input not neighbor room to move, please repeat\n";
}

void  print_shot_no_arrays(std::ostream& ostream)
{
  ostream << "ERROR: You have not enought arrays to show\n";
}

void  print_shot_not_neighboring(std::ostream& ostream)
{
  ostream << "ERROR: You shot not neighboring room, please repeat\n";
}

void print_intro(std::ostream& ostream, const Logic& logic)
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

void print_game_over(std::ostream& ostream, Logic::SubjectID person)
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

void print_feels(std::ostream& ostream, const Logic& logic)
{
  auto feels = logic.GetLevel().player_->Feels();
  for (auto const feel : feels) {
    switch(feel)
    {
      case Logic::SubjectID::WUMP :
        ostream << "FEELS: It`s smeels like Wumpus (possible the Wumpus is near)\n";
        break;
      case Logic::SubjectID::PIT  :
        ostream << "FEELS: You feel the wind (possible the bats is near)\n";
        break;
      case Logic::SubjectID::BAT  :
        ostream << "FEELS: You feel the cold (possible the bottomless pit is near)\n";
        break;
      default : break;
    } 
  }
}

void print_neighbors(std::ostream& ostream, const Logic& model)
{
  auto current { model.GetLevel().player_->GetCurrRoomNum() };
  auto neighbor = helpers::get_neighboring_rooms
  (
    current,
    model.GetLevel().cave_.get()
  );

  ostream << "-\nYou see the legend on the floor with current room "
          << "number and directions:\n";
  ostream << "*** Room # " << current
          << ", tunnels to " << helpers::vint_to_string(neighbor, ", ")
          << " rooms ***\n";
}

void print_moved_bats(std::ostream& ostream)
{
  ostream << "INFO: You have been moved by the Bats to another room\n";
}

void print_killed_one_wump(std::ostream& ostream)
{
  ostream << "INFO: You killed one wumpus\n";
}

void print_unknown_command(std::ostream& ostream)
{
  ostream << "ERROR: Your input is not recognized\n";  
}

}  // namespace cli_helpers

}  // namespace wumpus_game