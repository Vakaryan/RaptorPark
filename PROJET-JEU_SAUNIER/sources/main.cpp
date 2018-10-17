                                                                                                     /*
/##################################################################################################\
# Description : #                                                                                  #
#################                                                                                  #
#                                                                                                  #
#  Ce fichier est le point d'entrée du moteur ( le "main()" ).                                     #
#                                                                                                  #
#                                                                                                  #
\##################################################################################################/
                                                                                                     */

#include "window.h"
#include "input.h"
#include "timer.h"
#include "ogl.h"
#include "load.h"
#include "camera.h"
#include "maths_3d.h"
#include "AL/al.h"
#include "AL/alc.h"
#include "../projet/Forest.h"
#include "../projet/RaptorMcRaptoface.h"
#include "../projet/terrain.h"
#include <time.h>
#include <chrono>

#define PI 3.14159265

/****************************************************************************\
*                                                                            *
*                            Variables EXTERNES                              *
*                                                                            *
\****************************************************************************/


/****************************************************************************\
*                                                                            *
*                            Variables GLOBALES                              *
*                                                                            *
\****************************************************************************/
WINDOW    *win = NULL;
MY_INPUT  *inp = NULL;
TIMER     *tim = NULL;
Texture  *texture_grant = NULL;
CAMERA   *cam = NULL;

float	angleX = 0; 
float	angleY = 0;
float	angleZ = 0;
float	angleYmin = 0;
float	angleYsec = 0;
float	angleYh = 0;
float   posX = 0;
float   posY = 25;
float   posZ = 5;
bool    isRaptiAlive = true;
bool    fight;
int     timerRMR = 0;
float   bulletSpeed = 3;
bool    playerShoot = false;
bool    enemyShoot = false; 
int     timerEnemyShoot = 0;
float   bulletX_player = 0;
float   bulletZ_player = 0;
float   bulletAngleY_player = 0;
float   bulletX_0 = 0;
float   bulletZ_0 = 0;
float   bulletAngleY_0 = 0;
float   bulletX_1 = 0;
float   bulletZ_1 = 0;
float   bulletAngleY_1 = 0;
float   bulletX_2 = 0;
float   bulletZ_2 = 0;
float   bulletAngleY_2 = 0;
Forest  *forest = NULL;
RaptorMcRaptoface  *rex = NULL;  //player
RaptorMcRaptoface  *rapti = NULL;   //ennemy
Terrain *terrain = NULL;

/****************************************************************************\
*                                                                            *
*                             Variables LOCALES                              *
*                                                                            *
\****************************************************************************/



/********************************************************************\
*                                                                    *
*  Démarre l'application (avant la main_loop). Renvoie false si      *
*  il y a une erreur.                                                *
*                                                                    *
\********************************************************************/
bool start()
{
	// initialisations de base
	// -----------------------
	win = new WINDOW();									// prépare la fenêtre
	win->create( 800, 600, 16 , 60 , false );			// crée la fenêtre

	tim = new TIMER();									// crée un timer

	cam = new CAMERA();

	inp = new MY_INPUT(win);								// initialise la gestion clavier souris
	create_context(*win);								// crée le contexte OpenGL sur la fenêtre
	init_font(*win, "Courier");							// initialise la gestion de texte avec OpenGL

  
	// initialisations d'OpenGL
	// ------------------------
	glClearColor(0.0f,0.0f,0.0f,1.0f);					// set clear color for color buffer (RGBA, black)
	glViewport(0,0,win->Xres,win->Yres);				// zone de rendu (tout l'écran)
 	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LESS);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// mapping quality = best
	glFrontFace(GL_CCW);								// front of face is defined counter clock wise
	glPolygonMode(GL_FRONT, GL_FILL);					// front of a face is filled
	glPolygonMode(GL_BACK,  GL_LINE);					// back of a face is made of lines
	glCullFace(GL_BACK);								// cull back face only
	glDisable(GL_CULL_FACE);						    // disable back face culling


	win->set_title("RaptorPark");


	
	
	//load textures

	texture_grant = new Texture();
	texture_grant->load_texture("alangrant3.tga", NULL);
	glGenTextures(1, texture_grant->OpenGL_ID);


	fight = false;


	forest = new Forest();
	rex = new RaptorMcRaptoface();
	rapti = new RaptorMcRaptoface();
	terrain = new Terrain();
	

	return true;
}

