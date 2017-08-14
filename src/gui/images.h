// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: RAII struct managing image resources in game

#ifndef IMAGES_H
#define IMAGES_H

#include <FL/Fl.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_GIF_Image.H>

#include "enums/enums.h"

namespace wumpus_game {

struct Images
{
  Images();
  ~Images();

  Fl_Image* GetMainBackground(int level, int w, int h);
  Fl_Image* GetPlayerImage(PlayerState, int level);
  Fl_Image* GetPlayerBg(int level);
  Fl_Image* GetRoomImage(RoomState, int level);
  Fl_Image* GetInfoImages(InfoStuff, int level);

  // For cave level

  Fl_PNG_Image* img_bg_cv_;
  Fl_PNG_Image* img_bg_uw_;
  Fl_PNG_Image* img_bg_bc_;
  Fl_PNG_Image* img_bg_hm_;
  Fl_PNG_Image* img_stay_cv_;
  Fl_PNG_Image* img_shot_cv_;
  Fl_PNG_Image* img_shot_bc_;
  Fl_PNG_Image* img_shot_lb_;
  Fl_PNG_Image* img_walk_cv_;
  Fl_PNG_Image* img_walk_hm_;
  Fl_PNG_Image* img_bats_uw_;
  Fl_PNG_Image* img_bats_cv_;
  Fl_PNG_Image* img_bats_bc_;
  Fl_PNG_Image* img_kill_wump_cv_;
  Fl_PNG_Image* img_kill_wump_bc_;
  Fl_PNG_Image* img_kill_wump_hm_;
  Fl_PNG_Image* img_no_arrows_cv_;
  Fl_PNG_Image* img_unknown_cv_;
  Fl_PNG_Image* img_dead_wump_cv_;
  Fl_PNG_Image* img_dead_pits_cv_;
  Fl_PNG_Image* img_dead_pits_bc_;
  Fl_PNG_Image* img_feels_box_cv_;
  Fl_PNG_Image* img_feels_bats_uw_;
  Fl_PNG_Image* img_feels_bats_cv_;
  Fl_PNG_Image* img_feels_bats_bc_;
  Fl_PNG_Image* img_feels_pits_cv_;
  Fl_PNG_Image* img_feels_pits_bc_;
  Fl_PNG_Image* img_feels_wumps_cv_;
  Fl_PNG_Image* img_feels_wumps_hm_;

  Fl_PNG_Image* img_room_on_cv_;
  Fl_PNG_Image* img_room_off_cv_;
  Fl_PNG_Image* img_room_mark_cv_;

  Fl_PNG_Image* wdg_info_cover_cv_;
  Fl_PNG_Image* wdg_info_level_cv_;
  Fl_PNG_Image* wdg_info_wumps_cv_;
  Fl_PNG_Image* wdg_info_wumps_hm_;
  Fl_PNG_Image* wdg_info_bats_uw_;
  Fl_PNG_Image* wdg_info_bats_cv_;
  Fl_PNG_Image* wdg_info_bats_bc_;
  Fl_PNG_Image* wdg_info_pits_cv_;
  Fl_PNG_Image* wdg_info_pits_bc_;
  Fl_PNG_Image* wdg_info_arrows_cv_;
  Fl_PNG_Image* wdg_info_arrows_lb_;
  Fl_PNG_Image* wdg_info_arrows_bc_;
  Fl_PNG_Image* wdg_info_arrows_hm_;
  Fl_PNG_Image* wdg_info_continue_cv_;
  Fl_PNG_Image* wdg_info_continue_de_cv_;

  Fl_PNG_Image* bg_cv_main_;
  Fl_PNG_Image* bg_uw_main_;
  Fl_PNG_Image* bg_dt_main_;
  Fl_PNG_Image* bg_cp_main_;
  Fl_PNG_Image* bg_lb_main_;
  Fl_PNG_Image* bg_hm_main_;
};

namespace helpers {

  Fl_PNG_Image* resize_img(Fl_PNG_Image*, int, int);

}  // namespace helpers

}  // namespace wumpus_game

#endif  // IMAGES_H
