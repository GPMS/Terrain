#include <stdio.h>

#include "vector.h"

void SetVec3(Vec3* vec, float x, float y, float z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

// vec = vec1 - vec2
void SubVec3(Vec3* vec, const Vec3* vec1, const Vec3* vec2)
{
    vec->x = vec1->x - vec2->x;
    vec->y = vec1->y - vec2->y;
    vec->z = vec1->z - vec2->z;
}

void CrossProductVec3(Vec3* vec, const Vec3* vec1, const Vec3* vec2)
{
    vec->x = vec1->y * vec2->z - vec1->z * vec2->y;
    vec->y = vec1->x * vec2->z - vec1->z * vec2->x;
    vec->z = vec1->x * vec2->y - vec1->y * vec2->x;
}

void PrintVec3(const Vec3 vec, const char *name)
{
    printf("%s (%.0f, %.0f, %.0f)\n", name, vec.x, vec.y, vec.z);
}
