#pragma once

#include <stdio.h>

#include <GL/glu.h>

#include "vector.h"

#define PI 3.14159265

typedef struct {
    Vec3 pos;
    Vec3 target;
    Vec3 rolling;
} Camera;

typedef struct {
    GLfloat x, y;
} Rotation;

typedef struct {
    Vec3 position;
    Vec3 initialPosition;

    Rotation rotation;
    Rotation initialRotation;
} Observer;

typedef struct {
    float** data;
    size_t size;
} Map;

typedef struct {
    Camera camera;
    Observer observer;

    Map heightMap;

    int running;
} Program;

extern const int WIDTH;
extern const int HEIGHT;

extern Program program;

extern float lightX;
extern float lightY;
extern float lightZ;

extern float scale;

void DrawCameraInfo(const Camera* camera);
