#include "../turtle.h"

typedef int xxx;

int main() {
    initWorld(80,60,10);
    setSpeed(80);
    setImmediate(TRUE);
    setPenColor(RED);
    for(int i=0;i<4;i++) {
        fd(-10);
        lt(90);
    }
    line(0,0,400,400);
    circle(200,200,50); 
    pause();
    hide();
    pause();
    return 0;
}
