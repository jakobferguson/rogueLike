#pragma once
#include "../menu/menu.h"
#include "renderer.h"

struct game_state {
    int screen_is_dirty;
    struct menu *active_menu;
    int menu_selection;
    
};

int run_game(int rows, int cols);
int play();
int quit_game();

int set_settings_as_active();
int set_mainmenu_as_active();
