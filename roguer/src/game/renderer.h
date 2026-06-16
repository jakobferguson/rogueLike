#include "../menu/menu.h"
#pragma once

struct window {
    int height;
    int width;
};

void renderer_clear_screen(void);
void renderer_draw_border(struct window *w, char d);
void renderer_renmenu(struct window *w, struct menu *m, int s);
