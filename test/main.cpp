#include "../turtle.h"

int main() {
    initWorld(800,600,1);
    setSpeed(400);

    for(int i=0;i<4;i++) {
        fd(100);
        lt(90);
    }
    pause();
    hide();
    pause();
    return 0;
}
