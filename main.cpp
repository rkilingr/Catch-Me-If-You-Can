/*CG Mini Project*/
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<string.h>
#include <GL/glut.h>
#include <iostream>
#include<time.h>
#include "SOIL.h"
#define DEG2RAD 0.01745329251
#define SINSUM 114.5886501
using namespace std;
static bool spinning = true,menuFlag=true,gameFlag=false,yolkFlag=false,leftButtonFlag=false,rightButtonFlag=false,moveChickenFlag=false;
GLuint tex_2d,tex1_2d;
static GLfloat currentAngleOfRotation = 0.0;
static const int FPS = 120;
GLfloat rotation = 90.0;int counter=0;
float posX = 0, posY = 0, posZ = 0,chickenPos=0,speed=1,menuChickPos;int eggBreaks=0;
class FallingEgg{
public:
float x,y,eggSize,posYEgg=0,eggVelocity=0,posnBasket=0;
bool status=false,yolkFlag=false,randomSet=false,collisionFlag=false;
public:
FallingEgg(){;}
 FallingEgg(float x,float y,float eggSize){
    this->x=x;
    this->y=y;
    this->eggSize=eggSize;

}
    void setYolkFlag(){
    eggBreaks++;
    yolkFlag=true;
    }
    void attClear(){
    x=y=eggSize=eggVelocity=0;
    posYEgg=0;
    status=yolkFlag=collisionFlag=false;
    }
 void setVar(float x,float y,float eggSize){
    this->x=x;
    this->y=y;
    this->eggSize=eggSize;

}
void setCollisionFlag(){

    collisionFlag=true;
}
void draw(){
    GLfloat eggColor[3]={1.0,1.0,1.0};
    if(!collisionFlag)
    glTranslatef(0,this->posYEgg,0);
    else
    glTranslatef(posnBasket,this->posYEgg,0);
    if(!yolkFlag)
        this->drawEgg(0.27,0.35,eggColor);
    else
        this->drawYolk();


}
bool isEnabled(){
return status;
}
float getYPos(){
    return posYEgg;
}
void setYpos(float y){
    posYEgg=y;
}
void setEnabled(){
    status=true;
}
void setDisabled(){
    status=false;
}
void drawEgg(float radiusX,float radiusY,GLfloat *color){

   int i;
    glColor3fv(color);
   glBegin(GL_POLYGON);

   for(i=0;i<360;i++)
   {
      float rad = i*DEG2RAD;
      glVertex2f(cos(rad)*radiusX*this->eggSize+x,
                  sin(rad)*radiusY*this->eggSize+y);
   }

   glEnd();

}
void drawYolk(){
    float sizeOuter=35,sizeInner=23;
    GLfloat outer[3]={1.0,1.0,1.0};
    this->drawEgg(0.35*sizeOuter/eggSize,0.25*sizeOuter/eggSize,outer);
    GLfloat inner[3]={1.0,0.78823529,0.01568627};
    this->drawEgg(0.35*sizeInner/eggSize,0.25*sizeInner/eggSize,inner);

    }

};

//Function on mouse to stop rotation
void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    spinning = true;
  } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    spinning = false;
  }
  printf("%d %d\n",x,y);
  if(button==GLUT_LEFT_BUTTON&&x>474&&x<808&&y>157&&y<224){
    menuFlag=false;gameFlag=true;counter=0;
  }
}


