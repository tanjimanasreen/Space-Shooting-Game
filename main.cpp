#include <GL/gl.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#include<windows.h>
#include <string>
#include <sstream>

using namespace std;

double mousex;
double mousey;

string s="HP";
string s1="Score: ";
string s2="Game Over";
string s3="You Won!!!";
string s4="You Loose!!!";

float _angle = 0.0;
float _cameraAngle = 0.0;
float _ang_tri = 0.0;
float p1=0.0;
float p2=0.0;
float p3=0.0;
float angle=0.0;
float trans=0.0;
float angleToRotate=0.0;
float _angleeee = 0.0;
float _anglee = 0.0;
float _angleee = 0.0;
float _angl = 0.0;
float angleToRotateBG=0.0;
float eneymove=-2.5;
float mov=0.0;
float eneSize=0.2;
float movPlat=2;
float movPlat2=-4;
float angleToRotateEnemy1=0.0;
float angleToRotateEnemy2=0.0;
float angleToRotateEnemy3=0.0;
float bossX=0;
float bossY=3;
float bossZ=1;
float bossSize=0.3;
float healthLimit=1.15;
float healthDec=0.01;
float bossHP=1;
float bulletsize=0.02;

int deaths=0;
int timer=100;
int score=0;
int buffProb=33;
int len=s.length();
int enemycount=1;
int mainmenu=1;
int high_score = 0;
int howtoplay=0;
int about = 0;
int life = 3;
int flag=0;
int a=0;
int game_over=0;
int game_play=0;
int xyz=1;

vector<float> pos;
vector<float>eneypos;
vector<float>eneposCheck;
vector<float>eneYpos;
vector<float>eneyXpos;
vector<float>bulletYPos;
vector<float>bulletXpos;
vector<int>enemySpawnType;
vector<int>hitCheck;
vector<int>healthBuff;
vector<float>bossXpos;
vector<float>bossBulletX;
vector<float>bossBulletY;

bool boss=false;
bool transition=false;
bool bosshit=false;
bool gameover=false;
bool bossupdate=false;
bool leftC=true;
bool pauseGame=false;
bool fullscreen=false;
bool winner=false;
bool enespawn=false;
bool gameReload=false;
//bool ship1=true;
//bool ship2=false;

void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void MainMenu(){
    glLineWidth(4);
    glColor3f(1.0,1.0,1.0);

    renderBitmapString(-1.7f,-0.0f,GLUT_BITMAP_TIMES_ROMAN_24,"SHOOTING GAME");
    renderBitmapString(0.50f,0.8f,GLUT_BITMAP_TIMES_ROMAN_24,"PLAY");
    renderBitmapString(0.5f,0.4f,GLUT_BITMAP_TIMES_ROMAN_24,"RULES");
    renderBitmapString(0.5f,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,"ABOUT");
    renderBitmapString(0.5f,-0.4f,GLUT_BITMAP_TIMES_ROMAN_24,"EXIT");
}

void howToPlay(){
    glColor3f(1.0f,1.0f,1.0f);
    renderBitmapString(-0.4f,1.7f,GLUT_BITMAP_TIMES_ROMAN_24,"RULES FOR THIS GAME");

    glBegin(GL_LINES);
        glVertex2f(-0.6f,-1.5f);
        glVertex2f(-0.6f,-1.2f);
        glVertex2f(-0.6f,-1.5f);
        glVertex2f(0.6f,-1.5f);
        glVertex2f(-0.6f,-1.2f);
        glVertex2f(0.6f,-1.2f);
        glVertex2f(0.6f,-1.5f);
        glVertex2f(0.6f,-1.2f);
	glEnd();

	renderBitmapString(-2.7f,1.4f,GLUT_BITMAP_HELVETICA_18,"1. hit left arrow key to move the shooter Left");
	renderBitmapString(-2.7f,1.2f,GLUT_BITMAP_HELVETICA_18,"2. hit Right arrow key to move the shooter Right");
	renderBitmapString(-2.7f,1.0f,GLUT_BITMAP_HELVETICA_18,"3. hit Space to key to Shoot");
	renderBitmapString(-2.7f,0.8f,GLUT_BITMAP_HELVETICA_18,"4. one killed = one point");
	renderBitmapString(-2.7f,0.6f,GLUT_BITMAP_HELVETICA_18,"5. one missed shot will cost one life");
	renderBitmapString(-2.7f,0.4f,GLUT_BITMAP_HELVETICA_18,"6. press Esc to exit the game");
	renderBitmapString(-2.7f,0.2f,GLUT_BITMAP_HELVETICA_18,"7. press p to pause the game");
	renderBitmapString(-2.7f,0.0f,GLUT_BITMAP_HELVETICA_18,"8. press f to change full screen the game");

	renderBitmapString(-0.2f,-1.4f,GLUT_BITMAP_TIMES_ROMAN_24,"BACK");
}

void showAbout(){
    glColor3f(1.0f,1.0f,1.0f);
    renderBitmapString(-0.2f,1.8f,GLUT_BITMAP_TIMES_ROMAN_24,"ABOUT");
    renderBitmapString(-0.9f,1.0f,GLUT_BITMAP_TIMES_ROMAN_24,"GAME NAME : ENEMY SHOOTER ");
    renderBitmapString(-0.9f,0.7f,GLUT_BITMAP_HELVETICA_18,"GAME TYPE : 3D SHOTTING");
    renderBitmapString(-0.9f,0.4f,GLUT_BITMAP_HELVETICA_18,"COURSE : COMPUTER GRAPHICS");
    renderBitmapString(-0.9f,0.1f,GLUT_BITMAP_HELVETICA_18,"FACULTY : MD. HASIBUL HASAN");
    renderBitmapString(-0.9f,-0.2f,GLUT_BITMAP_HELVETICA_18,"-----------------------------------");
    renderBitmapString(-0.9f,-0.4f,GLUT_BITMAP_TIMES_ROMAN_24,"GROUP MEMBERS:-");
    renderBitmapString(-0.9f,-0.6f,GLUT_BITMAP_HELVETICA_18,"TANJIMA NASREEN JENIA");
    renderBitmapString(-0.9f,-0.7f,GLUT_BITMAP_HELVETICA_18,"MUHTASIM HAFIZ");
    renderBitmapString(-0.9f,-0.8f,GLUT_BITMAP_HELVETICA_18,"RIFAD MD JOBAYER");
    renderBitmapString(-0.9f,-0.9f,GLUT_BITMAP_HELVETICA_18,"TAREQ JAMAN");


    glBegin(GL_LINES);
        glVertex2f(-0.6f,-1.5f);
        glVertex2f(-0.6f,-1.2f);
        glVertex2f(-0.6f,-1.5f);
        glVertex2f(0.6f,-1.5f);
        glVertex2f(-0.6f,-1.2f);
        glVertex2f(0.6f,-1.2f);
        glVertex2f(0.6f,-1.5f);
        glVertex2f(0.6f,-1.2f);
	glEnd();

	renderBitmapString(-0.2f,-1.4f,GLUT_BITMAP_TIMES_ROMAN_24,"BACK");
}
//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


void eraseAllEnemy()
{
    if(eneypos.empty())
    {
        return;
    }
    for(int i=0;i<eneYpos.size();i++)
    {
        eneYpos.erase(eneYpos.begin() + i);;
        eneyXpos.erase(eneyXpos.begin()+i);
        enemySpawnType.erase(enemySpawnType.begin()+i);
        hitCheck.erase(hitCheck.begin()+i);
    }
}

void eraseEnemy(int i)
{
    eneYpos.erase(eneYpos.begin() + i);;
    eneyXpos.erase(eneyXpos.begin()+i);
    enemySpawnType.erase(enemySpawnType.begin()+i);
   hitCheck.erase(hitCheck.begin()+i);

}

void enemypos()
{
    for(float i=-2.5;i<2.5;i+=eneSize)
    {
        eneypos.push_back(i);
        eneposCheck.push_back(0);
    }
}

void bossXposGen()
{
    int c=0;
    for(float i=-2.5;i<2.5;i+=bossSize)
    {
        bossXpos.push_back(i);
        cout<<i<<" "<<c<<endl;
        c++;

    }
}

