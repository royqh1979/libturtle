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
using ege::ALICEBLUE;
using ege::ANTIQUEWHITE;
using ege::AQUA;
using ege::AQUAMARINE;
using ege::AZURE;
using ege::BEIGE;
using ege::BISQUE;
using ege::BLACK;
using ege::BLANCHEDALMOND;
using ege::BLUE;
using ege::BLUEVIOLET;
using ege::BROWN;
using ege::BURLYWOOD;
using ege::CADETBLUE;
using ege::CHARTREUSE;
using ege::CHOCOLATE;
using ege::CORAL;
using ege::CORNFLOWERBLUE;
using ege::CORNSILK;
using ege::CRIMSON;
using ege::CYAN;
using ege::DARKBLUE;
using ege::DARKCYAN;
using ege::DARKGOLDENROD;
using ege::DARKGRAY;
using ege::DARKGREEN;
using ege::DARKKHAKI;
using ege::DARKMAGENTA;
using ege::DARKOLIVEGREEN;
using ege::DARKORANGE;
using ege::DARKORCHID;
using ege::DARKRED;
using ege::DARKSALMON;
using ege::DARKSEAGREEN;
using ege::DARKSLATEBLUE;
using ege::DARKSLATEGRAY;
using ege::DARKTURQUOISE;
using ege::DARKVIOLET;
using ege::DEEPPINK;
using ege::DEEPSKYBLUE;
using ege::DIMGRAY;
using ege::DODGERBLUE;
using ege::FIREBRICK;
using ege::FLORALWHITE;
using ege::FORESTGREEN;
using ege::FUCHSIA;
using ege::GAINSBORO;
using ege::GHOSTWHITE;
using ege::GOLD;
using ege::GOLDENROD;
using ege::GRAY;
using ege::GREEN;
using ege::GREENYELLOW;
using ege::HONEYDEW;
using ege::HOTPINK;
using ege::INDIANRED;
using ege::INDIGO;
using ege::IVORY;
using ege::KHAKI;
using ege::LAVENDER;
using ege::LAVENDERBLUSH;
using ege::LAWNGREEN;
using ege::LEMONCHIFFON;
using ege::LIGHTBLUE;
using ege::LIGHTCORAL;
using ege::LIGHTCYAN;
using ege::LIGHTGOLDENRODYELLOW;
using ege::LIGHTGRAY;
using ege::LIGHTGREEN;
using ege::LIGHTPINK;
using ege::LIGHTSALMON;
using ege::LIGHTSEAGREEN;
using ege::LIGHTSKYBLUE;
using ege::LIGHTSLATEGRAY;
using ege::LIGHTSTEELBLUE;
using ege::LIGHTYELLOW;
using ege::LIGHTRED;
using ege::LIGHTMAGENTA;
using ege::LIME;
using ege::LIMEGREEN;
using ege::LINEN;
using ege::MAGENTA;
using ege::MAROON;
using ege::MEDIUMAQUAMARINE;
using ege::MEDIUMBLUE;
using ege::MEDIUMORCHID;
using ege::MEDIUMPURPLE;
using ege::MEDIUMSEAGREEN;
using ege::MEDIUMSLATEBLUE;
using ege::MEDIUMSPRINGGREEN;
using ege::MEDIUMTURQUOISE;
using ege::MEDIUMVIOLETRED;
using ege::MIDNIGHTBLUE;
using ege::MINTCREAM;
using ege::MISTYROSE;
using ege::MOCCASIN;
using ege::NAVAJOWHITE;
using ege::NAVY;
using ege::OLDLACE;
using ege::OLIVE;
using ege::OLIVEDRAB;
using ege::ORANGE;
using ege::ORANGERED;
using ege::ORCHID;
using ege::PALEGOLDENROD;
using ege::PALEGREEN;
using ege::PALETURQUOISE;
using ege::PALEVIOLETRED;
using ege::PAPAYAWHIP;
using ege::PEACHPUFF;
using ege::PERU;
using ege::PINK;
using ege::PLUM;
using ege::POWDERBLUE;
using ege::PURPLE;
using ege::RED;
using ege::ROSYBROWN;
using ege::ROYALBLUE;
using ege::SADDLEBROWN;
using ege::SALMON;
using ege::SANDYBROWN;
using ege::SEAGREEN;
using ege::SEASHELL;
using ege::SIENNA;
using ege::SILVER;
using ege::SKYBLUE;
using ege::SLATEBLUE;
using ege::SLATEGRAY;
using ege::SNOW;
using ege::SPRINGGREEN;
using ege::STEELBLUE;
using ege::TAN;
using ege::TEAL;
using ege::THISTLE;
using ege::TOMATO;
using ege::TURQUOISE;
using ege::VIOLET;
using ege::WHEAT;
using ege::WHITE;
using ege::WHITESMOKE;
using ege::YELLOW;
using ege::YELLOWGREEN;

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
int setBackgroundImage(const char* filename);
int setBackgroundImage(const wchar_t* filename);
void setBackgroundColor(ege::color_t color);
void fill();

#endif
