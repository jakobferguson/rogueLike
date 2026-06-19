#pragma once
#include "../game/renderer.h"

#define MENU_MAX_OPTIONS 5


struct menu_option {
    const char *label;
    int (*action)(void *ctx);
    void *arg;
    struct label rendered_label;
};

struct menu {
    const char *title;
    const int num_options;
    struct menu_option options[MENU_MAX_OPTIONS];
    struct box rendered_menu;
};


void show_menu(struct window *w, struct menu* m, int x, int y, int selection);
