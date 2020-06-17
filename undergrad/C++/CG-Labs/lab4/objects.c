#include "objects.h"

#include <math.h>

#define PI 3.14159265358979

/*	colour currently used for drawing							*/
static GLfloat *currentColour;	
static GLfloat defaultBlack[] = {0.0, 0.0, 0.0, 1.0};

#define IS_A_SURFACE 1
#define IS_NOT_A_SURFACE 0

/*	private routine to set up colour prior to drawing object	*/
void privateSetColour(int isSurface)
	{	/*	privateSetColour() */
	/* if we're drawing a surface & not in wireframe mode */
	if (isSurface && !wireFrame)
		{ /* real surface */
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, currentColour);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, defaultBlack);
		} /* real surface */
	else
		{ /* wireframe edges */
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, currentColour);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, defaultBlack);
		} /* wireframe edges */
	}	/*	privateSetColour() */

/*	utility for setting the colour of an object					*/
void setColour(GLfloat *theColour)
	{	/*	setColour() */
	/* store it for later use */
	currentColour = theColour;	
	}	/*	setColour() */

/****************************/
/*	0-D, 1-D, & 2-D objects */
/****************************/

/*	draws a point at the origin 								*/
void drawPoint()
	{	/*	drawPoint() */
	/* make sure colour is properly set */
	privateSetColour(IS_NOT_A_SURFACE);

	glPointSize(5.0);
	/* then draw a single point */
	glBegin(GL_POINTS);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glPointSize(1.0);
	}	/*	drawPoint() */

/*	draws a line of length 1 along the x axis 					*/
void drawLine()
	{	/*	drawLine() */
	/* make sure colour is properly set */
	privateSetColour(IS_NOT_A_SURFACE);
	
	/* draw the line */
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();
	glLineWidth(1.0);
	}	/*	drawLine() */

/*	draws a line of length 1 along the x axis 					*/
void drawLineBetween(GLfloat *from, GLfloat *to)
	{ /* drawLineBetween() */
	/* make sure colour is properly set */
	privateSetColour(IS_NOT_A_SURFACE);
	
	/* draw the line */
	glBegin(GL_LINES);
	glVertex3fv(from);
	glVertex3fv(to);
	glEnd();
	} /* drawLineBetween() */


