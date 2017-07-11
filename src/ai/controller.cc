
#include "controller.h"

namespace mvc_set {

    // constexpr int kLevels {5};
    
    // Logic logic{};

    // AiController ctrl {logic};
    // CliView view {std::cout, logic};
    // logic.RegisterObserver(view);


    // int i{0};
    // do {
    //   logic.NewLevel(i);
    //   const Level& level = logic.GetLevel();
    //   do {
    //     int curr_room = level.player_->GetCurrRoomNum();
    //     auto rooms = helpers::get_neighboring_rooms(curr_room, level.cave_.get());
    //     auto feels = level.player_->Feels();
        
    //     bool wump = false;
    //     for (auto& feel : feels) {
    //       if (feel == Subject::WUMP) wump = true;
    //     }
    //     int cell = rand_toolkit::get_rand(0,2);
    //     logic.Turn(static_cast<int>(wump), rooms[cell]);

    //   } while (!logic.GameOver());
    // } while (++i <= kLevels);

}  // namespace mvc_set