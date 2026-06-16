#include "game.h"
#include "../menu/menu.h"
#include "renderer.h"
#include "controller.h"
#include <unistd.h>

int running = 1;

struct menu main_menu = {
    .title = "Main Menu",
    .options = { 
        (struct menu_option){ .label = "Start", .action = &play }, 
        (struct menu_option){ .label = "Settings", .action = &set_settings_as_active },
        (struct menu_option){ .label = "Quit", .action = &quit_game }
    },
    .num_options = 3
};
    
struct menu settings_menu = {
    .title = "Settings",
    .options = {
        (struct menu_option){ .label = "back", .action = &set_mainmenu_as_active }
    },
    .num_options = 1
};

struct game_state game = {
        .screen_is_dirty = 1,
        .active_menu = &main_menu,
        .menu_selection = 0
};

int quit_game(){
    running = 0; 
    return 0;
}

int play(){
    ///load data if there is any
     
    return 0;
}

int set_settings_as_active(){
    game.active_menu = &settings_menu;
    game.menu_selection = 0;
    game.screen_is_dirty = 1;
    return 0;
}

int set_mainmenu_as_active(){
    game.active_menu = &main_menu;
    game.menu_selection = 0;
    game.screen_is_dirty = 1;
    return 0;
}

int run_game(){
    ///Init
    struct window w = {
        .height = 50,
        .width = 120
    };

    //wait for resize
    char buf;
    while (running){
        if (game.screen_is_dirty){
            renderer_clear_screen();
            renderer_draw_border(&w, '=');
            if (game.active_menu != NULL) renderer_renmenu(&w, game.active_menu, game.menu_selection);
            
            game.screen_is_dirty = 0;
        }
        if (read(STDIN_FILENO, &buf, 1) > 0){
            controller_read_command(&buf, &game);
        }
    } 
    ///Close down 
    return 0; 
}
