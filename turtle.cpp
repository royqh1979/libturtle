#include "turtle.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <queue>

#define BASE_STEP 1

    #define COLOR_EQUAL(col1, col2) ((col1.r == col2.r) && (col1.g == col2.g) && (col1.b == col2.b) && (col1.a == col2.a))

typedef struct
{
	double x;
	double y;
	double orient; //Í·Ö¸Ïò½Ç¶È
	bool is_pen_down;
	Color pen_color;
	int pen_size;
	int move_speed;
	Texture2D icon;
	double icon_width;
	double icon_height;
	bool is_show; //ÊÇ·ñÏÔÊ¾º£¹ê
} Turtle;

typedef struct
{
	int width;
	int height;
	double scale;
	Color back_color;
	bool is_rewind;
	bool is_immediate;
	Image world_image;
	Texture2D background;
	bool use_background_image;
	int origin_x;
	int origin_y;
	int frame_count;
	bool window_should_close;
} World;

static World* pWorld = NULL;
static Turtle* pTurtle = NULL;

static double d2a(double degree)
{
	return degree*M_PI/180.0;
}


static void displayWorld() {
	if (WindowShouldClose()) {
		pWorld->window_should_close = true;
	}
	Texture2D world_texture = LoadTextureFromImage(pWorld->world_image);
	
	BeginDrawing();
	ClearBackground(pWorld->back_color);
	DrawTexture(world_texture,0,0,pWorld->back_color);	
	if (pTurtle->is_show) {
		Vector2 pos;
		pos.x=pTurtle->x-(pTurtle->icon_width*sqrt(2)/2)*cos(d2a(pTurtle->orient+90+45));
		pos.y=pTurtle->y-(pTurtle->icon_height*sqrt(2)/2)*sin(d2a(pTurtle->orient+90+45));
		DrawTextureEx(pTurtle->icon,pos,pTurtle->orient+90,1,pWorld->back_color);
	}
	EndDrawing();
	UnloadTexture(world_texture);
}


static void refreshWorld()
{
	pWorld->frame_count++;
	pWorld->frame_count%=pTurtle->move_speed;
	if (pTurtle->move_speed>100)
	{
		int s=pTurtle->move_speed/100;
		if (pWorld->frame_count%s!=1)
		{
			return; //skip frame
		}
		usleep(10);
	}
	else
	{
		usleep(1000/pTurtle->move_speed);
	}
	displayWorld();
}

