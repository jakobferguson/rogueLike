#include "menu.h"
#include <string.h>
#include <unistd.h>

void show_menu(struct window *w, struct menu* m, int x, int y, int selection){
    draw_box(&(m->rendered_menu), w, x, y);
    for (int i = 0; i < m->num_options; i++){
        clear_label_attributes(&(m->options[i].rendered_label));
    }
    toggle_label_attributes(&(m->options[selection].rendered_label), REVERSE);
    for (int i = 0; i < m->num_options; i++){
        draw_label(&(m->options[i].rendered_label), w, x + (m->rendered_menu.width / 2) - (strlen(m->options[i].label) / 2), y + 2 + i);
    }
}
