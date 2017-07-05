
#include "view.h"

namespace mvc_set {

bool CliView::IncomingNotify(Show msg)
{
  switch(msg)
  {
    case Show::WINDOW :
      model_.StartGame();
      break;
    
    case Show::INTRO :
      cli_helpers::print_intro(ostream_);
      break;
    
    case Show::GAME_OVER :
      cli_helpers::print_game_over(ostream_, model_.game_over_cause_);
      break;

    case Show::PLAYER_FEELS :
      cli_helpers::print_feels(ostream_, model_.player_);
      break;

    case Show::NEIGH_ROOMS :
      cli_helpers::print_neighbors(ostream_, model_);
      break;    
    
    case Show::MOVED_BATS :
      cli_helpers::print_moved_bats(ostream_);
      break;

    case Show::PROMPT :
      cli_helpers::print_prompt(ostream_);
      break;
    
    case Show::ERROR_ACTION :
      cli_helpers::print_error_action(ostream_);
      break;
    
    case Show::ERROR_ROOM :
      cli_helpers::print_error_room(ostream_);
      break;

    default: break;
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
  ostream << "ERROR: You input not neighbor room, please repeat\n";
}

void print_error_action(std::ostream& ostream)
{
  ostream << "ERROR: You input error action, please repeat\n";
}

void print_intro(std::ostream& ostream)
{
  ostream << "You are in the dark cave. Somewhere here lives the Wumpus.\n"
          << "You have the bow and unlimited count of arrows. Find and kill him!\n"
          << "And be aware about presence of other danger things -"
          << "the Bats and the Bottomless pit\n\n";
}

void print_game_over(std::ostream& ostream, CliView::Person person)
{
  switch (person) {
    case CliView::Person::PLAYER:
      ostream << "***You have killed the Wumpus! Congratulations!***\n";
      break;
    case CliView::Person::WUMP:
      ostream << "***You have been killed by Wumpus***\n";
      break;
    case CliView::Person::PIT:
      ostream << "***The bottomless pit is your perpetual retreat***\n";
      break;
    case CliView::Person::UNKNOWN:
    default:
      ostream << "***See you later!***\n";
      break;
  }
}

void print_feels(std::ostream& ostream, const wumpus_game::Player& player)
{
  using namespace wumpus_game;

  auto feels = player.Feels();
  for (auto const feel : feels) {
    switch(feel)
    {
      case Logic::Person::WUMP :
        ostream << "FEELS: It`s smeels like Wumpus (possible the Wumpus is near)\n";
        break;
      case Logic::Person::PIT  :
        ostream << "FEELS: You feel the wind (possible the bats is near)\n";
        break;
      case Logic::Person::BAT  :
        ostream << "FEELS: You feel the cold (possible the bottomless pit is near)\n";
        break;
      default : break;
    } 
  }
}

void print_neighbors(std::ostream& ostream, const wumpus_game::Logic& model)
{
  using namespace wumpus_game;
  
  auto current { model.player_.GetCurrRoomNum() };
  auto neighbor = helpers::get_neighboring_rooms(current, model.cave_);

  ostream << "You see the legend on the floor with current room "
          << "number and directions:\n";
  ostream << "*** Room # " << current
          << ", tunnels to " << helpers::vint_to_string(neighbor, ", ")
          << " rooms ***\n";
}

void print_moved_bats(std::ostream& ostream)
{
  ostream << "INFO: You have been moved by the Bats to another room\n";
}

}  // namespace cli_helpers

}  // namespace mvc_set