#include "../turtle.h"

typedef int xxx;

int main() {
    initWorld(800,600);
//    PIMAGE back = ege::newimage(800,600);
//    setbkcolor(WHITE,back);
//    setcolor(RED,back);
    //setBackgroundImage(back);
	//setBackgroundColor(GREEN);
    //setbkcolor(WHITE);
	
    setSpeed(100);
	fillEllipse(100,100,20,40,RED);
	
	fillCircle(200,200,60,BLUE);

    //setImmediate(TRUE);
    //setPenColor(BLACK);
    for(int i=0;i<4;i++) {
        fd(150);
        lt(90);
    }

    pause();
	clearScreen();
    hide();
    pause();
    return 0;
}
