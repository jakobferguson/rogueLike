#include "renderer.h" 
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GLYPHATTRIBUTEBYTES 34 ///\033[1;2;3;4;5;7;9;21;53m
#define TRUECOLORBYTESREQ 19 ///\033[38;2;255;255;255m
#define GLYPHLENGTH 4
#define MAXCELLBYTESSIZE GLYPHATTRIBUTEBYTES + TRUECOLORBYTESREQ * 2 + GLYPHLENGTH
#define NUMBEROFATTRS 13
#define ATTRSMETABITOFFSET 2


const char *glyphs[] = {
      /* light box drawing */
      "┌", "─", "┐", "│", "└", "┘", "├", "┤", "┬", "┴", "┼",
      /* double box drawing */
      "═", "║", "╔", "╗", "╚", "╝",
      /* heavy box drawing */
      "┏", "━", "┓", "┃", "┗", "┛",
      /* rounded corners */
      "╭", "╮", "╰", "╯",
      /* block elements */
      "█", "▓", "▒", "░", "▀", "▄", "▌", "▐"
  };

enum glyphs_name {
    LITE_TLC,
    LITE_TBS,
    LITE_TRC,
    LITE_LRS,
    LITE_BLC,
    LITE_BRC,
    LITE_LT,
    LITE_RT,
    LITE_TT,
    LITE_BT,
    LITE_C
};


static const int attr_codes[] = {
    1, //BOLD
    2, //FAINT
    3, //ITALIZ
    4, //UNDERLINE
    5, //BLINK  
    6, //RAPIDBLINK
    7, //REVERSE
    8, //CONCEAL
    9, //STRIKETHROUGH
    21, //DOUBLEUNDERLINE
    53, //OVERLINE
    51, //FRAMED
    52  //ENCIRCLED
};

int init_window(int x, int y, struct window *w){
    *w = (struct window) {
        .height = x,
        .width = y,
        .frame = calloc(x * y, sizeof(struct pixel_cell)), 
        .screen_buffer = malloc(x * y * MAXCELLBYTESSIZE)
    };
    if (w->frame != NULL) return 0;
    else return -1;
}

int window_build_line_buffer(struct window *w, int line, int *offset){
    struct pixel_cell *p;
    
    //set cursor for next line
    *offset += sprintf((char *)w->screen_buffer + *offset, "\033[%d;%dH", line + 1, 1);

    //parse pixel_cell struct fields to outputs
    for (int i = 0; i < w->width; i++){
        p = w->frame + (w->width * line) + i;
        //default clear
        *offset += sprintf((char *)w->screen_buffer + *offset, "\033[0");
        //check if has attributes
        if (p->attributes & (1 << HASATTRS)){
            for (int j = 0; j < NUMBEROFATTRS; j++){
                if (p->attributes & (1 << j)){
                    *offset += sprintf((char *)w->screen_buffer + *offset, ";%d", attr_codes[j]);
                }
            }
        }
        if (p->attributes & (1 << HASCOLOR)){
                //38;2;⟨r⟩;⟨g⟩;⟨b⟩m Select RGB foreground color
                *offset += sprintf((char *)w->screen_buffer + *offset, ";38;2;%d;%d;%d", p->fg_r, p->fg_g, p->fg_b);
                //48;2;⟨r⟩;⟨g⟩;⟨b⟩m Select RGB background color
                *offset += sprintf((char *)w->screen_buffer + *offset, ";48;2;%d;%d;%d", p->bg_r, p->bg_g, p->bg_b);
        }
        //m ends all attributes
        *offset += sprintf((char *)w->screen_buffer + *offset, "m");
        //write glyph
        if (p->byte[0] != '\0'){
            *offset += sprintf((char *)w->screen_buffer + *offset, "%s", p->byte);
        } else {
            *offset += sprintf((char *)w->screen_buffer + *offset, " ");
        }
    }

    return 0;
}

int write_window(struct window *w){
    int offset = 0;
    /*for the number of lines
     * parse the line
     * write the line
     * next line
     */
    write(STDOUT_FILENO, "\033[H", 3);
    for (int i = 0; i < w->height; i++){
        window_build_line_buffer(w, i, &offset);
    }
    write(STDOUT_FILENO, w->screen_buffer, offset);

    return 0;
}

