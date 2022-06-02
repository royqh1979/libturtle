#include "../turtle.h"

typedef int xxx;

int main() {
	TurtleState ts;
    initWorld(800,600);
//    PIMAGE back = ege::newimage(800,600);
//    setbkcolor(WHITE,back);
//    setcolor(RED,back);
    //setBackgroundImage(back);
	//setBackgroundColor(GREEN);
    //setbkcolor(WHITE);
	
    setSpeed(500);
	fillEllipse(100,100,20,40,RED);
	
	//fillCircle(200,200,60,BLUE);
	drawEllipse(50,50,150,250);

    //setImmediate(TRUE);
    //setPenColor(BLACK);
    for(int i=0;i<360;i++) {
        fd(4);
        lt(1);
    }
	pu();
	ts=getState();
	lt(90);
	fd(10);
	fill(SEAGREEN);
	setState(ts);
	pd();
    pause();
	clearScreen();
    hide();
    pause();
    return 0;
}