void background()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glTranslatef(2.7, 0.8, 0.0);
    glPushMatrix();
    glRotatef(-70,1.0,0.0,0.0);
    glPushMatrix();

    glRotatef(angleToRotate,0.0,0.0,1.0);
    glColor3ub(69,7,74);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glutSolidSphere(.3,20,20);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0.0, -0.0, 0.0);


	glBegin(GL_LINES);
	for(int i=0;i<200;i++)
	{
		float pi=5;
		float A=(i*2*pi)/100;
		float r=0.4;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();




    glPushMatrix();
    glTranslatef(-2.8, 0.8, 0.0);
    glPushMatrix();
    glRotatef(-70,1.0,0.0,0.0);
    glPushMatrix();

    glRotatef(angleToRotate,0.0,0.0,1.0);
    glColor3ub(30,33,82);
     glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glutSolidSphere(.2,20,20);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glPopMatrix();
    glPushMatrix();
	glTranslatef(0.0, -0.0, 0.0);

    glColor3ub(30,33,82);
	glBegin(GL_LINES);
	for(int i=0;i<200;i++)
	{
		float pi=5;
		float A=(i*2*pi)/100;
		float r=0.3;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4, 2.5, 0.0);
    glPushMatrix();
    glRotatef(-50.0,1.0,0.0,0.0);
    glPushMatrix();

    glRotatef(angleToRotate,0,0,1);
    glColor3ub(46,91,17);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glutSolidSphere(.1,20,20);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glPopMatrix();
    glPushMatrix();
	glTranslatef(0.0, -0.0, 0.0);
    glColor3ub(46,91,17);
	glBegin(GL_LINES);
	for(int i=0;i<200;i++)
	{
		float pi=5;
		float A=(i*2*pi)/100;
		float r=0.15;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();

    glPopMatrix();
    glPopMatrix();
    glPopMatrix();


glPointSize(1);
glBegin(GL_POINTS);

    glColor3f(1.0,1.0,1.0);

    glVertex2f(0.0,1.2);
    glVertex2f(0.2,2.2);
    glVertex2f(0.4,2.6);
    glVertex2f(0.6,1.4);
    glVertex2f(0.8,2.3);
    glVertex2f(1.0,1.2);
    glVertex2f(1.2,1.7);
    glVertex2f(1.4,1.4);
    glVertex2f(1.6,2.5);
    glVertex2f(1.8,1.8);
    glVertex2f(2.0,0.7);
    glVertex2f(2.2,1.9);
    glVertex2f(2.4,2.6);
    glVertex2f(2.6,1.5);
    glVertex2f(2.8,1.9);
    glVertex2f(3.0,2.7);
    glVertex2f(3.2,2.2);
    glVertex2f(3.4,1.3);
    glVertex2f(3.6,0.9);
    glVertex2f(3.8,2.1);
    glVertex2f(4.0,1.4);
    glVertex2f(4.2,2.6);
    glVertex2f(4.3,1.6);
    glVertex2f(4.4,2.1);
    glVertex2f(4.5,0.6);
    glVertex2f(4.5,2.7);
    glVertex2f(4.6,1.9);
    glVertex2f(4.7,0.2);
    glVertex2f(4.8,1.3);
    glVertex2f(4.9,1.7);
    glVertex2f(5.0,1.5);
    glVertex2f(5.0,2.7);
    glVertex2f(5.1,2.2);
    glVertex2f(5.2,2.6);
    glVertex2f(5.3,1.2);
    glVertex2f(5.4,1.7);
    glVertex2f(5.5,1.3);
    glVertex2f(5.6,2.4);
    glVertex2f(5.7,1.9);
    glVertex2f(5.8,0.6);
    glVertex2f(5.9,2.2);
    glVertex2f(0.0,3.1);
    glVertex2f(0.2,2.7);
    glVertex2f(0.6,3.2);
    glVertex2f(1.0,2.9);
    glVertex2f(1.4,3.1);
    glVertex2f(2.0,2.8);
    glVertex2f(2.4,3.2);
    glVertex2f(3.0,3.0);
    glVertex2f(3.6,2.8);
    glVertex2f(4.0,2.7);
    glVertex2f(4.6,3.2);
    glVertex2f(5.0,2.9);
    glVertex2f(5.4,3.0);
    glVertex2f(5.6,3.2);

    glVertex2f(-0.2,2.1);
    glVertex2f(-0.4,2.7);
    glVertex2f(-0.6,1.3);
    glVertex2f(-0.8,2.5);
    glVertex2f(-1.0,1.1);
    glVertex2f(-1.2,1.8);
    glVertex2f(-1.4,1.3);
    glVertex2f(-1.6,2.6);
    glVertex2f(-1.8,1.7);
    glVertex2f(-2.0,0.6);
    glVertex2f(-2.2,1.8);
    glVertex2f(-2.4,2.6);
    glVertex2f(-2.6,1.5);
    glVertex2f(-2.8,1.9);
    glVertex2f(-3.0,2.6);
    glVertex2f(-3.2,2.2);
    glVertex2f(-3.4,1.2);
    glVertex2f(-3.6,0.9);
    glVertex2f(-3.8,2.8);
    glVertex2f(-4.0,1.6);
    glVertex2f(-4.2,2.6);
    glVertex2f(-4.3,1.6);
    glVertex2f(-4.4,2.1);
    glVertex2f(-4.5,0.6);
    glVertex2f(-4.5,2.7);
    glVertex2f(-4.6,1.9);
    glVertex2f(-4.7,0.2);
    glVertex2f(-4.8,1.3);
    glVertex2f(-4.9,1.5);
    glVertex2f(-5.0,2.7);
    glVertex2f(-5.0,1.2);
    glVertex2f(-5.1,2.2);
    glVertex2f(-5.2,2.6);
    glVertex2f(-5.3,1.2);
    glVertex2f(-5.4,1.7);
    glVertex2f(-5.5,1.3);
    glVertex2f(-5.6,2.4);
    glVertex2f(-5.7,1.9);
    glVertex2f(-5.8,0.6);
    glVertex2f(-5.9,2.2);
    glVertex2f(-0.0,3.1);
    glVertex2f(-0.2,2.7);
    glVertex2f(-0.6,3.2);
    glVertex2f(-1.0,2.9);
    glVertex2f(-1.4,3.1);
    glVertex2f(-2.0,2.8);
    glVertex2f(-2.4,3.2);
    glVertex2f(-3.0,3.0);
    glVertex2f(-3.6,2.8);
    glVertex2f(-4.0,2.7);
    glVertex2f(-4.6,3.2);
    glVertex2f(-5.0,2.9);
    glVertex2f(-5.4,3.0);
    glVertex2f(-5.6,3.2);

    glVertex2f(-1.5,0.8);

    glVertex2f(3.350,0.4);
    glVertex2f(2.600,0.2);


    glVertex2f(-4.200,0.4);
    glVertex2f(-3.075,0.2);
    glVertex2f(-4.150,0.0);
    glVertex2f(-3.225,-0.2);
    glVertex2f(-2.900,-0.4);
    glVertex2f(-4.175,-0.6);
    glVertex2f(-3.450,-0.8);
    glVertex2f(-4.525,-1.0);
    glVertex2f(-3.700,-1.2);
    glVertex2f(-2.975,-1.4);
    glVertex2f(-3.350,-1.6);
    glVertex2f(-3.825,-1.8);
    glVertex2f(-2.800,-2.0);
    glVertex2f(-4.3,-2.2);
    glVertex2f(-2.250,-2.4);
    glVertex2f(-3.6,-2.6);
    glVertex2f(-4.00,-2.8);
    glVertex2f(-4.800,0.7);
    glVertex2f(-4.850,-0.4);
    glVertex2f(-4.900,-1.7);
    glVertex2f(-4.950,-1.1);
    glVertex2f(-5.000,-1.4);
    glVertex2f(-5.050,-0.2);
    glVertex2f(-5.100,0.2);
    glVertex2f(-5.150,-0.4);
    glVertex2f(-5.100,-2.5);
    glVertex2f(-4.500,-2.6);
    glVertex2f(-4.900,-2.7);
    glVertex2f(-4.600,-2.8);
    glVertex2f(-5.100,-2.8);
    glVertex2f(-4.500,-1.4);
    glVertex2f(-4.600,-2.0);

    glVertex2f(-5.800,-0.6);
    glVertex2f(-5.700,-1.2);
    glVertex2f(-5.600,-0.7);
    glVertex2f(-5.500,-0.2);
    glVertex2f(-5.400,-1.1);
    glVertex2f(-5.300,-0.3);
    glVertex2f(-5.200,-0.9);

    glVertex2f(-5.800,-1.6);
    glVertex2f(-5.700, 0.2);
    glVertex2f(-5.600,-1.3);
    glVertex2f(-5.500,-1.6);
    glVertex2f(-5.400,-2.2);
    glVertex2f(-5.300,-1.9);
    glVertex2f(-5.200, 0.4);

    glVertex2f(-5.700,-2.9);
    glVertex2f(-5.500,-3.0);
    glVertex2f(-5.300,-3.2);
    glVertex2f(-5.100,-3.0);
    glVertex2f(-4.900,-3.1);
    glVertex2f(-4.700,-2.9);

    glVertex2f(-3.100,-2.9);
    glVertex2f(-3.300,-3.1);
    glVertex2f(-3.500,-2.7);
    glVertex2f(-3.700,-3.0);
    glVertex2f(-3.900,-2.6);
    glVertex2f(-4.100,-2.8);
    glVertex2f(-4.300,-3.1);
    glVertex2f(-4.500,-2.9);
    glVertex2f(-4.700,-3.2);

    glVertex2f(-3.100,-2.6);
    glVertex2f(-3.300,-2.2);
    glVertex2f(-3.500,-2.4);
    glVertex2f(-3.700,-1.4);
    glVertex2f(-3.900,-1.9);
    glVertex2f(-4.100,-2.5);
    glVertex2f(-4.300,-1.2);
    glVertex2f(-4.500,-2.1);
    glVertex2f(-4.700,-0.9);


    glVertex2f(1.5,0.8);

    glVertex2f(3.350,0.4);
    glVertex2f(2.600,0.2);

    glVertex2f(4.200,0.4);
    glVertex2f(3.075,0.2);
    glVertex2f(4.150,0.0);
    glVertex2f(3.225,-0.2);
    glVertex2f(2.900,-0.4);
    glVertex2f(4.175,-0.6);
    glVertex2f(3.450,-0.8);
    glVertex2f(4.525,-1.0);
    glVertex2f(3.700,-1.2);
    glVertex2f(2.975,-1.4);
    glVertex2f(3.350,-1.6);
    glVertex2f(3.825,-1.8);
    glVertex2f(2.800,-2.0);
    glVertex2f(4.3,-2.2);
    glVertex2f(2.250,-2.4);
    glVertex2f(3.6,-2.6);
    glVertex2f(4.00,-2.8);
    glVertex2f(4.800,0.7);
    glVertex2f(4.850,-0.4);
    glVertex2f(4.900,-1.7);
    glVertex2f(4.950,-1.1);
    glVertex2f(5.000,-1.4);
    glVertex2f(5.050,-0.2);
    glVertex2f(5.100,0.2);
    glVertex2f(5.150,-0.4);
    glVertex2f(5.100,-2.5);
    glVertex2f(4.500,-2.6);
    glVertex2f(4.900,-2.7);
    glVertex2f(4.600,-2.8);
    glVertex2f(5.100,-2.8);
    glVertex2f(4.500,-1.4);
    glVertex2f(4.600,-2.0);

    glVertex2f(5.800,-0.6);
    glVertex2f(5.700,-1.2);
    glVertex2f(5.600,-0.7);
    glVertex2f(5.500,-0.2);
    glVertex2f(5.400,-1.1);
    glVertex2f(5.300,-0.3);
    glVertex2f(5.200,-0.9);

    glVertex2f(5.800,-1.6);
    glVertex2f(5.700, 0.2);
    glVertex2f(5.600,-1.3);
    glVertex2f(5.500,-1.6);
    glVertex2f(5.400,-2.2);
    glVertex2f(5.300,-1.9);
    glVertex2f(5.200, 0.4);

    glVertex2f(5.700,-2.9);
    glVertex2f(5.500,-3.0);
    glVertex2f(5.300,-3.2);
    glVertex2f(5.100,-3.0);
    glVertex2f(4.900,-3.1);
    glVertex2f(4.700,-2.9);

    glVertex2f(3.100,-2.9);
    glVertex2f(3.300,-3.1);
    glVertex2f(3.500,-2.7);
    glVertex2f(3.700,-3.0);
    glVertex2f(3.900,-2.6);
    glVertex2f(4.100,-2.8);
    glVertex2f(4.300,-3.1);
    glVertex2f(4.500,-2.9);
    glVertex2f(4.700,-3.2);

    glVertex2f(3.100,-2.6);
    glVertex2f(3.300,-2.2);
    glVertex2f(3.500,-2.4);
    glVertex2f(3.700,-1.4);
    glVertex2f(3.900,-1.9);
    glVertex2f(4.100,-2.5);
    glVertex2f(4.300,-1.2);
    glVertex2f(4.500,-2.1);
    glVertex2f(4.700,-0.9);



    glEnd();

    glPushMatrix();
    glScalef(0.1,0.1,0.1);
    glPushMatrix();
    glTranslatef(1.0,20.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0,20.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(32.0,16.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10.0,28.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-26.0,25.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-36.0,-20.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-40.0,-12.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(36.0,-25.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40.0,-8.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40.0,-8.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
        glPushMatrix();
    glTranslatef(40.0,-8.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
        glPushMatrix();
    glTranslatef(30.0,2.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-25.0,4.50,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15.0,25.50,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
        glPushMatrix();
    glTranslatef(-40.0,14.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
        glPushMatrix();
    glTranslatef(40.0,26.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
            glPushMatrix();
    glTranslatef(-50.0,16.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(48.0,13.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-48.0,-23.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(50.0,-26.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(56.0,-20.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
    glPushMatrix();

    glTranslatef(-56.0,-4.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-56.0,28.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(55.0,25.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(30.0,-27.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-33.0,-26.0,1.0);
    glRotatef(angleToRotate,0,0,1);
	glBegin(GL_TRIANGLES);

	//Triangle
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.0, 0.3, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);

	glVertex3f(0.0, -0.8, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);

	glEnd();
    glPopMatrix();

    glPopMatrix();


    glPushMatrix();
    glScalef(1.0,1.0,0.0);


    glPushMatrix();
    glTranslatef(2.8, 2.0, 0.0);
    glRotatef(angleToRotateBG,0,0,1);
    glColor3ub(65,132,215);
    glutSolidSphere(.02,20,20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.8, 1.2, 0.0);
    glRotatef(angleToRotate,0,0,1);
    glColor3ub(255,132,215);
    glutSolidSphere(.02,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8, 1.15, 0.0);
    glRotatef(angleToRotateBG,0,0,1);
    glColor3ub(55,132,255);
    glutSolidSphere(.02,20,20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.85, 1.2, 0.0);
    glRotatef(angleToRotateBG,0,0,1);
    glColor3ub(255,12,15);
    glutSolidSphere(.02,20,20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.9, 1.1, 0.0);
    glRotatef(angleToRotateBG,0,0,1);
    glColor3ub(25,205,15);
    glutSolidSphere(.02,20,20);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glScalef(0.1,0.1,0.1);
    glTranslatef(40,22.0,0.0);
    glPushMatrix();
    glRotatef(-50, 1.0, 1.0, 1.0);
    glPushMatrix();
    glRotatef(_angl, 0.0, 0.0, 1.0);
    glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(_angl, 0.0, 0.0, 1.0);
	glColor3f(1.0,0.0,0.0);
    glutWireSphere(.5,50,50);
	glPopMatrix();
	glPopMatrix();

    glPushMatrix();
    glRotatef(_angleeee, 0.0, 0.0, 1.0);
    glPushMatrix();
	glTranslatef(0.0, 1.2, 0.0);
	glRotatef(_angleeee, 0.0, 0.0, 1.0);
	glColor3f(0.0,1.0,0.0);
    glutWireSphere(.2,50,50);
	glPopMatrix();
	glPopMatrix();

    glPushMatrix();
    glRotatef(_anglee, 0.0, 0.0, 1.0);
    glPushMatrix();
	glTranslatef(0.0,-1.7, 0.0);
	glRotatef(_anglee, 0.0, 0.0, 1.0);
	glColor3f(1.0,1.0,0.0);
    glutWireSphere(0.25,50,50);
	glPopMatrix();
	glPopMatrix();

    glPushMatrix();
    glRotatef(_angleee, 0.0, 0.0, 1.0);
    glPushMatrix();
	glTranslatef(0.0, 2.5, 0.0);
	glRotatef(_angleee, 0.0, 0.0, 1.0);
	glColor3f(0.0,1.0,1.0);
    glutWireSphere(.35,50,50);
	glPopMatrix();
    glPopMatrix();
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);
	for(int i=0;i<200;i++)
	{
		float pi=5;
		float A=(i*2*pi)/100;
		float r=1.2;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();


	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES);
	for(int i=0;i<200;i++)
	{
		float pi=5;
		float A=(i*2*pi)/100;
		float r=1.7;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();


	glPopMatrix();

	glPushMatrix();

	glBegin(GL_LINES);
	for(int i=0;i<200;i++)
	{
		float pi=5;
		float A=(i*2*pi)/100;
		float r=2.5;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
	glEnd();


	glPopMatrix();
	glPopMatrix();
    glPopMatrix();


}




void platformdesign()
{
glPushMatrix();

glPushMatrix();
    int r=50,g=50,b=50;
    glTranslatef(0,mov,-.2);
    glBegin(GL_QUADS);
    for(float i=-7;i<=3;i+=0.35)
    {
        glColor3ub(r,g,b);


        glVertex2f(-2.5,i);
        glVertex2f(2.5,i);
        glVertex2f(2.5,i+.35);
        glVertex2f(-2.5,i+.35);
        r+=5;
        g+=5;
        b+=5;

        if(r==255||g==255||b==265)
        {
            r=100;
            g=100;
            b=100;
        }

    }

     glEnd();
glPopMatrix();
glPopMatrix();
}

void letterPrintPlayerHP()
{
    glColor3ub(255,255,255);
    glRasterPos2f(1.85,3.0);
    for(int i=0;i<len;i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[i]);
    }
}

string int_to_str(int num)
{
    stringstream ss;
    ss << num;

    return ss.str();
}


void ScorePrint()
{
    string temp=int_to_str(score);
    glColor3ub(255,255,255);
    glRasterPos2f(2.8,2.7);
    for(int i=0;i<temp.length();i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,temp[i]);
    }

    glRasterPos2f(1.8,2.7);
    for(int i=0;i<s1.length();i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s1[i]);
    }

}

void StatusPrint(string temp)
{
    glColor3ub(255,255,255);
    glRasterPos2f(-0.2,0.3);
    for(int i=0;i<temp.length();i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,temp[i]);
    }
}


void GameOverPrint()
{
    glColor3ub(255,255,255);
    glRasterPos2f(-0.2,0.1);
    for(int i=0;i<s2.length();i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s2[i]);

    }

    string temp=int_to_str(score);
    glColor3ub(255,255,255);
    glRasterPos2f(0.4,-.1);
    for(int i=0;i<temp.length();i++)
    {

        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,temp[i]);
    }

    glRasterPos2f(-0.2,-.1);
    for(int i=0;i<s1.length();i++)
    {

        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s1[i]);
    }

}

void GameOverScene()
{

    glPointSize(1);
glBegin(GL_POINTS);

    glColor3f(1.0,1.0,1.0);

    glVertex2f(0.0,1.2);
    PlaySound(TEXT("pause.wav"), NULL, SND_LOOP | SND_ASYNC);
    glVertex2f(0.2,2.2);
    glVertex2f(0.4,2.6);
    glVertex2f(0.6,1.4);
    glVertex2f(0.8,2.3);
    glVertex2f(1.0,1.2);
    glVertex2f(1.2,1.7);
    glVertex2f(1.4,1.4);
    glVertex2f(1.6,2.5);
    glVertex2f(1.8,1.8);
    glVertex2f(2.0,0.7);
    glVertex2f(2.2,1.9);
    glVertex2f(2.4,2.6);
    glVertex2f(2.6,1.5);
    glVertex2f(2.8,1.9);
    glVertex2f(3.0,2.7);
    glVertex2f(3.2,2.2);
    glVertex2f(3.4,1.3);
    glVertex2f(3.6,0.9);
    glVertex2f(3.8,2.1);
    glVertex2f(4.0,1.4);
    glVertex2f(4.2,2.6);
    glVertex2f(4.3,1.6);
    glVertex2f(4.4,2.1);
    glVertex2f(4.5,0.6);
    glVertex2f(4.5,2.7);
    glVertex2f(4.6,1.9);
    glVertex2f(4.7,0.2);
    glVertex2f(4.8,1.3);
    glVertex2f(4.9,1.7);
    glVertex2f(5.0,1.5);
    glVertex2f(5.0,2.7);
    glVertex2f(5.1,2.2);
    glVertex2f(5.2,2.6);
    glVertex2f(5.3,1.2);
    glVertex2f(5.4,1.7);
    glVertex2f(5.5,1.3);
    glVertex2f(5.6,2.4);
    glVertex2f(5.7,1.9);
    glVertex2f(5.8,0.6);
    glVertex2f(5.9,2.2);
    glVertex2f(0.0,3.1);
    glVertex2f(0.2,2.7);
    glVertex2f(0.6,3.2);
    glVertex2f(1.0,2.9);
    glVertex2f(1.4,3.1);
    glVertex2f(2.0,2.8);
    glVertex2f(2.4,3.2);
    glVertex2f(3.0,3.0);
    glVertex2f(3.6,2.8);
    glVertex2f(4.0,2.7);
    glVertex2f(4.6,3.2);
    glVertex2f(5.0,2.9);
    glVertex2f(5.4,3.0);
    glVertex2f(5.6,3.2);

    glVertex2f(-0.2,2.1);
    glVertex2f(-0.4,2.7);
    glVertex2f(-0.6,1.3);
    glVertex2f(-0.8,2.5);
    glVertex2f(-1.0,1.1);
    glVertex2f(-1.2,1.8);
    glVertex2f(-1.4,1.3);
    glVertex2f(-1.6,2.6);
    glVertex2f(-1.8,1.7);
    glVertex2f(-2.0,0.6);
    glVertex2f(-2.2,1.8);
    glVertex2f(-2.4,2.6);
    glVertex2f(-2.6,1.5);
    glVertex2f(-2.8,1.9);
    glVertex2f(-3.0,2.6);
    glVertex2f(-3.2,2.2);
    glVertex2f(-3.4,1.2);
    glVertex2f(-3.6,0.9);
    glVertex2f(-3.8,2.8);
    glVertex2f(-4.0,1.6);
    glVertex2f(-4.2,2.6);
    glVertex2f(-4.3,1.6);
    glVertex2f(-4.4,2.1);
    glVertex2f(-4.5,0.6);
    glVertex2f(-4.5,2.7);
    glVertex2f(-4.6,1.9);
    glVertex2f(-4.7,0.2);
    glVertex2f(-4.8,1.3);
    glVertex2f(-4.9,1.5);
    glVertex2f(-5.0,2.7);
    glVertex2f(-5.0,1.2);
    glVertex2f(-5.1,2.2);
    glVertex2f(-5.2,2.6);
    glVertex2f(-5.3,1.2);
    glVertex2f(-5.4,1.7);
    glVertex2f(-5.5,1.3);
    glVertex2f(-5.6,2.4);
    glVertex2f(-5.7,1.9);
    glVertex2f(-5.8,0.6);
    glVertex2f(-5.9,2.2);
    glVertex2f(-0.0,3.1);
    glVertex2f(-0.2,2.7);
    glVertex2f(-0.6,3.2);
    glVertex2f(-1.0,2.9);
    glVertex2f(-1.4,3.1);
    glVertex2f(-2.0,2.8);
    glVertex2f(-2.4,3.2);
    glVertex2f(-3.0,3.0);
    glVertex2f(-3.6,2.8);
    glVertex2f(-4.0,2.7);
    glVertex2f(-4.6,3.2);
    glVertex2f(-5.0,2.9);
    glVertex2f(-5.4,3.0);
    glVertex2f(-5.6,3.2);

    glVertex2f(-1.5,0.8);

    glVertex2f(3.350,0.4);
    glVertex2f(2.600,0.2);


    glVertex2f(-4.200,0.4);
    glVertex2f(-3.075,0.2);
    glVertex2f(-4.150,0.0);
    glVertex2f(-3.225,-0.2);
    glVertex2f(-2.900,-0.4);
    glVertex2f(-4.175,-0.6);
    glVertex2f(-3.450,-0.8);
    glVertex2f(-4.525,-1.0);
    glVertex2f(-3.700,-1.2);
    glVertex2f(-2.975,-1.4);
    glVertex2f(-3.350,-1.6);
    glVertex2f(-3.825,-1.8);
    glVertex2f(-2.800,-2.0);
    glVertex2f(-4.3,-2.2);
    glVertex2f(-2.250,-2.4);
    glVertex2f(-3.6,-2.6);
    glVertex2f(-4.00,-2.8);
    glVertex2f(-4.800,0.7);
    glVertex2f(-4.850,-0.4);
    glVertex2f(-4.900,-1.7);
    glVertex2f(-4.950,-1.1);
    glVertex2f(-5.000,-1.4);
    glVertex2f(-5.050,-0.2);
    glVertex2f(-5.100,0.2);
    glVertex2f(-5.150,-0.4);
    glVertex2f(-5.100,-2.5);
    glVertex2f(-4.500,-2.6);
    glVertex2f(-4.900,-2.7);
    glVertex2f(-4.600,-2.8);
    glVertex2f(-5.100,-2.8);
    glVertex2f(-4.500,-1.4);
    glVertex2f(-4.600,-2.0);

    glVertex2f(-5.800,-0.6);
    glVertex2f(-5.700,-1.2);
    glVertex2f(-5.600,-0.7);
    glVertex2f(-5.500,-0.2);
    glVertex2f(-5.400,-1.1);
    glVertex2f(-5.300,-0.3);
    glVertex2f(-5.200,-0.9);

    glVertex2f(-5.800,-1.6);
    glVertex2f(-5.700, 0.2);
    glVertex2f(-5.600,-1.3);
    glVertex2f(-5.500,-1.6);
    glVertex2f(-5.400,-2.2);
    glVertex2f(-5.300,-1.9);
    glVertex2f(-5.200, 0.4);

    glVertex2f(-5.700,-2.9);
    glVertex2f(-5.500,-3.0);
    glVertex2f(-5.300,-3.2);
    glVertex2f(-5.100,-3.0);
    glVertex2f(-4.900,-3.1);
    glVertex2f(-4.700,-2.9);

    glVertex2f(-3.100,-2.9);
    glVertex2f(-3.300,-3.1);
    glVertex2f(-3.500,-2.7);
    glVertex2f(-3.700,-3.0);
    glVertex2f(-3.900,-2.6);
    glVertex2f(-4.100,-2.8);
    glVertex2f(-4.300,-3.1);
    glVertex2f(-4.500,-2.9);
    glVertex2f(-4.700,-3.2);

    glVertex2f(-3.100,-2.6);
    glVertex2f(-3.300,-2.2);
    glVertex2f(-3.500,-2.4);
    glVertex2f(-3.700,-1.4);
    glVertex2f(-3.900,-1.9);
    glVertex2f(-4.100,-2.5);
    glVertex2f(-4.300,-1.2);
    glVertex2f(-4.500,-2.1);
    glVertex2f(-4.700,-0.9);


    glVertex2f(1.5,0.8);

    glVertex2f(3.350,0.4);
    glVertex2f(2.600,0.2);


    glVertex2f(4.200,0.4);
    glVertex2f(3.075,0.2);
    glVertex2f(4.150,0.0);

    glVertex2f(0.0,-1.2);
    glVertex2f(0.2,-2.2);
    glVertex2f(0.4,-2.6);
    glVertex2f(0.6,-1.4);
    glVertex2f(0.8,-2.3);
    glVertex2f(1.0,-1.2);
    glVertex2f(1.2,-1.7);
    glVertex2f(1.4,-1.4);
    glVertex2f(1.6,-2.5);
    glVertex2f(1.8,-1.8);
    glVertex2f(2.0,-0.7);
    glVertex2f(2.2,-1.9);
    glVertex2f(2.4,-2.6);
    glVertex2f(2.6,-1.5);
    glVertex2f(2.8,-1.9);
    glVertex2f(3.0,-2.7);
    glVertex2f(3.2,-2.2);
    glVertex2f(3.4,-1.3);
    glVertex2f(3.6,-0.9);
    glVertex2f(3.8,-2.1);

    glVertex2f(0.05,-1.2);
    glVertex2f(-0.2,-2.2);
    glVertex2f(-0.4,-2.6);
    glVertex2f(-0.6,-1.4);
    glVertex2f(-0.8,-2.3);
    glVertex2f(-1.0,-1.2);
    glVertex2f(-1.2,-1.7);
    glVertex2f(-1.4,-1.4);
    glVertex2f(-1.6,-2.5);
    glVertex2f(-1.8,-1.8);
    glVertex2f(-2.0,-0.7);
    glVertex2f(-2.2,-1.9);
    glVertex2f(-2.4,-2.6);
    glVertex2f(-2.6,-1.5);
    glVertex2f(-2.8,-1.9);
    glVertex2f(-3.0,-2.7);
    glVertex2f(-3.2,-2.2);
    glVertex2f(-3.4,-1.3);
    glVertex2f(-3.6,-0.9);
    glVertex2f(-3.8,-2.1);
    glVertex2f(-4.00,-2.8);
    glVertex2f(-4.800,0.7);
    glVertex2f(-4.850,-0.4);
    glVertex2f(-4.900,-1.7);
    glVertex2f(-4.950,-1.1);
    glVertex2f(-5.000,-1.4);
    glVertex2f(-5.050,-0.2);
    glVertex2f(-5.100,0.2);
    glVertex2f(-5.150,-0.4);
    glVertex2f(-5.100,-2.5);
    glVertex2f(-4.500,-2.6);
    glVertex2f(-4.900,-2.7);
    glVertex2f(-4.600,-2.8);
    glVertex2f(-5.100,-2.8);
    glVertex2f(-4.500,-1.4);
    glVertex2f(-4.600,-2.0);

    glVertex2f(3.225,-0.2);
    glVertex2f(2.900,-0.4);
    glVertex2f(4.175,-0.6);
    glVertex2f(3.450,-0.8);
    glVertex2f(4.525,-1.0);
    glVertex2f(3.700,-1.2);
    glVertex2f(2.975,-1.4);
    glVertex2f(3.350,-1.6);
    glVertex2f(3.825,-1.8);
    glVertex2f(2.800,-2.0);
    glVertex2f(4.3,-2.2);
    glVertex2f(2.250,-2.4);
    glVertex2f(3.6,-2.6);
    glVertex2f(4.00,-2.8);
    glVertex2f(4.800,0.7);
    glVertex2f(4.850,-0.4);
    glVertex2f(4.900,-1.7);
    glVertex2f(4.950,-1.1);
    glVertex2f(5.000,-1.4);
    glVertex2f(5.050,-0.2);
    glVertex2f(5.100,0.2);
    glVertex2f(5.150,-0.4);
    glVertex2f(5.100,-2.5);
    glVertex2f(4.500,-2.6);
    glVertex2f(4.900,-2.7);
    glVertex2f(4.600,-2.8);
    glVertex2f(5.100,-2.8);
    glVertex2f(4.500,-1.4);
    glVertex2f(4.600,-2.0);

    glVertex2f(5.800,-0.6);
    glVertex2f(5.700,-1.2);
    glVertex2f(5.600,-0.7);
    glVertex2f(5.500,-0.2);
    glVertex2f(5.400,-1.1);
    glVertex2f(5.300,-0.3);
    glVertex2f(5.200,-0.9);

    glVertex2f(5.800,-1.6);
    glVertex2f(5.700, 0.2);
    glVertex2f(5.600,-1.3);
    glVertex2f(5.500,-1.6);
    glVertex2f(5.400,-2.2);
    glVertex2f(5.300,-1.9);
    glVertex2f(5.200, 0.4);

    glVertex2f(5.700,-2.9);
    glVertex2f(5.500,-3.0);
    glVertex2f(5.300,-3.2);
    glVertex2f(5.100,-3.0);
    glVertex2f(4.900,-3.1);
    glVertex2f(4.700,-2.9);

    glVertex2f(3.100,-2.9);
    glVertex2f(3.300,-3.1);
    glVertex2f(3.500,-2.7);
    glVertex2f(3.700,-3.0);
    glVertex2f(3.900,-2.6);
    glVertex2f(4.100,-2.8);
    glVertex2f(4.300,-3.1);
    glVertex2f(4.500,-2.9);
    glVertex2f(4.700,-3.2);

    glVertex2f(3.100,-2.6);
    glVertex2f(3.300,-2.2);
    glVertex2f(3.500,-2.4);
    glVertex2f(3.700,-1.4);
    glVertex2f(3.900,-1.9);
    glVertex2f(4.100,-2.5);
    glVertex2f(4.300,-1.2);
    glVertex2f(4.500,-2.1);
    glVertex2f(4.700,-0.9);
glEnd();

}
void letterPrintBossHP()
{
    glColor3ub(255,255,255);
    glRasterPos2f(-4.35,3.0);
    for(int i=0;i<len;i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[i]);

    }
}

void bossHealthDesign()
{
    //XP Meter
    glPushMatrix();
    glTranslatef(-2.85,2.95,0);
    glColor3ub(0,255,0);
    glBegin(GL_QUADS);
    glVertex2f(-1.1,0);
    glVertex2f(bossHP,0);
    glVertex2f(bossHP,.25);
    glVertex2f(-1.1,.25);
    glEnd();
    glPopMatrix();

    //Outer Border
    glPushMatrix();
    glTranslatef(-3.1,2.9,0);
    glColor3ub(0,100,0);
    glBegin(GL_QUADS);
    glVertex2f(1.3,0);
    glVertex2f(-1.3,0);
    glVertex2f(-1.3,.05);
    glVertex2f(1.3,.05);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.1,3.2,0);
    glColor3ub(0,100,0);
    glBegin(GL_QUADS);
    glVertex2f(1.3,0);
    glVertex2f(-1.3,0);
    glVertex2f(-1.3,.05);
    glVertex2f(1.3,.05);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8,2.9,0);
    glColor3ub(0,100,0);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(-.05,0);
    glVertex2f(-.05,.35);
    glVertex2f(0,.35);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.95,2.9,0);
    glColor3ub(0,100,0);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(-.05,0);
    glVertex2f(-.05,.35);
    glVertex2f(0,.35);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.4,2.9,0);
    glColor3ub(0,100,0);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(-.05,0);
    glVertex2f(-.05,.35);
    glVertex2f(0,.35);
    glEnd();
    glPopMatrix();

    letterPrintBossHP();
}

void healthDesign()
{
    //XP Meter
    glPushMatrix();
    glTranslatef(3.35,2.95,0);
    glColor3ub(0,255,0);
    glBegin(GL_QUADS);
    glVertex2f(-1.1,0);
    glVertex2f(healthLimit,0);
    glVertex2f(healthLimit,.25);
    glVertex2f(-1.1,.25);
    glEnd();
    glPopMatrix();

    //Outer Border
    glPushMatrix();
    glTranslatef(3.1,2.9,0);
    glColor3ub(0,100,0);
    glBegin(GL_QUADS);
    glVertex2f(-1.4,0);
    glVertex2f(1.4,0);
    glVertex2f(1.4,.05);
    glVertex2f(-1.4,.05);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.1,3.2,0);
    glColor3ub(0,100,0);
    glBegin(GL_QUADS);
    glVertex2f(-1.4,0);
    glVertex2f(1.4,0);
    glVertex2f(1.4,.05);
    glVertex2f(-1.4,.05);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.7,2.9,0);
    glColor3ub(0,100,0);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(.05,0);
    glVertex2f(.05,.35);
    glVertex2f(0,.35);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.2,2.9,0);
    glColor3ub(0,100,0);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(.05,0);
    glVertex2f(.05,.35);
    glVertex2f(0,.35);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.5,2.9,0);
    glColor3ub(0,100,0);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(.05,0);
    glVertex2f(.05,.35);
    glVertex2f(0,.35);
    glEnd();
    glPopMatrix();

    letterPrintPlayerHP();
}

