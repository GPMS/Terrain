#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <GL/glut.h>

#include "main.h"
#include "input.h"
#include "vector.h"
#include "map.h"
#include "light.h"

#define DRAWLIGHT 1

const int WIDTH = 500;
const int HEIGHT = 500;

float lightX = -50.0f;
float lightY = 300.0f;
float lightZ = 50.0f;

float scale = 1;

Program program;

// Colors
//                            R    G    B
const GLfloat black[]   =   {0.0, 0.0, 0.0};
const GLfloat gray[]    =   {0.5, 0.5, 0.5};
const GLfloat white[]   =   {1.0, 1.0, 1.0};
const GLfloat red[]     =   {1.0, 0.0, 0.0};
const GLfloat green[]   =   {0.0, 1.0, 0.0};
const GLfloat blue[]    =   {0.0, 0.0, 1.0};
const GLfloat yellow[]  =   {1.0, 1.0, 0.0};

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    SetVec3(&program.camera.pos, 0.0f, 10.0f, 10.0f);
    SetVec3(&program.camera.target, 0.0f, 0.0f, 0.0f);
    SetVec3(&program.camera.rolling, 0.0f, 1.0f, 0.0f);

    glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -WIDTH/2, WIDTH/2);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glShadeModel(GL_SMOOTH);

    time_t t;
    srand((unsigned) time(&t));

    LoadMap(&program.heightMap);
    //GenerateMap(&program.heightMap);

    EnableLight();
}

void SetCamera(const Camera* camera)
{
    gluLookAt(camera->pos.x, camera->pos.y, camera->pos.z,
              camera->target.x, camera->target.y, camera->target.z,
              camera->rolling.x, camera->rolling.y, camera->rolling.z);
}

void display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SetCamera(&program.camera);

    GLfloat lightPosition[4] = { lightX, lightY, lightZ, 1.0f};
    printf("%.0f, %.0f, %.0f\n", lightX, lightY, lightZ);
    SetLight(lightPosition);

    glPushMatrix();
        glScalef(scale, scale, scale);
        glColor3fv(blue);
        DrawMap(&program.heightMap);
    glPopMatrix();

#if DRAWLIGHT
    glColor3fv(yellow);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex3f(lightPosition[0], lightPosition[1], lightPosition[2]);
    glEnd();

    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glColor3fv(red);
        glVertex3f(lightPosition[0], lightPosition[1], lightPosition[2]);
        glVertex3f(lightPosition[0], 0.0f, lightPosition[2]);

        glColor3fv(blue);
        glVertex3f(lightPosition[0], 0.0f, lightPosition[2]);
        glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
#endif

    //glFlush();
    glutSwapBuffers();
}

void DrawCameraInfo(const Camera* camera)
{
    printf("Camera Info:\n");
    PrintVec3(camera->pos, "Position");
    PrintVec3(camera->target, "Target");
    PrintVec3(camera->rolling, "Rolling");
}

void ReshapeWindow(GLsizei w, GLsizei h)
{
    // Prevent zero division
    if ( h == 0 ) h = 1;

    glViewport(0, 0, w, h);
}

/*
void SetObserver(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    SetLight();

    // Position and orientate observer
    Observer* observer = &program.observer;

    glTranslatef(-observer->position.x,
                 -observer->position.y,
                 -observer->position.z);
    glRotatef(observer->rotation.x,1,0,0);
    glRotatef(observer->rotation.y,0,1,0);
}

void SetVizualisationParameters(void)
{
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coor->denadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
    gluPerspective(angle,fAspect,0.5,500);

    SetObserver();
}*/

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    // Especifica o buffer a ser utilizado
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Janela inicial");
    glutReshapeFunc(ReshapeWindow);

    glutDisplayFunc(display);

    // Keyboard
    glutKeyboardFunc(KeyboardKeyDown);
    glutSpecialFunc(KeyboardSpecialKeyDown);

    // Mouse
    glutMouseFunc(MouseButton);
    glutMotionFunc(MouseMove);

    init();

    glutMainLoop();

    return 0;
}
