
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Window.H>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "coords.h"
#include "room_button.h"
#include "../3rdparty/observer.h"
#include "../logic.h"
#include "../events.h"

namespace mvc_set {

struct Gui
: public Fl_Window
, Observer<Input&, int&>
, Observer<Show>
{
  typedef wumpus_game::Logic Model;
  typedef wumpus_game::Logic::Person Person;
  typedef std::vector<RoomButton*> RoomButtons;

  Gui(Model& model);
  ~Gui();

  bool IncomingNotify(Show) override;         // observer-view
  bool IncomingNotify(Input&, int&) override; // observer-controller
  
private:
  void SetCallbacks();
  static void cb_btnstart(Fl_Widget* widget, void* gui);
  static void cb_btnquit(Fl_Widget* widget, void* gui);
  static void cb_btnhelp(Fl_Widget* widget, void* gui);

  void StartGame();
  void CreateRoomsButtons();

  // This move to the functions, since here all only 
  void TuneInterfaceView();
  void RefreshRoomsButtons();
  void TuneRoomsButtons();
  void DisableRoomsButtons();
  void EnableRoomsButtons();

  Model&            model_;
  RoomButtons       rooms_;
  Fl_Window*        window_;
  Fl_PNG_Image*     img_level_;
  Fl_PNG_Image*     img_cover_;
  Fl_Box*           box_cover_;
  Fl_Box*           box_level_;
  Fl_Box*           box_label_;
  Fl_Button*        btn_start_;
  Fl_Button*        btn_help_;
  Fl_Button*        btn_quit_;
  Fl_Text_Buffer*   output_;
  Fl_Text_Display*  display_;

};  // struct Gui

namespace gui_helpers {

  bool find_room_button(const std::vector<RoomButton*>&, Fl_Widget*);
  // std::vector<RoomButtonCoords> get_coordinates(const std::string&)
  void show_prompt(Fl_Text_Buffer*);
  void show_error_room(Fl_Text_Buffer*);
  void show_error_action(Fl_Text_Buffer*);
  void show_intro(Fl_Text_Buffer*);
  void show_game_over(Fl_Text_Buffer*, Gui::Person);
  void show_feels(Fl_Text_Buffer*, const wumpus_game::Player&);
  void show_neighbors(Fl_Text_Buffer*, const wumpus_game::Logic&);
  void show_moved_bats(Fl_Text_Buffer*);
  void clear_subject_pos(std::vector<RoomButton*>&, wumpus_game::Subject&);
  void show_subject_pos(std::vector<RoomButton*>&, wumpus_game::Subject&);
  void enable_rooms_buttons(std::vector<RoomButton*>&);
  void disable_rooms_buttons(std::vector<RoomButton*>&);

}

}  // namespace mvc_set