void shipDesign()
{

glPushMatrix();
    glTranslatef(trans,-3,0.0);
    glScalef(.6,.6,.6);

    //Left Part
    glPushMatrix();
    glTranslatef(-.5,0,0);
    glScalef(.4,.4,.4);

    glPushMatrix();
    glColor3ub(0,0,100);
    glScalef(.5,1,.5);
    glRotatef(-180,0,0,1);
    glutSolidCube(.75);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(100,0,100);
    glTranslatef(0,.5,0);
    glRotatef(-90,1,0,0);
    glScalef(.5,.5,.5);
    glutSolidCone(.5,1.5,20,20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,0,1);
    glTranslatef(0,-.8,0);
    glRotatef(-90,1,0,0);
    glScalef(.5,.5,.5);
    glRotatef(angleToRotate,0,0,1);
    glutWireCone(.8,1.5,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(0,0,100);
    glTranslatef(.55,0,0);
    glScalef(1,.5,.5);
    glRotatef(-180,0,0,1);
    glutSolidCube(.8);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,0,255);
    glTranslatef(0,.5,0);
    glRotatef(-90,1,0,0);
    glScalef(.5,.5,.1);
    glRotatef(angleToRotate,0,0,1);
    glutSolidTorus(.1,.3,50,50);
    glPopMatrix();

    glPopMatrix();

    //Right Part
    glPushMatrix();
    glTranslatef(.5,0,0);
    glScalef(.4,.4,.4);

    glPushMatrix();
    glColor3ub(0,0,100);
    glScalef(.5,1,.5);
    glRotatef(-180,0,0,1);
    glutSolidCube(.75);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(100,0,100);
    glTranslatef(0,.5,0);
    glRotatef(-90,1,0,0);
    glScalef(.5,.5,.5);
    glutSolidCone(.5,1.5,20,20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,0,1);
    glTranslatef(0,-.8,0);
    glRotatef(-90,1,0,0);
    glScalef(.5,.5,.5);
    glRotatef(angleToRotate,0,0,1);
    glutWireCone(.8,1.5,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(0,0,100);
    glTranslatef(-.55,0,0);
    glScalef(1,.5,.5);
    glRotatef(-180,0,0,1);
    glutSolidCube(.8);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,0,255);
    glTranslatef(0,.5,0);
    glRotatef(-90,1,0,0);
    glScalef(.5,.5,.1);
    glRotatef(angleToRotate,0,0,1);
    glutSolidTorus(.1,.3,50,50);
    glPopMatrix();

    glPopMatrix();

    //Middle Part
    glPushMatrix();
    glScalef(.7,.7,.7);

    glPushMatrix();
    glColor3ub(0,0,100);
    glScalef(.5,1,.5);
    glRotatef(-180,0,0,1);
    glutSolidCube(.75);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(100,0,100);
    glTranslatef(0,.8,0);
    glRotatef(-90,1,0,0);
    glScalef(.5,.5,.5);
    glutSolidCone(.5,1.5,20,20);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,0,255);
    glTranslatef(0,.5,0);
    glRotatef(-90,1,0,0);
    glScalef(.5,.5,.2);
    glRotatef(angleToRotate,0,0,1);
    glutSolidTorus(.2,.5,50,50);
    glPopMatrix();


    glPushMatrix();
    glColor3ub(100,0,100);
    glTranslatef(0,-.8,0);
    glRotatef(-90,1,0,0);
    glScalef(.5,.5,.5);
    glRotatef(angleToRotate,0,0,1);
    glutWireCone(.8,1.5,50,50);
    glPopMatrix();

    glPopMatrix();

