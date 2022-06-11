#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <GL/gl.h>

const int tileSize = 10;

void PrintMap(Map *map)
{
    size_t size = map->size;

    printf("%ldx%ld\n", size, size);
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
            printf("%3.2f ", map->data[i][j]);
        printf("\b\n");
    }
}

int randomNumber(int minNum, int maxNum)
{
    int result = 0, lowNum = 0, hiNum = 0;

    if (minNum < maxNum)
    {
        lowNum = minNum;
        hiNum = maxNum + 1; // include max_num in output
    } else {
        lowNum = maxNum + 1; // include max_num in output
        hiNum = minNum;
    }

    result = (rand() % (hiNum - lowNum)) + lowNum;
    return result;
}

void GenerateMap(Map* map)
{
    size_t size;

    map->size = size = randomNumber(20, 100);

    map->data = (float**) malloc(sizeof(float*) * size);
    for (int i = 0; i < size; i++)
    {
        map->data[i] = (float*) malloc(sizeof(float) * size);
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            map->data[i][j] = randomNumber(0, 500);
    }
}

void LoadMap(Map* map)
{
    size_t size = 0;

    FILE* fp = fopen("heightMap.csv", "r");

    // No file!
    // Go with default 5x5 size
    if (!fp)
    {
        // Size allocation
        map->size = size = 5;
        map->data = (float**) malloc(sizeof(float*) * size);
        for (int i = 0; i < size; i++)
        {
            map->data[i] = (float*) malloc(sizeof(float) * size);
        }

        // Fill it with 0s
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
                map->data[i][j] = 0.0f;
        }
    }
    else
    {
        // Map size is commaCount+1 x commaCount+1
        int ch;
        int commaCount = 0;
        while ((ch=fgetc(fp)) != EOF)
        {
            if (ch == ',')
                commaCount++;
            else if (ch == '\n')
                break;
        }

        // Size allocation
        map->size = size = commaCount+1;
        map->data = (float**) malloc(sizeof(float*) * size);
        for (int i = 0; i < size; i++)
        {
            map->data[i] = (float*) malloc(sizeof(float) * size);
        }

        // Rewind to the beginning of the file
        fseek(fp, 0, SEEK_SET);

        // Read numbers and fill map->data
        int i = 0;
        int j = 0;
        int count = 0;
        char buffer[20] = {'\0'};
        while ((ch=fgetc(fp)) != EOF)
        {
            if (ch == ',')
            {
                sscanf(buffer, "%f", &map->data[i][j]);
                memset(buffer, '\0', sizeof(buffer));
                count = 0;
                j++;
            }
            else if (ch == '\n')
            {
                sscanf(buffer, "%f", &map->data[i][j]);
                memset(buffer, '\0', sizeof(buffer));
                count = 0;
                j = 0;
                i++;
                if (i >= size)
                    break;
            }
            else if (isxdigit(ch) || ch == '.')
            {
                buffer[count++] = ch;
            }
        }
    }
}

void DestroyMap(Map* map)
{
    for (int i=0; i < map->size; i++)
        free(map->data[i]);
    free(map->data);
}

float GetX(int x, size_t size)
{
    float startX = -((size * tileSize) / 2.0f);
    return startX + x*tileSize;
}

float GetZ(int y, size_t size)
{
    float startZ = -((size * tileSize) / 2.0f);
    return startZ + y*tileSize;
}

void SetNormalVector(GLfloat vertex0[3], GLfloat vertex1[3], GLfloat vertex2[3])
{
    Vec3 vertex[3];
    SetVec3(&vertex[0], vertex0[0], vertex0[1], vertex0[2]);
    SetVec3(&vertex[1], vertex1[0], vertex1[1], vertex1[2]);
    SetVec3(&vertex[2], vertex2[0], vertex2[1], vertex2[2]);

    Vec3 vectors[2];
    // 1 -> 0
    SubVec3(&vectors[0], &vertex[0], &vertex[1]);
    // 1 -> 2
    SubVec3(&vectors[1], &vertex[2], &vertex[1]);

    Vec3 normal;
    CrossProductVec3(&normal, &vectors[0], &vectors[1]);

    //PrintVec3(normal, "Normal");

    glNormal3f(normal.x, normal.y, -normal.z);
}

void GetVertex(GLfloat vertex[3], int x, int y, const Map* map)
{
    vertex[0] = GetX(x, map->size);
    vertex[1] = map->data[y][x] * 100;
    vertex[2] = GetZ(y, map->size);
}

void DrawMap(const Map* map)
{
    size_t size = map->size;

    for (int y = 0; y < size-1; y++)
    {
        glBegin(GL_QUADS);
        for (int x = 0; x < size-1; x++)
        {
            // Get coordinates
            // 0 --- 1
            // |     |
            // 3 --- 2
            GLfloat vertex[4][3];
            GetVertex(vertex[0],   x,   y, map);
            GetVertex(vertex[1], x+1,   y, map);
            GetVertex(vertex[2], x+1, y+1, map);
            GetVertex(vertex[3],   x, y+1, map);

            // Draw
            for (int i = 0; i < 4; i++)
                glVertex3fv(vertex[i]);

            SetNormalVector(vertex[0], vertex[3], vertex[2]);
        }
        glEnd();
    }
    glEnable(GL_NORMALIZE);
}
