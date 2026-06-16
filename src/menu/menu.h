#pragma once

#define MENU_MAX_OPTIONS 5


struct menu_option {
    const char *label;
    int (*action)(void *ctx);
    void *arg;
};

struct menu {
    const char *title;
    const int num_options;
    struct menu_option options[MENU_MAX_OPTIONS];
};