void init(){
    // set clear color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // set fill color to white
    glColor3f(1.0, 1.0, 1.0);

    //set up standard orthogonal view with clipping
    //box as cube of side 2 centered at origin
    //This is the default view and these statements could be removed
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1366, 0, 768);

}
void output(float x, float y, const char *string,int choice)
{
      int len, i;
            glColor3f(1.0,0.0,0.0);
           glRasterPos2f(x,y);
           len=(int) strlen(string);
           for (i = 0; i < len; i++)
			{
			switch(choice){
             case 1:glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
             break;
             case 2:glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
             break;
             default:glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,string[i]);
             }

			}
}
/*  *Objects
1.Chicken
*/
void drawChicken(float k1, float k2,float k)
{

//body sk

glBegin(GL_POLYGON);
glColor3f(1.0,1.0,1.0);
glVertex2f(20*k+k1,86*k+k2);
glVertex2f(31*k+k1,95*k+k2);
glVertex2f(40*k+k1,75*k+k2);
glVertex2f(60*k+k1,75*k+k2);
glVertex2f(100*k+k1,95*k+k2);
glVertex2f(90*k+k1,70*k+k2);
glVertex2f(118*k+k1,63*k+k2);
glVertex2f(65*k+k1,40*k+k2);
glVertex2f(20*k+k1,40*k+k2);
glEnd();

//leg1

glBegin(GL_POLYGON);
glColor3f(0.8235,0.41176,0.117);
glVertex2f(50*k+k1,40*k+k2);
glVertex2f(53*k+k1,40*k+k2);
glVertex2f(53*k+k1,0*k+k2);
glVertex2f(49*k+k1,0*k+k2);
glVertex2f(53*k+k1,5*k+k2);
glVertex2f(50*k+k1,40*k+k2);
glEnd();

//leg2

glBegin(GL_POLYGON);
glColor3f(0.8235,0.41176,0.117);
glVertex2f(40*k+k1,40*k+k2);
glVertex2f(50*k+k1,40*k+k2);
glVertex2f(48*k+k1,33*k+k2);
glVertex2f(46*k+k1,0*k+k2);
glVertex2f(40*k+k1,0*k+k2);
glEnd();

//rk thale

glBegin(GL_POLYGON);
glColor3f(1.0,0.0,0.0);
glVertex2f(15*k+k1,105*k+k2);
glVertex2f(30*k+k1,105*k+k2);
glVertex2f(31*k+k1,95*k+k2);
glVertex2f(20*k+k1,86*k+k2);
glVertex2f(15*k+k1,86*k+k2);
glEnd();

//rk kokku
glBegin(GL_POLYGON);
glColor3f(1,1,.4);
glVertex2f(15*k+k1,97*k+k2);
glVertex2f(0*k+k1,95*k+k2);
glVertex2f(0*k+k1,92*k+k2);
glVertex2f(15*k+k1,90*k+k2);
glEnd();

//kannu

glBegin(GL_POLYGON);
glColor3f(0.0,0.0,0.0);
glVertex2f(20*k+k1,100*k+k2);
glVertex2f(23*k+k1,100*k+k2);
glVertex2f(23*k+k1,95*k+k2);
glVertex2f(20*k+k1,95*k+k2);
glEnd();

//juttu :P

glBegin(GL_POLYGON);
glColor3f(1.0,0.0,0.0);
glVertex2f(20*k+k1,105*k+k2);
glVertex2f(15*k+k1,115*k+k2);
glVertex2f(22*k+k1,112*k+k2);
glVertex2f(24*k+k1,118*k+k2);
glVertex2f(26*k+k1,112*k+k2);
glVertex2f(31*k+k1,118*k+k2);
glVertex2f(25*k+k1,105*k+k2);
glEnd();
glFlush();
}

//Egg
void missMark(float x,float y,GLfloat* color){
glColor3fv(color);
glBegin(GL_POLYGON);
glVertex2d(0+x,50+y);
glVertex2d(20+x,50+y);
glVertex2d(60+x,0+y);
glVertex2d(40+x,0+y);
glEnd();
glBegin(GL_POLYGON);
glVertex2d(0+x,0+y);
glVertex2d(40+x,50+y);
glVertex2d(60+x,50+y);
glVertex2d(20+x,0+y);
glEnd();
}

//Function for drawing Basket
void drawBasket(float x,float y,float size1){
glColor3f(0.64705882352,0.16470588235,0.16470588235);
glBegin(GL_POLYGON);
glVertex2d(x,y);
glVertex2d(x,y+0.08*size1);
glVertex2d(x+0.22*size1,y+0.08*size1);
glVertex2d(x+0.22*size1,y);
glEnd();
glBegin(GL_POLYGON);
glVertex2d(x,y+0.08*size1);
glVertex2d(x,y+0.12*size1);
glVertex2d(x+0.03*size1,y+0.12*size1);
glVertex2d(x+0.03*size1,y+0.08*size1);
glEnd();
glBegin(GL_POLYGON);
glVertex2d(x+0.19*size1,y+0.08*size1);
glVertex2d(x+0.19*size1,y+0.12*size1);
glVertex2d(x+0.22*size1,y+0.12*size1);
glVertex2d(x+0.22*size1,y+0.08*size1);
glEnd();
}

