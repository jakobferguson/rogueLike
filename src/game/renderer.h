#pragma once

#include <stdint.h>
struct pixel_cell {
    //length of the following glyph
    uint8_t len;
  
    //glyph/character
    char byte[4];   

    //foreground rgb
    uint8_t fg_r;
    uint8_t fg_g;
    uint8_t fg_b;

    //background rgb
    uint8_t bg_r;
    uint8_t bg_g;
    uint8_t bg_b;

    //character flags bold, italic, etc
    uint8_t attributes;
};

struct window {
    int height;
    int width;
    struct pixel_cell *frame;
    void *screen_buffer;
};

struct box {
    int width;
    int height;
    uint8_t background_length;
    int border_type;
    char *background;
};

int init_window(int x, int y, struct window *w);
int write_window(struct window *w);

int init_box(struct box *b, int x, int y, char bg[], int border_type);
int draw_box(struct box *b, struct window *w);