/********************************************************************\
*                                                                    *
*  les formes                                               *
*                                                                    *
\********************************************************************/





void AlanGrant() {glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_grant->OpenGL_ID[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // on répète la texture en cas de U,V > 1.0
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    // ou < 0.0
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // indique qu'il faut mélanger la texture avec la couleur courante

																 // charge le tableau de la texture en mémoire vidéo et crée une texture mipmap

	if (texture_grant->isRGBA)
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, texture_grant->img_color->lenx, texture_grant->img_color->leny, GL_RGBA, GL_UNSIGNED_BYTE, texture_grant->img_all);
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, texture_grant->img_color->lenx, texture_grant->img_color->leny, GL_RGB, GL_UNSIGNED_BYTE, texture_grant->img_color->data);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex3f(-20, 0, -200);
	glTexCoord2d(1, 0); glVertex3f(20, 0, -200);
	glTexCoord2d(1, 1); glVertex3f(20, 50, -200);
	glTexCoord2d(0, 1); glVertex3f(-20, 50, -200);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void UpdateBullet_player() {
	bulletX_player -= bulletSpeed * sin(bulletAngleY_player*PI/180);
	bulletZ_player -= bulletSpeed * cos(bulletAngleY_player*PI/180);
}

void UpdateBullet_enemy() {
	bulletX_0 -= (bulletSpeed/2) * sin(bulletAngleY_0*PI / 180);
	bulletZ_0 += (bulletSpeed/2) * cos(bulletAngleY_0*PI / 180);
	bulletX_1 -= (bulletSpeed/2) * sin(bulletAngleY_1*PI / 180);
	bulletZ_1 += (bulletSpeed/2) * cos(bulletAngleY_1*PI / 180);
	bulletX_2 -= (bulletSpeed/2) * sin(bulletAngleY_2*PI / 180);
	bulletZ_2 += (bulletSpeed/2) * cos(bulletAngleY_2*PI / 180);
}


