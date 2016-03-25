#include "../turtle.h"

int main() {
    initWorld(800,600,1);
    setSpeed(100000);

    for(;;){
        for(int i=0;i<360;i++) {
            fd(1);
            lt(1);
        }
        fd(2);
        lt(1);
    }

    pause();
    hide();
    pause();
    return 0;
}
