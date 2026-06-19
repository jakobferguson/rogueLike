#pragma once

#include <stdint.h>
struct pixel_cell {
    //glyph/character
    char byte[5];   

    //foreground rgb
    uint8_t fg_r;
    uint8_t fg_g;
    uint8_t fg_b;

    //background rgb
    uint8_t bg_r;
    uint8_t bg_g;
    uint8_t bg_b;

    //character flags bold, italic, etc
    uint16_t attributes;
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

struct label {
    int width;
    int height;
    char *info;   
    uint16_t attributes;
};

enum glyph_attributes {
    BOLD,
    FAINT,
    ITALIC,
    UNDERLINE,
    BLINKSLOW,
    BLINKFAST,
    REVERSE,
    CONCEAL,
    STRIKETHROUGH,
    DOUBLEUNDERLINE,
    OVERLINE,
    FRAMED,
    ENCIRCLED,
    HASATTRS,
    HASCOLOR

};


int init_window(int x, int y, struct window *w);
int write_window(struct window *w);
void renderer_clear_screen(struct window *w);

int init_box(struct box *b, int x, int y, char bg[], int border_type);
int draw_box(struct box *b, struct window *w, int x, int y);
int draw_label(struct label *l, struct window *w, int x, int y);
void toggle_label_attributes(struct label *l, enum glyph_attributes attr);
void clear_label_attributes(struct label *l);
