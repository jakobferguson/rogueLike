#include "game/game.h"
#include <termios.h>
#include <unistd.h>

int main(void){
    struct termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    struct termios newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ///:tcgetattr(STDIN_FILENO, &oldt);
    //ensure that the flags are correct
   
    run_game();

    ///at exit, how do we deinf
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}
