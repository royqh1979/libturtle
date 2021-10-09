#ifndef TURTLE_WORLD_H
#define TURTLE_WORLD_H 1
#include <ege.h>

#ifndef BOOL
typedef int BOOL;
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef PIMAGE
using ege::PIMAGE;
using ege::BLACK;
using ege::BLUE;
using ege::GREEN;
using ege::CYAN;
using ege::RED;
using ege::MAGENTA;
using ege::BROWN;
using ege::LIGHTGRAY;
using ege::DARKGRAY;
using ege::LIGHTBLUE;
using ege::LIGHTGREEN;
using ege::LIGHTCYAN;
using ege::LIGHTRED;
using ege::LIGHTMAGENTA;
using ege::YELLOW;
using ege::WHITE;
using ege::color_t;
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
void setPenColor(ege::color_t color);
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
void setCaption(const char* title);
void setBackgroundImage(PIMAGE backImg);
void setBackgroundColor(ege::color_t color);
void fill();

#endif