glPopMatrix();
}

void shipDesign2()
{
glPushMatrix();
    glTranslatef(trans,-3,.3);
    glScalef(.7,.7,.7);

    glPushMatrix();
    glColor3ub(0,128,128);
    glutSolidSphere(.3,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,200,0);
    glTranslatef(0,0,-.3);
    glScalef(.5,.5,.5);
    glRotatef(angleToRotate,0,0,1);
    glutWireTorus(.1,.5,20,20);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(255,200,0);
    glTranslatef(0,0,.2);
    glScalef(.5,.5,.5);
    glutSolidTorus(.1,.4,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(200,200,255);
    glScalef(.5,.5,.5);
    glutSolidTorus(.2,.5,50,50);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(0,0,100);
    glTranslatef(-.2,0,0);
    glRotatef(-45,0,1,0);
    glPushMatrix();
    glTranslatef(0,-.4,0);
    glRotatef(-100,1,0,0);
    glScalef(.4,.4,.4);
    glutSolidCone(.2,1.5,50,50);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glColor3ub(0,0,100);
    glTranslatef(.2,0,0);
    glRotatef(45,0,1,0);
    glPushMatrix();
    glTranslatef(0,-.4,0);
    glRotatef(-100,1,0,0);
    glScalef(.4,.4,.4);
    glutSolidCone(.2,1.5,50,50);
    glPopMatrix();
    glPopMatrix();

glPopMatrix();
}

void enemySpawn1()
{
             glPushMatrix();

                glScalef(.35,.35,.35);
                glRotatef(angleToRotateEnemy1,0,1,0);
                glPushMatrix();
                glColor3ub(255,99,71);
                glRotatef(angleToRotate,0,0,1);
                glutSolidSphere(.3,20,20);
                glPopMatrix();

                glPushMatrix();
                glColor3ub(255,204,0);
                glScalef(1,.2,.3);
                glutSolidTorus(.2,.3,20,20);
                glPopMatrix();

                glPushMatrix();
                glColor3ub(255,204,0);
                glRotatef(45,0,1,0);
                glScalef(1,.2,.3);
                glutSolidTorus(.2,.3,20,20);
                glPopMatrix();

                glPushMatrix();
                glColor3ub(255,204,0);
                glRotatef(-45,0,1,0);
                glScalef(1,.2,.3);
                glutSolidTorus(.2,.3,20,20);
                glPopMatrix();

                glPushMatrix();
                glColor3ub(255,204,0);
                glRotatef(90,0,1,0);
                glScalef(1,.2,.3);
                glutSolidTorus(.2,.3,20,20);
                glPopMatrix();

            glPopMatrix();

}

void enemySpawn2()
{

             glPushMatrix();


                glScalef(.4,.4,.4);
                glRotatef(angleToRotateEnemy2,0,-1,0);
                glPushMatrix();
                glColor3ub(255,0,0);
                glRotatef(-95,1,0,0);
                glScalef(.5,.5,.2);
                glutSolidTorus(.07,.5,20,20);
                glPopMatrix();

                glPushMatrix();
                glColor3ub(0,255,0);
                glScalef(.5,.5,.5);
                glutWireOctahedron();
                glPopMatrix();

                glPushMatrix();
                glColor3ub(255,255,0);
                glutSolidSphere(.08,20,20);
                glPopMatrix();
            glPopMatrix();

}


void enemySpawn3()
{
    glPushMatrix();
    glScalef(.7,.7,.7);

    glPushMatrix();
    glColor3ub(75,0,130);
    glRotatef(angleToRotateEnemy3,0,0,1);
    glScalef(.135,.135,.135);
    glutWireDodecahedron();
    glPopMatrix();

    glPushMatrix();
    glColor3ub(75,0,130);
    glRotatef(angleToRotateEnemy3,0,0,1);
    glScalef(.14,.14,.14);
    glutWireDodecahedron();
    glPopMatrix();

    glPushMatrix();
    glColor3ub(75,0,130);
    glRotatef(angleToRotateEnemy3,0,0,1);
    glScalef(.145,.145,.145);
    glutWireDodecahedron();
    glPopMatrix();

    glPushMatrix();
    glColor3ub(75,0,130);
    glRotatef(angleToRotateEnemy3,0,0,1);
    glScalef(.15,.15,.15);
    glutWireDodecahedron();
    glPopMatrix();

    glPushMatrix();
    glColor3ub(30,144,255);
    glRotatef(angleToRotateEnemy3,0,1,0);
    glScalef(.13,.13,.13);
    glutSolidOctahedron();
    glPopMatrix();

    glPopMatrix();
}


void drawEnemy()
{
   for(int i=0;i<eneYpos.size();i++)
    {
        if(hitCheck[i]==1)
        {
            glPushMatrix();
                glTranslatef(eneyXpos[i],eneYpos[i],0);
                glColor3ub(255,255,0);

                glutSolidSphere(0.15,100,100);


            glPopMatrix();
            continue;
        }


        if(enemySpawnType[i]==1)
        {   glPushMatrix();

                glTranslatef(eneyXpos[i],eneYpos[i],.1);
                enemySpawn1();
            glPopMatrix();
            continue;
        }

        glPushMatrix();
                glTranslatef(eneyXpos[i],eneYpos[i],.1);
                enemySpawn2();
            glPopMatrix();


    }
}

void NdrawEnemy()
{
   for(int i=0;i<eneYpos.size();i++)
    {
        if(enemySpawnType[i]==4)
        {


        glPushMatrix();

        glPushMatrix();
        glTranslatef(eneyXpos[i],eneYpos[i],0);

        glColor3ub(255,0,0);
        glPushMatrix();
        glScalef(0.1,0.1,0.1);
        glRotatef(80,1.0,0.0,0.0);
        glPushMatrix(); //Save the transformations performed thus far
        glColor3ub(255,0,0);
        glRotatef(-90,1.0,0.0,0.0);
        glutSolidCone(1,2,20,20);
        glPopMatrix();
        glPushMatrix(); //Save the transformations performed thus far
        glRotatef(-90,0.0,1.0,0.0);
        glutSolidCone(1,2,20,20);
        glPopMatrix();
        glPushMatrix(); //Save the transformations performed thus far
        glRotatef(-90,0.0,-1.0,0.0);
        glutSolidCone(1,2,20,20);
        glPopMatrix();
        glPushMatrix(); //Save the transformations performed thus far
        glRotatef(-90,1.0,1.0,0.0);
        glutSolidCone(1,2,20,20);
        glPopMatrix();
        glPushMatrix(); //Save the transformations performed thus far
        glRotatef(-90,1.0,-1.0,0.0);
        glutSolidCone(1,2,20,20);
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
        eraseEnemy(i);

        glPopMatrix();
            continue;
        }


        if(enemySpawnType[i]==3)
        {
          glPushMatrix();
          glTranslatef(eneyXpos[i],eneYpos[i],.1);
            ///healthbuff spawn design
                glPushMatrix();
                    glTranslatef(0,0,0.1);
                    enemySpawn3();
                glPopMatrix();
            glPopMatrix();
            continue;
        }

        if(enemySpawnType[i]==1)
        {   glPushMatrix();
                glTranslatef(eneyXpos[i],eneYpos[i],.1);
                enemySpawn1();
            glPopMatrix();
            continue;
        }

        glPushMatrix();
                glTranslatef(eneyXpos[i],eneYpos[i],.1);
                enemySpawn2();
            glPopMatrix();

    }
}


void drawBoss(){
    glPushMatrix();
        glTranslatef(bossX,bossY,bossZ);
        glScalef(.35,.35,.35);
    int r=203;int g=203;
    if(bosshit)
    {
        bosshit=false;
        r=255;g=0;
    }
        glPushMatrix();
        glColor3ub(r,g,0);
        glutSolidOctahedron();
        glPopMatrix();

        glPushMatrix();
        glColor3ub(255,255,0);
        glRotatef(45,0,1,0);
        glutSolidOctahedron();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0,.35);
    glPushMatrix();
        glTranslatef(bossX,bossY,0);
        glColor3ub(255,0,255);
        glRotatef(angleToRotate,0,-1,0);
        glutSolidTorus(0.02,0.5,50,50);

    glPopMatrix();

    glPushMatrix();
        glTranslatef(bossX,bossY,0);
        glColor3ub(255,0,255);
        glRotatef(angleToRotate,0,1,0);
        glutSolidTorus(0.02,0.5,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(bossX,bossY,0);
        glColor3ub(255,0,255);
        glRotatef(angleToRotate,1,0,0);
        glutSolidTorus(0.02,0.5,50,50);
    glPopMatrix();

    glPopMatrix();

}



void DrawBossBullet()
{
    glColor3ub(0,0,200);
        for(int i=0;i<bossBulletX.size();i++)
        {
             glPushMatrix();
                glTranslatef(bossBulletX[i],bossBulletY[i],0.3);
                glutWireSphere(bulletsize,50,50);
            glPopMatrix();
        }
}



void bulletDraw()
{
    glColor3ub(200,0,0);
        for(int i=0;i<bulletXpos.size();i++)
        {
             glPushMatrix();
                glTranslatef(bulletXpos[i],bulletYPos[i],0.3);
                glutWireSphere(bulletsize,50,50);
            glPopMatrix();
        }
}

void eraseHItenemy()
{
    for(int i=0;i<hitCheck.size();i++)
    {
        if(hitCheck[i]==1)
        {
            eraseEnemy(i);
        }
    }
}
void getCoord( int x, int y){
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
	winZ=0;
	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	mousex=posX*100/2;
	mousey=(posY*100)/2;
	glutPostRedisplay();
}

void handleMouseclick(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && game_play==0 && mainmenu==1){
        getCoord(x,y);
        if( mousex >=5 && mousex<=15.0 && mousey>=7.65f ){
            game_play=1;
            game_over=0;
            xyz=0;
            fullscreen=true;
            glutFullScreen();
            Beep(1700,20);
        }

         else if(mousex>=5 && mousex<=15.0 && mousey>=4  && mousey <=5.5)  {
            mainmenu=0;
            howtoplay=1;
            Beep(1500,20);
        }
           else if(mousex>=5 && mousex<=15 && mousey>=-1 && mousey<=2){
             mainmenu=0;
            about=1;
            Beep(1300,20);
        }
         else if(mousex>=3 && mousex<=15 && mousey>=-05 && mousey<=-02){
           Beep(1100,20);
    exit(0);
}
    }

    else if (button == GLUT_LEFT_BUTTON && game_play==0 && mainmenu==0 && about==1){
        getCoord(x,y);
        if(mousex>=-6 && mousex<=0.6 && mousey>=-15 && mousey<=-12){
            mainmenu=1;
            about=0;
            Beep(900,20);
        }
    }
    else if (button == GLUT_LEFT_BUTTON && game_play==0 && mainmenu==0 && howtoplay==1){
        getCoord(x,y);
        if(mousex>=-6 && mousex<=0.6 && mousey>=-15 && mousey<=-12){
            mainmenu=1;
            howtoplay=0;
            Beep(700,20);
        }
    }


}
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


