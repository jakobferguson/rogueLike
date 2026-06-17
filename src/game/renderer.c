#include "renderer.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GLYPHATTRIBUTEBYTES 22 ///\033[1;2;3;4;5;7;9;21;53m
#define TRUECOLORBYTESREQ 19 ///\033[38;2;255;255;255m
#define GLYPHLENGTH 4
#define MAXCELLBYTESSIZE GLYPHATTRIBUTEBYTES + TRUECOLORBYTESREQ * 2 + GLYPHLENGTH

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


int init_window(int x, int y, struct window *w){
    *w = (struct window) {
        .height = y,
        .width = x,
        .frame = calloc(x * y, sizeof(struct pixel_cell)) 
        .window_buffer = malloc(x * y * )
    };
    if (w->frame != NULL) return 0;
    else return -1;
}

char *window_build_line_buffer(){
}

int write_window(struct window *w){
    /*for the number of lines
     * parse the line
     * write the line
     * next line
     */
    char *line_buffer;  
    for (int i = 0; i < w->height; i++){
        line_buffer = window_build_line_buffer(w->frame + (i * w->width), w->width);
        write(STDOUT_FILENO, line_buffer, sizeof(line_buffer));
        write(STDOUT_FILENO, "\n", 1);
    }

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

int draw_box(struct box *b, struct window *w){
    //go to location
    //draw border
    if (b->border_type == 0){
        const char *border_glyphs[] = {glyphs[LITE_TLC], glyphs[LITE_TBS], glyphs[LITE_TRC], glyphs[LITE_LRS], glyphs[LITE_BLC], glyphs[LITE_BRC]};
    }
    for (int i = 1; i < b->height - 1; i++){
        memcpy(w->frame + (i * w->width), src, sizeof(src));
    }
    return 0;
}

void renderer_clear_screen(void){
    write(STDOUT_FILENO, "\033[2J\033[H", 7);
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
