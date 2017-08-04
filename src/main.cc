// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game

#include <iostream>

#include "entities/logic.h"
#include "cli/view.h"
#include "cli/controller.h"
#include "ai/controller.h"
#include "gui/windows.h"
#include "gui/media.h"
#include "gui/controller.h"
#include "audio/audio_output.h"
#include "scores/scores.h"
#include "settings/config.h"

int main()
{
  using namespace wumpus_game;

  Config        config  {};
  Logic         logic   {config};
  AudioOutput   sounds  {config};
  Windows       gui     {config};

  Media         media   {gui, sounds, logic, config};
  GuiController ctrl    {gui, logic, config};
  Scores        scores  {logic, config};

  logic.RegisterObserver(media);
  logic.RegisterObserver(scores);

  gui.UseAudio(sounds);
  gui.VoiceEvents();

  ctrl.SetControls(gui);  // set callbacks explicit for more readable reason
  ctrl.RunModel();

  return 0;
}

