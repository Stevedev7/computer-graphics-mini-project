#include<windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <conio.h>
#include <time.h>

int treeLengths[] = {160,130,180,200};

enum GameState {START,RUNNING,COLLIDED};
enum PlayerState {STILL,RUN,JUMP,FALL,DEAD};

class Car{
private:
    float marginBottom = 50, marginLeft = 840, size = 1;
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
    void renderWheel(int x, int y, int r){
        float theta;
        glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i++){
            theta = i * (3.1416 / 180);
            glVertex2f(x + r * cos(theta), y + r * sin(theta));
        }
        glEnd();
    }

public:
    void render(){
        glBegin(GL_POLYGON);
        glColor3f(1, 0, 0);
        for(int i = 0; i < 10; i ++){
            glVertex2f(marginLeft + (carBody[i][0] * size), marginBottom + (carBody[i][1] * size));
        }
        glEnd();
        glLineWidth(4);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        for(int i = 0; i < 10; i ++){
            glVertex2f(marginLeft + (carBody[i][0] * size), marginBottom + (carBody[i][1] * size));
        }
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(0.65, 0.73, 0.96);
        for(int i = 10; i < 14; i++){
            glVertex2f(marginLeft + (carBody[i][0] * size), marginBottom + (carBody[i][1] * size));
        }
        glEnd();
        glLineWidth(4);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        for(int i = 10; i < 14; i ++){
            glVertex2f(marginLeft + (carBody[i][0] * size), marginBottom + (carBody[i][1] * size));
        }
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(0.65, 0.73, 0.96);
        for(int i = 14; i < 18; i++){
            glVertex2f(marginLeft + (carBody[i][0] * size), marginBottom + (carBody[i][1] * size));
        }
        glEnd();
        glLineWidth(4);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        for(int i = 14; i < 18; i++){
            glVertex2f(marginLeft + (carBody[i][0] * size), marginBottom + (carBody[i][1] * size));
        }
        glEnd();
        glColor3f(0,0,0);
        renderWheel(marginLeft + (carWheels[0][0] * size), marginBottom + (carWheels[0][1] * size), (carWheels[0][2] * size));
        renderWheel(marginLeft + (carWheels[1][0] * size), marginBottom + (carWheels[1][1] * size), (carWheels[1][2] * size));
        glColor3f(1, 1, 1);
        renderWheel(marginLeft + (carWheels[0][0] * size), marginBottom + (carWheels[0][1] * size), (carWheels[0][2] * size * 0.6));
        renderWheel(marginLeft + (carWheels[1][0] * size), marginBottom + (carWheels[1][1] * size), (carWheels[1][2] * size * 0.6));
        glEnd();
    }

};


class Aeroplane{

private:
    float marginBottom = 50, marginLeft = 640, size = 0.5;
    float body[71][2] = {
        {25, 144},
        {27, 148},
        {28, 151},
        {31, 152},
        {37, 158},
        {42, 160},
        {51, 168},
        {58, 170},
        {83, 180},
        {100, 187},
        {110, 195},
        {119, 202},
        {126, 205},
        {134, 209},
        {144, 214},
        {154, 217},
        {162, 219},
        {165, 220},
        {169, 220},
        {175, 220},
        {181, 220},
        {188, 219},
        {200, 218},
        {210, 216},
        {216, 215},
        {223, 213},
        {231, 211},
        {238, 210},
        {245, 209},
        {252, 206},
        {264, 201},
        {321, 196},
        {431, 186},
        {595, 180},
        {749, 171},
        {753, 171},
        {756, 168},
        {758, 165},
        {759, 163},
        {759, 129},
        {757, 126},
        {755, 124},
        {750, 122},
        {740, 121},
        {729, 118},
        {722, 117},
        {714, 116},
        {706, 115},
        {696, 115},
        {375, 111},
        {351, 111},
        {317, 112},
        {247, 113},
        {207, 114},
        {170, 116},
        {145, 118},
        {129, 119},
        {108, 120},
        {99, 122},
        {89, 123},
        {72, 124},
        {65, 126},
        {57, 127},
        {51, 128},
        {46, 130},
        {40, 131},
        {34, 133},
        {31, 136},
        {27, 138},
        {26, 142},
        {25, 144}
    };


