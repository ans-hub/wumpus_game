// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents player on the map

#include "widget_player.h"

namespace wumpus_game {

WidgetPlayer::WidgetPlayer(AudioOut& audio, Images& images)
  : Fl_Group{0, 0, 60, 70}
  , room_{-1}
  , level_{-1}
  , state_{State::STAY}
  , audio_{audio}
  , images_{images}
  , box_player_{(new Fl_Box((60 - 32) / 2, (70 + 10 - 32) / 2, 32, 32))}
  , box_wumps_{(new Fl_Box(20, 0, 20, 20))}
  , box_bats_{(new Fl_Box(40, 0, 20, 20))}
  , box_pits_{(new Fl_Box(0, 0, 20, 20))}
{
  TuneAppearance();
  end();
}

void WidgetPlayer::Redraw(int level)
{
  level_ = level;
  
  // Set feels box images

  auto* wump_image = images_.GetPlayerImage(State::FEELS_WUMP, level_);
  box_wumps_->image(wump_image);

  auto* bats_image = images_.GetPlayerImage(State::FEELS_BATS, level_);
  box_bats_->image(bats_image);

  auto* pits_image = images_.GetPlayerImage(State::FEELS_PITS, level_);
  box_pits_->image(pits_image);

  // Set player background
  
  image(images_.GetPlayerBackground(level_));
}

// Sets relevant image and plays sound

void WidgetPlayer::SetState(State state)
{
  // Schedule stop track playback if it is repeated

  bool repeat_snd{false};
  auto last_snd = config::GetPlayerSound(state_, level_);
  audio_.Stop(last_snd, false);

  state_ = state;

  // Change image of widget and define sound repeating

  auto* curr_image = images_.GetPlayerImage(state_, level_);
  box_player_->image(curr_image);

  // Play new sound

  if (state == State::MOVED_BY_BATS || state == State::WALK)
    repeat_snd = true;
  auto curr_snd = config::GetPlayerSound(state_, level_);
  audio_.Play(curr_snd, repeat_snd);

  redraw();
}

// Show feels icons

void WidgetPlayer::ShowFeels(bool wump, bool bats, bool pits)
{
  wump ? box_wumps_->show() : box_wumps_->hide();
  bats ? box_bats_->show()  : box_bats_->hide();
  pits ? box_pits_->show()  : box_pits_->hide();

  if(wump)
    audio_.Play(config::GetPlayerSound(State::FEELS_WUMP, level_));

  redraw();
}

// PRIVATE REALISATION

void WidgetPlayer::TuneAppearance()
{
  resizable(0);
  align(Fl_Align(513));
  box_player_->align(Fl_Align(513));
}

}  // namespace wumpus_game