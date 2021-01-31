#include "../turtle.h"

typedef int xxx;

int main() {
    initWorld(800,600);
    PIMAGE back = newimage(800,600);
    setbkcolor(WHITE,back);
    setcolor(RED,back);
    circle(400,300,200,back);
    //setBackgroundImage(back);
    //setbkcolor(WHITE);
    setSpeed(200);
    //setImmediate(TRUE);
    setPenColor(BLACK);
    for(int i=0;i<4;i++) {
        fd(150);
        lt(90);
    }
    //line(0,0,400,400);
    //circle(200,200,50);
	 
    pause();
    hide();
    pause();
    return 0;
}
