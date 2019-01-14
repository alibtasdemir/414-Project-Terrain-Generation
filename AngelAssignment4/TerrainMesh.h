#pragma once
#include "PerlinNoise.h"
#include "Mesh.h"
#include <vector>
//siv::PerlinNoise perlinNoise;
float PerlinNoise(float x, float y);
//Mesh GenerateFlatMesh(float sizeX, float sizeZ, float step);
Mesh* GenerateTerrainMesh(float sizeX, float sizeZ, float step);