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
class Forest
{
public:
	Texture * texture_a = NULL;
	Forest();
	void Tree();
	void ForestCreate(float xmin, float xmax, float zmin, float zmax, float sizerow, float sizecolumn);
	~Forest();
};

