// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game

#include <iostream>

#include "3rdparty/rand_toolkit.h"

#include "entities/logic.h"
#include "ai/controller.h"
#include "cli/view.h"
#include "cli/controller.h"
#include "gui/windows.h"
#include "gui/view.h"
#include "gui/controller.h"
#include "gui/images.h"
#include "audio/audio_out.h"
#include "scores/scores.h"
#include "config.h"

void preload_background_music(wumpus_game::AudioOut& sounds)
{
  using namespace wumpus_game;

  for (int i = 1; i <= config::levels_max; ++i) 
    sounds.Load(config::GetBackgroundMusic(i), true);
}

void start_random_generator()
{
  rand_toolkit::start_rand();
}

int main()
{
  using namespace wumpus_game;
  
  Logic         logic   {};
  AudioOut      audio   {};
  Images        images  {};

  Windows       gui     {images, audio};
  GuiController ctrl    {logic, gui};
  GuiView       view    {logic, gui};
  CliView       cerr    {std::cout, logic};
  Scores        scores  {logic};

  logic.RegisterObserver(view);
  logic.RegisterObserver(scores);
  logic.RegisterObserver(cerr);

  preload_background_music(audio);
  start_random_generator();

  return ctrl.RunModel();
}

