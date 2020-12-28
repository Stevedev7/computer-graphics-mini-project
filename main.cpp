// #include<windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <thread>
#include <time.h>


int treeLengths[] = {160,130,180,200};
enum GameState {START,RUNNING,COLLIDED};
enum PlayerState {STILL,RUN,JUMP,FALL,DEAD};

class Car{
private:
    float marginBottom = 30, marginLeft = 10000, size = 0.8;
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

    void setMargin(float margin){
        marginLeft = margin;
    }

    float getMargin(){
        return marginLeft;
    }

};


class Aeroplane{

private:
    float marginBottom = 100, marginLeft = 6000, size = 0.2;
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

    void setMarginBottom(float margin){
        marginBottom = margin;
    }

    void setMarginLeft(float margin){
        marginLeft = margin;
    }

    float getMarginLeft(){
        return marginLeft;
    }

    float getMarginBottom(){
        return marginBottom;
    }
};


class BackgroundGraphics{
    // {{},{},{}}
    float bcol[5][3] = {{1,0.55,0.156},{1,.97,.87},{1,0.49,0.17},{1,0.35,0.22},{.44,0.20,0.27}};
    float bco[28][3][2] = {{{0},{-30,500},{1080,400}},{{0},{0,510},{140,510}},{{0},{20,520},{100,510}},{{0},{40,530},{80,520}},{{0},{350,510},{460,500}},
    {{0},{360,520},{380,510}},{{0},{420,520},{440,510}},{{0},{700,510},{960,500}},{{0},{840,520},{920,510}},{{0},{720,520},{800,510}},
    {{1},{470,560},{540,630}},
    {{2},{100,400},{320,410}},{{2},{120,410},{260,420}},{{2},{640,400},{960,410}},{{2},{680,410},{860,420}},{{2},{-30,400},{1080,300}},
    {{3},{-30,300},{1080,100}},{{3},{-30,330},{40,300}},{{3},{-30,320},{80,300}},{{3},{-30,310},{110,300}},{{3},{500,310},{660,300}},
    {{3},{510,320},{640,310}},{{3},{560,330},{610,320}},
    {{4},{1080,200},{-30,20}},{{4},{100,200},{320,210}},{{4},{120,210},{260,220}},{{4},{640,200},{960,210}},{{4},{680,210},{860,220}}
    };
    float leftMargin = -1080;

    void renderTree(){
        int i;
        for(i=leftMargin;i<=1400;i+=43){
            int height = treeLengths[i%4];

            glColor3f(.02,0.4,0.17);
            glBegin(GL_TRIANGLES);
            glVertex2f(i-30,15);
            glVertex2f(i+30,15);
            glVertex2f(i,height);
            glEnd();
        }

        leftMargin = leftMargin<-1080?-96:leftMargin-.1;
    }

    void renderRoad(){

        glColor3f(.34,.52,.69);
        glBegin(GL_POLYGON);
        glVertex2f(1080,-30);
        glVertex2f(-30,-30);
        glVertex2f(-30,20);
        glVertex2f(1080,20);
        glEnd();

        float markerStart = leftMargin;

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
    }

    public:
    void render(){
        for(int i=0;i<28;++i)
        {
            glColor3fv(bcol[(int)bco[i][0][0]]);
            glBegin(GL_POLYGON);
            glVertex2f(bco[i][1][0],bco[i][2][1]);
            glVertex2f(bco[i][1][0],bco[i][1][1]);
            glVertex2f(bco[i][2][0],bco[i][1][1]);
            glVertex2f(bco[i][2][0],bco[i][2][1]);
            glEnd();
        }

        renderTree();
        renderRoad();
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

    float MIN_LEFT = 50,MIN_BOTTOM = 20,MAX_TOP=150,MAX_RIGHT=150;

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
Aeroplane aeroplane;
BackgroundGraphics bg;

float speed = .4;

float jumpHeight = 0;
float MAX_HEIGHT = 280;

void init(){

    srand(time(NULL));

    glutInitWindowSize(1280,720);
    glutCreateWindow("Dino game");
    glClearColor(1,.62,0.129,0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-30,1080,-30,720);
}

void display(){
    bg.render();
    dino.renderBody();


    for(int i=0;i < 1280; i ++){
        if(aeroplane.getMarginLeft() <=  (-760 * 0.2)){
            aeroplane.setMarginLeft(2000 + (rand() % 1000));
            int top = rand() % 2;
            top == 0 ? aeroplane.setMarginBottom(100) : aeroplane.setMarginBottom(200);
        }else {

            // here aeroplane is assumed to be 20 units high and 100 units wide

            if( aeroplane.getMarginBottom() + 20 > dino.MIN_BOTTOM + dino.getJumpHeight() &&
                aeroplane.getMarginBottom() < dino.MAX_TOP + dino.getJumpHeight() &&
                aeroplane.getMarginLeft() <= dino.MAX_RIGHT &&
                aeroplane.getMarginLeft() + 100>= dino.MIN_LEFT){
                dino.setPlayerState(STILL);
            }

            aeroplane.setMarginLeft(aeroplane.getMarginLeft() - (0.002 * speed));


        }


        if(car.getMargin() <= -290){
            car.setMargin(2000 + (rand() % 1000));
        } else{

            //Car is 183 pixels wide and 30 pixels high
            //The bottom margin of the car remains constant throughout the game => 30 pixels
            if( 60 > dino.MIN_BOTTOM + dino.getJumpHeight() &&
                30 < dino.MAX_TOP + dino.getJumpHeight() &&
                car.getMargin() <= dino.MAX_RIGHT &&
                car.getMargin() + 183 >= dino.MIN_LEFT){
                dino.setPlayerState(STILL);
            }
            car.setMargin(car.getMargin() - (0.002 * speed));
        }

        //Making sure that the car and the aeroplane do not spawn really close to each other
        if(fabs(car.getMargin() -aeroplane.getMarginLeft()) <= 200){
            srand(time(0));
            car.setMargin(2000 + (rand() % 1000));
            aeroplane.setMarginLeft(2000 + (rand() % 1000));
        }

    }

    car.render();
    aeroplane.render();

    glFlush();
}

void keyboard(unsigned char key,int x,int y){
    if(key == ' ' && dino.getPlayerState() == STILL){
        dino.setJumpHeight(0);
        aeroplane.setMarginLeft(6000);
        car.setMargin(6000);
        dino.setPlayerState(RUN);
    }

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
