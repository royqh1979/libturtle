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


typedef struct{
	double x;
	double y;
	double orient; //ͷָ��Ƕ� 
	BOOL is_pen_down;
	color_t pen_color;
	int pen_size;
	int pen_speed;
	PIMAGE origin_icon;
	PIMAGE icon;
	int icon_x;
	int icon_y;
	BOOL is_show; //�Ƿ���ʾ���� 
} Turtle;

typedef struct {
	int width;
	int height;
	double scale;
	int back_color;
	BOOL rewind;
	BOOL immediate;
	PIMAGE world_image;
} World;

static Turtle myturtle;
static World myworld;
static double d2a(double degree) {
	return degree*M_PI/180.0;
}

static PIMAGE screenImage;


static void refreshWorld() {
	putimage(screenImage,0,0,myworld.world_image);
	if (myturtle.is_show) {
		putimage_transparent(screenImage,
			myturtle.icon,
			round(myturtle.x-myturtle.icon_x),round(myturtle.y-myturtle.icon_y),
			WHITE);
	}
	putimage(0,0,myworld.width*myworld.scale, myworld.height*myworld.scale,
		screenImage,
		0,0,myworld.width,myworld.height);
}

static void prepareTurtleOriginIcon() {
	int width,height;
	width=10;height=10;
	myturtle.origin_icon=newimage(width,height);
	myturtle.icon_x=width/2;
	myturtle.icon_y=height/2;
	
	setbkcolor(WHITE,myturtle.origin_icon);
	setfillcolor(BLACK,myturtle.origin_icon);
	cleardevice(myturtle.origin_icon);
	
 	putpixel(4,0,LIGHTRED,myturtle.origin_icon);
 	putpixel(5,0,LIGHTRED,myturtle.origin_icon);
 	putpixel(3,1,LIGHTRED,myturtle.origin_icon);
 	putpixel(4,1,LIGHTRED,myturtle.origin_icon);
 	putpixel(5,1,LIGHTRED,myturtle.origin_icon);
 	putpixel(6,1,LIGHTRED,myturtle.origin_icon);
 	putpixel(4,2,LIGHTRED,myturtle.origin_icon);
 	putpixel(5,2,LIGHTRED,myturtle.origin_icon);
 	
 	//���걳���� 
 	putpixel(4,3,RED, myturtle.origin_icon);
 	putpixel(5,3,RED, myturtle.origin_icon);
 	putpixel(3,4,RED, myturtle.origin_icon);
 	putpixel(6,4,RED, myturtle.origin_icon);
 	putpixel(2,5,RED, myturtle.origin_icon);
 	putpixel(7,5,RED, myturtle.origin_icon);
 	putpixel(2,6,RED, myturtle.origin_icon);
 	putpixel(7,6,RED, myturtle.origin_icon);
 	putpixel(3,7,RED, myturtle.origin_icon);
 	putpixel(6,7,RED, myturtle.origin_icon);
 	putpixel(4,8,RED, myturtle.origin_icon);
 	putpixel(5,8,RED, myturtle.origin_icon);
 	
 	//���걳
	 putpixel(4,4,DARKGRAY, myturtle.origin_icon);
	 putpixel(5,4,DARKGRAY, myturtle.origin_icon);
	 putpixel(3,5,DARKGRAY, myturtle.origin_icon);
	 putpixel(4,5,DARKGRAY, myturtle.origin_icon);
	 putpixel(5,5,DARKGRAY, myturtle.origin_icon);
	 putpixel(6,5,DARKGRAY, myturtle.origin_icon);
	 putpixel(3,6,DARKGRAY, myturtle.origin_icon);
	 putpixel(4,6,DARKGRAY, myturtle.origin_icon);
	 putpixel(5,6,DARKGRAY, myturtle.origin_icon);
	 putpixel(6,6,DARKGRAY, myturtle.origin_icon);
	 putpixel(4,7,DARKGRAY, myturtle.origin_icon);
	 putpixel(5,7,DARKGRAY, myturtle.origin_icon);
	 
	 //������֫
	 putpixel(1,3,LIGHTRED,myturtle.origin_icon); 
	 putpixel(1,4,LIGHTRED,myturtle.origin_icon); 
	 putpixel(2,3,LIGHTRED,myturtle.origin_icon); 
	 putpixel(2,4,LIGHTRED,myturtle.origin_icon); 

	 putpixel(7,3,LIGHTRED,myturtle.origin_icon); 
	 putpixel(7,4,LIGHTRED,myturtle.origin_icon); 
	 putpixel(8,3,LIGHTRED,myturtle.origin_icon); 
	 putpixel(8,4,LIGHTRED,myturtle.origin_icon); 

	 putpixel(1,7,LIGHTRED,myturtle.origin_icon); 
	 putpixel(1,8,LIGHTRED,myturtle.origin_icon); 
	 putpixel(2,7,LIGHTRED,myturtle.origin_icon); 
	 putpixel(2,8,LIGHTRED,myturtle.origin_icon); 

	 putpixel(7,7,LIGHTRED,myturtle.origin_icon); 
	 putpixel(7,8,LIGHTRED,myturtle.origin_icon); 
	 putpixel(8,7,LIGHTRED,myturtle.origin_icon); 
	 putpixel(8,8,LIGHTRED,myturtle.origin_icon); 
	 
	 //����β��
	 putpixel(4,9,LIGHTRED,myturtle.origin_icon); 
	 putpixel(5,9,LIGHTRED,myturtle.origin_icon); 
}

