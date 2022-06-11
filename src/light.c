#include "light.h"

#include <stdio.h>

void EnableLight()
{
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    // Set two lights for use
    glEnable(GL_LIGHT0);

    // Set Gouraud colorization model
    glShadeModel(GL_SMOOTH);
}

void DefineLight(GLenum light, float position[4], float ambient[4])
{
    //                      R    G    B    A
    GLfloat diffuse[4] =  {1.0, 1.0, 1.0, 1.0};
    GLfloat specular[4] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(light, GL_POSITION, position);
    glLightfv(light, GL_SPECULAR, specular );
    glLightfv(light, GL_DIFFUSE, diffuse );
    //glLightfv(light, GL_AMBIENT, ambient);
}

void DefineMaterial()
{
    // Define a refletância do material
    GLfloat specular[4] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, specular);

    // Define a concentração do brilho
    glMateriali(GL_FRONT_AND_BACK,GL_SHININESS, 60);
}

void SetLight(GLfloat lightPosition[4])
{
    DefineMaterial();

    // Enable ambient light
    //                     R    G    B    A
    GLfloat ambient[4] = {0.1, 0.1, 0.1, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    // Set each light
    DefineLight(GL_LIGHT0, lightPosition, ambient);
}