/********************************************************************\
*                                                                    *
*  Boucle principale, appelée pour construire une image, gérer les   *
*  entrées.                                                          *
*                                                                    *
\********************************************************************/
void main_loop() 
{

	auto framerate = tim->timer_get_ms();




	//////////////////////////////////////////////////////////////////////////////////////////////////
	//				gestion des touches	et du temps													//
	//////////////////////////////////////////////////////////////////////////////////////////////////
	
	inp->refresh();
	tim->update_horloge();
	inp->get_mouse_movement();


	if (inp->keys[KEY_CODE_ESCAPE]) 
	{	  
		PostMessage(win->handle,WM_CLOSE,0,0);	// Stoppe la "pompe à message" en y envoyant le message "QUIT"
	}

	point dir = cam->direction - cam->position;

	if (inp->keys[KEY_CODE_Z]) {
		if ((posX + dir.x * 2) < 180 && (posX + dir.x * 2) > -180 && (posZ + dir.z * 2) < 180 && (posZ + dir.z * 2) > -180) {
			posX += dir.x * 2;
			posZ += dir.z * 2;
		}
	}

	if (inp->keys[KEY_CODE_S]) {
		if ((posX - dir.x * 2) < 80 && (posX - dir.x * 2) > -180 && (posZ - dir.z * 2) < 190 && (posZ - dir.z * 2) > -180) {
			posX -= dir.x * 2;
			posZ -= dir.z * 2;
		}
	}

	if (inp->keys[KEY_CODE_Q]) {
		if ((posX - produit_vectoriel(dir, cam->orientation).x * 2) < 180 && (posX - produit_vectoriel(dir, cam->orientation).x * 2) > -180 && (posZ - produit_vectoriel(dir, cam->orientation).z * 2) < 180 && (posZ - produit_vectoriel(dir, cam->orientation).z * 2) > -180) {
			posX -= produit_vectoriel(dir, cam->orientation).x * 2;
			posZ -= produit_vectoriel(dir, cam->orientation).z * 2;
		}
	}

	if (inp->keys[KEY_CODE_D]) {
		if ((posX + produit_vectoriel(dir, cam->orientation).x * 2) < 180 && (posX + produit_vectoriel(dir, cam->orientation).x * 2) > -180 && (posZ + produit_vectoriel(dir, cam->orientation).z * 2) < 180 && (posZ + produit_vectoriel(dir, cam->orientation).z * 2) > -180) {
			posX += produit_vectoriel(dir, cam->orientation).x * 2;
			posZ += produit_vectoriel(dir, cam->orientation).z * 2;
		}
	}



	float size = 10;
	float size2 = 0.3;

	angleX -= 0.1*(float)inp->Yrelmouse;       
	angleY -= 0.1*(float)inp->Xrelmouse;
	if (angleY > 45) {
		angleY = 45;
	}
	if (angleY < -45) {
		angleY = -45;
	}
	if (angleX > 60) {
		angleX -= 60;
	}
	if (angleX < -60) {
		angleX += 60;
	}





	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	//////////////////////////////////////////////////////////////////////////////////////////////////
	//						ça commence ici															//
	//////////////////////////////////////////////////////////////////////////////////////////////////

	// votre code OpenGL ici
	glMatrixMode(GL_PROJECTION);  //la matrice de projection sera celle selectionnee
	//composition d'une matrice de projection
	glLoadIdentity(); //on choisit la matrice identité
	gluPerspective(60,(double)win->Xres/(double)win->Yres,10,30000);   //mise en place d'une proj angle de vue 60 deg near 10 far 30000
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//Mobile camera
	cam->update(point(posX, posY, posZ), angleX, angleY, angleZ);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam->position.x, cam->position.y, cam->position.z, cam->direction.x, cam->direction.y, cam->direction.z, cam->orientation.x, cam->orientation.y, cam->orientation.z);


	if (!rex->isDead) {
		glPushMatrix();
		glTranslatef(cam->position.x, cam->position.y - 25, cam->position.z - 7);
		glRotatef(angleY, 0, 1, 0);
		rex->RaptorCreate(true, cam->position.x, cam->position.y - 25, cam->position.z - 7);
		glPopMatrix();
	}

	terrain->CreateTerrain();

	forest->ForestCreate(-180, 180, -60, 170, 10, 10);

	if (cam->position.z <= -70) {
		fight = true;
	}


	if (inp->keys[KEY_CODE_SPACE] && fight && !playerShoot) {
		playerShoot = true;
		bulletX_player = rex->posX - 5 * sin(angleY*PI / 180);
		bulletZ_player = rex->posZ - 20;
		bulletAngleY_player = angleY;
	}

	if (playerShoot) {
		UpdateBullet_player();
		rex->Shoot(bulletX_player, cam->position.y - 10, bulletZ_player, bulletAngleY_player);
		if (bulletZ_player <= -160 && (bulletX_player >= -15 && bulletX_player <= 15)) {
			rapti->HP--;
			if (rapti->HP <= 0) {
				rapti->isDead = true;
			}
			playerShoot = false;
		}
		if (bulletZ_player <= -170) {
			playerShoot = false;
		}
	}


	if (!rapti->isDead) {
		glPushMatrix();
		glTranslatef(0, 0, -165);
		glScalef(2, 2, 2);
		glRotatef(180, 0, 1, 0);
		rapti->RaptorCreate(false, 0, 0, -165);
		glPopMatrix();
		if (fight && !enemyShoot) {
			timerEnemyShoot++;
			bulletX_0 = rapti->posX;
			bulletZ_0 = rapti->posZ + 20;
			bulletAngleY_0 = 0;
			bulletX_1 = rapti->posX;
			bulletZ_1 = rapti->posZ + 20;
			bulletAngleY_1 = 35;
			bulletX_2 = rapti->posX;
			bulletZ_2 = rapti->posZ + 20;
			bulletAngleY_2 = -35;
			if (timerEnemyShoot >= 25) {
				enemyShoot = true;
				timerEnemyShoot = 0;
			}
		}
	}

	if (!rapti->isDead && enemyShoot) {
		UpdateBullet_enemy();
		rapti->Shoot(bulletX_0, 20, bulletZ_0, 0);
		rapti->Shoot(bulletX_1, 20, bulletZ_1, 0);
		rapti->Shoot(bulletX_2, 20, bulletZ_2, 0);
		bool mb = (bulletZ_0 >= rex->posZ - 5 && bulletX_0 >= rex->posX - 5 && bulletX_0 <= rex->posX + 5);
		bool lb = (bulletZ_1 >= rex->posZ - 5 && bulletX_1 >= rex->posX - 5 && bulletX_1 <= rex->posX + 5);
		bool rb = (bulletZ_2 >= rex->posZ - 5 && bulletX_2 >= rex->posX - 5 && bulletX_2 <= rex->posX + 5);
		if (mb || lb || rb) {
			rex->HP--;
			if (rex->HP <= 0) {
				rex->isDead = true;
			}
			enemyShoot = false;
		}
		if (bulletZ_0 >= -70) {
			enemyShoot = false;
		}
	}
	
	
	if(rapti->isDead) {
		AlanGrant();
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//						ça finit ici															//
	//////////////////////////////////////////////////////////////////////////////////////////////////
	swap_buffer(win);	// affiche l'image composée à l'écran

	if (framerate + 16 - tim->timer_get_ms() > 0) {
		Sleep(framerate + 16 - tim->timer_get_ms());
	}
}



