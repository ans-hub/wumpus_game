// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: RAII struct managing image resources in game

// This class based on convience that all raw pointers which are taken
// from unique_ptrs by get(), they are not destroyed and not changed by
// classes used its

// Postfixes used in names of variables :
//  cv - cave theme
//  uw - underwater theme
//  dt - death town
//  bc - broken cpu theme
//  lb - last battle theme
//  hm - home theme

#include "images.h"

namespace wumpus_game {

Images::Images()
  
  // FormMain background

  : img_cv_{std::make_unique<Image>("resources/images/cv_main.png")}
  , img_uw_{std::make_unique<Image>("resources/images/uw_main.png")}
  , img_dt_{std::make_unique<Image>("resources/images/dt_main.png")}
  , img_bc_{std::make_unique<Image>("resources/images/bc_main.png")}
  , img_lb_{std::make_unique<Image>("resources/images/lb_main.png")}
  , img_hm_{std::make_unique<Image>("resources/images/hm_main.png")}
  
  // WidgetPlayer background
  
  , img_player_cv_{std::make_unique<Image>("resources/images/player_cv.png")}
  , img_player_uw_{std::make_unique<Image>("resources/images/player_uw.png")}
  , img_player_bc_{std::make_unique<Image>("resources/images/player_bc.png")}
  , img_player_hm_{std::make_unique<Image>("resources/images/player_hm.png")}

  // WidgetPlayer states
  
  , img_stay_cv_{std::make_unique<Image>("resources/images/player_stay.png")}
  , img_shot_cv_{std::make_unique<Image>("resources/images/player_shot.png")}
  , img_shot_bc_{std::make_unique<Image>("resources/images/player_shot_bc.png")}
  , img_shot_lb_{std::make_unique<Image>("resources/images/player_shot_lb.png")}
  , img_walk_cv_{std::make_unique<Image>("resources/images/player_walk.png")}
  , img_walk_hm_{std::make_unique<Image>("resources/images/player_walk_hm.png")}
  , img_bats_cv_{std::make_unique<Image>("resources/images/player_bats.png")}  
  , img_bats_uw_{std::make_unique<Image>("resources/images/player_bats_uw.png")}  
  , img_bats_bc_{std::make_unique<Image>("resources/images/player_bats_bc.png")}  
  , img_guide_closed_cv_{std::make_unique<Image>("resources/images/guide_closed.png")}
  , img_guide_opened_cv_{std::make_unique<Image>("resources/images/guide_opened.png")}
  , img_level_win_cv_{std::make_unique<Image>("resources/images/level_win.png")}
  , img_kill_wump_cv_{std::make_unique<Image>("resources/images/wump_killed.png")}
  , img_kill_wump_bc_{std::make_unique<Image>("resources/images/wump_killed_bc.png")}
  , img_kill_wump_hm_{std::make_unique<Image>("resources/images/wump_killed_hm.png")}
  , img_no_arrows_cv_{std::make_unique<Image>("resources/images/unknown_state.png")}
  , img_unknown_cv_{std::make_unique<Image>("resources/images/unknown_state.png")}
  , img_dead_wump_cv_{std::make_unique<Image>("resources/images/player_dead_w.png")}
  , img_dead_pits_cv_{std::make_unique<Image>("resources/images/player_dead_p.png")}
  , img_dead_pits_bc_{std::make_unique<Image>("resources/images/player_dead_p_bc.png")}
  , img_feels_box_cv_{std::make_unique<Image>("resources/images/feels_box.png")}
  , img_feels_bats_cv_{std::make_unique<Image>("resources/images/feels_bats.png")}
  , img_feels_bats_uw_{std::make_unique<Image>("resources/images/feels_bats_uw.png")}
  , img_feels_bats_bc_{std::make_unique<Image>("resources/images/feels_bats_bc.png")}
  , img_feels_pits_cv_{std::make_unique<Image>("resources/images/feels_pits.png")}
  , img_feels_pits_bc_{std::make_unique<Image>("resources/images/feels_pits_bc.png")}
  , img_feels_wumps_cv_{std::make_unique<Image>("resources/images/feels_wumps.png")}
  , img_feels_wumps_hm_{std::make_unique<Image>("resources/images/feels_wumps_hm.png")}
  