static void prepareTurtleOriginIcon()
{
	int width,height;
	width=10;
	height=10;
	Image icon = GenImageColor(width,height,BLANK);
	
	pTurtle->icon_width = width;
	pTurtle->icon_height = height;
	
	ImageDrawPixel(&icon,4,0,LIGHTRED);
	ImageDrawPixel(&icon,5,0,LIGHTRED);
	ImageDrawPixel(&icon,3,1,LIGHTRED);
	ImageDrawPixel(&icon,4,1,LIGHTRED);
	ImageDrawPixel(&icon,5,1,LIGHTRED);
	ImageDrawPixel(&icon,6,1,LIGHTRED);
	ImageDrawPixel(&icon,4,2,LIGHTRED);
	ImageDrawPixel(&icon,5,2,LIGHTRED);
	
	//»­¹ê±³ÂÖÀª
	ImageDrawPixel(&icon,4,3,RED);
	ImageDrawPixel(&icon,5,3,RED);
	ImageDrawPixel(&icon,3,4,RED);
	ImageDrawPixel(&icon,6,4,RED);
	ImageDrawPixel(&icon,2,5,RED);
	ImageDrawPixel(&icon,7,5,RED);
	ImageDrawPixel(&icon,2,6,RED);
	ImageDrawPixel(&icon,7,6,RED);
	ImageDrawPixel(&icon,3,7,RED);
	ImageDrawPixel(&icon,6,7,RED);
	ImageDrawPixel(&icon,4,8,RED);
	ImageDrawPixel(&icon,5,8,RED);
	
	//Ìî³ä¹ê±³
	ImageDrawPixel(&icon,4,4,DARKGRAY);
	ImageDrawPixel(&icon,5,4,DARKGRAY);
	ImageDrawPixel(&icon,3,5,DARKGRAY);
	ImageDrawPixel(&icon,4,5,DARKGRAY);
	ImageDrawPixel(&icon,5,5,DARKGRAY);
	ImageDrawPixel(&icon,6,5,DARKGRAY);
	ImageDrawPixel(&icon,3,6,DARKGRAY);
	ImageDrawPixel(&icon,4,6,DARKGRAY);
	ImageDrawPixel(&icon,5,6,DARKGRAY);
	ImageDrawPixel(&icon,6,6,DARKGRAY);
	ImageDrawPixel(&icon,4,7,DARKGRAY);
	ImageDrawPixel(&icon,5,7,DARKGRAY);
	
	//»æÖÆËÄÖ«
	ImageDrawPixel(&icon,1,3,LIGHTRED);
	ImageDrawPixel(&icon,1,4,LIGHTRED);
	ImageDrawPixel(&icon,2,3,LIGHTRED);
	ImageDrawPixel(&icon,2,4,LIGHTRED);
	
	ImageDrawPixel(&icon,7,3,LIGHTRED);
	ImageDrawPixel(&icon,7,4,LIGHTRED);
	ImageDrawPixel(&icon,8,3,LIGHTRED);
	ImageDrawPixel(&icon,8,4,LIGHTRED);
	
	ImageDrawPixel(&icon,1,7,LIGHTRED);
	ImageDrawPixel(&icon,1,8,LIGHTRED);
	ImageDrawPixel(&icon,2,7,LIGHTRED);
	ImageDrawPixel(&icon,2,8,LIGHTRED);
	
	ImageDrawPixel(&icon,7,7,LIGHTRED);
	ImageDrawPixel(&icon,7,8,LIGHTRED);
	ImageDrawPixel(&icon,8,7,LIGHTRED);
	ImageDrawPixel(&icon,8,8,LIGHTRED);
	
	//»æÖÆÎ²°Í
	ImageDrawPixel(&icon,4,9,LIGHTRED);
	ImageDrawPixel(&icon,5,9,LIGHTRED);
	pTurtle->icon = LoadTextureFromImage(icon);
	UnloadImage(icon);
}


void initWorld(int width,int height){
	if (pWorld!=NULL)
		return;
	InitWindow(width,height,"Turtle World");
	SetTargetFPS(30);
	
	pWorld = (World*)malloc(sizeof(World));
	pWorld->width = width;
	pWorld->height = height;
	pWorld->scale = 1.0;
	pWorld->back_color = WHITE;
	pWorld->is_rewind = false;
	pWorld->is_immediate = false;
	pWorld->origin_x = width/2;
	pWorld->origin_y = height/2;
	pWorld->use_background_image = false;
	pWorld->frame_count = 0;
	pWorld->window_should_close=false;
	
	pTurtle=(Turtle*)malloc(sizeof(Turtle));
	pTurtle->pen_size = 1;
	pTurtle->pen_color = BLACK;
	pTurtle->x=pWorld->origin_x;
	pTurtle->y=pWorld->origin_y;
	pTurtle->orient = -90;
	pTurtle->move_speed = 100;
	pTurtle->is_show = true;
	pTurtle->is_pen_down = true;
	prepareTurtleOriginIcon();
	
	pWorld->world_image = GenImageColor(width,height,BLANK);
}

void closeWorld(){
	if (pWorld==NULL)
		return;
	//pWorld->is_exit=true; 
	UnloadImage(pWorld->world_image);
	if (pWorld->use_background_image) {
		UnloadTexture(pWorld->background);
	}
	UnloadTexture(pTurtle->icon);
	CloseWindow();
	free(pWorld);
}

void pause() {
	if (pWorld==NULL)
		return;
	while(!pWorld->window_should_close) {
		displayWorld();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			break;
	}
}

void fd(double step)
{
	forward(step);
}