void menuChicken(float x,float y,float size4){
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2d(0+x,0+y);
glVertex2d(0+x,50*size4+y);
glVertex2d(50*size4+x,50*size4+y);
glVertex2d(50*size4+x,0+y);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_LINE_LOOP);
glVertex2d(0+x,0+y);
glVertex2d(0+x,50*size4+y);
glVertex2d(50*size4+x,50*size4+y);
glVertex2d(50*size4+x,0+y);
glEnd();
glColor3f(1.0,1.0,1.0);
glBegin(GL_POLYGON);
glVertex2d(12.5*size4+x,40*size4+y);
glVertex2d(12.5*size4+x,65*size4+y);
glVertex2d(37.5*size4+x,65*size4+y);
glVertex2d(37.5*size4+x,40*size4+y);
glEnd();
glColor3f(0.0,0.0,0.0);
glBegin(GL_LINE_LOOP);
glVertex2d(12.5*size4+x,40*size4+y);
glVertex2d(12.5*size4+x,65*size4+y);
glVertex2d(37.5*size4+x,65*size4+y);
glVertex2d(37.5*size4+x,40*size4+y);
glEnd();
glPointSize(5);
glBegin(GL_POINTS);
glVertex2d(18.75*size4+x,57*size4+y);
glVertex2d(31.25*size4+x,57*size4+y);
glEnd();
glColor3f(1.0,0.0,0.0);
glBegin(GL_TRIANGLES);
glVertex2d(20.75*size4+x,45*size4+y);
glVertex2d(25*size4+x,42*size4+y);
glVertex2d(29.25*size4+x,45*size4+y);
glEnd();

glBegin(GL_TRIANGLES);
glVertex2d(20*size4+x,65*size4+y);
glVertex2d(15*size4+x,75*size4+y);
glVertex2d(24*size4+x,65*size4+y);
glEnd();
glBegin(GL_TRIANGLES);
glVertex2d(24*size4+x,65*size4+y);
glVertex2d(33*size4+x,75*size4+y);
glVertex2d(28*size4+x,65*size4+y);
glEnd();

}

void reshape(int width, int height){
    /* window ro reshape when made it bigger or smaller*/
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //clip the windows so its shortest side is 2.0
   if(width>=height)
		gluOrtho2D(0,1366,0*(GLfloat)height/(GLfloat)width,768*(GLfloat)height/(GLfloat)width);
	else
		gluOrtho2D(0*(GLfloat)width/(GLfloat)height,1366*(GLfloat)width/(GLfloat)height,0,768);
    // set viewport to use the entire new window

    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}
