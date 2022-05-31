#include "../turtle.h"

typedef int xxx;

int main() {
    initWorld(800,600);
//    PIMAGE back = ege::newimage(800,600);
//    setbkcolor(WHITE,back);
//    setcolor(RED,back);
//    circle(400,300,200,back);
    //setBackgroundImage(back);
	//setBackgroundColor(GREEN);
    //setbkcolor(WHITE);
    setSpeed(5000);
    //setImmediate(TRUE);
    //setPenColor(BLACK);
    for(int i=0;i<4;i++) {
        fd(150);
        lt(90);
    }
    pu();
    fd(50);
    lt(90);
    fd(50);

    pause();
    hide();
    pause();
    return 0;
}
