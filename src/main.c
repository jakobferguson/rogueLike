#include "game/game.h"
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(void){
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    struct termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    struct termios newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ///:tcgetattr(STDIN_FILENO, &oldt);
    //ensure that the flags are correct
    write(STDOUT_FILENO, "\033[?25l", 6);   
    run_game(ws.ws_row, ws.ws_col);
    write(STDOUT_FILENO, "\033[?25h", 6);
    ///at exit, how do we deinf
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}
