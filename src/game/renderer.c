#include "renderer.h" 
#include "../menu/menu.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

static inline int row_center(struct window *w){ return w->height / 2; } 
static inline int col_center(struct window *w){ return w->width / 2; }

void renderer_draw_border(struct window *w, char d){
    renderer_move_cursor(0,0);
    for (int i = 0; i < w->width; i++){
        write(STDOUT_FILENO, &d, 1);
    }
    for (int i = 1; i <= w->height; i++){ //we are overwritting the corner characters here
        renderer_move_cursor(i, 1);
        write(STDOUT_FILENO, &d, 1);

        renderer_move_cursor(i, w->width);
        write(STDOUT_FILENO, &d, 1);
    }
    renderer_move_cursor(w->height, 0);
    for (int i = 0; i < w->width; i++){
        write(STDOUT_FILENO, &d, 1);
    } 
}

void renderer_renmenu(struct window *w, struct menu *m, int s){
    renderer_move_cursor(row_center(w)-(m->num_options + 2), col_center(w)-(strlen(m->title)/2));
    write(STDOUT_FILENO, m->title, strlen(m->title));

    for (int i = 0; i < m->num_options; i++){
        renderer_move_cursor(row_center(w)+i, col_center(w)-(strlen(m->options[i].label)/2));
        if (i == s) {write(STDOUT_FILENO, "\033[7m", 4);}
        write(STDOUT_FILENO, m->options[i].label, strlen(m->options[i].label));
        if (i == s) {write(STDOUT_FILENO, "\033[0m", 4);}
    }
}