static void prepareTurtleIcon() {
    int height,width;
    int i,j;
    double x,y;
    double to_x,to_y;
    double angle=d2a(90+myturtle.orient);

    //FILE *fp=fopen("d:\\\\test.txt","a+");

    if (myturtle.icon!=NULL) {
    	delimage(myturtle.icon);
    }
    
    height=10;
	width=10;    
    myturtle.icon=newimage(width,height);
    
	setbkcolor(WHITE,myturtle.icon);
	setfillcolor(BLACK,myturtle.icon);
	cleardevice(myturtle.icon);
    for (i=0;i<10;i++) {
    	for (j=0;j<10;j++) {
    		x=j-myturtle.icon_x;
    		y=i-myturtle.icon_y;
    		to_x=x*cos(angle)-y*sin(angle)+myturtle.icon_x;
    		to_y=x*sin(angle)+y*cos(angle)+myturtle.icon_y;
    		if (to_x<0) {
    			to_x=0;
			} else if (to_x>=width) {
				to_x=width-1;
			}
			if (to_y<0) {
				to_y=0;
			} else if (to_y>=height) {
				to_y=height-1;
			}
			putpixel(to_x,to_y,getpixel(j,i,myturtle.origin_icon),myturtle.icon);
		}	
	}
		  
}


void initWorld(int width,int height,double scale){
	int pt[] = {
        10,0,
        0,20,
        20,20
    };
    fillpoly(6, pt);
	initgraph(width*scale,height*scale);
	myturtle.x=round(width/2);
	myturtle.y=round(height/2);
	myturtle.orient=-90;
	myturtle.is_pen_down=TRUE;
	myturtle.pen_color=BLACK;
	myturtle.pen_size=1;
	myturtle.pen_speed=1000;
	myturtle.icon=NULL;
	myturtle.is_show=TRUE;
	prepareTurtleOriginIcon();
	
	myworld.width=width;
	myworld.height=height;
	myworld.back_color=WHITE;
	myworld.rewind=TRUE;
	myworld.immediate=FALSE;
	myworld.scale=scale;
	myworld.world_image=newimage(width,height);
	
	screenImage=newimage(width,height);
	
	setcolor(myturtle.pen_color,myworld.world_image);
	setbkcolor(myworld.back_color, myworld.world_image);
	setfillcolor(myturtle.pen_color, myworld.world_image);
	setlinewidth(myturtle.pen_size, myworld.world_image);
	cleardevice(myworld.world_image);
	setrendermode(RENDER_MANUAL);
	prepareTurtleIcon();
		
	refreshWorld();
}


void fd(double step){
	forward(step);
}

