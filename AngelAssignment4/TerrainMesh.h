#pragma once
#include "PerlinNoise.h"
#include "Mesh.h"
#include <vector>
float remap(float minval, float maxval, float curval);
//siv::PerlinNoise perlinNoise;
float PerlinNoise(float x, float y);
//Mesh GenerateFlatMesh(float sizeX, float sizeZ, float step);
Mesh* GenerateTerrainMesh(float sizeX, float sizeZ, float step);