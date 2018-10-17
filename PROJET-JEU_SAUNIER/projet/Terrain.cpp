#include "terrain.h"



Terrain::Terrain()
{
	texture_grass = new Texture();
	texture_grass->load_texture("grass.tga", NULL);
	glGenTextures(1, texture_grass->OpenGL_ID);
	
	glBindTexture(GL_TEXTURE_2D, texture_grass->OpenGL_ID[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // on répète la texture en cas de U,V > 1.0
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    // ou < 0.0
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // indique qu'il faut mélanger la texture avec la couleur courante

																 // charge le tableau de la texture en mémoire vidéo et crée une texture mipmap

	if (texture_grass->isRGBA)
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, texture_grass->img_color->lenx, texture_grass->img_color->leny, GL_RGBA, GL_UNSIGNED_BYTE, texture_grass->img_all);
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, texture_grass->img_color->lenx, texture_grass->img_color->leny, GL_RGB, GL_UNSIGNED_BYTE, texture_grass->img_color->data);




	texture_fence = new Texture();
	texture_fence->load_texture("fence2.tga", NULL);
	glGenTextures(1, texture_fence->OpenGL_ID);

	glBindTexture(GL_TEXTURE_2D, texture_fence->OpenGL_ID[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // on répète la texture en cas de U,V > 1.0
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    // ou < 0.0
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // indique qu'il faut mélanger la texture avec la couleur courante

																 // charge le tableau de la texture en mémoire vidéo et crée une texture mipmap

	if (texture_fence->isRGBA)
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, texture_fence->img_color->lenx, texture_fence->img_color->leny, GL_RGBA, GL_UNSIGNED_BYTE, texture_fence->img_all);
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, texture_fence->img_color->lenx, texture_fence->img_color->leny, GL_RGB, GL_UNSIGNED_BYTE, texture_fence->img_color->data);

	
	
	texture_sky = new Texture();
	texture_sky->load_texture("skybox2.tga", NULL);
	glGenTextures(1, texture_sky->OpenGL_ID);

	glBindTexture(GL_TEXTURE_2D, texture_sky->OpenGL_ID[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // on répète la texture en cas de U,V > 1.0
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    // ou < 0.0
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // indique qu'il faut mélanger la texture avec la couleur courante

																 // charge le tableau de la texture en mémoire vidéo et crée une texture mipmap

	if (texture_sky->isRGBA)
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, texture_sky->img_color->lenx, texture_sky->img_color->leny, GL_RGBA, GL_UNSIGNED_BYTE, texture_sky->img_all);
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, texture_sky->img_color->lenx, texture_sky->img_color->leny, GL_RGB, GL_UNSIGNED_BYTE, texture_sky->img_color->data);
}


void Terrain::CreateTerrain() {
	Grass();
	Fences();
	Skybox();
}

void Terrain::Grass() {
	glBindTexture(GL_TEXTURE_2D, texture_grass->OpenGL_ID[0]);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 0); glVertex3f(-200, 0, 200);
	glTexCoord2d(1, 1); glVertex3f(200, 0, 200);
	glTexCoord2d(0, 1); glVertex3f(200, 0, -200);
	glTexCoord2d(0, 0); glVertex3f(-200, 0, -200);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Terrain::Fences(){
	glBindTexture(GL_TEXTURE_2D, texture_fence->OpenGL_ID[0]);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(-200, 0, 200);
	glTexCoord2d(1, 0); glVertex3f(-200, 0, -200);
	glTexCoord2d(1, 1); glVertex3f(-200, 50, -200);
	glTexCoord2d(0, 1); glVertex3f(-200, 50, 200);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 0); glVertex3f(-200, 0, 200);
	glTexCoord2d(1, 1); glVertex3f(-200, 50, 200);
	glTexCoord2d(0, 1); glVertex3f(200, 50, 200);
	glTexCoord2d(0, 0); glVertex3f(200, 0, 200);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 1); glVertex3f(200, 50, 200);
	glTexCoord2d(0, 1); glVertex3f(200, 50, -200);
	glTexCoord2d(0, 0); glVertex3f(200, 0, -200);
	glTexCoord2d(1, 0); glVertex3f(200, 0, 200);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(-200, 0, -200);
	glTexCoord2d(1, 0); glVertex3f(-20, 0, -200);
	glTexCoord2d(1, 1); glVertex3f(-20, 50, -200);
	glTexCoord2d(0, 1); glVertex3f(-200, 50, -200);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(20, 0, -200);
	glTexCoord2d(1, 0); glVertex3f(200, 0, -200);
	glTexCoord2d(1, 1); glVertex3f(200, 50, -200);
	glTexCoord2d(0, 1); glVertex3f(20, 50, -200);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void Terrain::Skybox() {
	glBindTexture(GL_TEXTURE_2D, texture_sky->OpenGL_ID[0]);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 0); glVertex3f(-500, 50, 500);
	glTexCoord2d(1, 1); glVertex3f(-500, 50, -500);
	glTexCoord2d(0, 1); glVertex3f(500, 50, -500);
	glTexCoord2d(0, 0); glVertex3f(500, 50, 500);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(-500, 0, -300);
	glTexCoord2d(1, 0); glVertex3f(500, 0, -300);
	glTexCoord2d(1, 1); glVertex3f(500, 150, -300);
	glTexCoord2d(0, 1); glVertex3f(-500, 150, -300);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

Terrain::~Terrain()
{
}
