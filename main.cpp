// #include<windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <conio.h>
#include <time.h>

enum GameState {START,RUNNING,COLLIDED};
enum PlayerState {STILL,RUN,JUMP,FALL,DEAD};

class Car{
private:
    int marginBottom = 50, marginLeft = 1280;
    float carBody[18][2] = {
        {0, 0},
        {0, 3},
        {7.5, 12},
        {45, 15},
        {105, 37.5},
        {180, 37.5},
        {202.5, 22.5},
        {225, 18},
        {229.5, 10.5},
        {229.5, 0},
        //front windshield
        {56, 17},
        {101, 33},
        {137, 33},
        {137, 17},
        //rear windshield
        {140, 17},
        {140, 33},
        {172.5, 33},
        {192, 17}
    };

    float carWheels[2][3] = {
        {60, 0, 12},
        {202.5, 2, 14}
    };

public:
    void render(){
        glBegin(GL_POLYGON);
        glColor3f(1, 0, 0);
        for(int i = 0; i < 10; i ++){
            glVertex2f(marginLeft + carBody[i][0], marginBottom + carBody[i][1]);
        }
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(0.65, 0.73, 0.96);
        for(int i = 10; i < 14; i++){
            glVertex2f(marginLeft + carBody[i][0], marginBottom + carBody[i][1]);
        }
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(0.65, 0.73, 0.96);
        for(int i = 14; i < 18; i++){
            glVertex2f(marginLeft + carBody[i][0], marginBottom + carBody[i][1]);
        }
        glEnd();
        renderWheel(marginLeft + carWheels[0][0], marginBottom + carWheels[0][1], carWheels[0][2]);
        renderWheel(marginLeft + carWheels[1][0], marginBottom + carWheels[1][1], carWheels[1][2]);
        glEnd();
        glFlush();
    }

    void renderWheel(int x, int y, int r){
        float theta;
        glBegin(GL_POLYGON);
        glColor3f(0,0,0);
        for(int i = 0; i < 360; i++){
            theta = i * (3.1416 / 180);
            glVertex2f(x + r * cos(theta), y + r * sin(theta));
        }
        glEnd();
    }

};

class Dinosour{

private:

    PlayerState playerState = STILL;

    float jumpHeight = 0;
    float bco[21][2][2] = {{{50,110},{60,130}},{{50,110},{70,100}},{{50,100},{80,70}},{{60,90},{140,60}},{{70,70},{150,50}},
    {{80,60},{120,40}},{{90,40},{110,50}},{{90,40},{100,30}},{{90,30},{110,20}},{{125,60},{135,20}},{{125,20},{145,30}},{{100,100},{160,70}},
    {{110,110},{170,80}},{{170,120},{120,110}},{{130,120},{170,150}},{{170,150},{190,120}},{{180,160},{140,150}},{{170,112},{185,117}},
    {{170,100},{180,90}},{{180,100},{190,85}},{{157,150},{150,145}}};

    bool rightFoot = true;

    public:

    void renderBody(){
    int i;

    glColor3f(0,0,0);
    for(i=0;i<20;++i){

        if(!(i>5 && i<11)){
            glBegin(GL_POLYGON);
            glVertex2f(bco[i][0][0],bco[i][1][1]+jumpHeight);
            glVertex2f(bco[i][1][0],bco[i][1][1]+jumpHeight);
            glVertex2f(bco[i][1][0],bco[i][0][1]+jumpHeight);
            glVertex2f(bco[i][0][0],bco[i][0][1]+jumpHeight);
            glEnd();
        }
    }

    glColor3f(1,.62,0.129);

    glBegin(GL_POLYGON);
    glVertex2f(bco[i][0][0],bco[i][1][1]+jumpHeight);
    glVertex2f(bco[i][1][0],bco[i][1][1]+jumpHeight);
    glVertex2f(bco[i][1][0],bco[i][0][1]+jumpHeight);
    glVertex2f(bco[i][0][0],bco[i][0][1]+jumpHeight);
    glEnd();

    renderLegs();

    }

    void renderLegs(){
        int i=0;
        for(i=6;i<11;i++){
            glColor3f(0,0,0);

            bool liftFoot = (i > 5 && i < 9 && rightFoot) | (i > 8 && i < 11 && !rightFoot);
            float liftHeight = jumpHeight + (liftFoot?10:0);

            glBegin(GL_POLYGON);
            glVertex2f(bco[i][0][0],bco[i][1][1]+liftHeight);
            glVertex2f(bco[i][1][0],bco[i][1][1]+liftHeight);
            glVertex2f(bco[i][1][0],bco[i][0][1]+liftHeight);
            glVertex2f(bco[i][0][0],bco[i][0][1]+liftHeight);
            glEnd();

        }

        if(playerState != STILL)
            if(rightFoot)
                rightFoot = false;
            else
                rightFoot = true;
    }

    void setJumpHeight(float height){
        jumpHeight = height;
    }

    float getJumpHeight(){
        return jumpHeight;
    }

    void setPlayerState(PlayerState state){
        playerState = state;
    }

    PlayerState getPlayerState(){
        return playerState;
    }
};

Dinosour dino;
Car car;

float jumpHeight = 0;
float MAX_HEIGHT = 240;

void init(){

    srand(time(NULL));

    glutInitWindowSize(1280,720);
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

    dino.renderBody();
    car.render();

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

    if(key == ' ' && dino.getPlayerState() != JUMP && dino.getPlayerState() != FALL){
        dino.setPlayerState(JUMP);
    }

    if(dino.getPlayerState() == STILL){
            dino.setPlayerState(RUN);
    }
}

void idle(){
    if(dino.getPlayerState() == JUMP && dino.getJumpHeight() >= MAX_HEIGHT){
        dino.setJumpHeight(dino.getJumpHeight() + .8);
        dino.setPlayerState(FALL);
    }

    if(dino.getPlayerState() == FALL && dino.getJumpHeight() <= 0){
        dino.setJumpHeight(0);
        dino.setPlayerState(RUN);
    }

    if(dino.getPlayerState() == JUMP){
        dino.setJumpHeight(dino.getJumpHeight() + .8);
        glutPostRedisplay();
    }

    if(dino.getPlayerState() == FALL){
        dino.setJumpHeight(dino.getJumpHeight() - .8);
        glutPostRedisplay();
    }

    if(dino.getPlayerState() == RUN)
        glutPostRedisplay();
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