    float windshield[47][2] = {
        {264, 201},
        {244, 194},
        {237, 192},
        {231, 190},
        {225, 188},
        {220, 187},
        {214, 186},
        {204, 184},
        {199, 182},
        {193, 181},
        {186, 180},
        {174, 179},
        {164, 178},
        {159, 179},
        {148, 178},
        {146, 179},
        {134, 180},
        {130, 181},
        {126, 182},
        {124, 183},
        {115, 183},
        {113, 184},
        {110, 185},
        {107, 186},
        {104, 187},
        {100, 187},
        {110, 195},
        {119, 202},
        {126, 205},
        {134, 209},
        {144, 214},
        {154, 217},
        {162, 219},
        {165, 220},
        {169, 220},
        {175, 220},
        {181, 220},
        {188, 219},
        {200, 218},
        {210, 216},
        {216, 215},
        {223, 213},
        {231, 211},
        {238, 210},
        {245, 209},
        {252, 206},
        {264, 201}
    };

    float wheelbox[6][2] = {
        {143, 118},
        {143, 96},
        {143, 94},
        {203, 91},
        {205, 93},
        {206, 112}
    };

    float wheelShaft[4][2] = {
        {168, 91},
        {168, 71},
        {176, 71},
        {176, 91},
    };

    float frontWheel [2][3] = {
        {171, 63, 16},
        {171, 63, 6}
    };

    float fin[7][2] = {
        {615, 181},
        {695, 306},
        {752, 302},
        {751, 286},
        {727, 287},
        {681, 176},
        {736, 172}
    };

    float wings[24][2] = {
        {270, 148},
        {338, 149},
        {398, 150},
        {562, 148},
        {589, 147},
        {628, 145},
        {646, 146},
        {665, 144},
        {689, 142},
        {698, 74},
        {689, 72},
        {646, 74},
        {549, 74},
        {546, 76},
        {543, 77},
        {545, 79},
        {549, 81},
        {555, 82},
        {565, 84},
        {581, 85},
        {599, 84},
        {627, 82},
        {651, 80},
        {672, 78}
    };


    float engine[19][2] = {
        {386, 117},
        {541, 76},
        {591, 73},
        {553, 71},
        {423, 71},
        {409, 71},
        {401, 74},
        {393, 76},
        {387, 78},
        {383, 80},
        {377, 84},
        {373, 87},
        {371, 91},
        {371, 97},
        {372, 103},
        {375, 108},
        {378, 112},
        {381, 114},
        {383, 116}

    };

    float rearWheelShaft[4][2] = {
        {571, 70},
        {571, 53},
        {578, 53},
        {578, 70}

    };

    float rearWheel[2][3] = {
        {572, 50, 16},
        {572, 50, 6}

    };

    float exhaust[4][2] = {
        {760, 166},
        {790, 160},
        {790, 135},
        {759, 127},
    };

    float rearFlap[16][2] = {
        {597, 160},
        {601, 163},
        {608, 164},
        {615, 166},
        {637, 166},
        {650, 167},
        {694, 162},
        {717, 160},
        {739, 158},
        {701, 156},
        {667, 155},
        {623, 156},
        {612, 157},
        {605, 157},
        {601, 156},
        {598, 158},
    };

    void renderBody(){
        glBegin(GL_POLYGON);
        glColor3f(0.56640625, 0.56640625, 0.56640625);
        for(int i = 0; i < 71; i ++){
            glVertex2f(marginLeft + (body[i][0] * size), marginBottom + (body[i][1] * size));
        }
        glEnd();
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        for(int i = 0; i < 71; i ++){
            glVertex2f(marginLeft + (body[i][0] * size), marginBottom + (body[i][1] * size));
        }
        glEnd();

        //exhaust
        glBegin(GL_POLYGON);
        glColor3f(0.265625, 0.265625, 0.265625);
        for(int i = 0; i < 4; i ++){
            glVertex2f(marginLeft + (exhaust[i][0] * size), marginBottom + (exhaust[i][1] * size));
        }
        glEnd();
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        for(int i = 0; i < 4; i ++){
            glVertex2f(marginLeft + (exhaust[i][0] * size), marginBottom + (exhaust[i][1] * size));
        }
        glEnd();
    }

