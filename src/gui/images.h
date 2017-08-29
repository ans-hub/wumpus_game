// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: RAII struct managing image resources in game

#ifndef IMAGES_H
#define IMAGES_H

#include <memory>
#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>

#include "enums/enums.h"
#include "config.h"

namespace wumpus_game {

struct Images
{
  using Image = Fl_PNG_Image;
  using ImagePtr = std::unique_ptr<Image>;
  using Vector = std::vector<ImagePtr>;   // access by [scene]
  using Vector2d = std::vector<Vector>;   // access by [scene][action]

  Images();

  Fl_Image* GetMainBackground(int level, int w, int h);
  Fl_Image* GetPlayerImage(PlayerState, int level);
  Fl_Image* GetPlayerBackground(int level);
  Fl_Image* GetRoomImage(RoomState, int level);
  Fl_Image* GetInfoImages(InfoStuff, int level);

private:
  std::string img_path_;

  Vector    wnd_main_;
  Vector2d  wdg_player_;
  Vector    wdg_player_bg_;
  Vector2d  wdg_room_;
  Vector2d  wdg_info_;
  
  template <class T>
  void LoadImage (Vector& v, T enums, std::string&& fname) // see note #1 after code
  {
    auto full_path = (img_path_ + fname);
    v[static_cast<int>(enums)] = std::make_unique<Image>(full_path.c_str());
  }   
};

namespace helpers {

  void ResizeImage(Images::ImagePtr&, int, int);
  void ResizeVector2d(Images::Vector2d&, int, int);

}  // namespace helpers

}  // namespace wumpus_game

#endif  // IMAGES_H

// Note #1 : this is member funcion since I want have a readable constructor
// This is not reduce perfomance since Images class is a singleton and adding
// one member function is not reduce perfomance so much as in not singleton 