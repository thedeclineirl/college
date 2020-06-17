#include <GL/glut.h>
#include "render.h"
#include "objects.h"

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


/* routine that actually does the rendering */
void Render()
    { /* Render() */

	setColour(green_colour); /* set the colour to a predfined colour, see above */
	glPushMatrix(); /* Push before applying geometric transformations */
	/* Draw someting here by calling a function that is included from the objects.h file  */
	//drawCube();
	glPopMatrix(); /* Pop to undo all previous transformations an bring you back to the origin */
	
	//the following is the method for inserting a new command
	setColour(orange_colour); 
	glPushMatrix(); 
	drawTetrahedron(); 	
	glPopMatrix();
	
	setColour(red_colour);
	glPushMatrix();
	drawOctahedron();
	glPopMatrix();

	int n = 40; //nSegments
	int m = 50; //nSlices
	setColour(yellow_colour);
	glPushMatrix();
	drawCylinder(n);
	glPopMatrix();
	
	setColour(cyan_colour);
	glPushMatrix();
	drawCone(n);
	glPopMatrix();
	
	setColour(magenta_colour);
	glPushMatrix();
	drawSphere(n,m); 
	glPopMatrix();
	
	

	
	
	
	return;
    } /* Render() */
