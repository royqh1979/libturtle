#ifndef TURTLE_WORLD_H
#define TURTLE_WORLD_H 1
#include <graphics.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    double x;
    double y;
    double angle;
} TurtleState;

void initWorld(int width,int height, double scale=1.0);
void fd(double step);
void forward(double step);
void bk(double step);
void backward(double step);
void lt(double degree);
void leftTurn(double degree);
void rt(double degree);
void rightTurn(double degree);
void pd();
void penDown();
void penUp();
void pu();
void cs();
void clear();
void clearScreen();
void home();
void setPenSize(int size);
void setPenColor(color_t color);
void setSpeed(int speed);
void setRewind(int isRewind);
void setImmediate(int isImmediate);
void pause();
void hide();
void show();
void setXY(double x, double y);
void setAngle(double angle);
void turnTo(double angle);
void gotoXY(double x, double y);
double getX();
double getY();
double getAngle();
TurtleState getState();
void setState(TurtleState state);
void faceXY(double x,double y);
double randBetween(double start,double end);
void setOrigin(int x, int y);

#ifdef __cplusplus
}
#endif

#endif