void forward(double step){
	double delta_x,delta_y;
	double x,y,old_x,old_y;
	//FILE *fp=fopen("d:\\\\test.txt1","a+");
	delta_x=BASE_STEP*cos(d2a(myturtle.orient));
	delta_y=BASE_STEP*sin(d2a(myturtle.orient));
	if (step<0) {
		delta_x=-delta_x;
		delta_y=-delta_y;
		step=-step;
	}
	old_x=x=myturtle.x;
	old_y=y=myturtle.y;
	//fprintf(fp,"%lf,%lf,%lf\n",delta_x,delta_y,myturtle.orient);
	for (int i=0;i<step;i++){
//		displayTurtle(old_x,old_y);
		if ((i+1)<step) {
			x+=delta_x;
			y+=delta_y;
		} else {
			x+=(step-i)*delta_x;
			y+=(step-i)*delta_y;
		}

		if (myworld.rewind) {
			if (x<0) {
				x+=myworld.width;
				old_x+=myworld.width;
			} else if (x>myworld.width) {
				x-=myworld.width;
				old_x-=myworld.width;
			}
			if (y<0) {
				y+=myworld.height;
				old_y+=myworld.height;
			} else if (y>myworld.height){
				y-=myworld.height;
				old_y-=myworld.height;				
			}
		}
		if (myturtle.is_pen_down) {
			line(round(old_x),round(old_y),round(x),round(y),myworld.world_image);
		}
		old_x=x;old_y=y;
		myturtle.x=x;
		myturtle.y=y;
		refreshWorld();
		if (!myworld.immediate) {
			delay_fps(myturtle.pen_speed);
		}
	}

	//fclose(fp);
}
void bk(double step){
	backward(step);
}
void backward(double step){
	forward(-step);
}
void lt(double degree){
	leftTurn(degree);
}
void leftTurn(double degree){
	myturtle.orient-=degree;
	while (myturtle.orient>360) {
		myturtle.orient-=360;
	}
	while (myturtle.orient<0) {
		myturtle.orient+=360;
	}
	prepareTurtleIcon();
	refreshWorld();
}
void rt(double degree) {
	rightTurn(degree);
}
void rightTurn(double degree){
	lt(-degree);
}
void pd(){
	penDown();
}
void penDown(){
	myturtle.is_pen_down=TRUE;
}
void penUp(){
	myturtle.is_pen_down=FALSE;
}
void pu(){
	penUp();
}
void clearScreen(){
	int to_x,to_y;
	cleardevice(myworld.world_image);

	to_x=round(myworld.width/2);
	to_y=round(myworld.height/2);
	myturtle.x=to_x;
	myturtle.y=to_y;		
	myturtle.orient=-90;
	prepareTurtleIcon();
	refreshWorld();
}

void cs(){
	clearScreen();
}
void clear(){
	clearScreen();
}

void home(){
	int to_x,to_y;
	
	to_x=round(myworld.width/2);
	to_y=round(myworld.height/2);
	//displayTurtle(myturtle.x,myturtle.y);
	if (myturtle.is_pen_down) {
		line(myturtle.x,myturtle.y,to_x,to_y,myworld.world_image);
	}
	myturtle.x=to_x;
	myturtle.y=to_y;		
	myturtle.orient=-90;
	prepareTurtleIcon();
	refreshWorld();
}
void setPenSize(int size) {
	myturtle.pen_size=size;
	setlinewidth(size,myworld.world_image);
};
void setPenColor(color_t color){
	myturtle.pen_color=color;
	setcolor(color);
}
void setSpeed(int speed) {
	myturtle.pen_speed=speed;
}
void setRewind(int isRewind) {
	myworld.rewind=isRewind;
}
void setImmediate(int isImmediate) {
	myworld.immediate=isImmediate;
}
void pause() {
	getch();
}
void show() {
	myturtle.is_show=TRUE;
	refreshWorld();
}
void hide() {
	myturtle.is_show=FALSE;
	refreshWorld();
}

void setXY(double x, double y) {
	int cent_x,cent_y;
	double to_x, to_y;

	cent_x=round(myworld.width/2);
	cent_y=round(myworld.height/2);
	to_x=cent_x+x;
	to_y=cent_y-y;
	if (myturtle.is_pen_down) {
		line(myturtle.x,myturtle.y,to_x,to_y,myworld.world_image);
	}
	myturtle.x=to_x;
	myturtle.y=to_y;
	refreshWorld();
}
void setAngle(double angle) {
	myturtle.orient=angle;
	prepareTurtleIcon();
	refreshWorld();
}