/*	draws a square of size 1 perpendicular to the y axis 		*/
void drawSquare()
	{	/*	drawSquare() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);

	/* draw the square */
	if (wireFrame)
		{ /* wireframe version */
		glBegin(GL_LINE_STRIP);
		glVertex3f(+0.5, -0.5, 0.0);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(-0.5, +0.5, 0.0);
		glVertex3f(+0.5, +0.5, 0.0);
		glVertex3f(+0.5, -0.5, 0.0);
		glVertex3f(-0.5, +0.5, 0.0);
		glEnd();
		} /* wireframe version */
	else
		{ /* surface version */
		glNormal3f(0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(-0.5, +0.5, 0.0);
		glVertex3f(+0.5, +0.5, 0.0);

		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(+0.5, +0.5, 0.0);
		glVertex3f(+0.5, -0.5, 0.0);
		glEnd();
		} /* surface version */
	}	/*	drawSquare() */

/*	draws a circle of radius 1 perpendicular to the y axis 		*/
void drawCircle(int nSegments)
	{	/*	drawCircle() */
	float theta;
	float increment = 2.0 * PI / (float) nSegments;
	float bound = 2.0 * PI + 0.5 * increment;
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw the circle */
	if (wireFrame)
		{ /* wireframe version */
		glBegin(GL_LINES);
		glVertex3f(1.0, 0.0, 0.0);
		for (theta = increment; theta <= bound; theta += increment)
			{ /* theta loop */
			glVertex3f(cos(theta), sin(theta), 0.0); 
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(cos(theta), sin(theta), 0.0); 
			/* this one carries over to the next one */
			glVertex3f(cos(theta), sin(theta), 0.0); 
			} /* theta loop */
		/* connect back to the centre */
		glVertex3f(0.0, 0.0, 0.0);
		glEnd();
		} /* wireframe version */
	else
		{ /* surface version */
		glNormal3f(0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
		for (theta = 0.0; theta <= bound; theta += increment)
			{ /* theta loop */
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(cos(theta), sin(theta), 0.0); 
			glVertex3f(cos(theta+increment), sin(theta+increment), 0.0); 
			} /* theta loop */
		glEnd();
		} /* surface version */
	}	/*	drawCircle() */


/****************************/
/*	Regular Platonic solids */
/****************************/

/*	draws a tetrahedron of size 1 centred at origin 			*/
void drawTetrahedron()
	{	/*	drawTetrahedron() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw an appropriate tetrahedron */
	if (wireFrame)
		glutWireTetrahedron();
	else
		glutSolidTetrahedron();
	}	/*	drawTetrahedron() */


/*	draws a cube of size 1 centred at origin 					*/
void drawCube()
	{	/*	drawCube() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw an appropriate cube */
	if (wireFrame)
		glutWireCube(1.0);
	else
		glutSolidCube(1.0);
	}	/*	drawCube() */


/*	draws an octahedron of size 1 centred at origin 			*/
void drawOctahedron()
	{	/*	drawOctahedron() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);

	/* draw an appropriate octahedron */
	if (wireFrame)
		glutWireOctahedron();
	else
		glutSolidOctahedron();
	}	/*	drawOctahedron() */


/*	draws a dodecahedron of size 1 centred at origin 			*/
void drawDodecahedron()
	{	/*	drawDodecahedron() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw an appropriate dodecahedron */
	if (wireFrame)
		glutWireDodecahedron();
	else
		glutSolidDodecahedron();
	}	/*	drawDodecahedron() */


/*	draws an icosahedron of size 1 centred at origin 			*/
void drawIcosahedron()
	{	/*	drawIcosahedron() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
		
	/* draw an appropriate icosahedron */
	if (wireFrame)
		glutWireIcosahedron();
	else
		glutSolidIcosahedron();
	}	/*	drawIcosahedron() */


/****************************/
/*	More complex solids 	*/
/****************************/

/*	draws a cylinder of height 1, radius 1						*/
void drawCylinder(int nSegments)
	{	/*	drawCylinder() */
	float theta;
	float increment = 2.0 * PI / (float) nSegments;
	float bound = 2.0 * PI + 0.5 * increment;
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw the cylinder */
	if (wireFrame)
		{ /* wireframe version */
		glBegin(GL_LINES);
		for (theta = 0.0; theta <= bound; theta += increment)
			{ /* theta loop */
			glVertex3f(cos(theta), -0.5, sin(theta));
			glVertex3f(cos(theta), 0.5, sin(theta));
			glVertex3f(0.0, -0.5, 0.0);
			glVertex3f(cos(theta), -0.5, sin(theta));
			glVertex3f(0.0, 0.5, 0.0);
			glVertex3f(cos(theta), 0.5, sin(theta));
			glVertex3f(cos(theta), -0.5, sin(theta));
			glVertex3f(cos(theta+increment), -0.5, sin(theta+increment));
			glVertex3f(cos(theta), 0.5, sin(theta));
			glVertex3f(cos(theta+increment), 0.5, sin(theta+increment));
			glVertex3f(cos(theta), -0.5, sin(theta));
			glVertex3f(cos(theta+increment), 0.5, sin(theta+increment));
			} /* theta loop */
		glEnd();
		} /* wireframe version */
	else
		{ /* surface version */
		glBegin(GL_TRIANGLES);
		for (theta = 0.0; theta <= bound; theta += increment)
			{ /* theta loop */
			glNormal3f(cos(theta), 0.0, sin(theta));
			glVertex3f(cos(theta), -0.5, sin(theta));
			glVertex3f(cos(theta), 0.5, sin(theta));
			glNormal3f(cos(theta+increment), 0.0, sin(theta+increment));
			glVertex3f(cos(theta+increment), 0.5, sin(theta+increment));

			glVertex3f(cos(theta+increment), 0.5, sin(theta+increment));
			glVertex3f(cos(theta+increment), -0.5, sin(theta+increment));
			glNormal3f(cos(theta), 0.0, sin(theta));
			glVertex3f(cos(theta), -0.5, sin(theta));
			
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(0.0, -0.5, 0.0);
			glVertex3f(cos(theta), -0.5, sin(theta));
			glVertex3f(cos(theta+increment), -0.5, sin(theta+increment));

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 0.5, 0.0);
			glVertex3f(cos(theta+increment), 0.5, sin(theta+increment));
			glVertex3f(cos(theta), 0.5, sin(theta));
			} /* theta loop */
		glEnd();
		} /* surface version */
	}	/*	drawCylinder() */

/*	draws a vertical cylinder of given height and radius 	*/
void drawVertCylinder(int nSegments, float height, float radius)
	{ /* drawVertCylinder() */
	float theta;
	float increment = 2.0 * PI / (float) nSegments;
	float bound = 2.0 * PI + 0.5 * increment;
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	glPushMatrix();
	glScalef(radius, radius, height);
	glTranslatef(0.0, 0.0, 0.5);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	
	/* draw the cylinder */
	if (wireFrame)
		{ /* wireframe version */
		glBegin(GL_LINES);
		for (theta = 0.0; theta <= bound; theta += increment)
			{ /* theta loop */
			glVertex3f(cos(theta), -0.5, sin(theta));
			glVertex3f(cos(theta), 0.5, sin(theta));
			glVertex3f(0.0, -0.5, 0.0);
			glVertex3f(cos(theta), -0.5, sin(theta));
			glVertex3f(0.0, 0.5, 0.0);
			glVertex3f(cos(theta), 0.5, sin(theta));
			glVertex3f(cos(theta), -0.5, sin(theta));
			glVertex3f(cos(theta+increment), -0.5, sin(theta+increment));
			glVertex3f(cos(theta), 0.5, sin(theta));
			glVertex3f(cos(theta+increment), 0.5, sin(theta+increment));
			glVertex3f(cos(theta), -0.5, sin(theta));
			glVertex3f(cos(theta+increment), 0.5, sin(theta+increment));
			} /* theta loop */
		glEnd();
		} /* wireframe version */
	else
		{ /* surface version */
		glBegin(GL_TRIANGLES);
		for (theta = 0.0; theta <= bound; theta += increment)
			{ /* theta loop */
			glNormal3f(cos(theta), 0.0, sin(theta));
			glVertex3f(cos(theta), -0.5, sin(theta));
			glVertex3f(cos(theta), 0.5, sin(theta));
			glNormal3f(cos(theta+increment), 0.0, sin(theta+increment));
			glVertex3f(cos(theta+increment), 0.5, sin(theta+increment));

			glVertex3f(cos(theta+increment), 0.5, sin(theta+increment));
			glVertex3f(cos(theta+increment), -0.5, sin(theta+increment));
			glNormal3f(cos(theta), 0.0, sin(theta));
			glVertex3f(cos(theta), -0.5, sin(theta));
			
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(0.0, -0.5, 0.0);
			glVertex3f(cos(theta), -0.5, sin(theta));
			glVertex3f(cos(theta+increment), -0.5, sin(theta+increment));

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 0.5, 0.0);
			glVertex3f(cos(theta+increment), 0.5, sin(theta+increment));
			glVertex3f(cos(theta), 0.5, sin(theta));
			} /* theta loop */
		glEnd();
		} /* surface version */
	glPopMatrix();
	} /* drawVertCylinder() */

