#include "Forest.h"


Forest::Forest()
{
	texture_a = new Texture();
	texture_a->load_texture("arbre.tga", "arbre_masque.tga");

	glGenTextures(1, texture_a->OpenGL_ID);                // crée un "nom" de texture (un identifiant associé à la texture)

	glAlphaFunc(GL_GREATER, 0.3);

	glBindTexture(GL_TEXTURE_2D, texture_a->OpenGL_ID[0]);    // et on active ce "nom" comme texture courante (définie plus bas)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // on répète la texture en cas de U,V > 1.0
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    // ou < 0.0


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // indique qu'il faut mélanger la texture avec la couleur courante


																 // charge le tableau de la texture en mémoire vidéo et crée une texture mipmap

	if (texture_a->isRGBA)
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, texture_a->img_color->lenx, texture_a->img_color->leny, GL_RGBA, GL_UNSIGNED_BYTE, texture_a->img_all);
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, texture_a->img_color->lenx, texture_a->img_color->leny, GL_RGB, GL_UNSIGNED_BYTE, texture_a->img_color->data);
}

void Forest::ForestCreate(float xmin, float xmax, float zmin, float zmax, float sizerow, float sizecolumn) {
	if (sizerow > 0 && sizecolumn > 0) {
		for (int x = xmin; x < xmax; x += (xmax - xmin) / sizerow) {
			for (int z = zmin; z < zmax; z += (zmax - zmin) / sizecolumn) {
				glPushMatrix();
				glTranslatef(x, 0, z);
				Tree();
				glPopMatrix();
			}
		}
	}
}

void Forest::Tree() {

	glBindTexture(GL_TEXTURE_2D, texture_a->OpenGL_ID[0]);

	float x = 20;
	float y = 50;
	float z = 0.5f;

	glPushMatrix();
	glScalef(1.2, 1.2, 1.2);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 0); glVertex3f(-x, 0, z);
	glTexCoord2d(1, 1); glVertex3f(-x, y, z);
	glTexCoord2d(0, 1); glVertex3f(x, y, z);
	glTexCoord2d(0, 0); glVertex3f(x, 0, z);
	glScalef(1.2, 1.2, 1.2);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glScalef(1.2, 1.2, 1.2);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 0); glVertex3f(-x, 0, z);
	glTexCoord2d(1, 1); glVertex3f(-x, y, z);
	glTexCoord2d(0, 1); glVertex3f(x, y, z);
	glTexCoord2d(0, 0); glVertex3f(x, 0, z);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glScalef(1.2, 1.2, 1.2);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 0); glVertex3f(-x, 0, z);
	glTexCoord2d(1, 1); glVertex3f(-x, y, z);
	glTexCoord2d(0, 1); glVertex3f(x, y, z);
	glTexCoord2d(0, 0); glVertex3f(x, 0, z);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glRotatef(270, 0, 1, 0);
	glScalef(1.2, 1.2, 1.2);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2d(1, 0); glVertex3f(-x, 0, z);
	glTexCoord2d(1, 1); glVertex3f(-x, y, z);
	glTexCoord2d(0, 1); glVertex3f(x, y, z);
	glTexCoord2d(0, 0); glVertex3f(x, 0, z);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

Forest::~Forest()
{
}