void RenderScene(char *path,float x,float y,float xsize,float ysize)
{
    //Clears the window with current clearing color

       //Sets current drawing color
       //NOTE: Values are in float format, so 1.0f is full intensity
    glColor3f(0.0f, 0.0f, 0.0f);

    //Draws a square/rectangle with above drawing color
    glRectf(x, y,x+xsize, y+ysize);

    glEnable(GL_TEXTURE_2D);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    if (counter == 0)
    {
    tex_2d = SOIL_load_OGL_texture
    (
        path,
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_NTSC_SAFE_RGB
    );
    counter = 1;
    }

    glBindTexture(GL_TEXTURE_2D, tex_2d);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0); glVertex2f(x, y);
        glTexCoord2f(1.0, 0.0); glVertex2f(x, y+ysize);
        glTexCoord2f(1.0, 1.0); glVertex2f(x+xsize, y+ysize);
        glTexCoord2f(0.0, 1.0); glVertex2f(x+xsize, 0);
    glEnd();

    //Swaps the onscreen and offscreen buffers and flushes them
    //glutSwapBuffers();
    glDisable(GL_TEXTURE_2D);

}
void drawObject(char *path,float x,float y,float xsize,float ysize)
{
    //Clears the window with current clearing color

       //Sets current drawing color
       //NOTE: Values are in float format, so 1.0f is full intensity
    glColor3f(0.0f, 0.0f, 0.0f);

    //Draws a square/rectangle with above drawing color
    glRectf(x, y,x+xsize, y+ysize);

    glEnable(GL_TEXTURE_2D);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


    tex1_2d = SOIL_load_OGL_texture
    (
        path,
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_NTSC_SAFE_RGB
    );

    glBindTexture(GL_TEXTURE_2D, tex1_2d);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0); glVertex2f(x, y);
        glTexCoord2f(1.0, 0.0); glVertex2f(x, y+ysize);
        glTexCoord2f(1.0, 1.0); glVertex2f(x+xsize, y+ysize);
        glTexCoord2f(0.0, 1.0); glVertex2f(x+xsize, y);
    glEnd();

    //Swaps the onscreen and offscreen buffers and flushes them
    //glutSwapBuffers();
    glDisable(GL_TEXTURE_2D);

}
//Menu
float textPos1=0,textPos2=0,textPos3=0;int textmotionCount=0;
void textMotion(){
float diff1=900/SINSUM;
float diff2=-1000/SINSUM;
float diff3=-350/SINSUM;
if(textmotionCount<181){
textPos1+=diff1*sin(textmotionCount*DEG2RAD);
textPos2+=diff2*sin(textmotionCount*DEG2RAD);
textPos3+=diff3*sin(textmotionCount*DEG2RAD);
textmotionCount+=1;}
}
void rect(){
    if(spinning){
    glColor3f(1.0, 0.0, 0.0);
    //output(600,700,"Catch Me If You Can",2);
    glPushMatrix();
    glTranslatef(0,textPos3,0);
    drawObject("resources/Title.png",400,1000,610,34);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(textPos1,0,0);
    drawObject("resources/NewGame.png",-400,500,347,82);
    drawObject("resources/HighScore.png",-400,300,347,82);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(textPos2,0,0);
    drawObject("resources/Instructions.png",1500,400,347,82);
    drawObject("resources/Exit.png",1500,200,347,82);
    glPopMatrix();
    textMotion();
    //output(600,600,"1. New Game",1);
    //output(600,500,"2. Instructions",1);
    //output(600,400,"3. High Score",1);
    //output(600,300,"4. Exit",1);
    }

}


void clearscreen(){
glClear(GL_COLOR_BUFFER_BIT);glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();


    glPopMatrix();
    glutSwapBuffers();
    glFlush();
    }

    //Function for displaying Game screen
    float size2=25,sizeChicken=0.65,xegg[8];FallingEgg egg[8];

void eggDrawHandler(){

    int i;

    for(i=0;i<8;i++){
    if(egg[i].isEnabled()){
        if(!egg[i].collisionFlag)
        egg[i].setVar(xegg[i],650,size2);
        else
        egg[i].setVar(posX,650,size2);
        glPushMatrix();egg[i].draw();glPopMatrix();

    } }
}
void chickenDrawHandler(){
        glPushMatrix();
        //Chicken draw Call
        glTranslatef(chickenPos,0,0);
        drawChicken(0,620,sizeChicken);
        GLfloat eggColor[3]={1.0,1.0,1.0};
        glPopMatrix();

}
float sizeBasket=250;

char tempScore[30],tempScore1[30];
int scoreInt=0,highScoreInt=0;
void levelUp(){
    speed+=2;
}
void scoreUp(){
char score[30]="Score:",highScore[30]="HighScore:";
char scoreChar[10],highScoreChar[10];

if(eggBreaks>=3)
scoreInt=0;
else
scoreInt+=10;
if(scoreInt>highScoreInt)highScoreInt=scoreInt;
strcpy(tempScore,score);sprintf(scoreChar,"%d",scoreInt);
strcpy(tempScore1,highScore);sprintf(highScoreChar,"%d",highScoreInt);
strcat(tempScore,scoreChar);
strcat(tempScore1,highScoreChar);
//if(scoreInt==200)
    //levelUp();
}
void drawRectangle(float x1,float y1,float b,float l){
glColor3f(0.0,0.5,0.0);
glBegin(GL_POLYGON);
glVertex2d(x1,y1);
glVertex2d(x1,y1+l);
glVertex2d(x1+b,y1+l);
glVertex2d(x1+b,y1);
glEnd();
}
int overCounter=0,t=0;
void gameOverScreen(){
overCounter++;
drawRectangle(500,284,400,200);
output(643,384,"Game Over!!",1);
if(overCounter>=240)
{gameFlag=false;menuFlag=true;
for(t=0;t<8;t++)
    egg[t].attClear();
overCounter=0;
if(scoreInt>highScoreInt)
    highScoreInt=scoreInt;scoreInt=0;
    scoreUp();eggBreaks=0;textPos1=0;textPos2=0;textPos3=0;textmotionCount=0;counter=0;
}
}

