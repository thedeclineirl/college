#include "objects.h"

#include <math.h>
#include "point.h"
#include "vector.h"

#define PI 3.14159265358979f
#define DEG2RAD PI/180.0f
#define PHI (1+sqrt(5))/2
#define TAU (-1+sqrt(5))/2
/*	colour currently used for drawing							*/
static GLfloat *currentColour;	
static GLfloat defaultBlack[] = {0.0, 0.0, 0.0, 1.0};

			/*         v0             v1            v2              v3		*/
GLint tet_vertices[4][3]  = { -1, -1, -1,    -1,  1,  1,     1, -1,  1,      1,  1, -1 }; 

GLint cube_vertices[8][3] = { -1, -1, -1,    -1, -1,  1,    -1,  1, -1,     -1,  1,  1,
			       1, -1, -1,     1, -1,  1,     1,  1, -1,      1,  1,  1};
			/*	v0	    v1		  v2	     v3         v4         v5     */
GLint oct_vertices[6][3]  = { 0, 0, 1,   0,  0, -1,    1, 0, 0,   0, -1, 0,  -1, 0, 0,   0, 1, 0  }; 

#define IS_A_SURFACE 1
#define IS_NOT_A_SURFACE 0

/*	private routine to set up colour prior to drawing object	*/
void privateSetColour(int isSurface){	/*	privateSetColour() */
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
/*	Regular Platonic solids */
/****************************/

/*	draws a tetrahedron of size 1			*/
void drawTetrahedron()
{	/*	drawTetrahedron() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw an appropriate tetrahedron */
	if(wireFrame){
		glBegin(GL_LINES);
		glVertex3f(-1.0, -5.0, -1.0); glVertex3f(1.0, -3.0, -1.0); 
		glVertex3f(1.0, -3.0, -1.0); glVertex3f(1.0, -5.0, 1.0); 
		glVertex3f(1.0, -5.0, 1.0); glVertex3f(-1.0, -5.0, -1.0); //face 3
		
		glVertex3f(-1.0, -3.0, 1.0); glVertex3f(1.0, -5.0, 1.0); 
		glVertex3f( 1.0, -3.0, -1.0); glVertex3f(-1.0, -3.0, 1.0); //face 2
		
		glVertex3f(1.0, -3.0, -1.0); glVertex3f(-1.0, -5.0, -1.0); 
		glVertex3f(-1.0, -5.0, -1.0); glVertex3f(-1.0, -3.0, 1.0);
		glVertex3f(-1.0, -3.0, 1.0); glVertex3f( 1.0, -3.0, -1.0); //face 1
		//the wireframe of face 0 is already drawn by the previous 3 faces 
		glEnd();
	}else{
		GLint vertices[4][3] = //a 2-d array of [4] vertices of [3] points
		{-1, -5, -1, 1, -5, 1, -1, -3, 1, 1, -3, -1};
		glBegin(GL_TRIANGLES); 
		glNormal3i(-1, -1, 1);//the normal vector of face 2 
		glVertex3iv(vertices[2]);glVertex3iv(vertices[1]);glVertex3iv(vertices[3]);
		glNormal3i( -1, 1, -1);//the normal vector of face0
		glVertex3iv(vertices[0]);glVertex3iv(vertices[1]);glVertex3iv(vertices[2]);
		glNormal3i( 1, -1, -1);//the normal vector of face1
		glVertex3iv(vertices[3]);glVertex3iv(vertices[0]);glVertex3iv(vertices[2]);
		glNormal3i( 1, 1, 1);//the normal vector of face3
		glVertex3iv(vertices[0]);glVertex3iv(vertices[3]);glVertex3iv(vertices[1]);
		glEnd();
		//the normal vectors are incorrect

	}
}

/*	draws a cube of size 1 					*/
void drawCube()
{	/*	drawCube() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw an appropriate cube */
	if (wireFrame){
		glBegin(GL_LINES);
		glVertex3f(3.0, -1.0, -1.0); glVertex3f(3.0, -1.0, 1.0);
		glVertex3f(3.0, -1.0, 1.0); glVertex3f(3.0, 1.0, 1.0);
		glVertex3f(3.0, 1.0, 1.0); glVertex3f(3.0, 1.0, -1.0);
		glVertex3f(3.0, 1.0, -1.0); glVertex3f(3.0, -1.0, -1.0);
		glVertex3f(3.0, -1.0, -1.0); glVertex3f( 5.0, -1.0, -1.0);
		glVertex3f(3.0, -1.0, 1.0); glVertex3f( 5.0, -1.0, 1.0);
		glVertex3f(3.0, 1.0, 1.0); glVertex3f( 5.0, 1.0, 1.0);
		glVertex3f(3.0, 1.0, -1.0); glVertex3f( 5.0, 1.0, -1.0);
		glVertex3f( 5.0, -1.0, -1.0); glVertex3f( 5.0, -1.0, 1.0);
		glVertex3f( 5.0, -1.0, 1.0); glVertex3f( 5.0, 1.0, 1.0);
		glVertex3f( 5.0, 1.0, 1.0); glVertex3f( 5.0, 1.0, -1.0);
		glVertex3f( 5.0, 1.0, -1.0); glVertex3f( 5.0, -1.0, -1.0);
		glEnd();
	}else{
		GLint vertices[8][3] =
		{3, -1, -1, 
		3, -1, 1, 
		3, 1, -1, 
		3, 1, 1,
		5, -1, -1, 
		5, -1, 1, 
		5, 1, -1, 
		5, 1, 1};
		glBegin(GL_TRIANGLES);
		glNormal3i(-1, 0, 0);//face 2
		glVertex3iv(vertices[0]);glVertex3iv(vertices[2]);glVertex3iv(vertices[3]);
		glVertex3iv(vertices[0]);glVertex3iv(vertices[3]);glVertex3iv(vertices[1]);
		glNormal3i( 0, -1, 0);//face0
		glVertex3iv(vertices[0]);glVertex3iv(vertices[1]);glVertex3iv(vertices[5]);
		glVertex3iv(vertices[0]);glVertex3iv(vertices[5]);glVertex3iv(vertices[4]);
		glNormal3i( 0, 0, -1);//face1
		glVertex3iv(vertices[0]);glVertex3iv(vertices[4]);glVertex3iv(vertices[6]);
		glVertex3iv(vertices[0]);glVertex3iv(vertices[6]);glVertex3iv(vertices[2]);
		glNormal3i( 1, 0, 0);////face3
		glVertex3iv(vertices[6]);glVertex3iv(vertices[5]);glVertex3iv(vertices[4]);
		glVertex3iv(vertices[6]);glVertex3iv(vertices[5]);glVertex3iv(vertices[7]);
		glNormal3i( 0, 1, 0);//face5
		glVertex3iv(vertices[6]);glVertex3iv(vertices[3]);glVertex3iv(vertices[7]);
		glVertex3iv(vertices[6]);glVertex3iv(vertices[3]);glVertex3iv(vertices[2]);
		glNormal3i( 0, 0, 1);//face4
		glVertex3iv(vertices[5]);glVertex3iv(vertices[3]);glVertex3iv(vertices[1]);
		glVertex3iv(vertices[5]);glVertex3iv(vertices[3]);glVertex3iv(vertices[7]);
		glEnd(); 
	}
}	/*	drawCube() */

/*	draws an octahedron of size 1			*/
void drawOctahedron()
{	//	drawOctahedron()
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	/*
	/* draw an appropriate octahedron */
	if (wireFrame){
		//to move from the origin add (0.0, 3.0, 0.0)
		glBegin(GL_LINES);
		glVertex3f(0.0, 3.0, 1.0); glVertex3f(-1.0, 3.0, 0.0);
		glVertex3f(-1.0, 3.0, 0.0); glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(0.0, 2.0, 0.0); glVertex3f(0.0, 3.0, 1.0); //face 2
		
		glVertex3f(-1.0, 3.0, 0.0); glVertex3f(0.0, 3.0, -1.0);
		glVertex3f(0.0, 3.0, -1.0); glVertex3f(0.0, 2.0, 0.0); //face 7
				
		glVertex3f(-1.0, 3.0, 0.0); glVertex3f(0.0, 4.0, 0.0);
		glVertex3f(0.0, 4.0, 0.0); glVertex3f(0.0, 3.0, -1.0); //face 4
		
		glVertex3f(0.0, 3.0, 1.0); glVertex3f(0.0, 4.0, 0.0); // face 1
		
		glVertex3f(0.0, 3.0, 1.0); glVertex3f(1.0, 3.0, 0.0);
		glVertex3f(1.0, 3.0, 0.0); glVertex3f(0.0, 4.0, 0.0); //face 0
		
		glVertex3f(0.0, 3.0, 1.0); glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(0.0, 2.0, 0.0); glVertex3f(1.0, 3.0, 0.0); //face 3
		
		glVertex3f(0.0, 2.0, 0.0); glVertex3f(0.0, 3.0, -1.0);
		glVertex3f(0.0, 3.0, -1.0); glVertex3f(1.0, 3.0, 0.0); //face 6
		//face 5 is already drawn in wireframe by the previous faces
		glEnd();
	}else{
		//to move from the origin add (0.0, 3.0, 0.0)
		GLint vertices[6][3] =
		{0, 3, 1,
		-1, 3, 0,
		0, 2, 0,
		0, 3, -1,
		0, 4, 0,
		1, 3, 0,};	
		glBegin(GL_TRIANGLES); //
		glNormal3i(-1, 2, -1);//face 2
		glVertex3iv(vertices[0]);glVertex3iv(vertices[1]);glVertex3iv(vertices[2]);
		glNormal3i( -1, 2, 1);//face7 
		glVertex3iv(vertices[1]);glVertex3iv(vertices[3]);glVertex3iv(vertices[2]);
		glNormal3i( -1, 4, -1);//face4
		glVertex3iv(vertices[1]);glVertex3iv(vertices[4]);glVertex3iv(vertices[3]);
		//the following normal vectors are incorrect
		glNormal3i( -1, 4, 1);//face1
		glVertex3iv(vertices[0]);glVertex3iv(vertices[4]);glVertex3iv(vertices[1]);
		glNormal3i(1, 2, -1);//face0
		glVertex3iv(vertices[0]);glVertex3iv(vertices[5]);glVertex3iv(vertices[4]);
		glNormal3i(1, 2, 1);//face3
		glVertex3iv(vertices[0]);glVertex3iv(vertices[2]);glVertex3iv(vertices[5]);
		glNormal3i( 1, 4, -1);//face6
		glVertex3iv(vertices[2]);glVertex3iv(vertices[3]);glVertex3iv(vertices[5]);
		glNormal3i( 1, 4, 1);//face5
		glVertex3iv(vertices[4]);glVertex3iv(vertices[5]);glVertex3iv(vertices[3]);
		glEnd();

	}
	
}	/*	drawOctahedron() */


/*	draws a dodecahedron of size 1 centred at origin 			*/
void drawDodecahedron()
{	/*	drawDodecahedron() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw an appropriate dodecahedron */
	if (wireFrame){

		/** TO DO : code goes here **/

	}else{

		/** TO DO : code goes here **/

	}
}	/*	drawDodecahedron() */


void drawIcosahedron(){	/*	drawIcosahedron() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw an appropriate icosahedron */
	if (wireFrame){

		/** TO DO : code goes here **/

	}else{

		/** TO DO : code goes here **/

	}
}

/****************************/
/*	More complex solids 	*/
/****************************/

/*	draws a cylinder of height 1, radius 1						*/
void drawCylinder(int nSegments)
{	/*	drawCylinder() */
	float i;
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw the cylinder */
	if (wireFrame)	{ /* wireframe version */
		
		for (float i = 0.0; i < nSegments; i += 1.0)
		{ /* a loop around circumference of a tube */
		float angle = PI * i * 2.0 / nSegments ;
		float nextAngle = PI * (i + 1.0) * 2.0 / nSegments;
		/* compute sin & cosine */
		float x1 = sin(angle), y1 = cos(angle);
		float x2 = sin(nextAngle), y2 = cos(nextAngle);
		glBegin(GL_LINES);
		glVertex3f(x1, y1, -3.0); glVertex3f(x2, y2, -2.0);
		glVertex3f(x1, y1, -2.0); glVertex3f(x2, y2, -2.0);
		glVertex3f(x2, y2, -2.0); glVertex3f(x2, y2, -3.0);
		glVertex3f(x1, y1, -3.0); glVertex3f(x2, y2, -3.0);
		
		glVertex3f(x1, y1, -3.0); glVertex3f(0.0, 0.0, -3.0);
		glVertex3f(x2, y2, -3.0); glVertex3f(0.0, 0.0, -3.0); //closes base
		glVertex3f(x1, y1, -2.0); glVertex3f(0.0, 0.0, -2.0);
		glVertex3f(x2, y2, -2.0); glVertex3f(0.0, 0.0, -2.0); //closes top
		glEnd();
		} /* a loop around circumference of a tube */

	/* wireframe version */
	}else{ /* surface version */
		
		for (float i = 0.0; i < nSegments; i += 1.0)
		{ /* a loop around circumference of a tube */
		float angle = PI * i * 2.0 / nSegments ;
		float nextAngle = PI * (i + 1.0) * 2.0 / nSegments;
		/* compute sin & cosine */
		float x1 = sin(angle), y1 = cos(angle);
		float x2 = sin(nextAngle), y2 = cos(nextAngle);
		glBegin(GL_TRIANGLES);
		/* draw top (green) triangle */
		glNormal3f(x1, y1, -3.0); glVertex3f(x1, y1, -3.0);
		glNormal3f(x2, y2, -3.0); glVertex3f(x2, y2, -2.0);
		glNormal3f(x1, y1, -3.0); glVertex3f(x1, y1, -2.0);
		/* draw bottom (red) triangle */
		glNormal3f(x1, y1, -3.0); glVertex3f(x1, y1, -3.0);
		glNormal3f(x2, y2, -3.0); glVertex3f(x2, y2, -3.0);
		glNormal3f(x2, y2, -3.0); glVertex3f(x2, y2, -2.0);
		/* draw top (green) triangle */
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(x1, y1, -3.0); glVertex3f(x2, y2, -3.0); glVertex3f(0.0, 0.0, -3.0); 
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(x2, y2, -2.0); glVertex3f(x1, y1, -2.0); glVertex3f(0.0, 0.0, -2.0); 
		glEnd();
		} /* a loop around circumference of a tube */

	} /* surface version */
}	/*	drawCylinder() */


/*	draws a cone of height 1, radius 1						*/
void drawCone(int nSegments){	/*	drawCone() */
	float i;
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	/* draw an appropriate sphere */
	if (wireFrame)	{ /* wireframe version */
			
			for (float i = 0.0; i < nSegments; i += 1.0)
			{ /* a loop around circumference of a tube */
			float angle = PI * i * 2.0 / nSegments ;
			float nextAngle = PI * (i + 1.0) * 2.0 / nSegments;
			/* compute sin & cosine */
			float x1 = sin(angle), y1 = cos(angle);
			float x2 = sin(nextAngle), y2 = cos(nextAngle);
			glBegin(GL_LINES);
			

			glVertex3f(x2, y2, 4.0); glVertex3f(0.0, 0.0, 3.0);
			glVertex3f(x2, y2, 4.0); glVertex3f(x1, y1, 4.0); 
			glVertex3f(x1, y1, 4.0); glVertex3f(0.0, 0.0, 4.0); // this line closes the base of the cone
						
			/* code for the inverse of the above
			 * glVertex3f(x1, y1, 4.0); glVertex3f(0.0, 0.0, 4.0);
			 * glVertex3f(x1, y1, 4.0); glVertex3f(0.0, 0.0, 3.0);
			 * glVertex3f(x1, y1, 3.0); glVertex3f(0.0, 0.0, 3.0); // this line closes the base of the cone
			**/
			glEnd();
			} /* a loop around circumference of a tube */

		/* wireframe version */
		}else{ /* surface version */
			
			for (float i = 0.0; i < nSegments; i += 1.0)
			{ /* a loop around circumference of a tube */
			float angle = PI * i * 2.0 / nSegments ;
			float nextAngle = PI * (i + 1.0) * 2.0 / nSegments;
			/* compute sin & cosine */
			float x1 = sin(angle), y1 = cos(angle);
			float x2 = sin(nextAngle), y2 = cos(nextAngle);
			glBegin(GL_TRIANGLES);
			/* drawtriangle */
			glNormal3f(0.0, 0.0, 3.0); glVertex3f(0.0, 0.0, 3.0);
			glNormal3f(x2, y2, 3.0); glVertex3f(x2, y2, 4.0);
			glNormal3f(x1, y1, 3.0); glVertex3f(x1, y1, 4.0);
			glEnd();
			} /* a loop around circumference of a tube */

		} /* surface version */	/*	drawCone() */
}

/*	draws a sphere of size 1 centred at origin 					*/
void drawSphere(int nSegments, int nSlices){	/*	drawSphere() */
	// assume radius equal to 1 to make things easier
	/* draw an appropriate sphere */
	float seg, slice;

	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	/* draw an appropriate sphere */
	if (wireFrame)	{ /* wireframe version */
		glBegin(GL_LINES);
		for (seg = 0.0; seg < nSegments; seg += 1.0)
				{					
				float theta = (PI * seg * 2.0) / nSegments ;
				float n_theta = PI * (seg + 1.0) * 2.0 / nSegments;
					for (slice= 0.0; slice < nSlices; slice += 1.0){
							float phi = (PI * slice * 2.0) / nSegments ;
							float n_phi = PI * (slice + 1.0) * 2.0 / nSegments;
						 /* a loop around circumference of a tube */
						/* compute sin & cosine */
						float x1 = cos(theta)*sin(phi), y1 = sin(theta)*sin(phi), z1=cos(phi);
						float x2 = cos(n_theta)*sin(phi), y2 = sin(n_theta)*sin(phi), z2=cos(phi);
						
						float x3 = cos(theta)*sin(n_phi), y3 = sin(theta)*sin(n_phi), z3=cos(n_phi);
						float x4 = cos(n_theta)*sin(n_phi), y4 = sin(n_theta)*sin(n_phi), z4=cos(n_phi);

						glVertex3f(x1, y1, z1);glVertex3f(x2, y2, z2);
						glVertex3f(x1, y1, z1);glVertex3f(x3, y3, z3);
						glVertex3f(x3, y3, z3);glVertex3f(x4, y4, z4);
						glVertex3f(x4, y4, z4); glVertex3f(x2, y2, z2);
					}
				}
		glEnd();
				}	
	
	/* wireframe version */
	else{ /* surface version */
		glBegin(GL_TRIANGLES);
		for (seg = 0.0; seg < nSegments; seg += 1.0)
				{					
				float theta = (PI * seg * 2.0) / nSegments ;
				float n_theta = PI * (seg + 1.0) * 2.0 / nSegments;
					for (slice= 0.0; slice < nSlices; slice += 1.0){
							float phi = (PI * slice * 2.0) / nSegments ;
							float n_phi = PI * (slice + 1.0) * 2.0 / nSegments;
						 /* a loop around circumference of a tube */
						/* compute sin & cosine */
						float x1 = cos(theta)*sin(phi), y1 = sin(theta)*sin(phi), z1=cos(phi);
						float x2 = cos(n_theta)*sin(phi), y2 = sin(n_theta)*sin(phi), z2=cos(phi);
						
						float x3 = cos(theta)*sin(n_phi), y3 = sin(theta)*sin(n_phi), z3=cos(n_phi);
						float x4 = cos(n_theta)*sin(n_phi), y4 = sin(n_theta)*sin(n_phi), z4=cos(n_phi);
						float x5 = (x1+x2+x3+x4)/4, y5 = (y1+y2+y3+y4)/4, z5 = (z1+z2+z3+z4)/4;
						
						glNormal3f(x5, y5, z5);	
						glVertex3f(x1, y1, z1);	glVertex3f(x3, y3, z3); glVertex3f(x2, y2, z2);
						glVertex3f(x3, y3, z3); glVertex3f(x2, y2, z2); glVertex3f(x4, y4, z4);
					}
				}
		glEnd();
		}
}
/**
 * 
void drawTrippySphere(int nSegments, int nSlices){
	// assume radius equal to 1 to make things easier
	// draw a trippy looking sphere
	float seg, slice;

	// make sure colour is properly set
	privateSetColour(IS_A_SURFACE);
	if (wireFrame)	{//no wireframe
	else{ // surface version
		glBegin(GL_TRIANGLES);
		for (seg = 0.0; seg < nSegments; seg += 1.0)
				{					
				float theta = (PI * seg * 2.0) / nSegments ;
				float n_theta = PI * (seg + 1.0) * 2.0 / nSegments;
					for (slice= 0.0; slice < nSlices; slice += 1.0){
							float phi = (PI * slice * 2.0) / nSegments ;
							float n_phi = PI * (slice + 1.0) * 2.0 / nSegments;
						 // a loop around circumference of a tube
						// compute sin & cosin
						float x1 = cos(theta)*sin(phi), y1 = sin(theta)*sin(phi), z1=cos(phi);
						float x2 = cos(n_theta)*sin(phi), y2 = sin(n_theta)*sin(phi), z2=cos(phi);
						
						float x3 = cos(theta)*sin(n_phi), y3 = sin(theta)*sin(n_phi), z3=cos(n_phi);
						float x4 = cos(n_theta)*sin(n_phi), y4 = sin(n_theta)*sin(n_phi), z4=cos(n_phi);
						float x5 = (x1+x2+x3+x4)/4, y5 = (y1+y2+y3+y4)/4, z5 = (z1+z2+z3+z4)/4;
						
						glNormal3f(x5, y5, z5);	
						glVertex3f(x1, y1, z1);	glVertex3f(x2, y2, z2); glVertex3f(x1, y1, z1);
						glVertex3f(x3, y3, z3); glVertex3f(x3, y3, z3); glVertex3f(x4, y4, z4);
						glVertex3f(x4, y4, z4); 
						glVertex3f(x2, y2, z2);
					}
				}
		glEnd();
		}

void drawTorus(float inner_radius, float outer_radius, int nSides, int nRings){
	float side, ring;
	// make sure colour is properly set
	privateSetColour(IS_A_SURFACE);
	// draw an appropriate sphere
	if (wireFrame)	{ // wireframe version
		// TO DO : code goes here
	} // wireframe version
	else{ // surface version	
		//TO DO : code goes here
	}
}  */

/*
 * void drawTeapot(float Size){
	//make sure colour is properly set
	privateSetColour(IS_A_SURFACE);
	//draw an appropriate sphere
	if (wireFrame)	{ //wireframe version
		//TO DO : code goes here 
	}else{
		//TO DO : code goes here
		}
	}*/ 

