#pragma once

typedef struct {
    float x, y, z;
} Vec3;

void SetVec3(Vec3* vec, float x, float y, float z);
void SubVec3(Vec3* vec, const Vec3* vec1, const Vec3* vec2);
void CrossProductVec3(Vec3* vec, const Vec3* vec1, const Vec3* vec2);
void PrintVec3(const Vec3 vec, const char *name);