void gameScreen(){
    glPushMatrix();
    RenderScene("resources/mario-underground-end11.png",0,0,1366,768);glPopMatrix();
    chickenDrawHandler();
    eggDrawHandler();

    glPushMatrix();
    glTranslatef(posX,posY,posZ);
    //Bakset draw call
    drawBasket(0,50,sizeBasket);
    glPopMatrix();

    output(1100,740,tempScore,1);
    output(1100,640,tempScore1,1);
    output(100,740,"Level:1",1);
    GLfloat grey[3]={0.8,0.8,0.8},red[3]={1.0,0.0,0.0};
    if(eggBreaks==0){
        missMark(500,700,grey);
        missMark(600,700,grey);
        missMark(700,700,grey);
    }
    if(eggBreaks==1){
        missMark(500,700,red);
        missMark(600,700,grey);
        missMark(700,700,grey);
    }
    if(eggBreaks==2){
        missMark(500,700,red);
        missMark(600,700,red);
        missMark(700,700,grey);
    }
    if(eggBreaks==3){
        missMark(500,700,red);
        missMark(600,700,red);
        missMark(700,700,red);
    }
    if(eggBreaks>=3){
        gameOverScreen();}
    glutSwapBuffers();

    glFlush();
}
float menuChickmove=0;
void menuChickMove(){
    if(menuChickmove>=181)
    menuChickmove=0;
    if(menuChickmove<181)
        menuChickPos=sin(menuChickmove*DEG2RAD)*20;
    menuChickmove+=2;
}

void menuScreen(){
    glPushMatrix();
    RenderScene("resources/WUUJj.png",0,0,1366,768);
    rect();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,menuChickPos,0);
    menuChicken(300,650,1.0);
    glPopMatrix();
    menuChickMove();
    glutSwapBuffers();
    glFlush();

}

void display(){
    //Clear Window
    //If in menu mode Display Menu


    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(menuFlag){
    menuScreen();
    }

    //If in Game mode Display game Screen
    else if(gameFlag){
    gameScreen();
    }

    else
    {clearscreen();
    }

}


float move_unit = 8;

//Keyboard Movement Controls
void keyboardown(int key, int x, int y)
{
    switch (key){
        case GLUT_KEY_RIGHT:
            rightButtonFlag=true;
            break;

        case GLUT_KEY_LEFT:
            leftButtonFlag=true;
        break;
        default:
         break;
    }

    glutPostRedisplay();
}
void keyboardup(int key, int x, int y)
{
    switch (key){
        case GLUT_KEY_RIGHT:
            rightButtonFlag=false;;
            break;

        case GLUT_KEY_LEFT:
            leftButtonFlag=false;
        break;
        default:
         break;
    }

    glutPostRedisplay();
}

void blank()
{
 glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 0.0);

}

//TImer function for realtime movement
float x=0.009,y[4],basketAcceleration=0.02,basketVelocity=0;int i=-1,j=0;
bool flag=true;
float value=1.5;
void basketHandler(){
//Handles the motion of the basket for catching
if(leftButtonFlag&&(posX>100)){
    if(basketVelocity>0)
        basketVelocity-=(0.05*value+basketAcceleration*value);
    else if(basketVelocity>-4*value)
        basketVelocity-=basketAcceleration*value;
    posX+=basketVelocity;
  }
  else if(rightButtonFlag&&(posX<1200)){
    if(basketVelocity<0)
        basketVelocity+=(0.05*value+basketAcceleration*value);
    else if(basketVelocity<4*value)
        basketVelocity+=basketAcceleration*value;
    posX+=basketVelocity*value;
  }
  else if((posX>1200)||(posX<100)){
  basketVelocity=0;
  }

  else{
    if(basketVelocity>0)
    basketVelocity/=(1.035+log(value)/50);
    else if(basketVelocity<0)
    basketVelocity/=(1.035+log(value)/50);
    posX+=basketVelocity*value;
  }

}


