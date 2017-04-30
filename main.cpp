/*CG Mini Project*/
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<string.h>
#include <GL/glut.h>
#include<set>
#include <iostream>
#include<time.h>
#include "SOIL.h"
#define DEG2RAD 0.01745329251
#define SINSUM 114.5886501
using namespace std;
static bool spinning = true,menuFlag=true,gameFlag=false,yolkFlag=false,leftButtonFlag=false,rightButtonFlag=false,diffNeg=false,moveChickenFlag=false,instrFlag=false,instrFullFlag=false,aboutFlag=false,aboutFillFlag=false,highScoreFlag=false;
GLuint tex_2d,tex1_2d,tex2_2d[30];
static GLfloat currentAngleOfRotation = 0.0;
static int FPS = 120;
GLfloat rotation = 90.0;
char scankey;
int counter=0,width, height,eggBreaks=0,value=2,chickenheadCount=0,chickNum=20,scankeyCount=0;
float posX = 0, posY = 0, posZ = 0,chickenPos=0,speed=1,menuChickPos,instrSize=0.0;

set<pair <string,int> > highScoreList;
void drawObject(int num,float x,float y,float xsize,float ysize)
{
    //Clears the window with current clearing color

       //Sets current drawing color
       //NOTE: Values are in float format, so 1.0f is full intensity
    glColor3f(0.0f, 0.0f, 0.0f);

    //Draws a square/rectangle with above drawing color

    glEnable(GL_TEXTURE_2D);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, tex2_2d[num]);

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
        this->drawEgg(0.38,0.35,eggColor);
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
   drawObject(9,x,y,radiusX*this->eggSize,radiusY*this->eggSize);


}
void drawYolk(){
    float sizeOuter=35,sizeInner=23;
    drawObject(10,x,y,sizeOuter,sizeInner);

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


void load_textures(){int i;
char path[100][50]={"resources/WUUJj.png","resources/cloud.png","resources/Title.png"
,"resources/NewGame.png","resources/HighScore.png","resources/Instructions.png"
,"resources/Exit.png","resources/Basket.png","resources/abstract_bird.png"
,"resources/white-egg-md.png","resources/Yolk.png","resources/ground.png"
,"resources/wrong.png","resources/wrong1.png","resources/fence.png"
,"resources/GameOver.png","resources/Levelup.png","resources/About.png"
,"resources/Instructionspage.png","resources/Aboutbutton.png","resources/chicken/chicken-1.png"
,"resources/chicken/chicken-2.png","resources/chicken/chicken-3.png","resources/chicken/chicken-4.png"
,"resources/highScorePage.png"};
for(i=0;i<25;i++)
tex2_2d[i] = SOIL_load_OGL_texture
    (
        path[i],
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_NTSC_SAFE_RGB
    );
    glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//............BIRD...............
//texture 1 active
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



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

void missMark(float x,float y,GLfloat* color){

if(color[0]==1.0)
drawObject(12,x,y,60,50);
else
drawObject(13,x,y,60,50);
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
void RenderScene(int num,float x,float y,float xsize,float ysize)
{
    //Clears the window with current clearing color

       //Sets current drawing color
       //NOTE: Values are in float format, so 1.0f is full intensity
    glColor3f(0.0f, 0.0f, 0.0f);

    //Draws a square/rectangle with above drawing color
    glRectf(x, y,x+xsize, y+ysize);

    glEnable(GL_TEXTURE_2D);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


    glBindTexture(GL_TEXTURE_2D, tex2_2d[num]);

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
    drawObject(2,400,1000,610,100);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(textPos1,0,0);
    drawObject(3,-400,500,347,82);
    drawObject(4,-400,300,347,82);
    drawObject(6,-400,100,347,82);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(textPos2,0,0);
    drawObject(5,1500,400,347,82);
    drawObject(19,1500,200,347,82);
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
        egg[i].setVar(xegg[i],650,size2+25);
        else
        egg[i].setVar(posX,650,size2+25);
        glPushMatrix();egg[i].draw();glPopMatrix();

    } }
}



void chickenDrawHandler(){
        chickenheadCount++;
        if(chickenheadCount>180&&chickenheadCount<241);
        else if(chickenheadCount>=241)
        chickenheadCount=0;
        else if(chickenheadCount==15||chickenheadCount==105)
        chickNum=20;
        else if(chickenheadCount==30||chickenheadCount==90||chickenheadCount==120||chickenheadCount==180)
        chickNum=21;
        else if(chickenheadCount==45||chickenheadCount==75||chickenheadCount==135||chickenheadCount==165)
        chickNum=22;
        else if(chickenheadCount==60||chickenheadCount==150)
        chickNum=23;
        glPushMatrix();
        //Chicken draw Call
        glTranslatef(chickenPos,0,0);
        //drawChicken(0,620,sizeChicken);
        if(diffNeg)
            drawObject(chickNum,0,620,150*sizeChicken,120*sizeChicken);
        else
            drawObject(chickNum,150*sizeChicken,620,-150*sizeChicken,120*sizeChicken);
        glPopMatrix();

}


float sizeBasket=250;
int level=0;
char tempScore[30],tempScore1[30];
int scoreInt=0,highScoreInt=0;int leveldisp=-1;
void levelUp(){
    FPS+=40;
    value-=0.000000001;
    level++;
    eggBreaks=0;leveldisp=0;
}
float leveldispPos=1500,difflevel=-1000/SINSUM;
void scoreUp(){
char score[30]="Score:",highScore[30]="HighScore:";
char scoreChar[10],highScoreChar[10];

if(eggBreaks>=3)
scoreInt=0;
else
scoreInt+=10;
if(scoreInt==200&&level==0)
    levelUp();
//if(scoreInt==280&&level==1)
    //levelUp();

if(scoreInt>highScoreInt){highScoreInt=scoreInt;highScoreFlag=true;}
strcpy(tempScore,score);sprintf(scoreChar,"%d",scoreInt);
strcpy(tempScore1,highScore);sprintf(highScoreChar,"%d",highScoreInt);
strcat(tempScore,scoreChar);
strcat(tempScore1,highScoreChar);
//if(scoreInt==200)
    //levelUp();
}


int overCounter=0,t=0;float movevariable=0,diff2=-1000/SINSUM,posScreen=1500;
void gameOverScreen(){
overCounter++;
drawObject(15,posScreen,768/2.0-45,606*0.5,336*0.5);
if(movevariable<181)
{
posScreen+=diff2*sin((movevariable++)*DEG2RAD);
}
//drawRectangle(500,284,400,200);
//output(643,384,"Game Over!!",1);
if(overCounter>=240)
{gameFlag=false;menuFlag=true;
for(t=0;t<8;t++)
    egg[t].attClear();
overCounter=0;
scoreInt=0;

    scoreUp();eggBreaks=0;textPos1=0;textPos2=0;textPos3=0;textmotionCount=0;counter=0;FPS=120;value=2;posScreen=1500;movevariable=0;leveldispPos=1500;leveldisp=-1;
}
}

void gameScreen(){
    glPushMatrix();drawObject(1,0,68,1366,700);glPopMatrix();
    drawObject(11,-1000,0,4000,68);
    drawObject(11,-1000,567,4000,68);
    if(leveldisp>=0&&leveldispPos>=-100){
    drawObject(16,leveldispPos,768/2.0-45,356*0.5,95*0.5);
    leveldispPos+=difflevel*sin((leveldisp++)*DEG2RAD);
    }
    if(leveldisp>=181)leveldisp=-1;
    eggDrawHandler();
    chickenDrawHandler();
   // drawObject(14,0,620,1366,100);
    glPushMatrix();
    glTranslatef(posX,posY,posZ);
    //Bakset draw call
    //drawBasket(0,50,sizeBasket);
    drawObject(7,0,50,0.22*sizeBasket,0.32*sizeBasket);
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


void aboutMenu(){
if(aboutFlag){
    if(!aboutFillFlag&&instrSize<=0.6)
        instrSize+=0.004166667;
    if(aboutFillFlag&&instrSize>=0)
        instrSize-=0.004166667;
    if(instrSize<0.001){instrSize=0;
        aboutFlag=false;}
    glPushMatrix();
    drawObject(17,683-1366*instrSize/2.0,384-768*instrSize/2.0,1366*instrSize,768*instrSize);
    glPopMatrix();
    }
    }


void instructionMenu(){

    if(instrFlag){
    if(!instrFullFlag&&instrSize<=0.6)
        instrSize+=0.004166667;
    if(instrFullFlag&&instrSize>=0)
        instrSize-=0.004166667;
    if(instrSize<0.001){instrSize=0;
        instrFlag=false;}
    glPushMatrix();
    drawObject(18,683-1366*instrSize/2.0,384-768*instrSize/2.0,1366*instrSize,768*instrSize);
    glPopMatrix();
    }}
    string name;
void highScoreMenu(){
drawObject(24,171,96,1024,576);
if(scankey==8&&scankeyCount==0)
{name.erase(name.size()-1);}
else if(scankey!=0&&scankeyCount==0)
name.append(&scankey);
output(500,450,name.c_str(),2);
if(scankey==13){
highScoreFlag=false;
pair<string,int> highScorePair(name,highScoreInt);
highScoreList.insert(highScorePair);
cout<<highScorePair.first<<endl<<highScorePair.second<<endl;
}
char score[30];
sprintf(score,"%d",highScoreInt);
output(600,400,score,2);

scankeyCount++;
}

void menuScreen(){
    glPushMatrix();
    RenderScene(0,0,0,1366,768);
    rect();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,menuChickPos,0);
    drawObject(9,300,650,300*0.3,258*0.3);
    //menuChicken(300,650,1.0);
    glPopMatrix();
    menuChickMove();
    instructionMenu();
    aboutMenu();
    if(highScoreFlag)
        highScoreMenu();
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
float x=0.015,y[4],basketAcceleration=0.02,basketVelocity=0;int i=-1,j=0;
bool flag=true;

void basketHandler(){
//Handles the motion of the basket for catching
if(leftButtonFlag&&(posX>100)){
    if(basketVelocity>0)
        basketVelocity-=(0.05*value+basketAcceleration*value);
    else if(basketVelocity>-4.0*value)
        basketVelocity-=basketAcceleration*value;
    posX+=basketVelocity;
  }
  else if(rightButtonFlag&&(posX<1200)){
    if(basketVelocity<0)
        basketVelocity+=(0.05*value+basketAcceleration*value);
    else if(basketVelocity<4.0*value)
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
        if(diff<0)diffNeg=true;else diffNeg=false;
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
if(menuFlag);

  glutPostRedisplay();
  glutTimerFunc(1000/FPS, timer, v);
}


//Keyboard
void keyPress(unsigned char key,int x,int y){
switch(key){
    case 49:menuFlag=false;gameFlag=true;counter=0;
     break;
     case '2':if(!instrFlag){instrFlag=true;instrFullFlag=false;}break;
     case 27:if(instrFlag)instrFullFlag=true;if(aboutFlag)aboutFillFlag=true;break;
     case '4':if(!aboutFlag){aboutFlag=true;aboutFillFlag=false;}break;
     case '5':exit(0);
}
if(highScoreFlag){
    if((key>64&&key<91)||(key>96&&key<128)||key==8||key==13)
        {scankey=key;scankeyCount=0;}
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
    load_textures();
    init();//glutReshapeFunc(reshape);
    glutTimerFunc(100, timer, 0);
    glutSpecialUpFunc(keyboardup);
    glutKeyboardFunc(keyPress);
    glutSpecialFunc(keyboardown);
    glutMouseFunc(mouse);
    glutMainLoop();
}
