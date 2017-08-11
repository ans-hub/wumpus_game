// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: RAII struct managing image resources in game

#include "images.h"

namespace wumpus_game {

Images::Images()
  : img_bg_cv_{(new Fl_PNG_Image("gui/images/widgets/player_bg.png"))}
  , img_stay_cv_{(new Fl_PNG_Image("gui/images/widgets/player_stay.png"))}
  , img_shot_cv_{(new Fl_PNG_Image("gui/images/widgets/player_shot.png"))}
  , img_walk_cv_{(new Fl_PNG_Image("gui/images/widgets/player_walk.png"))}
  , img_bats_cv_{(new Fl_PNG_Image("gui/images/widgets/player_bats.png"))}  
  , img_kill_wump_cv_{(new Fl_PNG_Image("gui/images/widgets/wump_killed.png"))}
  , img_no_arrows_cv_{(new Fl_PNG_Image("gui/images/widgets/unknown_state.png"))}
  , img_unknown_cv_{(new Fl_PNG_Image("gui/images/widgets/unknown_state.png"))}
  , img_dead_wump_cv_{(new Fl_PNG_Image("gui/images/widgets/player_dead_w.png"))}
  , img_dead_pits_cv_{(new Fl_PNG_Image("gui/images/widgets/player_dead_p.png"))}
  , img_feels_box_cv_{(new Fl_PNG_Image("gui/images/widgets/feels_box.png"))}
  , img_feels_bats_cv_{(new Fl_PNG_Image("gui/images/widgets/feels_bats.png"))}
  , img_feels_pits_cv_{(new Fl_PNG_Image("gui/images/widgets/feels_pits.png"))}
  , img_feels_wumps_cv_{(new Fl_PNG_Image("gui/images/widgets/feels_wumps.png"))}
  , img_room_on_cv_{(new Fl_PNG_Image("gui/images/widgets/room_on.png"))}
  , img_room_off_cv_{(new Fl_PNG_Image("gui/images/widgets/room_off.png"))}
  , img_room_mark_cv_{(new Fl_PNG_Image("gui/images/widgets/room_mark.png"))}
  , wdg_info_cover_cv_{new Fl_PNG_Image("gui/images/widgets/info_bg.png")}
  , wdg_info_level_cv_{new Fl_PNG_Image("gui/images/widgets/info_level.png")}
  , wdg_info_wumps_cv_{new Fl_PNG_Image("gui/images/widgets/info_wumps.png")}
  , wdg_info_bats_cv_{new Fl_PNG_Image("gui/images/widgets/info_bats.png")}
  , wdg_info_pits_cv_{new Fl_PNG_Image("gui/images/widgets/info_pits.png")}
  , wdg_info_arrows_cv_{new Fl_PNG_Image("gui/images/widgets/info_arrows.png")}
  , wdg_info_continue_cv_{new Fl_PNG_Image("gui/images/widgets/info_continue.png")}
  , bg_cv_main_{new Fl_PNG_Image("gui/images/forms/cv_main.png")}
  , bg_uw_main_{new Fl_PNG_Image("gui/images/forms/uw_main.png")}
  , bg_dt_main_{new Fl_PNG_Image("gui/images/forms/dt_main.png")}
  , bg_cp_main_{new Fl_PNG_Image("gui/images/forms/cp_main.png")}
  , bg_hm_main_{new Fl_PNG_Image("gui/images/forms/hm_main.png")}
{

}

Images::~Images()
{
  delete img_bg_cv_;
  delete img_stay_cv_;
  delete img_shot_cv_;
  delete img_walk_cv_;
  delete img_bats_cv_;
  delete img_kill_wump_cv_;
  delete img_no_arrows_cv_;
  delete img_unknown_cv_;
  delete img_dead_wump_cv_;
  delete img_dead_pits_cv_;
  delete img_feels_box_cv_;
  delete img_feels_bats_cv_;
  delete img_feels_pits_cv_;
  delete img_feels_wumps_cv_;
  delete img_room_on_cv_;
  delete img_room_off_cv_;
  delete img_room_mark_cv_;
  delete wdg_info_cover_cv_;
  delete wdg_info_level_cv_;
  delete wdg_info_wumps_cv_;
  delete wdg_info_bats_cv_;
  delete wdg_info_pits_cv_;
  delete wdg_info_arrows_cv_;
  delete wdg_info_continue_cv_;
  delete bg_cv_main_;
  delete bg_uw_main_;
  delete bg_dt_main_;
  delete bg_cp_main_;
  delete bg_hm_main_;
}

Fl_Image* Images::GetMainBackground(int level, int w, int h)
{
  if (level < 4) {
    bg_cv_main_ = helpers::resize_img(bg_cv_main_, w, h);
    return bg_cv_main_;
  }
  else if (level < 7) {
    bg_uw_main_ = helpers::resize_img(bg_uw_main_, w, h);
    return bg_uw_main_;
  }
  else if (level < 11) {
    bg_dt_main_ = helpers::resize_img(bg_dt_main_, w, h);
    return bg_dt_main_;
  }
  else if (level < 12) {
    bg_cp_main_ = helpers::resize_img(bg_cp_main_, w, h);
    return bg_cp_main_;
  }
  else if (level < 13) {
    bg_hm_main_ = helpers::resize_img(bg_hm_main_, w, h);   
    return bg_hm_main_;
  }
  return bg_cv_main_;
}

Fl_Image* Images::GetPlayerImage(PlayerState state, int level)
{
  // if (level == 1) {
    switch (state) {
      case PlayerState::STAY : return img_stay_cv_;
      case PlayerState::SHOT : return img_shot_cv_;
      case PlayerState::WALK : return img_walk_cv_;
      case PlayerState::MOVED_BY_BATS : return img_bats_cv_;
      case PlayerState::KILL_WUMP : return img_kill_wump_cv_;
      case PlayerState::HAVENT_ARROWS : return img_no_arrows_cv_;
      case PlayerState::UNKNOWN_STATE : return img_unknown_cv_;
      case PlayerState::KILLED_BY_WUMP : return img_dead_wump_cv_;
      case PlayerState::KILLED_BY_PITS : return img_dead_pits_cv_;
      case PlayerState::FEELS_WUMP : return img_feels_wumps_cv_;
      case PlayerState::FEELS_BATS : return img_feels_bats_cv_;
      case PlayerState::FEELS_PITS : return img_feels_pits_cv_;
    }
  // }
  return img_stay_cv_;
}

Fl_Image* Images::GetPlayerBg(int level)
{
  // if (level == 1)
    // return img_bg_cv_;
  return img_bg_cv_;
}

Fl_Image* Images::GetRoomImage(RoomState state, int level)
{
  // if (level == 1) {
    switch (state) {
      case RoomState::ON : return img_room_on_cv_;
      case RoomState::OFF : return img_room_off_cv_;
      case RoomState::MARK : return img_room_mark_cv_;
    }
  // }
}

Fl_Image* Images::GetInfoImages(InfoStuff state, int level)
{
  // if (level == 1) {
    switch (state) {
      case InfoStuff::COVER : return wdg_info_cover_cv_;
      case InfoStuff::ARROWS : return wdg_info_arrows_cv_;
      case InfoStuff::PITS : return wdg_info_pits_cv_;
      case InfoStuff::BATS : return wdg_info_bats_cv_;
      case InfoStuff::WUMPS : return wdg_info_wumps_cv_;
      case InfoStuff::LEVEL : return wdg_info_level_cv_;
      case InfoStuff::CONTINUE : return wdg_info_continue_cv_;
    }
  // }
}

namespace helpers {

Fl_PNG_Image* resize_img(Fl_PNG_Image* i, int w, int h)
{
  Fl_PNG_Image* old = i;
  Fl_Image* tmp = i->copy(w, h);
  delete old;
  return (Fl_PNG_Image*)tmp;
}

}  // namespace helpers

}  // namespace wumpus_game