    void renderWindShield(){
        glBegin(GL_POLYGON);
        glColor3f(0.58203125, 0.5234375, 0.36328125);
        for(int i = 0; i < 47; i ++){
            glVertex2f(marginLeft + (windshield[i][0] * size), marginBottom + (windshield[i][1] * size));
        }
        glEnd();
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        for(int i = 0; i < 47; i ++){
            glVertex2f(marginLeft + (windshield[i][0] * size), marginBottom + (windshield[i][1] * size));
        }
        glEnd();

    }

    void renderFin(){
        glBegin(GL_POLYGON);
        glColor3f(0.56640625, 0.56640625, 0.56640625);
        for(int i = 0; i < 6; i ++){
            glVertex2f(marginLeft + (fin[i][0] * size), marginBottom + (fin[i][1] * size));
        }
        glEnd();
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        for(int i = 0; i < 6; i ++){
            glVertex2f(marginLeft + (fin[i][0] * size), marginBottom + (fin[i][1] * size));
        }
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.53125, 0.53125, 0.53125);
        for(int i = 3; i < 7; i ++){
            glVertex2f(marginLeft + (fin[i][0] * size), marginBottom + (fin[i][1] * size));
        }
        glEnd();
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        for(int i = 3; i < 7; i ++){
            glVertex2f(marginLeft + (fin[i][0] * size), marginBottom + (fin[i][1] * size));
        }
        glEnd();
    }

    void renderWings(){
        glBegin(GL_POLYGON);
        glColor3f(0.484375, 0.484375, 0.484375);
        for(int i = 0; i < 15; i ++){
            glVertex2f(marginLeft + (wings[i][0] * size), marginBottom + (wings[i][1] * size));
        }
        glEnd();
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        for(int i = 0; i < 15; i ++){
            glVertex2f(marginLeft + (wings[i][0] * size), marginBottom + (wings[i][1] * size));
        }
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.3125, 0.3125, 0.3125);
        for(int i = 9; i < 24; i ++){
            glVertex2f(marginLeft + (wings[i][0] * size), marginBottom + (wings[i][1] * size));
        }
        glEnd();
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        for(int i = 9; i < 24; i ++){
            glVertex2f(marginLeft + (wings[i][0] * size), marginBottom + (wings[i][1] * size));
        }
        glEnd();

        // rear flaps

        glBegin(GL_POLYGON);
        glColor3f(0.3125, 0.3125, 0.3125);
        for(int i = 0; i < 16; i ++){
            glVertex2f(marginLeft + (rearFlap[i][0] * size), marginBottom + (rearFlap[i][1] * size));
        }
        glEnd();
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        for(int i = 0; i < 16; i ++){
            glVertex2f(marginLeft + (rearFlap[i][0] * size), marginBottom + (rearFlap[i][1] * size));
        }
        glEnd();
    }

    void renderEngine(){
        glBegin(GL_POLYGON);
        glColor3f(0, 0, 1);
        for(int i = 0; i < 19; i ++){
            glVertex2f(marginLeft + (engine[i][0] * size), marginBottom + (engine[i][1] * size));
        }
        glEnd();
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        for(int i = 0; i < 19; i ++){
            glVertex2f(marginLeft + (engine[i][0] * size), marginBottom + (engine[i][1] * size));
        }
        glEnd();
    }

public:
    void render(){
        renderBody();
        renderWindShield();
        renderFin();
        renderWings();
        // renderEngine();
        glFlush();
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
Aeroplane aero;

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

    glBegin(GL_POLYGON);
    glVertex2f(1080,200);
    glVertex2f(-30,200);
    glVertex2f(-30,20);
    glVertex2f(1080,20);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(100,200);
    glVertex2f(320,200);
    glVertex2f(320,210);
    glVertex2f(100,210);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(120,210);
    glVertex2f(260,210);
    glVertex2f(260,220);
    glVertex2f(120,220);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(640,200);
    glVertex2f(960,200);
    glVertex2f(960,210);
    glVertex2f(640,210);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(680,210);
    glVertex2f(860,210);
    glVertex2f(860,220);
    glVertex2f(680,220);
    glEnd();

    int i;
    for(i=-40;i<=1100;i+=23){
        int height = treeLengths[i%4];

        glColor3f(.02,0.4,0.17);
        glBegin(GL_TRIANGLES);
        glVertex2f(i-20,15);
        glVertex2f(i+20,15);
        glVertex2f(i,height);
        glEnd();
    }

    dino.renderBody();


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

    car.render();
    aero.render();
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
