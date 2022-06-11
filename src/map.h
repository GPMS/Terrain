#pragma once

#include "main.h"

extern const int tileSize;

void PrintMap(Map *map);
void LoadMap(Map* map);
void GenerateMap(Map* map);
void DestroyMap(Map* map);
void DrawMap(const Map* map);