/*	draws a cone of height 1, radius 1						*/
void drawCone(int nSegments)
	{	/*	drawCone() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw an appropriate sphere */
	if (wireFrame)
		glutWireCone(1.0, 1.0, nSegments, 1);
	else
		glutSolidCone(1.0, 1.0, nSegments, 1);
	}	/*	drawCone() */

/*	draws a sphere of size 1 centred at origin 					*/
void drawSphere(int nSegments, int nSlices)
	{	/*	drawSphere() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw an appropriate sphere */
	if (wireFrame)
		glutWireSphere(1.0, nSegments, nSlices);
	else
		glutSolidSphere(1.0, nSegments, nSlices);
	}	/*	drawSphere() */

/*	draws a torus centred at origin 							*/
void drawTorus(int ratioRadii, int nSegments, int nSlices)
	{	/*	drawTorus() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);

	/* draw an appropriate torus */
	if (wireFrame)
		glutWireTorus(1.0, ratioRadii, nSegments, nSlices);
	else
		glutSolidTorus(1.0, ratioRadii, nSegments, nSlices);
	}	/*	drawTorus() */


/*	draws a teapot centred at origin 							*/
void drawTeapot()
	{	/*	drawTeapot() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw an appropriate teapot */
	if (wireFrame)
		glutWireTeapot(1.0);
	else
		{ /* owch: GLUT has a bug */
		glFrontFace(GL_CW);
		glutSolidTeapot(1.0);
		glFrontFace(GL_CCW);
		} /* owch: GLUT has a bug */
	}	/*	drawTeapot() */
	

