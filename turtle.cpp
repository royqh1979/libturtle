#include "turtle.h"
#include <math.h>

#ifndef BOOL
typedef int BOOL;
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define BASE_STEP 1


typedef struct
{
    double x;
    double y;
    double orient; //Í·Ö¸Ïò½Ç¶È
    BOOL is_pen_down;
    color_t pen_color;
    int pen_size;
    int pen_speed;
    PIMAGE icon;
    double icon_width;
    double icon_height;
    BOOL is_show; //ÊÇ·ñÏÔÊ¾º£¹ê
} Turtle;

typedef struct
{
    int width;
    int height;
    double scale;
    int back_color;
    BOOL rewind;
    BOOL immediate;
    PIMAGE world_image;
    int origin_x;
    int origin_y;
    int frame_count;
} World;

static Turtle myturtle;
static World myworld;
static double d2a(double degree)
{
    return degree*M_PI/180.0;
}

static PIMAGE screenImage;

static void displayWorld()
{
    putimage(screenImage,0,0,myworld.world_image);
    if (myturtle.is_show)
    {
    	putimage_rotatetransparent(screenImage,
                             myturtle.icon,
                             myturtle.x,myturtle.y,
                             0,0,
                             myturtle.icon_width,
                             myturtle.icon_height,
                             myturtle.icon_width/2,
                             myturtle.icon_height/2,
                             WHITE,
							 (myturtle.orient+90)/180*PI);
    }
    putimage(0,0,screenImage);
}

static void refreshWorld()
{
    myworld.frame_count++;
    myworld.frame_count%=myturtle.pen_speed;
    if (myturtle.pen_speed>100)
    {
        int s=myturtle.pen_speed/100;
        if (myworld.frame_count%s!=1)
        {
            return;
        }
        delay_ms(10);
    }
    else
    {
        delay_ms(1000/myturtle.pen_speed);
    }
    displayWorld();
}

static void prepareTurtleOriginIcon()
{
    int width,height;
    width=10;
    height=10;
    myturtle.icon=newimage(width,height);
    myturtle.icon_width=width;
    myturtle.icon_height=height;


    setbkcolor(WHITE,myturtle.icon);
    setfillcolor(BLACK,myturtle.icon);
    cleardevice(myturtle.icon);

    putpixel(4,0,LIGHTRED,myturtle.icon);
    putpixel(5,0,LIGHTRED,myturtle.icon);
    putpixel(3,1,LIGHTRED,myturtle.icon);
    putpixel(4,1,LIGHTRED,myturtle.icon);
    putpixel(5,1,LIGHTRED,myturtle.icon);
    putpixel(6,1,LIGHTRED,myturtle.icon);
    putpixel(4,2,LIGHTRED,myturtle.icon);
    putpixel(5,2,LIGHTRED,myturtle.icon);

    //»­¹ê±³ÂÖÀª
    putpixel(4,3,RED, myturtle.icon);
    putpixel(5,3,RED, myturtle.icon);
    putpixel(3,4,RED, myturtle.icon);
    putpixel(6,4,RED, myturtle.icon);
    putpixel(2,5,RED, myturtle.icon);
    putpixel(7,5,RED, myturtle.icon);
    putpixel(2,6,RED, myturtle.icon);
    putpixel(7,6,RED, myturtle.icon);
    putpixel(3,7,RED, myturtle.icon);
    putpixel(6,7,RED, myturtle.icon);
    putpixel(4,8,RED, myturtle.icon);
    putpixel(5,8,RED, myturtle.icon);

    //Ìî³ä¹ê±³
    putpixel(4,4,DARKGRAY, myturtle.icon);
    putpixel(5,4,DARKGRAY, myturtle.icon);
    putpixel(3,5,DARKGRAY, myturtle.icon);
    putpixel(4,5,DARKGRAY, myturtle.icon);
    putpixel(5,5,DARKGRAY, myturtle.icon);
    putpixel(6,5,DARKGRAY, myturtle.icon);
    putpixel(3,6,DARKGRAY, myturtle.icon);
    putpixel(4,6,DARKGRAY, myturtle.icon);
    putpixel(5,6,DARKGRAY, myturtle.icon);
    putpixel(6,6,DARKGRAY, myturtle.icon);
    putpixel(4,7,DARKGRAY, myturtle.icon);
    putpixel(5,7,DARKGRAY, myturtle.icon);

    //»æÖÆËÄÖ«
    putpixel(1,3,LIGHTRED,myturtle.icon);
    putpixel(1,4,LIGHTRED,myturtle.icon);
    putpixel(2,3,LIGHTRED,myturtle.icon);
    putpixel(2,4,LIGHTRED,myturtle.icon);

    putpixel(7,3,LIGHTRED,myturtle.icon);
    putpixel(7,4,LIGHTRED,myturtle.icon);
    putpixel(8,3,LIGHTRED,myturtle.icon);
    putpixel(8,4,LIGHTRED,myturtle.icon);

    putpixel(1,7,LIGHTRED,myturtle.icon);
    putpixel(1,8,LIGHTRED,myturtle.icon);
    putpixel(2,7,LIGHTRED,myturtle.icon);
    putpixel(2,8,LIGHTRED,myturtle.icon);

    putpixel(7,7,LIGHTRED,myturtle.icon);
    putpixel(7,8,LIGHTRED,myturtle.icon);
    putpixel(8,7,LIGHTRED,myturtle.icon);
    putpixel(8,8,LIGHTRED,myturtle.icon);

    //»æÖÆÎ²°Í
    putpixel(4,9,LIGHTRED,myturtle.icon);
    putpixel(5,9,LIGHTRED,myturtle.icon);
}

