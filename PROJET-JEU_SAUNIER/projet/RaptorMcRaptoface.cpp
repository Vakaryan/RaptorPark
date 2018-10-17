#include "RaptorMcRaptoface.h"



RaptorMcRaptoface::RaptorMcRaptoface()
{

	model_raptor = new Model3D();
	model_raptor->load_3d_model("RAPTOR.off");
	texture_raptor = new Texture();
	texture_raptor->load_texture("RAPTOR.tga", NULL);


	glBindTexture(GL_TEXTURE_2D, texture_raptor->OpenGL_ID[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // on répète la texture en cas de U,V > 1.0
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    // ou < 0.0
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // indique qu'il faut mélanger la texture avec la couleur courante

																 // charge le tableau de la texture en mémoire vidéo et crée une texture mipmap

	if (texture_raptor->isRGBA)
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, texture_raptor->img_color->lenx, texture_raptor->img_color->leny, GL_RGBA, GL_UNSIGNED_BYTE, texture_raptor->img_all);
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, texture_raptor->img_color->lenx, texture_raptor->img_color->leny, GL_RGB, GL_UNSIGNED_BYTE, texture_raptor->img_color->data);
	
	isDead = false;
	HP = 10;
	isPlayer = true;
	posX = 0;
	posY = 0;
	posZ = 0;
}



void RaptorMcRaptoface::RaptorCreate(bool player, float x, float y, float z) {
	glBindTexture(GL_TEXTURE_2D, texture_raptor->OpenGL_ID[0]);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glScalef(0.1, 0.1, 0.1);
	glBegin(GL_TRIANGLES);
	int i;

	for (i = 0; i<model_raptor->nb_triangles; i++) {

		glTexCoord2f(model_raptor->points[model_raptor->faces[i].a].ucol,
			model_raptor->points[model_raptor->faces[i].a].vcol);
		glVertex3f(model_raptor->points[model_raptor->faces[i].a].x,
			model_raptor->points[model_raptor->faces[i].a].y,
			model_raptor->points[model_raptor->faces[i].a].z);

		glTexCoord2f(model_raptor->points[model_raptor->faces[i].b].ucol, model_raptor->points[model_raptor->faces[i].b].vcol);
		glVertex3f(model_raptor->points[model_raptor->faces[i].b].x, model_raptor->points[model_raptor->faces[i].b].y, model_raptor->points[model_raptor->faces[i].b].z);

		glTexCoord2f(model_raptor->points[model_raptor->faces[i].c].ucol, model_raptor->points[model_raptor->faces[i].c].vcol);
		glVertex3f(model_raptor->points[model_raptor->faces[i].c].x, model_raptor->points[model_raptor->faces[i].c].y, model_raptor->points[model_raptor->faces[i].c].z);

	}

	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	isPlayer = player;
	posX = x;
	posY = y;
	posZ = z;
}


void RaptorMcRaptoface::Shoot(float posx, float posy, float posz, float rotationAngle) {
	
	if (!isPlayer) {
		glPushMatrix();
		glTranslatef(posx, posy, posz);
		glRotatef(rotationAngle, 0, 1, 0);
		glBegin(GL_QUADS);
		glColor3f(1, 0, 0); glVertex3f(-2.5, 0, 0);
		glColor3f(1, 0, 0); glVertex3f(2.5, 0, 0);
		glColor3f(1, 0, 0); glVertex3f(2.5, 5, 0);
		glColor3f(1, 0, 0); glVertex3f(-2.5, 5, 0);
		glEnd();
		glPopMatrix();
	}

	else {
		std::cout << "Player shooting" << std::endl;
		glPushMatrix();
		glTranslatef(posx, posy, posz);
		glRotatef(rotationAngle, 0, 1, 0);
		glBegin(GL_QUADS);
		glColor3f(0, 0.5, 1); glVertex3f(-2.5,0,0);
		glColor3f(0, 0.5, 1); glVertex3f(2.5, 0,0);
		glColor3f(0, 0.5, 1); glVertex3f(2.5, 5 , 0);
		glColor3f(0, 0.5, 1); glVertex3f(-2.5, 5, 0);
		glEnd();
		glPopMatrix();
	}
}


RaptorMcRaptoface::~RaptorMcRaptoface()
{
}
