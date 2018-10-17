#pragma once
#include "../sources/window.h"
#include "../sources/input.h"
#include "../sources/timer.h"
#include "../sources/ogl.h"
#include "../sources/load.h"
#include "../sources/camera.h"
#include "../sources/maths_3d.h"
#include "AL/al.h"
#include "AL/alc.h"

class Terrain
{
public:
	Texture * texture_grass = NULL;
	Texture  *texture_fence = NULL;
	Texture  *texture_sky = NULL;
	Terrain();
	void CreateTerrain();
	void Grass();
	void Fences();
	void Skybox();
	void Tree();
	~Terrain();
};