if(game_over==0 && game_play==1){

if(!gameover){
    background();
    healthDesign();
    ScorePrint();
    if(boss)
    {
        bossHealthDesign();

    }

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	glRotatef(_cameraAngle, 0.0, 0.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units
    gluLookAt(0,0,1,0,0,-1,0,1,0);


glPushMatrix();
glRotatef(angle,0.0,1.0,1.0);
glScalef(.9,1,1);
glPushMatrix();
glRotatef(70.0,-1.0,0.0,0.0);


if(healthLimit<-1.1||bossHP<-1.1)
{
    cout<<"over"<<endl;
    cout<<score<<endl;
    gameover=true;

    if(bossHP<-1.1)
    {
        winner=true;
    }
}
    platformdesign();
    if(score<=75)
    {
       shipDesign();

    }else if(score>75)
    {
        shipDesign2();
    }

 if(bossupdate)
 {
     drawBoss();
 }

 if(boss==false || transition==true && bossupdate==false){
   NdrawEnemy();
 }else{

    drawBoss();

    if(transition==false)
        DrawBossBullet();
 }

 if(transition==false)
    bulletDraw();


glPopMatrix();

glPopMatrix();
 }
 else{
if(winner)
{
    StatusPrint(s3);

}else
{
    StatusPrint(s4);

}

 GameOverPrint();

 GameOverScene();
        fullscreen=false;
        glutPositionWindow(100,30);
        glutReshapeWindow(1200,800);
        gameReload=true;

 }
}
else if(game_play==0 && mainmenu==1){
		glPushMatrix();
            glTranslatef(0.0f, 0.0f,-5.0f);
            glColor3f(0.0f,0.0f,0.0f);
            MainMenu();
		glPopMatrix();
	}
	 else if(mainmenu==0 && howtoplay==1 && game_play==0){
        glPushMatrix();
            glTranslatef(0.0f, 0.0f,-5.0f);
            glColor3f(0.0f,0.0f,0.0f);
            howToPlay();
		glPopMatrix();
	}
	else if(mainmenu==0 && about==1 && game_play==0){
        glPushMatrix();
            glTranslatef(0.0f, 0.0f,-5.0f);
            glColor3f(0.0f,0.0f,0.0f);
            showAbout();
		glPopMatrix();
	}

	glutSwapBuffers();


}

