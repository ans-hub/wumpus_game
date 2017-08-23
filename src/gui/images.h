// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: RAII struct managing image resources in game

#ifndef IMAGES_H
#define IMAGES_H

#include <memory>

#include <FL/Fl.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>

#include "enums/enums.h"

namespace wumpus_game {

struct Images
{
  using Image = Fl_PNG_Image;
  using ImagePtr = std::unique_ptr<Image>;

  Images();

  Fl_Image* GetMainBackground(int level, int w, int h);
  Fl_Image* GetPlayerImage(PlayerState, int level);
  Fl_Image* GetPlayerBackground(int level);
  Fl_Image* GetRoomImage(RoomState, int level);
  Fl_Image* GetInfoImages(InfoStuff, int level);

  // FormMain background

  ImagePtr img_cv_;
  ImagePtr img_uw_;
  ImagePtr img_dt_;
  ImagePtr img_bc_;
  ImagePtr img_lb_;
  ImagePtr img_hm_;

  // WidgetPlayer background

  ImagePtr img_player_cv_;
  ImagePtr img_player_uw_;
  ImagePtr img_player_bc_;
  ImagePtr img_player_hm_;

  // WidgetPlayer states

  ImagePtr img_stay_cv_;
  ImagePtr img_shot_cv_;
  ImagePtr img_shot_bc_;
  ImagePtr img_shot_lb_;
  ImagePtr img_walk_cv_;
  ImagePtr img_walk_hm_;
  ImagePtr img_bats_cv_;
  ImagePtr img_bats_uw_;
  ImagePtr img_bats_bc_;
  ImagePtr img_guide_closed_cv_;
  ImagePtr img_guide_opened_cv_;
  ImagePtr img_level_win_cv_;
  ImagePtr img_kill_wump_cv_;
  ImagePtr img_kill_wump_bc_;
  ImagePtr img_kill_wump_hm_;
  ImagePtr img_no_arrows_cv_;
  ImagePtr img_unknown_cv_;
  ImagePtr img_dead_wump_cv_;
  ImagePtr img_dead_pits_cv_;
  ImagePtr img_dead_pits_bc_;
  ImagePtr img_feels_box_cv_;
  ImagePtr img_feels_bats_cv_;
  ImagePtr img_feels_bats_uw_;
  ImagePtr img_feels_bats_bc_;
  ImagePtr img_feels_pits_cv_;
  ImagePtr img_feels_pits_bc_;
  ImagePtr img_feels_wumps_cv_;
  ImagePtr img_feels_wumps_hm_;

  // WidgetRoom states

  ImagePtr img_room_dark_cv_;
  ImagePtr img_room_light_cv_;
  ImagePtr img_room_gate_cv_;
  ImagePtr img_room_guide_op_cv_;
  ImagePtr img_room_guide_cl_cv_;

  // WidgetInfo states

  ImagePtr wdg_info_cover_cv_;
  ImagePtr wdg_info_level_cv_;
  ImagePtr wdg_info_wumps_cv_;
  ImagePtr wdg_info_wumps_hm_;
  ImagePtr wdg_info_bats_cv_;
  ImagePtr wdg_info_bats_uw_;
  ImagePtr wdg_info_bats_bc_;
  ImagePtr wdg_info_pits_cv_;
  ImagePtr wdg_info_pits_bc_;
  ImagePtr wdg_info_arrows_cv_;
  ImagePtr wdg_info_arrows_lb_;
  ImagePtr wdg_info_arrows_bc_;
  ImagePtr wdg_info_arrows_hm_;
  ImagePtr wdg_info_continue_cv_;
  ImagePtr wdg_info_continue_de_cv_;
};

namespace helpers {

  void ResizeImage(Images::ImagePtr&, int, int);

}  // namespace helpers

}  // namespace wumpus_game

#endif  // IMAGES_H
