#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include <time.h>

float x_direction=-0.65;
float y_direction=0.95;
float y_point=0;
float x_point=1.0;
int key_r =1;
int key_l =0;
int jump =0;
int flag =1;
int flag_jump =0;
float a[250];
int score_value =0;
int health_value =3;
float x_num = -1.0;
float y_num = -1.0;

float random_num()
{
    float ra=(float)rand() / (float)RAND_MAX;
    float r =fmod((float)rand(),10.0)+ra;
    return  r;
}


void score(int score_value){
    char r2[50];
    sprintf(r2,"%d",score_value);
    char r1[]="Points : ";
    glColor3f(1.0,1.0,1.0);
    glRasterPos3f(-0.98,0.9,0.0);
    for(int i=0;r1[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r1[i]);


    for(int i=0;r2[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r2[i]);
}


void health(int health_value){
    char r2[50];
  sprintf(r2,"%d",health_value);
    char r1[]="Health : ";
    glColor3f(1.0,1.0,1.0);
    glRasterPos3f(0.70,0.9,0.0);
    for(int i=0;r1[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r1[i]);

    for(int i=0;r2[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r2[i]);

}

void hit(float x){
    if(x>=x_direction-0.1  && x<=x_direction+0.2 && y_point<=0.25){
        health_value-=1;
        x_point = 1.0;

    }


}

void finish(int score_value){
    glClear(GL_COLOR_BUFFER_BIT);

    char r3[50];
  sprintf(r3,"%d",score_value);
    char r1[]="*********GAME OVER*********";
    char r2[]="Total point : ";
    glColor3f(1.0,1.0,1.0);
    glRasterPos3f(-0.2,0.0,0.0);
    for(int i=0;r1[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r1[i]);
    glRasterPos3f(-0.25,-0.1,0.0);
    for(int i=0;r2[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r2[i]);

    for(int i=0;r3[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r3[i]);

}

void keyboard_keys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_LEFT:
        key_l=1;
        break;
    case GLUT_KEY_RIGHT:
        key_r=1;
        break;

    case GLUT_KEY_UP:
        jump=1;
        break;
    }
}
void timer(int)
{
    glutTimerFunc(1000/60,timer,0);
    x_point-=0.010;
    if(x_point <= -1.019999){
        x_point = 1.0;
        score_value+=1;
    }
     if(y_direction>-500.0)
    {
        y_direction-=0.005;

    }

    if(jump==1){
        y_point+=0.010;
        if(y_point >= 0.50000){
            flag_jump =1;
        }
        if(flag_jump == 1 && y_point>0.000000){
            y_point-=0.020;
        }
        else if(y_point<=0.000000){
                flag_jump=0;
            jump =0;
        }

    }


     if(key_l==1 && x_direction>=-1)
    {
        x_direction-=0.015;
        key_l=0;
    }
    if(key_r==1 && x_direction<=0.8)
    {
        x_direction+=0.015;
        key_r=0;
    }

    glutPostRedisplay();


}

 void ground(float x_num,float y_num)
 {

    glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_POLYGON);
     glColor3f(0.0,1.0,0.0);
     glVertex2f(x_num,y_num);
     glVertex2f(x_num+2.0,y_num);
     glVertex2f(x_num+2.0,y_num+0.25);
     glVertex2f(x_num,y_num+0.25);
     glEnd();
     glFlush();

 }
 void stickman(float x_direction, float y_point)
 {
    glColor3f(1.0, 0.0, 0.0);
glPointSize(5.0);
glLineWidth(5.0);
glBegin(GL_LINES);
glVertex2f(x_direction-0.1,-0.75+y_point);
     glVertex2f(x_direction,-0.55+y_point);
glEnd();

glBegin(GL_LINES);
glVertex2f(x_direction+0.1,-0.75+y_point);
     glVertex2f(x_direction,-0.55+y_point);
glEnd();

glBegin(GL_LINES);
glVertex2f(x_direction,-0.55+y_point);
     glVertex2f(x_direction,-0.35+y_point);
glEnd();
glBegin(GL_LINES);
glVertex2f(x_direction-0.2,-0.40+y_point);
     glVertex2f(x_direction+0.2,-0.40+y_point);
glEnd();
glBegin(GL_LINES);
glVertex2f(x_direction-0.20,-0.55+y_point);
     glVertex2f(x_direction-0.20,-0.1+y_point);
glEnd();
     glFlush();

 }

void DrawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}


void raindrop(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    glVertex2f(cx, cy+0.01);
    glVertex2f(cx+0.01, cy+0.01);
    glVertex2f(cx+0.01, cy);

    glEnd();
}
void circle_half(float cx=0.0, float cy=0.0, float r=1.0)
{
    int num=50;
    float pi=3.1416;
    glLineWidth(10.0);

    glBegin(GL_TRIANGLE_FAN);
    for(double i=0;i<=num;i+=(0.2))
    {
        float theta = pi*float(i)/float(num);
        float x= r*cosf(theta);
        float y= r*sinf(theta);
         glColor3f(1.0,1.0,1.0);

        glVertex2d(x+cx,y+cy);
    }
    glEnd();
}
void obstacle(float x_point){
    glBegin(GL_POLYGON);
    hit(x_point);
    glVertex2f(x_point, -0.75);
    glVertex2f(x_point-0.1, -0.75);
    glVertex2f(x_point-0.1, -0.50);
    glVertex2f(x_point, -0.50);

    glEnd();

}
void display()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

ground(x_num,y_num);
score(score_value);
    health(health_value);
    if(health_value<=0){
        finish(score_value);
        x_num = 20.0;
        y_num = 20.0;
        x_point=100.0;
        x_direction=2.0;
        y_direction=100.0;
    }

stickman(x_direction,y_point);
DrawCircle(x_direction, -0.25+y_point, 0.1, 1000);
circle_half(x_direction-0.2, -0.1+y_point, 0.1);
obstacle(x_point);
if(flag){
    for(int i=0; i<250;i++){
            a[i] =random_num();

        }
        flag =0;
    }

    for(int i=0;i<250;i=i+7)
    {

raindrop(-0.9, y_direction+a[i], 0.01, 1000);
raindrop(-0.7, y_direction+a[i+1], 0.01, 1000);
raindrop(-0.5, y_direction+a[i+2], 0.01, 1000);
raindrop(-0.3, y_direction+a[i+3], 0.01, 1000);
raindrop(0.0, y_direction+a[i+4], 0.01, 1000);
raindrop(0.2, y_direction+a[i+5], 0.01, 1000);
raindrop(0.5, y_direction+a[i+6], 0.01, 1000);
raindrop(0.7, y_direction+a[i+7], 0.01, 1000);
    }

glutSwapBuffers();
}


void init()
{
glClearColor(1.0,1.0,1.0,1.0);
}
 int main(int argc,char** argv)
 {
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
     glutInitWindowSize(1000,700);
     glutInitWindowPosition(200,20);
     glutCreateWindow("stick man Game ");
     glutTimerFunc(0,timer,0);
     glutDisplayFunc(display);
    glutSpecialFunc(keyboard_keys);
     glutMainLoop();
     return 0;
 }