void initWorld(int width,int height,double scale)
{
    initgraph(width*scale,height*scale);

    myworld.width=width;
    myworld.height=height;
    myworld.back_color=WHITE;
    myworld.rewind=TRUE;
    myworld.immediate=FALSE;
    myworld.scale=scale;
    myworld.world_image=newimage(width*scale,height*scale);
    myworld.frame_count=0;
    myworld.origin_x=width/2;
    myworld.origin_y=height/2;
    setcolor(myturtle.pen_color,myworld.world_image);
    setbkcolor(myworld.back_color, myworld.world_image);
    setfillcolor(myturtle.pen_color, myworld.world_image);
    setlinewidth(myturtle.pen_size, myworld.world_image);
    cleardevice(myworld.world_image);

    myturtle.x=myworld.origin_x;
    myturtle.y=myworld.origin_y;
    myturtle.orient=-90;
    myturtle.is_pen_down=TRUE;
    myturtle.pen_color=BLACK;
    myturtle.pen_size=1;
    myturtle.pen_speed=100;
    myturtle.icon=NULL;
    myturtle.is_show=TRUE;
    prepareTurtleOriginIcon();

    screenImage=newimage(width*scale,height*scale);

    setrendermode(RENDER_MANUAL);
    //prepareTurtleIcon();

    refreshWorld();
}


void fd(double step)
{
    forward(step);
}

void forward(double step)
{
    double delta_x,delta_y;
    double x,y,old_x,old_y;
    delta_x=BASE_STEP*cos(d2a(myturtle.orient));
    delta_y=BASE_STEP*sin(d2a(myturtle.orient));
    if (step<0)
    {
        delta_x=-delta_x;
        delta_y=-delta_y;
        step=-step;
    }
    old_x=x=myturtle.x;
    old_y=y=myturtle.y;

    for (int i=0; i<step; i++)
    {
        if ((i+1)<step)
        {
            x+=delta_x;
            y+=delta_y;
        }
        else
        {
            x+=(step-i)*delta_x;
            y+=(step-i)*delta_y;
        }

        if (myworld.rewind)
        {
            if (x<0)
            {
                x+=myworld.width;
                old_x+=myworld.width;
            }
            else if (x>myworld.width)
            {
                x-=myworld.width;
                old_x-=myworld.width;
            }
            if (y<0)
            {
                y+=myworld.height;
                old_y+=myworld.height;
            }
            else if (y>myworld.height)
            {
                y-=myworld.height;
                old_y-=myworld.height;
            }
        }
        if (myturtle.is_pen_down)
        {
            line(round(old_x*myworld.scale),round(old_y*myworld.scale),round(x*myworld.scale),round(y*myworld.scale),myworld.world_image);
        }
        old_x=x;
        old_y=y;
        myturtle.x=x;
        myturtle.y=y;
        refreshWorld();

    }

}
void bk(double step)
{
    backward(step);
}
void backward(double step)
{
    forward(-step);
}
void lt(double degree)
{
    leftTurn(degree);
}
void leftTurn(double degree)
{
    double origin_angle=myturtle.orient;
    if (!myworld.immediate)
    {
        if (degree>0)
        {
            for (int i=0; i<degree; i+=2)
            {
                myturtle.orient=origin_angle-i;
                //prepareTurtleIcon();
                refreshWorld();
            }
        }
        else
        {
            for (int i=0; i<-degree; i+=2)
            {
                myturtle.orient=origin_angle+i;
                //prepareTurtleIcon();
                refreshWorld();
            }
        }
    }
    degree=degree-(int)degree/360*360;
    myturtle.orient=origin_angle-degree;
    if (myturtle.orient>360)
    {
        myturtle.orient-=360;
    }
    if (myturtle.orient<0)
    {
        myturtle.orient+=360;
    }
    //prepareTurtleIcon();
    refreshWorld();
}
void rt(double degree)
{
    rightTurn(degree);
}
void rightTurn(double degree)
{
    lt(-degree);
}
void pd()
{
    penDown();
}
void penDown()
{
    myturtle.is_pen_down=TRUE;
}
void penUp()
{
    myturtle.is_pen_down=FALSE;
}
void pu()
{
    penUp();
}
void clearScreen()
{
    cleardevice(myworld.world_image);

    myturtle.x=myworld.origin_x;
    myturtle.y=myworld.origin_y;
    myturtle.orient=-90;
    //prepareTurtleIcon();
    refreshWorld();
}

