#include <GL/glut.h>
#include <math.h>
#include "render.h"
#include "objects.h"

#ifndef PI
#define PI 3.1415926536
#endif

/* Colour pallet */

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
static GLfloat pink_colour[] 	= { 1.0, 0.6, 0.6 };

						// black        blue        green      cyan
GLint cube_vert[8][3] = { 0, 0, 0,    0, 0, 1,    0, 1, 0,   0, 1, 1,
			  1, 0, 0,    1, 0, 1,    1, 1, 0,   1, 1, 1 };
			//  red       magenta      yellow      white
/* Part 1. No shading, no lighting, draw a cube with each vertex as a primary colour or a secondary colour
 *
 *	Primary Colours   : Red, Green, Blue
 *	Secondary Colours : Cyan, Magenta, Yellow
 *	Black is the absence of colour
 *      White is a combination of all the primary colours
 *      This gives us a colour for each vertex of the cube
 *
 */

void DrawColourCube(){
	glDisable(GL_LIGHTING);
//part 1
	glBegin(GL_TRIANGLES);
	glNormal3i(-1, 0, 0);//face 2
	glColor3fv(black_colour);	glVertex3iv(cube_vert[0]); 
	glColor3fv(green_colour);	glVertex3iv(cube_vert[2]); 
	glColor3fv(cyan_colour);	glVertex3iv(cube_vert[3]);
		
	glColor3fv(black_colour);	glVertex3iv(cube_vert[0]); 
	glColor3fv(cyan_colour);	glVertex3iv(cube_vert[3]); 
	glColor3fv(blue_colour);	glVertex3iv(cube_vert[1]);

	glNormal3i( 0, -1, 0);//face0
	glColor3fv(black_colour);	glVertex3iv(cube_vert[0]); 
	glColor3fv(blue_colour);	glVertex3iv(cube_vert[1]); 
	glColor3fv(magenta_colour);	glVertex3iv(cube_vert[5]);
	
	glColor3fv(black_colour);	glVertex3iv(cube_vert[0]); 
	glColor3fv(magenta_colour);	glVertex3iv(cube_vert[5]); 
	glColor3fv(red_colour);		glVertex3iv(cube_vert[4]);

	glNormal3i( 0, 0, -1);//face1
	glColor3fv(black_colour);	glVertex3iv(cube_vert[0]); 
	glColor3fv(red_colour);		glVertex3iv(cube_vert[4]); 
	glColor3fv(yellow_colour);	glVertex3iv(cube_vert[6]);
	
	glColor3fv(black_colour); 	glVertex3iv(cube_vert[0]); 
	glColor3fv(yellow_colour);	glVertex3iv(cube_vert[6]); 
	glColor3fv(green_colour);	glVertex3iv(cube_vert[2]);

	glNormal3i( 1, 0, 0);////face3
	glColor3fv(yellow_colour);	glVertex3iv(cube_vert[6]); 
	glColor3fv(magenta_colour);	glVertex3iv(cube_vert[5]); 
	glColor3fv(red_colour);		glVertex3iv(cube_vert[4]);
	
	glColor3fv(yellow_colour);	glVertex3iv(cube_vert[6]); 
	glColor3fv(magenta_colour);	glVertex3iv(cube_vert[5]); 
	glColor3fv(white_colour);	glVertex3iv(cube_vert[7]);
	
	glNormal3i( 0, 1, 0);//face5
	glColor3fv(yellow_colour);	glVertex3iv(cube_vert[6]); 
	glColor3fv(cyan_colour);	glVertex3iv(cube_vert[3]); 
	glColor3fv(white_colour);	glVertex3iv(cube_vert[7]);
	
	glColor3fv(yellow_colour);	glVertex3iv(cube_vert[6]); 
	glColor3fv(cyan_colour);	glVertex3iv(cube_vert[3]); 
	glColor3fv(green_colour);	glVertex3iv(cube_vert[2]);

	glNormal3i( 0, 0, 1);//face4
	glColor3fv(magenta_colour);	glVertex3iv(cube_vert[5]); 
	glColor3fv(cyan_colour);	glVertex3iv(cube_vert[3]); 
	glColor3fv(blue_colour);	glVertex3iv(cube_vert[1]);
	
	glColor3fv(magenta_colour);	glVertex3iv(cube_vert[5]); 
	glColor3fv(cyan_colour);	glVertex3iv(cube_vert[3]); 
	glColor3fv(white_colour);	glVertex3iv(cube_vert[7]);
	glEnd();
	
	glEnable(GL_LIGHTING);
}	
/* Part 2. shading and lighting enabled 
 *
 *	Primary Colours   : Red, Green, Blue
 *	Secondary Colours : Cyan, Magenta, Yellow
 *	All Colours Mixed : White
 *	Absence of Colour : Black
 *
 * Render a sphere at each vertex of the cube of each of the above colours
 *
 */

void DrawColourSpheres(){
	/** TO DO:: Draw Spheres with materials **/

	
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black_colour);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black_colour);
			glTranslatef( 0.0f, 0.0f, 0.0f );
			glScalef(0.1f, 0.1f, 0.1f);
			glutSolidSphere(1.0f, 20, 20);
		glPopMatrix();
		
		
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue_colour);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, blue_colour);
			glTranslatef( 0.0f, 0.0f, 1.0f );
			glScalef(0.1f, 0.1f, 0.1f);
			glutSolidSphere(1.0f, 20, 20);
		glPopMatrix();
		
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green_colour);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, green_colour);
			glTranslatef( 0.0f, 1.0f, 0.0f );
			glScalef(0.1f, 0.1f, 0.1f);
			glutSolidSphere(1.0f, 20, 20);
		glPopMatrix();
		
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cyan_colour);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cyan_colour);
			glTranslatef( 0.0f, 1.0f, 1.0f );
			glScalef(0.1f, 0.1f, 0.1f);
			glutSolidSphere(1.0f, 20, 20);	
		glPopMatrix();
			
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red_colour);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, red_colour);
			glTranslatef( 1.0f, 0.0f, 0.0f );
			glScalef(0.1f, 0.1f, 0.1f);
			glutSolidSphere(1.0f, 20, 20);
		glPopMatrix();

		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, magenta_colour);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, magenta_colour);
			glTranslatef( 1.0f, 0.0f, 1.0f );
			glScalef(0.1f, 0.1f, 0.1f);
			glutSolidSphere(1.0f, 20, 20);
		glPopMatrix();
				
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, yellow_colour);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, yellow_colour);
			glTranslatef( 1.0f, 1.0f, 0.0f );
			glScalef(0.1f, 0.1f, 0.1f);
			glutSolidSphere(1.0f, 20, 20);
		glPopMatrix();
		
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white_colour);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white_colour);
			glTranslatef( 1.0f, 1.0f, 1.0f );
			glScalef(0.1f, 0.1f, 0.1f);
			glutSolidSphere(1.0f, 20, 20);
		glPopMatrix();
				
}
