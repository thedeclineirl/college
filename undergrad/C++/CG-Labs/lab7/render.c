#include <GL/glut.h>
#include "render.h"
#include "objects.h"
#include <stdio.h>
#include "texturePPM.h"

static GLfloat black_colour[] 	= { 0.0, 0.0, 0.0 };
static GLfloat white_colour[] 	= { 1.0, 1.0, 1.0 };
static GLfloat grey_colour[] 	= { 0.5, 0.5, 0.5 };

static GLfloat red_colour[] 	= { 1.0, 0.0, 0.0 };
static GLfloat orange_colour[] 	= { 1.0, 0.5, 0.0 };
static GLfloat yellow_colour[] 	= { 1.0, 1.0, 0.0 };
static GLfloat green_colour[] 	= { 0.0, 1.0, 0.0 };
static GLfloat blue_colour[] 	= { 0.0, 0.0, 1.0 };
static GLfloat indigo_colour[] 	= { 0.0, 0.0, 0.5 };
static GLfloat violet_colour[] 	= { 0.5, 0.5, 0.5 };

static GLfloat cyan_colour[] 	= { 0.0, 1.0, 1.0 };
static GLfloat magenta_colour[] = { 1.0, 0.0, 1.0 };
static GLfloat brown_colour[] 	= { 0.5, 0.25, 0.0 };
static GLfloat dkgreen_colour[]	= { 0.0, 0.5, 0.0 };
int isLoaded=0;
texture* tex;
texture* tex2;


void loadTexture(){
	tex = loadPPM("sign.ppm");
	tex2 = loadPPM("grass.ppm");
	isLoaded=1;
}

/* routine that actually does the rendering */
void Render()
    { /* Render() */
	if(!isLoaded){
		loadTexture();
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->texBytes);
	//changes texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		

	glPushMatrix();
		glTranslatef( -1.0f, -7.0f, 1.0f );
		glEnable(GL_TEXTURE_2D);
		drawPanel();
		glDisable(GL_TEXTURE_2D);
	
		glPushMatrix();
			glTranslatef( 0.0f, 0.0f, -1.0f );
			glScalef(0.1f, 0.1f, 2.0f);
			drawCylinder(10);
		
			glPushMatrix();
				glTranslatef( 20.0f, 0.0f, 0.0f );

				drawCylinder(10);
			glPopMatrix();	
		glPopMatrix();
	glPopMatrix();
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex2->width, tex2->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex2->texBytes);
	glPushMatrix();
	
		glScalef(10.0f, 10.0f, 0.3f);
		glEnable(GL_TEXTURE_2D);
			drawSphere(36, 36);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
		
	
    } /* Render() */