void forward(double step)
{
	double delta_x,delta_y;
	double x,y,old_x,old_y;
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	delta_x=BASE_STEP*cos(d2a(pTurtle->orient));
	delta_y=BASE_STEP*sin(d2a(pTurtle->orient));
	if (step<0)
	{
		delta_x=-delta_x;
		delta_y=-delta_y;
		step=-step;
	}
	
	if (!pWorld->is_immediate) {
		old_x=x=pTurtle->x;
		old_y=y=pTurtle->y;
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
			
			if (pWorld->is_rewind)
			{
				if (x<0)
				{
					x+=pWorld->width;
					old_x+=pWorld->width;
				}
				else if (x>pWorld->width)
				{
					x-=pWorld->width;
					old_x-=pWorld->width;
				}
				if (y<0)
				{
					y+=pWorld->height;
					old_y+=pWorld->height;
				}
				else if (y>pWorld->height)
				{
					y-=pWorld->height;
					old_y-=pWorld->height;
				}
			}
			if (pTurtle->is_pen_down)
			{
				ImageDrawLine(
					&pWorld->world_image,
					round(old_x*pWorld->scale),
					round(old_y*pWorld->scale),
					round(x*pWorld->scale),
					round(y*pWorld->scale),
					pTurtle->pen_color);
			}
			old_x=x;
			old_y=y;
			pTurtle->x=x;
			pTurtle->y=y;
			refreshWorld();
		}
	} else {
		x=pTurtle->x+step*delta_x;
		y=pTurtle->y+step*delta_y;
		if (pWorld->is_rewind) {
			while (x<0) {
				x+=pWorld->width;
			}
			while (x>pWorld->width) {
				x-=pWorld->width;
			}
			while (y<0) {
				y+=pWorld->height;
			}
			while (y>pWorld->height) {
				y-=pWorld->height;
			}
		}
		if (pTurtle->is_pen_down) {
			ImageDrawLine(
				&pWorld->world_image,
				round(pTurtle->x*pWorld->scale),round(pTurtle->y*pWorld->scale),
				round(x*pWorld->scale),round(y*pWorld->scale),
				pTurtle->pen_color);
		}
		pTurtle->x=x;
		pTurtle->y=y;
	}
	refreshWorld();
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
	double origin_angle=pTurtle->orient;
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	if (!pWorld->is_immediate)
	{
		if (degree>0)
		{
			for (int i=0; i<degree; i+=2)
			{
				pTurtle->orient=origin_angle-i;
				refreshWorld();
			}
		}
		else
		{
			for (int i=0; i<-degree; i+=2)
			{
				pTurtle->orient=origin_angle+i;
				refreshWorld();
			}
		}
	}
	degree=degree-(int)degree/360*360;
	pTurtle->orient=origin_angle-degree;
	if (pTurtle->orient>360)
	{
		pTurtle->orient-=360;
	}
	if (pTurtle->orient<0)
	{
		pTurtle->orient+=360;
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
	if (pWorld==NULL)
		return;
	pTurtle->is_pen_down = true;
}

void penUp()
{
	if (pWorld==NULL)
		return;
	pTurtle->is_pen_down = false;
}

void pu()
{
	penUp();
}

void setPenDown(bool isPenDown) {
	if (pWorld==NULL)
		return;
	pTurtle->is_pen_down = isPenDown;
}

bool isPenDown() {
	if (pWorld==NULL)
		return false;
	return pTurtle->is_pen_down;
}

void clearScreen()
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	ImageClearBackground(&pWorld->world_image,BLANK);
		
	pTurtle->x=pWorld->origin_x;
	pTurtle->y=pWorld->origin_y;
	pTurtle->orient=-90;
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
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	to_x=pWorld->origin_x;
	to_y=pWorld->origin_y;
	if (pTurtle->is_pen_down)
	{
		ImageDrawLine(
			&pWorld->world_image,
			pTurtle->x*pWorld->scale,
			pTurtle->y*pWorld->scale,
			to_x*pWorld->scale,
			to_y*pWorld->scale,
			pTurtle->pen_color
			);
	}
	pTurtle->x=to_x;
	pTurtle->y=to_y;
	pTurtle->orient=-90;
	//prepareTurtleIcon();
	refreshWorld();
}
void setPenSize(int size)
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	pTurtle->pen_size=size;
};
void setPenColor(Color color)
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	pTurtle->pen_color=color;
}

