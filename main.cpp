#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

#include <time.h>

float x_direction=-1.0;
float y_direction=0.95;
int key_r =1;
int key_l =0;
int flag =1;
float a[250];
float random_num()
{

    float ra=(float)rand() / (float)RAND_MAX;
    float r =fmod((float)rand(),10.0)+ra;
    return  r;
}
void keyboard_keys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_LEFT:
        key_l=1;
        //printf("%d",key_l);
        break;
    case GLUT_KEY_RIGHT:
        key_r=1;
        //printf("%d",key_r);
        break;
    }
}
void timer(int)
{
    glutTimerFunc(1000/60,timer,0);
     if(y_direction>-500.0)
    {
        y_direction-=0.005;

    }
    x_direction+=0.010;

     if(key_r==1 && x_direction<=0.8)
    {
        x_direction+=0.010;
        key_r=1;
        key_l =0;
        //printf("%f",x_direction);
    }
    else
    {
        x_direction-=0.010;
        key_r=0;
        if(key_l==1 && x_direction>=-0.70){
            x_direction-=0.020;
        }
        else{
            key_l=0;
        }
        //printf("%f",x_direction);
    }

    glutPostRedisplay();


}

 void ground(void) //groud 
 {

    glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_POLYGON);
     glColor3f(0.0,1.0,0.0);
     glVertex2f(-1.0,-1.0);
     glVertex2f(1.0,-1.0);
     glVertex2f(1.0,-0.75);
     glVertex2f(-1.0,-0.75);
     glEnd();
     glFlush();

 }
 void stickman(float x_direction)
 {
    glColor3f(1.0, 0.0, 0.0);
glPointSize(5.0);
glLineWidth(5.0);
glBegin(GL_LINES);
glVertex2f(x_direction-0.1,-0.75);
     glVertex2f(x_direction,-0.55);
glEnd();

glBegin(GL_LINES);
glVertex2f(x_direction+0.1,-0.75);
     glVertex2f(x_direction,-0.55);
glEnd();

glBegin(GL_LINES);
glVertex2f(x_direction,-0.55);
     glVertex2f(x_direction,-0.35);
glEnd();
glBegin(GL_LINES);
glVertex2f(x_direction-0.2,-0.40);
     glVertex2f(x_direction+0.2,-0.40);
glEnd();
glBegin(GL_LINES);
glVertex2f(x_direction-0.20,-0.55);
     glVertex2f(x_direction-0.20,-0.1);
glEnd();
     glFlush();

 }

void DrawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
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

void display()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

ground();
stickman(x_direction);
DrawCircle(x_direction, -0.25, 0.1, 1000);
circle_half(x_direction-0.2, -0.1, 0.1);
if(flag){
    for(int i=0; i<250;i++){
            a[i] =random_num();
            //printf("%f\n",a[i]);
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
//gluOrtho2D(0,300,0,300);
}
 int main(int argc,char** argv)
 {
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
     glutInitWindowSize(1000,700);
     glutInitWindowPosition(200,20);
     glutCreateWindow("stick man animation");
     glutTimerFunc(0,timer,0);
     glutDisplayFunc(display);
    glutSpecialFunc(keyboard_keys);
     glutMainLoop();
     return 0;
 }
