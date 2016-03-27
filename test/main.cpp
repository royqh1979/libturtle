#include "../turtle.h"

int main() {
    initWorld(80,60,10);
    setSpeed(80);

    for(int i=0;i<4;i++) {
        fd(10);
        lt(90);
    }
    wait();
    hide();
    wait();
    return 0;
}