  // WidgetRoom states

  , img_room_dark_cv_{std::make_unique<Image>("resources/images/room_dark.png")}
  , img_room_light_cv_{std::make_unique<Image>("resources/images/room_light.png")}
  , img_room_gate_cv_{std::make_unique<Image>("resources/images/room_gate.png")}
  , img_room_guide_op_cv_{std::make_unique<Image>("resources/images/room_guide_op.png")}
  , img_room_guide_cl_cv_{std::make_unique<Image>("resources/images/room_guide_cl.png")}
  
  // WidgetInfo states

  , wdg_info_cover_cv_{std::make_unique<Image>("resources/images/info_bg.png")}
  , wdg_info_level_cv_{std::make_unique<Image>("resources/images/info_level.png")}
  , wdg_info_wumps_cv_{std::make_unique<Image>("resources/images/info_wumps.png")}
  , wdg_info_wumps_hm_{std::make_unique<Image>("resources/images/info_wumps_hm.png")}
  , wdg_info_bats_cv_{std::make_unique<Image>("resources/images/info_bats.png")}
  , wdg_info_bats_uw_{std::make_unique<Image>("resources/images/info_bats_uw.png")}
  , wdg_info_bats_bc_{std::make_unique<Image>("resources/images/info_bats_bc.png")}
  , wdg_info_pits_cv_{std::make_unique<Image>("resources/images/info_pits.png")}
  , wdg_info_pits_bc_{std::make_unique<Image>("resources/images/info_pits_bc.png")}
  , wdg_info_arrows_cv_{std::make_unique<Image>("resources/images/info_arrows.png")}
  , wdg_info_arrows_lb_{std::make_unique<Image>("resources/images/info_arrows_lb.png")}
  , wdg_info_arrows_bc_{std::make_unique<Image>("resources/images/info_arrows_bc.png")}
  , wdg_info_arrows_hm_{std::make_unique<Image>("resources/images/info_arrows_hm.png")}
  , wdg_info_continue_cv_{std::make_unique<Image>("resources/images/info_continue.png")}
  , wdg_info_continue_de_cv_{std::make_unique<Image>("resources/images/info_continue_de.png")}
{ }

Fl_Image* Images::GetMainBackground(int level, int w, int h)
{
  switch (level) {
    case 1 : case 2 : case 3 : default :
      helpers::ResizeImage(img_cv_, w, h);
      return img_cv_.get();
    case 4 : case 5 : case 6 :
      helpers::ResizeImage(img_uw_, w, h);
      return img_uw_.get();
    case 7 : case 8 : case 9 : case 10 :
      helpers::ResizeImage(img_dt_, w, h);
      return img_dt_.get();
    case 11 : case 12 :
      helpers::ResizeImage(img_bc_, w, h);
      return img_bc_.get();
    case 13 :
      helpers::ResizeImage(img_lb_, w, h);   
      return img_lb_.get();
    case 14 :
      helpers::ResizeImage(img_hm_, w, h);   
      return img_hm_.get();
  }
  return img_cv_.get();
}

Fl_Image* Images::GetPlayerImage(PlayerState state, int level)
{
  switch (state) {

    case PlayerState::STAY : default :
      return img_stay_cv_.get();
    
    case PlayerState::SHOT :
      if (level == 11 || level == 12)
        return img_shot_bc_.get();   
      else if (level == 13) 
        return img_shot_lb_.get();
      else if (level == 14)
        return img_walk_hm_.get();
      else
        return img_shot_cv_.get();
    
    case PlayerState::WALK :
      if (level == 14) 
        return img_walk_hm_.get();
      else
        return img_walk_cv_.get();
    
    case PlayerState::MOVED_BY_BATS :
      if (level == 4 || level == 5 || level == 6)
        return img_bats_uw_.get();
      else if (level == 11 || level == 12)
        return img_bats_bc_.get();
      else
        return img_bats_cv_.get();
    
    case PlayerState::KILL_WUMP : 
      if (level == 11 || level == 12)
        return img_kill_wump_bc_.get();              
      else if (level == 14)
        return img_kill_wump_hm_.get();
      else 
        return img_kill_wump_cv_.get();
    
    case PlayerState::HAVENT_ARROWS :
      return img_no_arrows_cv_.get();
    
    case PlayerState::UNKNOWN_STATE :
      return img_unknown_cv_.get();
    
    case PlayerState::KILLED_BY_WUMP :
      return img_dead_wump_cv_.get();
    
    case PlayerState::KILLED_BY_PITS :
      if (level == 11 || level == 12)
        return img_dead_pits_bc_.get();
      else      
        return img_dead_pits_cv_.get();

    case PlayerState::MEETS_CLOSED_GUIDE :  
      return img_guide_closed_cv_.get();

    case PlayerState::LEVEL_WIN :  
      return img_level_win_cv_.get(); 

    case PlayerState::FEELS_WUMP :
      if (level == 14) 
        return img_feels_wumps_hm_.get();
      else
        return img_feels_wumps_cv_.get();
    
    case PlayerState::FEELS_BATS :
      if (level == 4 || level == 5 || level == 6)
        return img_feels_bats_uw_.get();            
      if (level == 11 || level == 12)
        return img_feels_bats_bc_.get();
      else
        return img_feels_bats_cv_.get();
    
    case PlayerState::FEELS_PITS :
      if (level == 11 || level == 12)
        return img_feels_pits_bc_.get();
      else
        return img_feels_pits_cv_.get();
  }
}

Fl_Image* Images::GetPlayerBackground(int level)
{
  if (level == 4 || level == 5 || level == 6)
    return img_player_uw_.get();

  if (level == 11 || level == 12)
    return img_player_bc_.get();
  
  if (level == 14)
    return img_player_hm_.get();
  
  return img_player_cv_.get();
}

Fl_Image* Images::GetRoomImage(RoomState state, int)
{
  switch (state) {
    case RoomState::DARK : return img_room_dark_cv_.get();
    case RoomState::LIGHT : return img_room_light_cv_.get();
    case RoomState::GATE : return img_room_gate_cv_.get();
    case RoomState::GUIDE_CLOSED : return img_room_guide_cl_cv_.get();
    case RoomState::GUIDE_OPENED : return img_room_guide_op_cv_.get();
  }
  return img_room_dark_cv_.get();
}

Fl_Image* Images::GetInfoImages(InfoStuff state, int level)
{
  switch (state) {
    case InfoStuff::COVER :
      return wdg_info_cover_cv_.get();

    case InfoStuff::ARROWS :
      if (level == 11 || level == 12)
        return wdg_info_arrows_bc_.get(); 
      if (level == 13)
        return wdg_info_arrows_lb_.get();
      else if (level == 14) 
        return wdg_info_arrows_hm_.get();
      else 
        return wdg_info_arrows_cv_.get();     

    case InfoStuff::PITS :
      if (level == 11 || level == 12)
        return wdg_info_pits_bc_.get();
      else
        return wdg_info_pits_cv_.get();
    
    case InfoStuff::BATS :
      if (level == 4 || level == 5 || level == 6)
        return wdg_info_bats_uw_.get();    
      else if (level == 11 || level == 12)
        return wdg_info_bats_bc_.get();
      else
        return wdg_info_bats_cv_.get();

    case InfoStuff::WUMPS :
      if (level == 14)
        return wdg_info_wumps_hm_.get();
      else
        return wdg_info_wumps_cv_.get();
    
    case InfoStuff::LEVEL :
      return wdg_info_level_cv_.get();
    
    case InfoStuff::CONTINUE_IMAGE :
      return wdg_info_continue_cv_.get();
    
    case InfoStuff::CONTINUE_DEIMAGE :
      return wdg_info_continue_de_cv_.get();
  }
  return wdg_info_cover_cv_.get();
}

namespace helpers {

// Only one way to resize image on fltk (1.3.4)

void ResizeImage(Images::ImagePtr& i, int w, int h)
{
  Fl_PNG_Image* old = i.release();
  Fl_Image* tmp = old->copy(w, h);
  i.reset(static_cast<Fl_PNG_Image*>(tmp));
  delete old;
}

}  // namespace helpers

}  // namespace wumpus_game