int init_box(struct box *b, int x, int y,  char *bg, int border_type){
    *b = (struct box) {
        .width = x,
        .height = y,
        .background_length = strlen(bg),
        .background = bg,
        .border_type = border_type
    };
    return 0;
}

void set_pixel_foreground(struct pixel_cell *p, uint32_t hex_color){
    p->fg_r = (hex_color >> 16) & 0xFF;
    p->fg_g = (hex_color >> 8)  & 0xFF;
    p->fg_b = (hex_color)       & 0xFF;
}

void set_pixel_background(struct pixel_cell *p, uint32_t hex_color){
    p->bg_r = (hex_color >> 16) & 0xFF;
    p->bg_g = (hex_color >> 8)  & 0xFF;
    p->bg_b = (hex_color)       & 0xFF;
}

void toggle_pixel_attrs(struct pixel_cell *p, enum glyph_attributes attr){
    p->attributes ^= ( 1 << attr);

    p->attributes |= (1 << HASATTRS);
}

void clear_pixel_attrs(struct pixel_cell *p){
    p->attributes = 0;
}

void toggle_label_attributes(struct label *l, enum glyph_attributes attr){
    l->attributes ^= ( 1 << attr);

    l->attributes |= (1 << HASATTRS);
}

void clear_label_attributes(struct label *l){
    l->attributes = 0;
}

int draw_label(struct label *l, struct window *w, int x, int y){
    struct pixel_cell *pix_to_write = w->frame + (w->width * y + x);
    for (size_t i = 0; i < strlen(l->info); i++){
        memcpy(pix_to_write->byte, l->info + i, 1);
        pix_to_write->attributes = l->attributes;
        pix_to_write+=1;
    }
    return 0;
}

int draw_box(struct box *b, struct window *w, int x, int y){
    struct pixel_cell *pix_to_write;
    const int draw_point = w->width * y + x;
    for (int i = 1; i < b->width - 1; i++){
        pix_to_write = w->frame + i + draw_point;
        strcpy(pix_to_write->byte, glyphs[LITE_TBS]);
        pix_to_write = w->frame + ((b->height - 1) * w->width) + i + draw_point;
        strcpy(pix_to_write->byte, glyphs[LITE_TBS]);
    }
    for (int i = 1; i < b->height - 1; i++){
        pix_to_write = w->frame + (i * w->width) + draw_point;
        strcpy(pix_to_write->byte, glyphs[LITE_LRS]);
        pix_to_write += b->width - 1;
        strcpy(pix_to_write->byte, glyphs[LITE_LRS]);
    }
    for (int i = 1; i < b->height - 1; i++){
        for (int j = 1; j < b->width - 1; j++){
            pix_to_write = w->frame + (j + w->width * i) + draw_point;
            strcpy(pix_to_write->byte, b->background);
        }
    }
    //add corners
    pix_to_write = w->frame + draw_point;
    strcpy(pix_to_write->byte, glyphs[LITE_TLC]);
    pix_to_write = w->frame + b->width - 1 + draw_point;
    strcpy(pix_to_write->byte, glyphs[LITE_TRC]);
    pix_to_write = w->frame + w->width * (b->height - 1) + draw_point;
    strcpy(pix_to_write->byte, glyphs[LITE_BLC]);
    pix_to_write = w->frame + w->width * (b->height - 1) + b->width - 1 + draw_point;
    strcpy(pix_to_write->byte, glyphs[LITE_BRC]);

    return 0;
}

void renderer_clear_screen(struct window *w){
    memset(w->frame, 0, (size_t)w->width * w->height * sizeof(struct pixel_cell));
}

/**
 * Expects a column and row within the bounds of the size of the window
 *
 * @param col  Column in map grid (1-based)
 * @param row Row in map grid (1-based) 
 * @return void
 **/
void renderer_move_cursor(int row, int col){
    char buf[16];
    int nbytes = 0;
    nbytes = snprintf(buf, sizeof(buf), "\033[%d;%dH", row, col);
    write(STDOUT_FILENO, buf, nbytes);
}
