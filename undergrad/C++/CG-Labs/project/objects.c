#include "objects.h"

#include <math.h>
#include "point.h"
#include "vector.h"

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


void drawPanel(){
	privateSetColour(IS_A_SURFACE);
	if(wireFrame){
		//same as non-wireframe for testing purposes
		glBegin(GL_TRIANGLES);
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 0.0, 1.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(2.0, 0.0, 1.0);
		
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(2.0, 0.0, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(2.0, 0.0, 1.0);
		glEnd();
	}else{
		glBegin(GL_TRIANGLES);
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 0.0, 1.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(2.0, 0.0, 1.0);
		
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(2.0, 0.0, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(2.0, 0.0, 1.0);
		glEnd();
	}
}

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

/*	draws a sphere of size 1 centred at origin 					
void drawSphere(int nSegments, int nSlices)
	{	//	drawSphere() - original
	// make sure colour is properly set
	privateSetColour(IS_A_SURFACE);
	
	// draw an appropriate sphere
	if (wireFrame)
		glutWireSphere(1.0, nSegments, nSlices);
	else
		glutSolidSphere(1.0, nSegments, nSlices);
	}	//	drawSphere() - original
	*/
void drawSphere(int nSegments, int nSlices){	/*	drawSphere() */
	// assume radius equal to 1 to make things easier
	/* draw an appropriate sphere */
	float seg, slice;

	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	/* draw an appropriate sphere */
	if (wireFrame)	{ /* wireframe version */
		glBegin(GL_LINES);
		
		for (seg = 0.0f; seg < nSegments; seg += 1.0f)
		{ /* segments loop */
			
			float theta      = (2.0f * PI * seg) / nSegments;
			float n_theta = (2.0f * PI * (seg + 1.0f))/ nSegments;
			
			for(slice = 0.0f; slice < nSlices; slice += 1.0f)
			{ /* slices loop */
				float phi        = (2.0f * PI * slice) / nSlices;
				float n_phi   = (2.0f * PI * (slice + 1.0f))/ nSlices;
				
				/* compute sin & cosine */
				
				// bottom two points
				float x1 = cos(theta)*sin(phi),   y1 = sin(theta)*sin(phi),   z1 = cos(phi);
				float x2 = cos(n_theta)*sin(phi), y2 = sin(n_theta)*sin(phi), z2 = cos(phi);

				// top two for next phi
				float x3 = cos(theta)*sin(n_phi),   y3 = sin(theta)*sin(n_phi),   z3 = cos(n_phi);
				float x4 = cos(n_theta)*sin(n_phi), y4 = sin(n_theta)*sin(n_phi), z4 = cos(n_phi);
				
				glVertex3f(x1, y1, z1);	glVertex3f(x2, y2, z2);
				glVertex3f(x1, y1, z1); glVertex3f(x3, y3, z3);

				glVertex3f(x3, y3, z3); glVertex3f(x4, y4, z4);
				glVertex3f(x4, y4, z4); glVertex3f(x2, y2, z2);

				
			} /* slices loop */
		} /* segments loop */
		glEnd();
	} /* wireframe version */
	else{ /* surface version */
		glBegin(GL_TRIANGLES);
		for (seg = 0.0f; seg < nSegments; seg += 1.0f)
		{ /* segments loop */

			float theta   = (2.0f * PI * seg) / nSegments;
			float n_theta = (2.0f * PI * (seg + 1.0f))/ nSegments;
			
			for(slice = 0.0f; slice < nSlices; slice += 1.0f)
			{ /* slices loop */
				float phi     = (PI * slice) / nSlices;
				float n_phi   = (PI * (slice + 1.0f))/ nSlices;
				
				/* compute sin & cosine */
				
				// bottom two points
				float x1 = cos(theta)*sin(phi),   y1 = sin(theta)*sin(phi),   z1 = cos(phi);
				float x2 = cos(n_theta)*sin(phi), y2 = sin(n_theta)*sin(phi), z2 = cos(phi);

				// top two for next phi
				float x3 = cos(theta)*sin(n_phi),   y3 = sin(theta)*sin(n_phi),   z3 = cos(n_phi);
				float x4 = cos(n_theta)*sin(n_phi), y4 = sin(n_theta)*sin(n_phi), z4 = cos(n_phi);
				
				Vector n1(x1, y1, z1);
				Vector n2(x2, y2, z2);
				Vector n3(x3, y3, z3);
				Vector n4(x4, y4, z4);
				n1 = n1.norm();	n2 = n2.norm(); n3 = n3.norm(); n4 = n4.norm();
				
				glTexCoord2f(theta/(2.0*PI), phi/PI);
				glNormal3f(n1.x, n1.y, n1.z);
				glVertex3f(x1, y1, z1);
				
				glTexCoord2f(theta/(2.0*PI), n_phi/PI);
				glNormal3f(n3.x, n3.y, n3.z);
				glVertex3f(x3, y3, z3);
				
				glTexCoord2f(n_theta/(2.0*PI), phi/PI);
				glNormal3f(n2.x, n2.y, n2.z);
				glVertex3f(x2, y2, z2);
				
				glTexCoord2f(theta/(2.0*PI), n_phi/PI);
				glNormal3f(n3.x, n3.y, n3.z);
				glVertex3f(x3, y3, z3);
				
				glTexCoord2f(n_theta/(2.0*PI), n_phi/PI);
				glNormal3f(n4.x, n4.y, n4.z);
				glVertex3f(x4, y4, z4);
				
				glTexCoord2f(n_theta/(2.0*PI), phi/PI);
				glNormal3f(n2.x, n2.y, n2.z);
				glVertex3f(x2, y2, z2);
				
				
			} /* slices loop */
		} /* segments loop */
		glEnd();/*	drawSphere() */
	}
}

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
	