/********************************************************************\
*                                                                    *
* Arrête l'application                                               *
*                                                                    *
\********************************************************************/
void stop()
{
	delete inp;
	delete tim;

	if (win)
	{
		kill_font();
		kill_context(*win);
		delete win;
	}
}


/********************************************************************\
*                                                                    *
* Point d'entrée de notre programme pour Windows ("WIN32")           *
*                                                                    *
\********************************************************************/
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR szCmdLine,int iCmdShow)
{
	MSG  msg;

	win	= NULL;
	inp	= NULL;
	tim = NULL;

	if (start() == false)								// initialise la fenêtre et OpenGL
	{
		debug("start() : échec !");
		stop();
		return 1;
	}

	// main loop //
	// --------- //
	//   __
	//  /  \_
	//  |  \/ 
	//  \__/

	while (true)
	{
		if (PeekMessage(&msg, NULL,0,0,PM_NOREMOVE))	// s'il y a un message, appelle WndProc() pour le traiter
		{
			if (!GetMessage(&msg,NULL,0,0))				// "pompe à message"
				break;
			TranslateMessage(&msg);
			DispatchMessage (&msg);
		}
		else 
		{
			main_loop();								// sinon, appelle main_loop()
		}
	}


	stop();												// arrête OpenGL et ferme la fenêtre

	return 0;
}



/********************************************************************\
*                                                                    *
*  Boucle des messages                                               *
*                                                                    *
\********************************************************************/
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

  switch (msg)
    {

      case WM_MOVE:        win->Xpos = (dword) LOWORD(lParam);
                           win->Ypos = (dword) HIWORD(lParam);
                           return 0;

      case WM_CLOSE:       PostQuitMessage(0); // dit à GetMessage() de renvoyer 0
                           return 0;

      case WM_SYSCOMMAND:  // évite l'économiseur d'écran
                           switch (wParam)
                             {
                               case SC_SCREENSAVE:
                               case SC_MONITORPOWER:
                               return 0;
                             }
                           break;
/*
      case WM_CHAR:        la touche est traduite dans ce msg 
                           return 0;
*/

      case WM_KEYDOWN:     inp->set_key_down ((dword)wParam);
                           return 0;

      case WM_KEYUP:       inp->set_key_up   ((dword)wParam);
                           return 0;

      case WM_LBUTTONDOWN: inp->set_mouse_left_down();
                           return 0;

      case WM_LBUTTONUP:   inp->set_mouse_left_up();
                           return 0;

      case WM_RBUTTONDOWN: inp->set_mouse_right_down();
                           return 0;

      case WM_RBUTTONUP:   inp->set_mouse_right_up();
                           return 0;

      case WM_MBUTTONDOWN: inp->set_mouse_middle_down();
                           return 0;

      case WM_MBUTTONUP:   inp->set_mouse_middle_up();
                           return 0;

   }

  return DefWindowProc(hwnd,msg,wParam,lParam);
}