void setSpeed(int speed)
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	if (speed>=1)
	{
		pTurtle->move_speed=speed;
	}
	else
	{
		pTurtle->move_speed=1;
	}
}

void setRewind(int isRewind)
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;	
	pWorld->is_rewind=isRewind;
}

void setImmediate(int isImmediate)
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	pWorld->is_immediate=isImmediate;
}

void show()
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	pTurtle->is_show=true;
	refreshWorld();
}

void hide()
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	pTurtle->is_show=false;
	refreshWorld();
}

void setXY(double x, double y)
{
	pTurtle->x=pWorld->origin_x+x;
	pTurtle->y=pWorld->origin_y-y;
	refreshWorld();
}

double getX()
{
	if (pWorld==NULL)
		return 0;
	if (pWorld->window_should_close)
		return 0;
	return pTurtle->x-pWorld->origin_x;
}

double getY()
{
	if (pWorld==NULL)
		return 0;
	if (pWorld->window_should_close)
		return 0;
	return pWorld->origin_y-pTurtle->y;
}
void setAngle(double angle)
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	pTurtle->orient=-angle;
	refreshWorld();
}

double getAngle()
{
	if (pWorld==NULL)
		return 0;
	if (pWorld->window_should_close)
		return 0;
	return -pTurtle->orient;
}

TurtleState getState()
{
	TurtleState state;
	if (pWorld==NULL)
		return state;
	if (pWorld->window_should_close)
		return state;
	state.x=getX();
	state.y=getY();
	state.angle=getAngle();
	return state;
}

void setState(TurtleState state)
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	setXY(state.x,state.y);
	setAngle(state.angle);
}

void faceXY(double x,double y)
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	x=pWorld->origin_x+x;
	y=pWorld->origin_y-y;
	double delta_x=x-pTurtle->x;
	double delta_y=-(y-pTurtle->y);
	double angle=atan2(delta_y,delta_x)/M_PI*180;
	turnTo(angle);
}

void turnTo(double angle)
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	double turn_angle;
	turn_angle=-angle - pTurtle->orient ;
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
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	faceXY(x,y);
	
	x=pWorld->origin_x+x;
	y=pWorld->origin_y-y;
	double delta_x=x-pTurtle->x;
	double delta_y=-(y-pTurtle->y);
	double step=sqrt(delta_x*delta_x+delta_y*delta_y);
	fd(step);
	pTurtle->x=x;
	pTurtle->y=y;
	refreshWorld();
}

void setOrigin(int x, int y)
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	pWorld->origin_x=pWorld->origin_x+x;
	pWorld->origin_y=pWorld->origin_y-y;
	home();
	clearScreen();
}


void setCaption(const char* title)
{
	SetWindowTitle(title);
}

void setBackgroundImage(Image backImg)
{
	if (pWorld==NULL)
		return;
	if (pWorld->window_should_close)
		return;
	if (pWorld->use_background_image) {
		UnloadTexture(pWorld->background);
		pWorld->use_background_image = false;
	} 
	pWorld->background = LoadTextureFromImage(backImg);
	pWorld->use_background_image = true;
	refreshWorld();
}

int setBackgroundImageFile(const char* filename) {
	if (pWorld==NULL)
		return 0;
	if (pWorld->window_should_close)
		return 0;
	if (pWorld->use_background_image) {
		UnloadTexture(pWorld->background);
		pWorld->use_background_image = false;
	} 
	if (filename==NULL) 
		return 0;
	Image image = LoadImage(filename);
	setBackgroundImage(image);
	UnloadImage(image);
	return 0;
}

void setBackgroundColor(Color color)
{
	if (pWorld==NULL)
		return ;
	if (pWorld->window_should_close)
		return ;
	pWorld->back_color = color;
	refreshWorld();
}

