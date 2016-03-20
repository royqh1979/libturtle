#include "../turtle.h"

int main() {
    initWorld(800,600,1);
    setSpeed(50);

    gotoXY(50,50);
    gotoXY(100,0);
    pause();
    hide();
    pause();
    return 0;
}
