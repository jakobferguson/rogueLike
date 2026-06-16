#include "controller.h"
#include <unistd.h>

void controller_read_command(char *arr, struct game_state *gs){
    //We have a menu active
    if (gs->active_menu != NULL){
        if (*arr == 'w'){
            if (gs->menu_selection == 0) return; 
            gs->menu_selection-=1;   
            gs->screen_is_dirty = 1;
        } else if (*arr == 's'){
            if (gs->menu_selection == gs->active_menu->num_options - 1) return;
            gs->menu_selection+=1;
            gs->screen_is_dirty = 1;
        }
        if (*arr == '\n'){
            gs->active_menu->options[gs->menu_selection].action(NULL);    
        }
    }
}