void specialkey(int key,int  x,int y)
{

    if(key==GLUT_KEY_RIGHT){
     if(angle<25 && trans<2.5){
            angle+=1.0f;
            trans+=0.25f;
            cout<<angle<<" "<<trans<<endl;
    }

    glutPostRedisplay();

    }


    if(key==GLUT_KEY_LEFT){
        if(angle>-25 && trans>-2.5){
            angle-=1.0f;
           trans-=0.25f;
        cout<<angle<<" "<<trans<<endl;
    }
    glutPostRedisplay();

    }

}


void KeyboardCallback(unsigned char key, int x, int y)
{
    if(key==' ' && transition==false){
        float temp=trans;

        bulletXpos.push_back(temp);
        bulletYPos.push_back(-3);

    }

       if(key==27){
        exit(0);

    }

    if(key=='f'&&fullscreen==false)
    {
        fullscreen=true;
        glutFullScreen();
    }else if(key=='f'&&fullscreen==true)
    {

        fullscreen=false;
        glutPositionWindow(100,30);
        glutReshapeWindow(1200,800);
    }

    if(key=='p'&&pauseGame==true)
    {
        pauseGame=false;
        PlaySound(TEXT("resume.wav"), NULL, SND_ASYNC);
    }else if(key=='p'&&pauseGame==false)
    {
        pauseGame=true;
        PlaySound(TEXT("pause.wav"), NULL, SND_ASYNC);
    }

   /* if(key=='r'&&gameReload==true)
    {
        mainmenu=1;
        game_play=0;
        gameover=false;
    }*/


}