float chickenMotionVariable=0,diff=0,diff1=0;
float temp,theta=0;
void eggHandler(){
//Handles the motion of the Egg

for(j=0;j<8;j++){
  if(i==240*(j)){
        egg[(j-1)%8].setEnabled();
        egg[j].attClear();egg[j].setDisabled();


  }}
        for(j=0;j<8;j++){
  if(gameFlag&&egg[j].isEnabled()&&!egg[j].collisionFlag){egg[j].eggVelocity+=x;
    if(650+egg[j].getYPos()>50)
    egg[j].setYpos((egg[j].getYPos()-egg[j].eggVelocity));
    else if(!egg[j].yolkFlag)
    egg[j].setYolkFlag();
  }}


}

unsigned long long rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((unsigned long long)hi << 32) | lo;
}

void chickenHandler(){
if(i==1920/speed)
    i=0;

if(i==240/speed||i==0/speed||i==480/speed||i==720/speed||i==960/speed||i==1200/speed||i==1440/speed||i==1680/speed){
  moveChickenFlag=false;
        diff=xegg[(int)(i*speed/240)]-chickenPos-50;
        printf("%d %f %f %f %f\n",i,xegg[(int)(i/240*speed)],diff,egg[0].x,chickenPos);
        chickenMotionVariable=1;
        diff1=diff/SINSUM;temp=sizeChicken;
  }
  else{
  moveChickenFlag=true;
    if(chickenMotionVariable<180/speed){
        chickenPos+=diff1*sin(chickenMotionVariable*DEG2RAD);
        chickenMotionVariable+=1;
        theta=0;}
    else{
        theta+=3;
        sizeChicken=temp+temp*sin(theta*DEG2RAD)/3;}
  }



}

void collisionDetection(){
    for(j=0;j<8;j++){
        if(!egg[j].collisionFlag)
            if(egg[j].x-0.27+0.54*size2>=posX&&posX+0.22*sizeBasket>=egg[j].x-0.27){
                if(egg[j].y+0.7*size2+egg[j].getYPos()+0.7*size2>=50&&50+0.22*sizeBasket>=egg[j].y+egg[j].getYPos()+0.7*size2)
                    {
                    if(!egg[j].yolkFlag)
                        {
                        egg[j].setCollisionFlag();
                        scoreUp();
                        egg[j].posnBasket=egg[j].x-0.27-posX;
                        }
                    }
            }

    }

}
int k;int p=0;
void timer(int v) {
  if (spinning) {
    currentAngleOfRotation += 0.50;
    if (currentAngleOfRotation > 360.0) {
      currentAngleOfRotation -= 360.0;
    }
  }
  if(gameFlag){
if(i==0){
srand(rdtsc());
}
for(k=0;k<8;k++)
if(i==240*(k+1)/speed){
egg[((int)(i/240*speed+1))%8].randomSet=false;egg[((int)(i/240*speed+1))%8].attClear();}
for(k=0;k<8;k++){
    if(!egg[k].randomSet){
    printf("%d %d\t",k,xegg[k]);
    egg[k].randomSet=true;
    xegg[k]=rand()%1100+133;
}


    //Egg draw call
}
    chickenHandler();
    eggHandler();
    basketHandler();i++;
    collisionDetection();

}


  glutPostRedisplay();
  glutTimerFunc(1000/FPS, timer, v);
}

//Keyboard
void keyPress(unsigned char key,int x,int y){
switch(key){
    case 49:menuFlag=false;gameFlag=true;counter=0;
     break;
     case '4':exit(0);
}
}


int main(int argc, char** argv){

    //initialize mode and open a windows in upper left corner of screen
    //Windows tittle is name of program
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1366,768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Practice 1");
    glutDisplayFunc(display);
    init();//glutReshapeFunc(reshape);
    glutTimerFunc(100, timer, 0);
    glutSpecialUpFunc(keyboardup);
    glutKeyboardFunc(keyPress);
    glutSpecialFunc(keyboardown);
    glutMouseFunc(mouse);
    glutMainLoop();

}
