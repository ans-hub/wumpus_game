// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents player on the map

#include "widget_player.h"

namespace wumpus_game {

WidgetPlayer::WidgetPlayer(AudioOut& audio)
  : Fl_Group{0, 0, 60, 70}
  , curr_room_{-1}
  , audio_{audio}
  , last_state_{}
  , box_player_{(new Fl_Box((60 - 32) / 2, (70 + 10 - 32) / 2, 32, 32))}
  , box_wumps_{(new Fl_Box(20, 0, 20, 20))}
  , box_bats_{(new Fl_Box(40, 0, 20, 20))}
  , box_pits_{(new Fl_Box(0, 0, 20, 20))}
  , img_bg_{(new Fl_PNG_Image("../src/gui/widgets/img/player_bg.png"))}  
  , img_stay_{(new Fl_PNG_Image("../src/gui/widgets/img/player_stay.png"))}
  , img_shot_{(new Fl_PNG_Image("../src/gui/widgets/img/player_shot.png"))}
  , img_walk_{(new Fl_PNG_Image("../src/gui/widgets/img/player_walk.png"))}
  , img_bats_{(new Fl_PNG_Image("../src/gui/widgets/img/player_bats.png"))}  
  , img_kill_wump_{(new Fl_PNG_Image("../src/gui/widgets/img/wump_killed.png"))}
  , img_no_arrows_{(new Fl_PNG_Image("../src/gui/widgets/img/unknown_actions.png"))}
  , img_unknown_{(new Fl_PNG_Image("../src/gui/widgets/img/unknown_action.png"))}
  , img_dead_wump_{(new Fl_PNG_Image("../src/gui/widgets/img/player_dead_w.png"))}
  , img_dead_pits_{(new Fl_PNG_Image("../src/gui/widgets/img/player_dead_p.png"))}
  , img_feels_box_{(new Fl_PNG_Image("../src/gui/widgets/img/feels_box.png"))}
  , img_feels_bats_{(new Fl_PNG_Image("../src/gui/widgets/img/feels_bats.png"))}
  , img_feels_pits_{(new Fl_PNG_Image("../src/gui/widgets/img/feels_pits.png"))}
  , img_feels_wumps_{(new Fl_PNG_Image("../src/gui/widgets/img/feels_wumps.png"))}
{
  TuneAppearance();
  end();
}

void WidgetPlayer::SetState(State state)
{
  bool repeat_snd{false};
  audio_.Stop(config::GetSound(last_state_));

  switch (state) {
    case State::MOVED_BY_BATS :
      box_player_->image(img_bats_); repeat_snd = true; break;
    
    case State::STAY : 
      box_player_->image(img_stay_); break;
    
    case State::WALK : 
      box_player_->image(img_walk_); repeat_snd = true; break;
    
    case State::SHOT : 
      box_player_->image(img_shot_); break;
    
    case State::KILLED_BY_WUMP : 
      box_player_->image(img_dead_wump_); break;

    case State::KILLED_BY_PITS : 
      box_player_->image(img_dead_pits_); break;
    
    case State::KILL_WUMP : 
      box_player_->image(img_kill_wump_); break;
    
    case State::HAVENT_ARROWS : 
      box_player_->image(img_no_arrows_); break;
    
    case State::UNKNOWN_ACTION : 
      box_player_->image(img_unknown_); break;    
    
    default : break;
  }
  
  last_state_ = state;
  audio_.Play(config::GetSound(state), repeat_snd);               
  redraw();
}

void WidgetPlayer::ShowFeelsIcons(bool wump, bool bats, bool pits)
{
  if (wump) 
    box_wumps_->show();
  else
    box_wumps_->hide();
  if (bats)
    box_bats_->show();
  else
    box_bats_->hide();
  if (pits)
    box_pits_->show();
  else
    box_pits_->hide();
  redraw();
}

// PRIVATE REALISATION

void WidgetPlayer::TuneAppearance()
{
  resizable(0);
  image(img_bg_);
  align(Fl_Align(513));
  
  box_player_->image(img_stay_);
  box_player_->align(Fl_Align(513));
  box_wumps_->image(img_feels_wumps_);
  box_bats_->image(img_feels_bats_);
  box_pits_->image(img_feels_pits_);
}

}  // namespace wumpus_game