# data file for the Fltk User Interface Designer (fluid)
version 1.0304
header_name {.h}
code_name {.cc}
Function {make_window()} {open
} {
  Fl_Window {} {
    label {Hunt the Wumpus} open
    xywh {706 436 425 600} type Double color 34 visible
  } {
    Fl_Box {} {
      image {img/cover.jpg} xywh {-5 0 435 625} align 192
    }
    Fl_Box {} {selected
      image {img/level.png} xywh {2 54 425 390} align 192
    }
    Fl_Button {} {
      label Start
      xywh {27 555 105 25} deactivate
    }
    Fl_Button {} {
      label Move
      xywh {165 555 105 25}
    }
    Fl_Button {} {
      label Shot
      xywh {297 555 105 25}
    }
    Fl_Text_Display {} {
      label {Output:}
      xywh {26 435 375 100} box PLASTIC_UP_FRAME color 92 labelcolor 25
    }
    Fl_Box {} {
      label {HUNT THE WUMPUS}
      xywh {30 20 370 45} box PLASTIC_UP_FRAME color 84 labelsize 28 labelcolor 115
    }
    Fl_Light_Button {} {
      label Y
      xywh {320 209 30 30} value 1 color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {80 209 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {155 209 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {245 209 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {261 254 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {140 254 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {80 264 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {320 264 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {300 329 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {95 329 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {200 329 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {200 284 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {265 144 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {135 144 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {200 144 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {200 89 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {25 89 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {370 89 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {370 384 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
    Fl_Light_Button {} {
      xywh {25 384 30 30} color 36 selection_color 69 labeltype SHADOW_LABEL labelcolor 94
    }
  }
}
