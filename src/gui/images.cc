// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: RAII struct managing image resources in game

// This class based on some conviences:

// - all raw pointers which are taken from unique_ptrs by get(), they are 
//   not destroyed and not changed by classes used its. The first reason
//   why I not return unique_ptr but return raw pointer is readable context
//   in entities classes. The second reason is that this is not library.

// - access to ptrs of Images is carried out through vector of vector since 
//   complexity is constant. But in this case I need some conviences for
//   guarantee that while access to items of vector I have not exceptions
//   such as `out_of_range`. For this reasons I set convience, that all enums
//   have last field `count`, each image vector is initialized by this value.
//   All nested vectors are initialized by maximum scenes count. And the last
//   convience is that base scene should have all values of enums in vectors,
//   since if in the scene we have nullptr to image, we should use image of 
//   base scene

// Postfixes used in names of files :
//  cv - cave theme
//  uw - underwater theme
//  dt - death town
//  bc - broken cpu theme
//  lb - last battle theme
//  hm - home theme

#include "images.h"

namespace wumpus_game {

Images::Images()
  : img_path_     {config::GetImagesPath()}
  , wnd_main_     {static_cast<int>(Scene::count)}
  , wdg_player_   { }
  , wdg_player_bg_{static_cast<int>(Scene::count)}
  , wdg_room_     { }
  , wdg_info_     { }
{
  // Resizing vectors (see note #1 after code)

  helpers::ResizeVector2d(
    wdg_player_,
    static_cast<int>(Scene::count),
    static_cast<int>(PlayerState::count)
  );

  helpers::ResizeVector2d(
    wdg_room_,
    static_cast<int>(Scene::count),
    static_cast<int>(RoomState::count)
  );

  helpers::ResizeVector2d(
    wdg_info_,
    static_cast<int>(Scene::count),
    static_cast<int>(InfoStuff::count)
  );

  // FormMain background
  
  LoadImage(wnd_main_, Scene::CAVE, "cv_main.png"); 
  LoadImage(wnd_main_, Scene::UNDERWATER, "uw_main.png"); 
  LoadImage(wnd_main_, Scene::DEAD_TOWN, "dt_main.png"); 
  LoadImage(wnd_main_, Scene::BROKEN_CPU, "bc_main.png"); 
  LoadImage(wnd_main_, Scene::LAST_BATTLE, "lb_main.png"); 
  LoadImage(wnd_main_, Scene::SWEET_HOME, "hm_main.png");
  
  // WidgetPlayer states

  auto& player_scene_cv = wdg_player_[static_cast<int>(Scene::CAVE)];
  
  LoadImage(player_scene_cv, PlayerState::STAY, "player_stay.png");
  LoadImage(player_scene_cv, PlayerState::SHOT, "player_shot.png");
  LoadImage(player_scene_cv, PlayerState::WALK, "player_walk.png");
  LoadImage(player_scene_cv, PlayerState::MOVED_BY_BATS, "player_bats.png");
  LoadImage(player_scene_cv, PlayerState::MEETS_CLOSED_GUIDE, "guide_closed.png");
  LoadImage(player_scene_cv, PlayerState::LEVEL_WIN, "level_win.png");
  LoadImage(player_scene_cv, PlayerState::KILL_WUMP, "wump_killed.png");
  LoadImage(player_scene_cv, PlayerState::HAVENT_ARROWS, "unknown_state.png");
  LoadImage(player_scene_cv, PlayerState::UNKNOWN_STATE, "unknown_state.png");
  LoadImage(player_scene_cv, PlayerState::KILLED_BY_WUMP, "player_dead_w.png");
  LoadImage(player_scene_cv, PlayerState::KILLED_BY_PITS, "player_dead_p.png");
  LoadImage(player_scene_cv, PlayerState::FEELS_WUMP, "feels_wumps.png");
  LoadImage(player_scene_cv, PlayerState::FEELS_BATS, "feels_bats.png");
  LoadImage(player_scene_cv, PlayerState::FEELS_PITS, "feels_pits.png");
  
  auto& player_scene_uw = wdg_player_[static_cast<int>(Scene::UNDERWATER)];
  
  LoadImage(player_scene_uw, PlayerState::MOVED_BY_BATS, "player_bats_uw.png");
  LoadImage(player_scene_uw, PlayerState::FEELS_BATS, "feels_bats_uw.png");

  auto& player_scene_bc = wdg_player_[static_cast<int>(Scene::BROKEN_CPU)];
  
  LoadImage(player_scene_bc, PlayerState::SHOT, "player_shot_bc.png");
  LoadImage(player_scene_bc, PlayerState::MOVED_BY_BATS, "player_bats_bc.png");
  LoadImage(player_scene_bc, PlayerState::KILL_WUMP, "wump_killed_bc.png");
  LoadImage(player_scene_bc, PlayerState::KILLED_BY_PITS, "player_dead_p_bc.png");
  LoadImage(player_scene_bc, PlayerState::FEELS_BATS, "feels_bats_bc.png");
  LoadImage(player_scene_bc, PlayerState::FEELS_PITS, "feels_pits_bc.png");
  
  auto& player_scene_hm = wdg_player_[static_cast<int>(Scene::SWEET_HOME)];

  LoadImage(player_scene_hm, PlayerState::WALK, "player_walk_hm.png");
  LoadImage(player_scene_hm, PlayerState::KILL_WUMP, "wump_killed_hm.png");
  LoadImage(player_scene_hm, PlayerState::FEELS_WUMP, "feels_wumps_hm.png");
  
  // WidgetPlayer background
  
  LoadImage(wdg_player_bg_, Scene::CAVE, "player_cv.png"); 
  LoadImage(wdg_player_bg_, Scene::UNDERWATER, "player_uw.png"); 
  LoadImage(wdg_player_bg_, Scene::BROKEN_CPU, "player_bc.png"); 
  LoadImage(wdg_player_bg_, Scene::SWEET_HOME, "player_hm.png"); 
  
  // WidgetRoom states

  auto& room_scene_cv = wdg_room_[static_cast<int>(Scene::CAVE)];
  
  LoadImage(room_scene_cv, RoomState::DARK, "room_dark.png"); 
  LoadImage(room_scene_cv, RoomState::LIGHT, "room_light.png"); 
  LoadImage(room_scene_cv, RoomState::GATE, "room_gate.png"); 
  LoadImage(room_scene_cv, RoomState::GUIDE_OPENED, "room_guide_op.png"); 
  LoadImage(room_scene_cv, RoomState::GUIDE_CLOSED, "room_guide_cl.png"); 
  
  // WidgetInfo states

  auto& info_scene_cv = wdg_info_[static_cast<int>(Scene::CAVE)];

  LoadImage(info_scene_cv, InfoStuff::COVER, "info_bg.png"); 
  LoadImage(info_scene_cv, InfoStuff::ARROWS, "info_arrows.png"); 
  LoadImage(info_scene_cv, InfoStuff::LEVEL, "info_level.png"); 
  LoadImage(info_scene_cv, InfoStuff::WUMPS, "info_wumps.png"); 
  LoadImage(info_scene_cv, InfoStuff::BATS, "info_bats.png"); 
  LoadImage(info_scene_cv, InfoStuff::PITS, "info_pits.png"); 
  LoadImage(info_scene_cv, InfoStuff::CONTINUE_IMAGE, "info_continue.png"); 
  LoadImage(info_scene_cv, InfoStuff::CONTINUE_DEIMAGE, "info_continue_de.png");
  
  auto& info_scene_uw = wdg_info_[static_cast<int>(Scene::UNDERWATER)];
  
  LoadImage(info_scene_uw, InfoStuff::BATS, "info_bats_uw.png");

  auto& info_scene_bc = wdg_info_[static_cast<int>(Scene::BROKEN_CPU)];
  
  LoadImage(info_scene_bc, InfoStuff::BATS, "info_bats_bc.png");
  LoadImage(info_scene_bc, InfoStuff::PITS, "info_pits_bc.png");
  LoadImage(info_scene_bc, InfoStuff::ARROWS, "info_arrows_bc.png");
  
  auto& info_scene_lb = wdg_info_[static_cast<int>(Scene::LAST_BATTLE)];
  
  LoadImage(info_scene_lb, InfoStuff::ARROWS, "info_arrows_lb.png");

  auto& info_scene_hm = wdg_info_[static_cast<int>(Scene::SWEET_HOME)];

  LoadImage(info_scene_hm, InfoStuff::WUMPS, "info_wumps_hm.png");
  LoadImage(info_scene_hm, InfoStuff::ARROWS, "info_arrows_hm.png");
}

Fl_Image* Images::GetMainBackground(int level, int w, int h)
{
  auto scene = static_cast<int>(config::GetSceneType(level));
  auto img   = wnd_main_[scene].get();

  if (!img) {
    scene = static_cast<int>(config::GetDefaultScene());
  }
  helpers::ResizeImage(wnd_main_[scene], w, h);
  return wnd_main_[scene].get();
}

Fl_Image* Images::GetPlayerImage(PlayerState state, int level)
{
  auto scene = static_cast<int>(config::GetSceneType(level));
  auto action = static_cast<int>(state);
  auto img   = wdg_player_[scene][action].get();
  
  if (img) 
    return img;
  else {
    scene = static_cast<int>(config::GetDefaultScene());
    return wdg_player_[scene][action].get();
  }
}

Fl_Image* Images::GetPlayerBackground(int level)
{
  auto scene = static_cast<int>(config::GetSceneType(level));
  auto img   = wdg_player_bg_[scene].get();

  if (img)
    return img;
  else {
    scene = static_cast<int>(config::GetDefaultScene());
    return wdg_player_bg_[scene].get();
  }
}

Fl_Image* Images::GetRoomImage(RoomState state, int level)
{
  auto scene = static_cast<int>(config::GetSceneType(level));
  auto action = static_cast<int>(state);
  auto img   = wdg_room_[scene][action].get();
  
  if (img) 
    return img;
  else {
    scene = static_cast<int>(config::GetDefaultScene());
    return wdg_room_[scene][action].get();
  }
}

Fl_Image* Images::GetInfoImages(InfoStuff state, int level)
{
  auto scene = static_cast<int>(config::GetSceneType(level));
  auto action = static_cast<int>(state);
  auto img   = wdg_info_[scene][action].get();
  
  if (img) 
    return img;
  else {
    scene = static_cast<int>(config::GetDefaultScene());
    return wdg_info_[scene][action].get();
  }
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

void ResizeVector2d(Images::Vector2d& v, int w, int h)
{
  v.resize(w);                  
  for (auto& p : v) {
    p.resize(h);
  }
}


}  // namespace helpers

}  // namespace wumpus_game

// Note #1 : resizing Vector2d by helper function needs to prevent copy semantic
// if initialize through initializer_list (since init_list not support move semantic,
// but it needs to initialize vector by empty unique_ptrs)