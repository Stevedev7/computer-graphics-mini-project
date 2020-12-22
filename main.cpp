#include<windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

enum GameState {START,RUNNING,COLLIDED};
enum PlayerState {STILL,RUN,JUMP,FALL,DEAD};


PlayerState playerState = STILL;

class Dinosour{

    PlayerState playerState = STILL;

    void renderBody(){

    }

    void renderLegs(){

    }
};

float jumpHeight = 0;
float MAX_HEIGHT = 240;

void init(){

    srand(time(NULL));

    glutInitWindowSize(1080,720);
    glutCreateWindow("Dino game");
    glClearColor(1,.62,0.129,0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-30,1080,-30,720);
}

void display(){

    glColor3f(1,0.55,0.156);

    glBegin(GL_POLYGON);
    glVertex2f(-30,500);
    glVertex2f(1080,500);
    glVertex2f(1080,400);
    glVertex2f(-30,400);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0,510);
    glVertex2f(140,510);
    glVertex2f(140,500);
    glVertex2f(0,500);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(20,520);
    glVertex2f(100,520);
    glVertex2f(100,510);
    glVertex2f(20,510);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(40,530);
    glVertex2f(80,530);
    glVertex2f(80,520);
    glVertex2f(40,520);
    glEnd();

    // break

    glBegin(GL_POLYGON);
    glVertex2f(350,510);
    glVertex2f(460,510);
    glVertex2f(460,500);
    glVertex2f(350,500);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(360,520);
    glVertex2f(380,520);
    glVertex2f(380,510);
    glVertex2f(360,510);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(420,520);
    glVertex2f(440,520);
    glVertex2f(440,510);
    glVertex2f(420,510);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(700,510);
    glVertex2f(960,510);
    glVertex2f(960,500);
    glVertex2f(700,500);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(840,520);
    glVertex2f(920,520);
    glVertex2f(920,510);
    glVertex2f(840,510);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(720,520);
    glVertex2f(800,520);
    glVertex2f(800,510);
    glVertex2f(720,510);
    glEnd();

    glColor3f(1,.97,.87);

    glBegin(GL_POLYGON);
    glVertex2f(470,560);
    glVertex2f(540,560);
    glVertex2f(540,630);
    glVertex2f(470,630);
    glEnd();

    glColor3f(1,0.49,0.17);

    glBegin(GL_POLYGON);
    glVertex2f(100,400);
    glVertex2f(320,400);
    glVertex2f(320,410);
    glVertex2f(100,410);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(120,410);
    glVertex2f(260,410);
    glVertex2f(260,420);
    glVertex2f(120,420);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(640,400);
    glVertex2f(960,400);
    glVertex2f(960,410);
    glVertex2f(640,410);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(680,410);
    glVertex2f(860,410);
    glVertex2f(860,420);
    glVertex2f(680,420);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-30,400);
    glVertex2f(1080,400);
    glVertex2f(1080,300);
    glVertex2f(-30,300);
    glEnd();

    glColor3f(1,0.35,0.22);

    glBegin(GL_POLYGON);
    glVertex2f(-30,300);
    glVertex2f(1080,300);
    glVertex2f(1080,100);
    glVertex2f(-30,100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-30,330);
    glVertex2f(40,330);
    glVertex2f(40,300);
    glVertex2f(-30,300);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-30,320);
    glVertex2f(80,320);
    glVertex2f(80,300);
    glVertex2f(-30,300);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-30,310);
    glVertex2f(110,310);
    glVertex2f(110,300);
    glVertex2f(-30,300);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(500,310);
    glVertex2f(660,310);
    glVertex2f(660,300);
    glVertex2f(500,300);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(510,320);
    glVertex2f(640,320);
    glVertex2f(640,310);
    glVertex2f(510,310);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(560,330);
    glVertex2f(610,330);
    glVertex2f(610,320);
    glVertex2f(560,320);
    glEnd();

    glColor3f(.44,0.20,0.27);

    /*
    glBegin(GL_POLYGON);
    glVertex2f(-30,200);
    glVertex2f(1080,200);
    glVertex2f(1080,20);
    glVertex2f(-30,20);
    glEnd();
    */

        int buildingStart = -30;
        int buildingHeight = 0;
        int buildingWidth = 0;

    for(int i=0;buildingStart<=1080;++i){
        buildingWidth = (10 + rand()% 50);
        buildingHeight = (100 + rand()% 100);

        glBegin(GL_POLYGON);
        glVertex2f(buildingStart,20);
        glVertex2f(buildingStart+buildingWidth,20);
        glVertex2f(buildingStart+buildingWidth,buildingHeight);
        glVertex2f(buildingStart,buildingHeight);
        glEnd();

        buildingStart += buildingWidth;
    }

    glColor3f(0,0,0);
    // glColor3f(.019,.62,.50);

    glBegin(GL_POLYGON);
    glVertex2f(50,110+jumpHeight);
    glVertex2f(50,130+jumpHeight);
    glVertex2f(60,130+jumpHeight);
    glVertex2f(60,110+jumpHeight);
    glEnd();

   // glColor3f(.019,.62,.40);

    glBegin(GL_POLYGON);
    glVertex2f(50,110+jumpHeight);
    glVertex2f(70,110+jumpHeight);
    glVertex2f(70,100+jumpHeight);
    glVertex2f(50,100+jumpHeight);
    glEnd();

 //   glColor3f(.019,.62,.30);

    glBegin(GL_POLYGON);
    glVertex2f(50,100+jumpHeight);
    glVertex2f(80,100+jumpHeight);
    glVertex2f(80,70+jumpHeight);
    glVertex2f(50,70+jumpHeight);
    glEnd();

 //   glColor3f(.019,.62,.20);

    glBegin(GL_POLYGON);
    glVertex2f(60,90+jumpHeight);
    glVertex2f(140,90+jumpHeight);
    glVertex2f(140,60+jumpHeight);
    glVertex2f(60,60+jumpHeight);
    glEnd();

  //  glColor3f(.019,.62,.10);

    glBegin(GL_POLYGON);
    glVertex2f(70,70+jumpHeight);
    glVertex2f(150,70+jumpHeight);
    glVertex2f(150,50+jumpHeight);
    glVertex2f(70,50+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(80,60+jumpHeight);
    glVertex2f(120,60+jumpHeight);
    glVertex2f(120,40+jumpHeight);
    glVertex2f(80,40+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(90,40+jumpHeight);
    glVertex2f(110,40+jumpHeight);
    glVertex2f(110,50+jumpHeight);
    glVertex2f(90,50+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(90,30+jumpHeight);
    glVertex2f(100,30+jumpHeight);
    glVertex2f(100,40+jumpHeight);
    glVertex2f(90,40+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(90,30+jumpHeight);
    glVertex2f(110,30+jumpHeight);
    glVertex2f(110,20+jumpHeight);
    glVertex2f(90,20+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(125,60+jumpHeight);
    glVertex2f(135,60+jumpHeight);
    glVertex2f(135,20+jumpHeight);
    glVertex2f(125,20+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(125,30+jumpHeight);
    glVertex2f(145,30+jumpHeight);
    glVertex2f(145,20+jumpHeight);
    glVertex2f(125,20+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(100,100+jumpHeight);
    glVertex2f(160,100+jumpHeight);
    glVertex2f(160,70+jumpHeight);
    glVertex2f(100,70+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(110,110+jumpHeight);
    glVertex2f(170,110+jumpHeight);
    glVertex2f(170,80+jumpHeight);
    glVertex2f(110,80+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(120,120+jumpHeight);
    glVertex2f(170,120+jumpHeight);
    glVertex2f(170,110+jumpHeight);
    glVertex2f(120,110+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(130,150+jumpHeight);
    glVertex2f(170,150+jumpHeight);
    glVertex2f(170,120+jumpHeight);
    glVertex2f(130,120+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(170,150+jumpHeight);
    glVertex2f(190,150+jumpHeight);
    glVertex2f(190,120+jumpHeight);
    glVertex2f(170,120+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(180,160+jumpHeight);
    glVertex2f(140,160+jumpHeight);
    glVertex2f(140,150+jumpHeight);
    glVertex2f(180,150+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(170,112+jumpHeight);
    glVertex2f(185,112+jumpHeight);
    glVertex2f(185,117+jumpHeight);
    glVertex2f(170,117+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(170,100+jumpHeight);
    glVertex2f(180,100+jumpHeight);
    glVertex2f(180,90+jumpHeight);
    glVertex2f(170,90+jumpHeight);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(180,100+jumpHeight);
    glVertex2f(190,100+jumpHeight);
    glVertex2f(190,85+jumpHeight);
    glVertex2f(180,85+jumpHeight);
    glEnd();

    glColor3f(1,.62,0.129);

    glBegin(GL_POLYGON);
    glVertex2f(157,150+jumpHeight);
    glVertex2f(157,145+jumpHeight);
    glVertex2f(150,145+jumpHeight);
    glVertex2f(150,150+jumpHeight);
    glEnd();

    glColor3f(.34,.52,.69);
    glBegin(GL_POLYGON);
    glVertex2f(1080,-30);
    glVertex2f(-30,-30);
    glVertex2f(-30,20);
    glVertex2f(1080,20);
    glEnd();

    float markerStart = -70;

    for(int i=0;markerStart<=1080;i+=1,markerStart+=75)
    {
        glColor3f(1,1,1);
        glBegin(GL_POLYGON);
        glVertex2f(20+markerStart,-7);
        glVertex2f(markerStart+75,-7);
        glVertex2f(markerStart+75,-3);
        glVertex2f(20+markerStart,-3);
        glEnd();

    }
    glFlush();
}

void keyboard(unsigned char key,int x,int y){

    printf("%c",key);

    if(key == ' ' && playerState != JUMP && playerState != FALL)
        playerState = JUMP;
}

void idle(){
    if(playerState == JUMP && jumpHeight >= MAX_HEIGHT){
        jumpHeight -= .5;
        playerState = FALL;
    }

    if(playerState == FALL && jumpHeight <= 0){
        jumpHeight = 0;
        playerState = RUN;
    }

    if(playerState == JUMP){
        jumpHeight += .5;
        glutPostRedisplay();
    }

    if(playerState == FALL){
        jumpHeight -= .5;
        glutPostRedisplay();
    }

}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
