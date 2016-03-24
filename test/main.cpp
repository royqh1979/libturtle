#include "../turtle.h"

int main() {
    TurtleState state;
    double x,y,angle;
    initWorld(800,600,1);
    setSpeed(50);

    gotoXY(50,50);
    state=getState();
    gotoXY(100,0);
    lt(90);
    fd(100);
    setState(state);
    
    x=getX();
    y=getY();
    angle=getAngle();
    lt(45);
    fd(100);
    setXY(x,y);
    setAngle(angle);
    pause();
    hide();
    pause();
    return 0;
}