void enemyspawnUpdate()
{

        for(int i=0;i<eneYpos.size();i++)
        {
            eneYpos[i]-=0.2;

            if(eneYpos[i]<-3)
            {
                deaths++;
                healthLimit-=healthDec;
                eraseEnemy(i);
                enemycount++;
            }
        }

}


void enemyGenLoc()
{
     if(enemycount>0)
        {
            int i=rand()%2;
            enemycount-i;

            if(enemycount<0)
            {
                    i=enemycount;
                    enemycount=0;
            }


            for(int j=0;j<i;j++)
            {
                int pos=rand()%eneypos.size();
                eneposCheck[pos]+=1;
                eneYpos.push_back(3);
                float temp=eneypos[pos];
                eneyXpos.push_back(temp);

                if((rand()%100+1)%buffProb==0)
                {

                    enemySpawnType.push_back(3);
                    cout<<(rand()%100+1)%buffProb<<" buff"<<endl;

                }else{
                        enemySpawnType.push_back(rand()%2);

                }

                hitCheck.push_back(0);

            }


        }
}

void collisionDetection(int i)
{
     for(int j=0;j<eneYpos.size();j++)
            {

                if(abs(bulletYPos[i]-eneYpos[j])<=bulletsize &&abs(bulletXpos[i]-eneyXpos[j])<=bulletsize)
                {
                    bulletYPos.erase(bulletYPos.begin() + i);
                    bulletXpos.erase(bulletXpos.begin()+i);

                    hitCheck[j]=1;
                    Beep(1000,20);

                    if(enemySpawnType[j]==3)
                    {
                        healthLimit+=3*healthDec;
                        if(healthLimit>1.15)
                        {
                            healthLimit=1.15;
                            score+=10;
                        }

                    }
                        enemySpawnType[j]=4;

                    cout<<hitCheck.size()<<" "<<eneYpos.size()<<" test "<<endl;

                    cout<<"bulletYpos"<<bulletYPos[i]<<"bulletXpos"<<bulletXpos[i]<<endl;
                    cout<<"bulletYpos"<<bulletYPos[i]<<"bulletXpos"<<bulletXpos[i]<<endl;

                    score++;
                    break;

                }


            }
}


