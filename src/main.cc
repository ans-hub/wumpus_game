// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game file

#include <iostream>

#include "3rdparty/rand_toolkit.h"
#include "3rdparty/audio/audio_out.h"

#include "entities/logic.h"
#include "ai/ai_controller.h"
#include "cli/cli_view.h"
#include "cli/cli_controller.h"
#include "gui/windows.h"
#include "gui/gui_view.h"
#include "gui/gui_controller.h"
#include "gui/images.h"
#include "scores/scores.h"
#include "music/music.h"

void start_random_generator()
{
  rand_toolkit::start_rand();
}

int main()
{
  using namespace wumpus_game;
  
  Logic         logic     {};
  AudioOut      audio_out {};
  Images        images    {};

  Windows       gui       {images, audio_out};
  GuiView       view      {logic, gui};
  CliView       debug     {std::cout, logic};
  Scores        scores    {logic};
  GuiController ctrl      {logic, gui};
  Music background_music  {logic, audio_out};   // see note #1

  logic.RegisterObserver(view);
  logic.RegisterObserver(background_music);
  logic.RegisterObserver(scores);
  logic.RegisterObserver(debug);

  start_random_generator();
  
  return ctrl.RunModel();
}

// Note #1 : background music plays through Music class instance, but
// sounds plays by each widgets ownself. Reference to audio output 
// transmitted over Windows class instance (this class is owner of all
// gui widgets and forms)
