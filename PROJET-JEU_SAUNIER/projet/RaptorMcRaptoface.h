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
#include <iostream>
class RaptorMcRaptoface
{
public:
	bool isPlayer;
	bool isDead;
	int HP;
	float posX;
	float posY;
	float posZ;
	Texture * texture_raptor = NULL;
	Model3D  *model_raptor = NULL;
	void RaptorCreate(bool player, float x, float y, float z);
	void Shoot(float posx, float posy, float posz, float rotationAngle);
	RaptorMcRaptoface();
	~RaptorMcRaptoface();
};

