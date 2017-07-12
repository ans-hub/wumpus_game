// Package: mvc_set
// Description: https://github.com/ans-hub/mvc_set
// Author: Anton Novoselov, 2017
// File: realisation of `gui`

#include "gui.h"

namespace mvc_set {

Gui::Gui (Model& model)
: Fl_Window(200, 200, "Examples")
, model_{model}
, rooms_{}
, window_{new Fl_Window(425, 700, "Hunt the Wumpus")}
, img_level_{(new Fl_PNG_Image("gui/data/level.png"))}
, img_cover_{(new Fl_PNG_Image("gui/data/cover.png"))}
, box_cover_{new Fl_Box(-5, 0, 435, 625)}
, box_level_{new Fl_Box(2, 54, 425, 390)}
, box_label_{new Fl_Box(30, 20, 370, 45, "HUNT THE WUMPUS")}
, btn_start_{new Fl_Button(27, 655, 105, 25, "Start new")}
, btn_help_{new Fl_Button(165, 655, 105, 25, "Help")}
, btn_quit_{new Fl_Button(297, 655, 105, 25, "Quit")}
, output_{new Fl_Text_Buffer()}
, display_{new Fl_Text_Display(26, 435, 375, 200, "Output")}
{
  TuneInterfaceView();
  CreateRoomsButtons();
  TuneRoomsButtons();
  SetCallbacks();
  
  gui_helpers::show_intro(output_);
  gui_helpers::disable_rooms_buttons(rooms_);
  
  window_->end();
  window_->show();
}

Gui::~Gui()
{
  for (auto v : rooms_) delete v;
  delete display_;
  delete output_;
  delete btn_quit_;
  delete btn_help_;
  delete btn_start_;
  delete box_label_;
  delete box_level_;
  delete box_cover_;
  delete img_cover_;
  delete img_level_;
  delete window_;
}

// CALLBACKS

void Gui::SetCallbacks()
{
  btn_start_->callback((cb_btnstart), (void*)this);
  btn_quit_->callback((cb_btnquit), (void*)this);
  btn_help_->callback((cb_btnhelp), (void*)this);
}

void Gui::cb_btnstart(Fl_Widget*, void* gui)
{
  // gui_helpers::enable_rooms_buttons(((Gui*)gui)->rooms_);
  ((Gui*)gui)->StartGame();
}

void Gui::cb_btnquit(Fl_Widget*, void* gui)
{
  ((Gui*)gui)->window_->hide();
}

void Gui::cb_btnhelp(Fl_Widget*, void* gui)
{
  gui_helpers::show_intro(((Gui*)gui)->output_);
}

// `CONTROLLER` ROLE FUNCTIONS

bool Gui::IncomingNotify(Input& action, int& room)
{
  do {
    if (gui_helpers::find_room_button(rooms_, Fl::pushed())) {
      room = ((RoomButton*)Fl::pushed())->num_;
      if (Fl::event_button() == FL_LEFT_MOUSE) {
        action = Input::MOVE;
      }
      if (Fl::event_button() == FL_RIGHT_MOUSE) {
        action = Input::SHOT;
      }
      Fl::pushed(nullptr);
      return true;
    }
    if (!window_->shown()) {
      action = Input::QUIT;
      break;
    }
  } while(Fl::wait());
  return false;
}

// `VIEW` ROLE FUNCTIONS

bool Gui::IncomingNotify(Show msg)
{
  switch(msg)
  {
    case Show::WINDOW :
      Fl::run();
      break;

    case Show::INTRO :
      btn_start_->deactivate();
      gui_helpers::enable_rooms_buttons(rooms_);      
      // gui_helpers::show_intro(output_);
      break;
    
    case Show::GAME_OVER :
      btn_start_->activate();
      gui_helpers::show_game_over(output_, model_.game_over_cause_);
      gui_helpers::disable_rooms_buttons(rooms_);
      break;
    
    case Show::PLAYER_FEELS :
      gui_helpers::show_feels(output_, model_.player_);
      break;

    case Show::NEIGH_ROOMS :
      gui_helpers::show_neighbors(output_, model_);
      break;    

    case Show::PLAYER_MOVED :
      gui_helpers::clear_subject_pos(rooms_, model_.player_);
      gui_helpers::show_subject_pos(rooms_, model_.player_);
      break;
    
    // case Show::PLAYER_SHOT
    
    case Show::MOVED_BATS :
      gui_helpers::show_moved_bats(output_);
      gui_helpers::clear_subject_pos(rooms_, model_.player_);      
      gui_helpers::show_subject_pos(rooms_, model_.player_);
      break;

    case Show::PROMPT :
      gui_helpers::show_prompt(output_);
      break;

    case Show::ERROR_ACTION :
      gui_helpers::show_error_action(output_);
      break;
    
    case Show::ERROR_ROOM :
      gui_helpers::show_error_room(output_);
      break;

    default : break;
  }
  return true;
}

// REALISATION DETAILS

void Gui::TuneInterfaceView()
{
  window_->color((Fl_Color)34);
  box_cover_->image(img_cover_);
  box_cover_->align(Fl_Align(192));
  box_level_->image(img_level_);
  box_level_->align(Fl_Align(192));
  box_label_->box(FL_PLASTIC_UP_FRAME);
  box_label_->color((Fl_Color)84);
  box_label_->labelsize(28);
  box_label_->labelcolor((Fl_Color)115);
  display_->box(FL_PLASTIC_UP_FRAME);
  display_->color(FL_BLACK);
  display_->labelcolor((Fl_Color)25);
  display_->textcolor((Fl_Color)25);
  display_->align(FL_ALIGN_TOP);
  display_->buffer(output_);
  display_->wrap_mode(Fl_Text_Display::WRAP_AT_BOUNDS, 0);
}

void Gui::CreateRoomsButtons()
{
  // Read coords from file
  
  std::vector<RoomButtonCoords> coords;
  std::ifstream ifs {"gui/data/coords.txt"};
  
  while(true)
  {
    RoomButtonCoords b;
    if (!(ifs >> b)) break;
    coords.push_back(b);
  }
  
  // Create room buttons by readed coords

  rooms_.resize(20);
  for (int i{0}; i < model_.cave_.GetSize(); ++i) {
    auto b = coords[i];
    rooms_[b.num_] = new RoomButton(b.num_, b.x_, b.y_, b.w_, b.h_, model_);
  }
}

void Gui::RefreshRoomsButtons()
{
  for (auto& v : rooms_) {
    v->value(0);
    v->label("");
  }
}

void Gui::TuneRoomsButtons()
{
  for (auto& v : rooms_) {
    v->color((Fl_Color)36);
    v->selection_color((Fl_Color)69);
    v->labeltype(FL_SHADOW_LABEL);
    v->labelcolor((Fl_Color)94);
  }
}

void Gui::StartGame()
{
  model_.Rebuild();
  gui_helpers::enable_rooms_buttons(rooms_);
  RefreshRoomsButtons();
  gui_helpers::show_subject_pos(rooms_, model_.player_);
  model_.StartGame();
}

namespace gui_helpers {

bool find_room_button(const std::vector<RoomButton*>& r, Fl_Widget* w)
{
  auto result = std::find(std::begin(r), std::end(r), w);
  if (result != std::end(r)) {
    return true;
  }
  return false;
}

void show_prompt(Fl_Text_Buffer*)
{
  // output->insert(0, ">$ Move or shot?\n");
  // Fl::flush();
}

void show_error_room(Fl_Text_Buffer* output)
{
  output->insert(0, "ERROR: You input not neighbor room, please repeat\n");
}

void show_error_action(Fl_Text_Buffer* output)
{
  output->insert(0, "ERROR: You input error action, please repeat\n");
}

void show_intro(Fl_Text_Buffer* output)
{
  output->text("");
  output->append("You are in the dark cave. Somewhere here lives the Wumpus. ");
  output->append("You have the bow and unlimited count of arrows. Find and kill him!");
  output->append("And be aware about presence of other danger things -");
  output->append("the Bats and the Bottomless pit. Press 'Start game' to hunt\n");
  Fl::flush();
}

void show_game_over(Fl_Text_Buffer* output, Gui::Person person)
{
  switch (person) {
    case Gui::Person::PLAYER :
      output->insert(0,"***You have killed the Wumpus!***\n");
      break;
    case Gui::Person::WUMP    :
      output->insert(0, "***You have been killed by Wumpus***\n");
      break;
    case Gui::Person::PIT :
      output->insert(0, "***The bottomless pit is your perpetual retreat***\n");
      break;
    case Gui::Person::UNKNOWN :
    default:
      output->insert(0, "***See you later!***\n");
      break;
  }
  Fl::flush();
}

void show_feels(Fl_Text_Buffer* output, const wumpus_game::Player& player)
{
  using namespace wumpus_game;

  auto feels = player.Feels();
  for (auto const feel : feels) {
    switch(feel)
    {
      case Logic::Person::WUMP :
        output->insert(0, "It`s smeels like Wumpus (possible the Wumpus is near)\n");
        break;
      case Logic::Person::BAT  :
        output->insert(0, "You feel the wind (possible the bats is near)\n");
        break;
      case Logic::Person::PIT  :
        output->insert(0, "You feel the cold (possible the bottomless pit is near)\n");
        break;
      default : break;
    } 
  }
  if (feels.empty()) {
    output->insert(0, "I feel nothing...\n");
  }
}

void show_neighbors(Fl_Text_Buffer*, const wumpus_game::Logic&)
{
  using namespace wumpus_game;
  
}

void show_moved_bats(Fl_Text_Buffer* output)
{
  output->insert(0, "You have been moved by the Bats to another room\n");
}

// make here subject pos, which search subject here and clear
void clear_subject_pos(std::vector<RoomButton*>& rooms, wumpus_game::Subject&)
{
  for (auto& v : rooms) {
    v->label("");
  }
} 

void show_subject_pos(std::vector<RoomButton*>& rooms, wumpus_game::Subject& subj)
{
  RoomButton* btn = rooms.at(subj.GetCurrRoomNum());
  btn->label("Y");
  btn->value(1);
}

void enable_rooms_buttons(std::vector<RoomButton*>& rooms)
{
  for (auto& v : rooms) {
    v->activate();
  }
}

void disable_rooms_buttons(std::vector<RoomButton*>& rooms)
{
  for (auto& v : rooms) {
    v->color(FL_BLACK);
    v->deactivate();
  }
}

}  // namespace gui_helpers

}  // namespace mvc_set