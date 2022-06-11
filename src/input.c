#include <GL/glut.h>

#include "input.h"
#include "map.h"

int wireFrameMode = 0;

void KeyboardKeyDown(unsigned char key, int _x, int _y)
{
    Camera* camera = &program.camera;
    switch(key)
    {
        case 'w':
            if (wireFrameMode)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                wireFrameMode = 0;
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                wireFrameMode = 1;
            }
            break;
        case 'a':
            lightY += 2.0f;
            break;
        case 'z':
            lightY -= 2.0f;
            break;
        case '-':
            scale -= 0.2f;
            break;
        case '+':
            scale += 0.2f;
            break;
        case '?':
            DrawCameraInfo(camera);
            break;
        case 27:
            exit(0);
            break;
    }

    glutPostRedisplay();
}

void KeyboardSpecialKeyDown(int key, int x, int y)
{
    switch (key)
    {
        //case GLUT_KEY_HOME: if(angle>=10)  angle -=5;
        //                    break;
        //case GLUT_KEY_END:  if(angle<=150) angle +=5;
        //                    break;
        case GLUT_KEY_UP:
            lightZ -= 2.0f;
            break;
        case GLUT_KEY_DOWN:
            lightZ += 2.0f;
            break;
        case GLUT_KEY_LEFT:
            lightX -= 2.0f;
            break;
        case GLUT_KEY_RIGHT:
            lightX += 2.0f;
            break;
        case GLUT_KEY_F5:   glEnable(GL_LIGHT0);
                            break;
        case GLUT_KEY_F6:   glDisable(GL_LIGHT0);
                            break;
    }

    glutPostRedisplay();
}

void MouseButton(int button, int state, int x, int y)
{
}

void MouseMove(int x, int y)
{
}
