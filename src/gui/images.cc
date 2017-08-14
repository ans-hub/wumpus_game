// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: RAII struct managing image resources in game

#include "images.h"

namespace wumpus_game {

Images::Images()
  : img_bg_cv_{(new Fl_PNG_Image("resources/images/widgets/player_bg.png"))}
  , img_bg_uw_{(new Fl_PNG_Image("resources/images/widgets/player_bg_uw.png"))}
  , img_bg_bc_{(new Fl_PNG_Image("resources/images/widgets/player_bg_bc.png"))}
  , img_bg_hm_{(new Fl_PNG_Image("resources/images/widgets/player_bg_hm.png"))}
  , img_stay_cv_{(new Fl_PNG_Image("resources/images/widgets/player_stay.png"))}
  , img_shot_cv_{(new Fl_PNG_Image("resources/images/widgets/player_shot.png"))}
  , img_shot_bc_{(new Fl_PNG_Image("resources/images/widgets/player_shot_bc.png"))}
  , img_shot_lb_{(new Fl_PNG_Image("resources/images/widgets/player_shot_lb.png"))}
  , img_walk_cv_{(new Fl_PNG_Image("resources/images/widgets/player_walk.png"))}
  , img_walk_hm_{(new Fl_PNG_Image("resources/images/widgets/player_walk_hm.png"))}
  , img_bats_cv_{(new Fl_PNG_Image("resources/images/widgets/player_bats.png"))}  
  , img_bats_uw_{(new Fl_PNG_Image("resources/images/widgets/player_bats_uw.png"))}  
  , img_bats_bc_{(new Fl_PNG_Image("resources/images/widgets/player_bats_bc.png"))}  
  , img_kill_wump_cv_{(new Fl_PNG_Image("resources/images/widgets/wump_killed.png"))}
  , img_kill_wump_bc_{(new Fl_PNG_Image("resources/images/widgets/wump_killed_bc.png"))}
  , img_kill_wump_hm_{(new Fl_PNG_Image("resources/images/widgets/wump_killed_hm.png"))}
  , img_no_arrows_cv_{(new Fl_PNG_Image("resources/images/widgets/unknown_state.png"))}
  , img_unknown_cv_{(new Fl_PNG_Image("resources/images/widgets/unknown_state.png"))}
  , img_dead_wump_cv_{(new Fl_PNG_Image("resources/images/widgets/player_dead_w.png"))}
  , img_dead_pits_cv_{(new Fl_PNG_Image("resources/images/widgets/player_dead_p.png"))}
  , img_dead_pits_bc_{(new Fl_PNG_Image("resources/images/widgets/player_dead_p_bc.png"))}
  , img_feels_box_cv_{(new Fl_PNG_Image("resources/images/widgets/feels_box.png"))}
  , img_feels_bats_cv_{(new Fl_PNG_Image("resources/images/widgets/feels_bats.png"))}
  , img_feels_bats_uw_{(new Fl_PNG_Image("resources/images/widgets/feels_bats_uw.png"))}
  , img_feels_bats_bc_{(new Fl_PNG_Image("resources/images/widgets/feels_bats_bc.png"))}
  , img_feels_pits_cv_{(new Fl_PNG_Image("resources/images/widgets/feels_pits.png"))}
  , img_feels_pits_bc_{(new Fl_PNG_Image("resources/images/widgets/feels_pits_bc.png"))}
  , img_feels_wumps_cv_{(new Fl_PNG_Image("resources/images/widgets/feels_wumps.png"))}
  , img_feels_wumps_hm_{(new Fl_PNG_Image("resources/images/widgets/feels_wumps_hm.png"))}
  , img_room_on_cv_{(new Fl_PNG_Image("resources/images/widgets/room_on.png"))}
  , img_room_off_cv_{(new Fl_PNG_Image("resources/images/widgets/room_off.png"))}
  , img_room_mark_cv_{(new Fl_PNG_Image("resources/images/widgets/room_mark.png"))}
  , wdg_info_cover_cv_{new Fl_PNG_Image("resources/images/widgets/info_bg.png")}
  , wdg_info_level_cv_{new Fl_PNG_Image("resources/images/widgets/info_level.png")}
  , wdg_info_wumps_cv_{new Fl_PNG_Image("resources/images/widgets/info_wumps.png")}
  , wdg_info_wumps_hm_{new Fl_PNG_Image("resources/images/widgets/info_wumps_hm.png")}
  , wdg_info_bats_cv_{new Fl_PNG_Image("resources/images/widgets/info_bats.png")}
  , wdg_info_bats_uw_{new Fl_PNG_Image("resources/images/widgets/info_bats_uw.png")}
  , wdg_info_bats_bc_{new Fl_PNG_Image("resources/images/widgets/info_bats_bc.png")}
  , wdg_info_pits_cv_{new Fl_PNG_Image("resources/images/widgets/info_pits.png")}
  , wdg_info_pits_bc_{new Fl_PNG_Image("resources/images/widgets/info_pits_bc.png")}
  , wdg_info_arrows_cv_{new Fl_PNG_Image("resources/images/widgets/info_arrows.png")}
  , wdg_info_arrows_lb_{new Fl_PNG_Image("resources/images/widgets/info_arrows_lb.png")}
  , wdg_info_arrows_bc_{new Fl_PNG_Image("resources/images/widgets/info_arrows_bc.png")}
  , wdg_info_arrows_hm_{new Fl_PNG_Image("resources/images/widgets/info_arrows_hm.png")}
  , wdg_info_continue_cv_{new Fl_PNG_Image("resources/images/widgets/info_continue.png")}
  , wdg_info_continue_de_cv_{new Fl_PNG_Image("resources/images/widgets/info_continue_de.png")}
  , bg_cv_main_{new Fl_PNG_Image("resources/images/forms/cv_main.png")}
  , bg_uw_main_{new Fl_PNG_Image("resources/images/forms/uw_main.png")}
  , bg_dt_main_{new Fl_PNG_Image("resources/images/forms/dt_main.png")}
  , bg_cp_main_{new Fl_PNG_Image("resources/images/forms/cp_main.png")}
  , bg_lb_main_{new Fl_PNG_Image("resources/images/forms/lb_main.png")}
  , bg_hm_main_{new Fl_PNG_Image("resources/images/forms/hm_main.png")}
{

}

Images::~Images()
{
  delete img_bg_cv_;
  delete img_bg_uw_;
  delete img_bg_bc_;
  delete img_bg_hm_;
  delete img_stay_cv_;
  delete img_shot_cv_;
  delete img_shot_bc_;
  delete img_shot_lb_;
  delete img_walk_cv_;
  delete img_walk_hm_;
  delete img_bats_cv_;
  delete img_bats_bc_;
  delete img_kill_wump_cv_;
  delete img_kill_wump_bc_;
  delete img_kill_wump_hm_;
  delete img_no_arrows_cv_;
  delete img_unknown_cv_;
  delete img_dead_wump_cv_;
  delete img_dead_pits_cv_;
  delete img_feels_box_cv_;
  delete img_feels_bats_cv_;
  delete img_feels_pits_cv_;
  delete img_feels_pits_bc_;
  delete img_feels_wumps_cv_;
  delete img_feels_wumps_hm_;
  delete img_room_on_cv_;
  delete img_room_off_cv_;
  delete img_room_mark_cv_;
  delete wdg_info_cover_cv_;
  delete wdg_info_level_cv_;
  delete wdg_info_wumps_cv_;
  delete wdg_info_wumps_hm_;
  delete wdg_info_bats_cv_;
  delete wdg_info_bats_uw_;  
  delete wdg_info_bats_bc_;
  delete wdg_info_pits_cv_;
  delete wdg_info_pits_bc_;
  delete wdg_info_arrows_cv_;
  delete wdg_info_arrows_bc_;
  delete wdg_info_arrows_lb_;
  delete wdg_info_arrows_hm_;
  delete wdg_info_continue_cv_;
  delete wdg_info_continue_de_cv_;
  delete bg_cv_main_;
  delete bg_uw_main_;
  delete bg_dt_main_;
  delete bg_cp_main_;
  delete bg_lb_main_;
  delete bg_hm_main_;
}

Fl_Image* Images::GetMainBackground(int level, int w, int h)
{
  switch (level) {
    case 1 : case 2 : case 3 : default :
      bg_cv_main_ = helpers::resize_img(bg_cv_main_, w, h);
      return bg_cv_main_;
    case 4 : case 5 : case 6 :
      bg_uw_main_ = helpers::resize_img(bg_uw_main_, w, h);
      return bg_uw_main_;
    case 7 : case 8 : case 9 : case 10 :
      bg_dt_main_ = helpers::resize_img(bg_dt_main_, w, h);
      return bg_dt_main_;
    case 11 : case 12 :
      bg_cp_main_ = helpers::resize_img(bg_cp_main_, w, h);
      return bg_cp_main_;
    case 13 :
      bg_lb_main_ = helpers::resize_img(bg_lb_main_, w, h);   
      return bg_lb_main_;    
    case 14 :
      bg_hm_main_ = helpers::resize_img(bg_hm_main_, w, h);   
      return bg_hm_main_;
  }
  return bg_cv_main_;
}

Fl_Image* Images::GetPlayerImage(PlayerState state, int level)
{
  switch (state) {
    case PlayerState::STAY : default :
      return img_stay_cv_;
    
    case PlayerState::SHOT :
      if (level == 11 || level == 12)
        return img_shot_bc_;   
      else if (level == 13) 
        return img_shot_lb_;
      else if (level == 14)
        return img_walk_hm_;
      else
        return img_shot_cv_;
    
    case PlayerState::WALK :
      if (level == 14) 
        return img_walk_hm_;
      else
        return img_walk_cv_;
    
    case PlayerState::MOVED_BY_BATS :
      if (level == 4 || level == 5 || level == 6)
        return img_bats_uw_;
      else if (level == 11 || level == 12)
        return img_bats_bc_;
      else
        return img_bats_cv_;
    
    case PlayerState::KILL_WUMP : 
      if (level == 11 || level == 12)
        return img_kill_wump_bc_;              
      else if (level == 14)
        return img_kill_wump_hm_;
      else 
        return img_kill_wump_cv_;
    
    case PlayerState::HAVENT_ARROWS :
      return img_no_arrows_cv_;
    
    case PlayerState::UNKNOWN_STATE :
      return img_unknown_cv_;
    
    case PlayerState::KILLED_BY_WUMP :
      return img_dead_wump_cv_;
    
    case PlayerState::KILLED_BY_PITS :
      if (level == 11 || level == 12)
        return img_dead_pits_bc_;
      else      
        return img_dead_pits_cv_;
      
    
    case PlayerState::FEELS_WUMP :
      if (level == 14) 
        return img_feels_wumps_hm_;
      else
        return img_feels_wumps_cv_;
    
    case PlayerState::FEELS_BATS :
      if (level == 4 || level == 5 || level == 6)
        return img_feels_bats_uw_;            
      if (level == 11 || level == 12)
        return img_feels_bats_bc_;
      else
        return img_feels_bats_cv_;
    
    case PlayerState::FEELS_PITS :
      if (level == 11 || level == 12)
        return img_feels_pits_bc_;
      else
        return img_feels_pits_cv_;
  }
}

Fl_Image* Images::GetPlayerBg(int level)
{
  if (level == 4 || level == 5 || level == 6)
    return img_bg_uw_;
  if (level == 11 || level == 12)
    return img_bg_bc_;
  else if (level == 14)
    return img_bg_hm_;
  else 
    return img_bg_cv_;    
}

Fl_Image* Images::GetRoomImage(RoomState state, int level)
{
  switch (state) {
    case RoomState::ON : return img_room_on_cv_;
    case RoomState::OFF : return img_room_off_cv_;
    case RoomState::MARK : return img_room_mark_cv_;
  }
}

Fl_Image* Images::GetInfoImages(InfoStuff state, int level)
{
  switch (state) {
    case InfoStuff::COVER :
      return wdg_info_cover_cv_;

    case InfoStuff::ARROWS :
      if (level == 11 || level == 12)
        return wdg_info_arrows_bc_;      
      if (level == 13)
        return wdg_info_arrows_lb_;
      else if (level == 14) 
        return wdg_info_arrows_hm_;
      else 
        return wdg_info_arrows_cv_;        

    case InfoStuff::PITS :
      if (level == 11 || level == 12)
        return wdg_info_pits_bc_;
      else
        return wdg_info_pits_cv_;
    
    case InfoStuff::BATS :
      if (level == 4 || level == 5 || level == 6)
        return wdg_info_bats_uw_;        
      else if (level == 11 || level == 12)
        return wdg_info_bats_bc_;
      else
        return wdg_info_bats_cv_;

    case InfoStuff::WUMPS :
      if (level == 14)
        return wdg_info_wumps_hm_;
      else
        return wdg_info_wumps_cv_;
    
    case InfoStuff::LEVEL :
      return wdg_info_level_cv_;
    
    case InfoStuff::CONTINUE_IMAGE :
      return wdg_info_continue_cv_;
    
    case InfoStuff::CONTINUE_DEIMAGE :
      return wdg_info_continue_de_cv_;
  }
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