void bossXUpdate()
{
    if(transition==true && eneYpos.empty())
    {
        bossZ-=0.1;
        timer=300;
        if(bossZ<0.3)
        {
            transition=false;
            bossupdate==false;
            bossZ=0.3;
            timer=100;
        }
        return;
    }


    if(leftC)
    {
        if(bossX-0.25<-2.5)
        {
            leftC=false;
            bossX+=0.25;
        }else{

            bossX-=0.25;
        }
    }
    else {

        if(bossX+0.25>2.5)
        {
            leftC=true;
            bossX-=0.25;
        }
        else{

            bossX+=0.25;
        }

    }
}

void BossBullet()
{
    bossBulletX.push_back(bossX);
    bossBulletY.push_back(bossY);
}


void BossBulletUpdate()
{
    for(int i=0;i<bossBulletX.size();i++)
    {
        bossBulletY[i]-=0.3;

        if(bossBulletY[i]<-3.5)
        {
                bossBulletY.erase(bossBulletY.begin() + i);;
                bossBulletX.erase(bossBulletX.begin()+i);
        }
    }
}

void bossbulletCollision()
{
    for(int i=0;i<bossBulletX.size();i++)
    {
         if(abs(bossBulletY[i]-(-3))>=0&&abs(bossBulletY[i]-(-3))<=bulletsize && abs(bossBulletX[i]-trans)>=0&&abs(bossBulletX[i]-trans)<=bulletsize && !gameover)
         {

                bossBulletX.erase(bossBulletX.begin() + i);;
                bossBulletY.erase(bossBulletY.begin()+i);
                healthLimit-=0.08;
                cout<<"player hit"<<endl;

         }
    }

}

void bossHitDetect()
{

        for(int i=0;i<bulletXpos.size();i++)
        {
             if(abs(bulletYPos[i]-(3))<=bulletsize &&abs(bossBulletX[i]-trans)<=bulletsize && !gameover)
         {
                cout<<" boss hit"<<endl;
                score++;
                bulletYPos.erase(bulletYPos.begin() + i);;
                bulletXpos.erase(bulletXpos.begin()+i);
                if(bossHP>-1.2)
                {
                    bossHP-=.1;
                    bosshit=true;
                    Beep(300,20);
                }

                if(bossHP<-1.1)
                {
                    gameover=true;
                    winner=true;
                }
         }
    }

}

void update(int value) {

    if(pauseGame==false && gameover==false && xyz==0)
    {
            if(score>100 && boss ==false && transition==false)
            {
                boss=true; transition=true;

                 for(int i=0;i<bulletXpos.size();i++)
                {
                    bulletYPos.erase(bulletYPos.begin() + i);
                    bulletXpos.erase(bulletXpos.begin()+i);
                }

            }

            if(transition==true )
            {
                if(eneYpos.empty())
                {
                    bossupdate=true;
                    bossXUpdate();



                }else{
                    enemySpawnType[0]=4;

                }
            }

            if(boss==false && transition==false){
                eraseHItenemy();
                enemyGenLoc();
                enemyspawnUpdate();
            }


            if(boss==true && transition==false)
            {
                bossXUpdate();
                BossBullet();
                BossBulletUpdate();
                bossbulletCollision();
                bossHitDetect();
            }


        for(int i=0;i<bulletXpos.size();i++)
        {
            bulletYPos[i]+=0.2;
        if(!boss){
            collisionDetection(i);

            }

            if(bulletYPos[i]>3.5)
            {
                bulletYPos.erase(bulletYPos.begin() + i);;
                bulletXpos.erase(bulletXpos.begin()+i);

            }

        }

        movPlat-=.2;

        if(movPlat<=-4)
        {
            movPlat=2;
        }

        angleToRotate+=2.0;
        if(angleToRotate>360)
        {
            angleToRotate-=360;
        }

        angleToRotateEnemy1+=25.0;
        if(angleToRotateEnemy1>360)
        {
            angleToRotateEnemy1-=360;
        }

        angleToRotateEnemy2+=10.0;
        if(angleToRotateEnemy2>360)
        {
            angleToRotateEnemy2-=360;
        }

        angleToRotateEnemy3+=20.0;
        if(angleToRotateEnemy3>360)
        {
            angleToRotateEnemy3-=360;
        }

        angleToRotateBG+=0.2;
        if(angleToRotateBG>360)
        {
            angleToRotateBG-=360;
        }
        _angleeee += 0.3f;
        if (_angleeee > 360) {
            _angleeee -= 360;
        }
        _angl += 1.6f;	glutKeyboardFunc(KeyboardCallback);

        if (_angl > 360) {
            _angl -= 360;
        }
        _anglee += 0.9f;
        if (_anglee > 360) {
            _anglee -= 360;
        }
        _angleee += 1.5f;
        if (_angleee > 360) {
            _angleee -= 360;
        }

    }
	glutPostRedisplay();

	glutTimerFunc(timer, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(100,30);

	//Create the window
	glutCreateWindow("Space Shooting Game");
	enemypos();
	bossXposGen();
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);

	glutReshapeFunc(handleResize);

	glutSpecialFunc(specialkey);
	glutKeyboardFunc(KeyboardCallback);
    glutMouseFunc(handleMouseclick);

	glutTimerFunc(25, update, 0); //Add a timer
	PlaySound(TEXT("resume.wav"), NULL, SND_LOOP | SND_ASYNC);

	glutMainLoop();
	return 0;
}