void cs()
{
    clearScreen();
}
void clear()
{
    clearScreen();
}

void home()
{
    int to_x,to_y;

    to_x=myworld.origin_x;
    to_y=myworld.origin_y;
    if (myturtle.is_pen_down)
    {
        line(myturtle.x*myworld.scale,myturtle.y*myworld.scale,to_x*myworld.scale,to_y*myworld.scale,myworld.world_image);
    }
    myturtle.x=to_x;
    myturtle.y=to_y;
    myturtle.orient=-90;
    //prepareTurtleIcon();
    refreshWorld();
}
void setPenSize(int size)
{
    myturtle.pen_size=size;
    setlinestyle(SOLID_LINE,0,size,myworld.world_image);
    setlinewidth(size,myworld.world_image);
};
void setPenColor(color_t color)
{
    myturtle.pen_color=color;
    setcolor(color,myworld.world_image);
}
void setSpeed(int speed)
{
    if (speed>=1)
    {
        myturtle.pen_speed=speed;
    }
    else
    {
        myturtle.pen_speed=1;
    }
}
void setRewind(int isRewind)
{
    myworld.rewind=isRewind;
}
void setImmediate(int isImmediate)
{
    myworld.immediate=isImmediate;
}
void pause()
{
    myworld.frame_count=0;
    //prepareTurtleIcon();
    displayWorld();
    getch();
}
void show()
{
    myturtle.is_show=TRUE;
    refreshWorld();
}
void hide()
{
    myturtle.is_show=FALSE;
    refreshWorld();
}

void setXY(double x, double y)
{
    myturtle.x=myworld.origin_x+x;
    myturtle.y=myworld.origin_y-y;
    refreshWorld();
}

double getX()
{
    int cent_x;
    cent_x=round(myworld.width/2);
    return myturtle.x-cent_x;
}
double getY()
{
    int cent_y;
    cent_y=round(myworld.height/2);
    return cent_y-myturtle.y;
}
void setAngle(double angle)
{
    myturtle.orient=-angle;
    //prepareTurtleIcon();
    refreshWorld();
}
double getAngle()
{
    return -myturtle.orient;
}

TurtleState getState()
{
    TurtleState state;
    state.x=getX();
    state.y=getY();
    state.angle=getAngle();
    return state;
}

void setState(TurtleState state)
{
    BOOL pd=myturtle.is_pen_down;
    myturtle.is_pen_down=0;
    setXY(state.x,state.y);
    setAngle(state.angle);
    myturtle.is_pen_down=pd;
}
void faceXY(double x,double y)
{
    x=myworld.origin_x+x;
    y=myworld.origin_y-y;
    double delta_x=x-myturtle.x;
    double delta_y=-(y-myturtle.y);
    double angle=atan2(delta_y,delta_x)/M_PI*180;
    turnTo(angle);
}

void turnTo(double angle)
{
    double turn_angle;
    turn_angle=-angle - myturtle.orient ;
    while (turn_angle>180)
    {
        turn_angle=turn_angle-360;
    }
    while (turn_angle<-180)
    {
        turn_angle=360+turn_angle;
    }
    rt(turn_angle);
}
void gotoXY(double x, double y)
{
    faceXY(x,y);

    x=myworld.origin_x+x;
    y=myworld.origin_y-y;
    double delta_x=x-myturtle.x;
    double delta_y=-(y-myturtle.y);
    double step=sqrt(delta_x*delta_x+delta_y*delta_y);
    fd(step);
    myturtle.x=x;
    myturtle.y=y;
    //prepareTurtleIcon();
    refreshWorld();
}

double randBetween(double start,double end)
{
    return (end-start)*randomf()+start;
}

void setOrigin(int x, int y)
{
    myworld.origin_x=myworld.origin_x+x;
    myworld.origin_y=myworld.origin_y-y;
    home();
    clearScreen();
}
