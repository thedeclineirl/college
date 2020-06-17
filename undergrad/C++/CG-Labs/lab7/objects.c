#include "objects.h"

#include <math.h>
#include "point.h"
#include "vector.h"

#define PI 3.14159265358979f
#define DEG2RAD PI/180.0f
#define PHI (1+sqrt(5))/2
#define TAU (-1+sqrt(5))/2
/*	colour currently used for drawing							*/
	
static GLfloat defaultBlack[] = {0.0, 0.0, 0.0, 1.0};
static GLfloat *currentColour=defaultBlack;
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


/*	draws a tetrahedron of size 1 centred at origin 			*/
void drawTetrahedron()
{	/*	drawTetrahedron() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw an appropriate tetrahedron */
	if(wireFrame){
		
		glBegin(GL_LINES);	
		
		glVertex3iv(tet_vertices[0]); glVertex3iv(tet_vertices[1]);
		glVertex3iv(tet_vertices[1]); glVertex3iv(tet_vertices[3]);
		glVertex3iv(tet_vertices[3]); glVertex3iv(tet_vertices[0]);
		
		glVertex3iv(tet_vertices[0]); glVertex3iv(tet_vertices[2]);
		glVertex3iv(tet_vertices[2]); glVertex3iv(tet_vertices[3]);
		glVertex3iv(tet_vertices[1]); glVertex3iv(tet_vertices[2]);

		glEnd();
	}else{
		glBegin(GL_TRIANGLES);

		glNormal3i(-1, -1, 1);		//face 0
		glVertex3iv(tet_vertices[0]); glVertex3iv(tet_vertices[2]);  glVertex3iv(tet_vertices[1]);

		glNormal3i( 1, -1, -1 );	//face 1
		glVertex3iv(tet_vertices[0]); glVertex3iv(tet_vertices[3]);  glVertex3iv(tet_vertices[2]);

		glNormal3i( 1, 1, 1 );		//face 2
		glVertex3iv(tet_vertices[3]); glVertex3iv(tet_vertices[1]);  glVertex3iv(tet_vertices[2]);

		glNormal3i( -1,  1,  -1 );	//face 3
		glVertex3iv(tet_vertices[0]); glVertex3iv(tet_vertices[1]);  glVertex3iv(tet_vertices[3]);

		glEnd();
	}
}

/*	draws a cube of size 1 centred at origin 					*/
void drawCube()
{	/*	drawCube() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	
	/* draw an appropriate cube */
	if (wireFrame){

		glBegin(GL_LINES);
		
		glVertex3f(-1.0, -1.0, -1.0); glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(-1.0, -1.0, 1.0); glVertex3f(-1.0, 1.0, 1.0);
	
		glVertex3f(-1.0, 1.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
		glVertex3f(-1.0, 1.0, -1.0); glVertex3f(-1.0, -1.0, -1.0);
	
		glVertex3f(-1.0, -1.0, -1.0); glVertex3f( 1.0, -1.0, -1.0);
		glVertex3f(-1.0, -1.0, 1.0);  glVertex3f( 1.0, -1.0, 1.0);
	
		glVertex3f(-1.0, 1.0, 1.0);   glVertex3f( 1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, -1.0);  glVertex3f( 1.0, 1.0, -1.0);
	
		glVertex3f( 1.0, -1.0, -1.0); glVertex3f( 1.0, -1.0, 1.0);
		glVertex3f( 1.0, -1.0, 1.0);  glVertex3f( 1.0, 1.0, 1.0);
	
		glVertex3f( 1.0, 1.0, 1.0);   glVertex3f( 1.0, 1.0, -1.0);
		glVertex3f( 1.0, 1.0, -1.0);  glVertex3f( 1.0, -1.0, -1.0);
		glEnd();
	}else{
		glBegin(GL_TRIANGLES);

		glNormal3i(-1, 0, 0);//face 2
		glVertex3iv(cube_vertices[0]); glVertex3iv(cube_vertices[2]); glVertex3iv(cube_vertices[3]);
		glVertex3iv(cube_vertices[0]); glVertex3iv(cube_vertices[3]); glVertex3iv(cube_vertices[1]);

		glNormal3i( 0, -1, 0);//face0
		glVertex3iv(cube_vertices[0]); glVertex3iv(cube_vertices[1]); glVertex3iv(cube_vertices[5]);
		glVertex3iv(cube_vertices[0]); glVertex3iv(cube_vertices[5]); glVertex3iv(cube_vertices[4]);

		glNormal3i( 0, 0, -1);//face1
		glVertex3iv(cube_vertices[0]); glVertex3iv(cube_vertices[4]); glVertex3iv(cube_vertices[6]);
		glVertex3iv(cube_vertices[0]); glVertex3iv(cube_vertices[6]); glVertex3iv(cube_vertices[2]);

		glNormal3i( 1, 0, 0);////face3
		glVertex3iv(cube_vertices[6]); glVertex3iv(cube_vertices[5]); glVertex3iv(cube_vertices[4]);
		glVertex3iv(cube_vertices[6]); glVertex3iv(cube_vertices[5]); glVertex3iv(cube_vertices[7]);
		
		glNormal3i( 0, 1, 0);//face5
		glVertex3iv(cube_vertices[6]); glVertex3iv(cube_vertices[3]); glVertex3iv(cube_vertices[7]);
		glVertex3iv(cube_vertices[6]); glVertex3iv(cube_vertices[3]); glVertex3iv(cube_vertices[2]);

		glNormal3i( 0, 0, 1);//face4
		glVertex3iv(cube_vertices[5]); glVertex3iv(cube_vertices[3]); glVertex3iv(cube_vertices[1]);
		glVertex3iv(cube_vertices[5]); glVertex3iv(cube_vertices[3]); glVertex3iv(cube_vertices[7]);
		
		glEnd();
	}
}	/*	drawCube() */


/*	draws an octahedron of size 1 centred at origin 			*/
void drawOctahedron()
{	/*	drawOctahedron() */
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	/*
	/* draw an appropriate octahedron */
	if (wireFrame){
		glBegin(GL_LINES);
		
		glVertex3iv(oct_vertices[0]); glVertex3iv(oct_vertices[2]);
		glVertex3iv(oct_vertices[0]); glVertex3iv(oct_vertices[3]);
		glVertex3iv(oct_vertices[0]); glVertex3iv(oct_vertices[4]);
		glVertex3iv(oct_vertices[0]); glVertex3iv(oct_vertices[5]);

		glVertex3iv(oct_vertices[1]); glVertex3iv(oct_vertices[2]);
		glVertex3iv(oct_vertices[1]); glVertex3iv(oct_vertices[3]);
		glVertex3iv(oct_vertices[1]); glVertex3iv(oct_vertices[4]);
		glVertex3iv(oct_vertices[1]); glVertex3iv(oct_vertices[5]);

		glVertex3iv(oct_vertices[3]); glVertex3iv(oct_vertices[2]);
		glVertex3iv(oct_vertices[2]); glVertex3iv(oct_vertices[5]);
		glVertex3iv(oct_vertices[5]); glVertex3iv(oct_vertices[4]);
		glVertex3iv(oct_vertices[4]); glVertex3iv(oct_vertices[3]);

		glEnd();
	}else{

		glBegin(GL_TRIANGLES);

		/* Top */
		glNormal3i(-1, -1, 1 ); //face 0
		glVertex3iv(oct_vertices[0]); glVertex3iv(oct_vertices[3]); glVertex3iv(oct_vertices[4]);
		
		glNormal3i(-1, 1, 1 ); //face 1
		glVertex3iv(oct_vertices[0]); glVertex3iv(oct_vertices[4]); glVertex3iv(oct_vertices[5]);
		
		glNormal3i( 1, 1, 1 ); //face 2
		glVertex3iv(oct_vertices[0]); glVertex3iv(oct_vertices[2]); glVertex3iv(oct_vertices[5]);

		glNormal3i( 1, -1, 1 ); //face 3
		glVertex3iv(oct_vertices[0]); glVertex3iv(oct_vertices[3]); glVertex3iv(oct_vertices[2]);
	
		/* Bottom */
		glNormal3i(-1, -1, -1 ); //face 4
		glVertex3iv(oct_vertices[1]); glVertex3iv(oct_vertices[3]); glVertex3iv(oct_vertices[4]);
		
		glNormal3i(-1, 1, -1 ); //face 5
		glVertex3iv(oct_vertices[1]); glVertex3iv(oct_vertices[4]); glVertex3iv(oct_vertices[5]);
		
		glNormal3i( 1, 1, -1 ); //face 6
		glVertex3iv(oct_vertices[1]); glVertex3iv(oct_vertices[2]); glVertex3iv(oct_vertices[5]);

		glNormal3i( 1, -1, -1 ); //face 7
		glVertex3iv(oct_vertices[1]); glVertex3iv(oct_vertices[3]); glVertex3iv(oct_vertices[2]);

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
		glBegin(GL_LINES);
		
		/* Face 0 */
		//glVertex()
		glEnd();
	}else{
	
	}
}	/*	drawDodecahedron() */


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
		glBegin(GL_LINES);
		for (i = 0.0f; i < nSegments; i += 1.0f){ /* theta loop */

			float angle = (PI * i * 2.0f) / nSegments ;
			float nextAngle = (PI * (i + 1.0f) * 2.0f) / nSegments;
			/* compute sin & cosine */
			float x1 = sin(angle), y1 = cos(angle);
			float x2 = sin(nextAngle), y2 = cos(nextAngle);
			
			// draw a wireframe panel
			glVertex3f(x1, y1, 0.0f); glVertex3f(x1, y1, 1.0f);
			glVertex3f(x1, y1, 1.0f); glVertex3f(x2, y2, 1.0f);
			glVertex3f(x2, y2, 1.0f); glVertex3f(x2, y2, 0.0f);
			glVertex3f(x2, y2, 0.0f); glVertex3f(x1, y1, 0.0f);
			glVertex3f(x1, y1, 0.0f); glVertex3f(x2, y2, 1.0f);

		} /* theta loop */
		glEnd();
		} /* wireframe version */
	else{ /* surface version */
		glBegin(GL_TRIANGLES);
		for(i = 0.0f; i < nSegments; i += 1.0f)
		{ /* theta loop */
			float angle = PI * i * 2.0f / nSegments ;
			float nextAngle = PI * (i + 1.0f) * 2.0f / nSegments;

			/* compute sin & cosine */
			float x1 = sin(angle), y1 = cos(angle);
			float x2 = sin(nextAngle), y2 = cos(nextAngle);
			
			Vector n1(x1, y1, 0.0f);
			Vector n2(x2, y2, 0.0f);
			Vector n3(x1, y1, 1.0f);
			Vector n4(x2, y2, 1.0f);
		
			n1.norm(); n2.norm(); n3.norm(); n4.norm();

			glNormal3f(n1.x, n1.y, n1.z);
			glVertex3f(x1, y1, 0.0f); 

			glNormal3f(n4.x, n4.y, n4.z);
			glVertex3f(x2, y2, 1.0f); 
			
			glNormal3f(n3.x,n3.y, n3.z);
			glVertex3f(x1, y1, 1.0f);

			glNormal3f(n1.x, n1.y, n1.z);
			glVertex3f(x1, y1, 0.0f); 
	
			glNormal3f(n2.x, n2.y, n2.z);
			glVertex3f(x2, y2, 0.0f); 

			glNormal3f(n4.x, n4.y, n4.z);
			glVertex3f(x2, y2, 1.0f);
		} /* theta loop */
		glEnd();
	} /* surface version */
}	/*	drawCylinder() */


/*	draws a cone of height 1, radius 1						*/
void drawCone(int nSegments){	/*	drawCone() */
	float i;
	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	/* draw an appropriate sphere */
	if (wireFrame)	{ /* wireframe version */
		glBegin(GL_LINES);
		for (i = 0.0f; i < nSegments; i += 1.0f){ /* theta loop */

			float angle = (PI * i * 2.0f) / nSegments ;
			float nextAngle = (PI * (i + 1.0f) * 2.0f) / nSegments;
			/* compute sin & cosine */
			float x1 = sin(angle), y1 = cos(angle);
			float x2 = sin(nextAngle), y2 = cos(nextAngle);
			
			// draw a wireframe panel
			glVertex3f(x1, y1, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 1.0); glVertex3f(x2, y2, 0.0f);
			glVertex3f(x2, y2, 0.0f); glVertex3f(x1, y1, 0.0f);
		} /* theta loop */
		glEnd();
		} /* wireframe version */
	else{ /* surface version */
		glBegin(GL_TRIANGLES);
		for (i = 0.0f; i < nSegments; i += 1.0f)
		{ /* theta loop */
			float angle =  (2.0f * PI * i) / nSegments ;
			float nextAngle = (2.0f * PI * (i + 1.0f))/ nSegments;

			/* compute sin & cosine */
			float x1 = sin(angle), y1 = cos(angle);
			float x2 = sin(nextAngle), y2 = cos(nextAngle);

			Vector n1(x1, y1, 0.0f);
			Vector n2(x2, y2, 0.0f);
			Vector n3(0.0f, 0.0f, 1.0f);
		
			n1.norm();
			n2.norm();
			n3.norm();

			glNormal3f(n1.x, n1.y, n1.z);
			glVertex3f(x1, y1, 0.0f); 
			glNormal3f(n2.x, n2.y, n2.z);
			glVertex3f(x2, y2, 0.0f);
			glNormal3f(n3.x, n3.y, n3.z);
			glVertex3f(0.0f, 0.0f, 1.0f);

		} /* theta loop */
		glEnd();
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

void drawTorus(float inner_radius, float outer_radius, int nSides, int nRings){

	float side, ring;

	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	/* draw an appropriate sphere */
	if (wireFrame)	{ /* wireframe version */
		glBegin(GL_LINES);
		
		for (side = 0.0f; side < nSides; side += 1.0f)
		{ /* segments loop */


			float u      = (2.0f * PI * side) / nSides;
			float new_u = (2.0f * PI * (side + 1.0f))/ nSides;
			
			for(ring = 0.0f; ring < nRings; ring += 1.0f)
			{ /* slices loop */
				float v        = (2.0f * PI * ring) / nRings;
				float new_v   = (2.0f * PI * (ring + 1.0f))/ nRings;
				
				/* compute sin & cosine */	
				// bottom two points
				float x1 = (outer_radius + inner_radius*cos(v))*cos(u);
				float y1 = (outer_radius + inner_radius*cos(v))*sin(u);
				float z1 = inner_radius*sin(v);
		
				float x2 = (outer_radius + inner_radius*cos(new_v))*cos(u);
				float y2 = (outer_radius + inner_radius*cos(new_v))*sin(u);
				float z2 = inner_radius*sin(new_v);

				// top two for next phi
				float x3 = (outer_radius + inner_radius*cos(v))*cos(new_u);
				float y3 = (outer_radius + inner_radius*cos(v))*sin(new_u);
				float z3 = inner_radius*sin(v);

				float x4 = (outer_radius + inner_radius*cos(new_v))*cos(new_u);
				float y4 = (outer_radius + inner_radius*cos(new_v))*sin(new_u);
				float z4 = inner_radius*sin(new_v);

				glVertex3f(x1, y1, z1); glVertex3f(x3, y3, z3); glVertex3f(x2, y2, z2);

				glVertex3f(x3, y3, z3); glVertex3f(x4, y4, z4); glVertex3f(x2, y2, z2);
				
			} /* ring loop */
		} /* segments loop */
		glEnd();
	} /* wireframe version */
	else{ /* surface version */
		glBegin(GL_TRIANGLES);
		for (side = 0.0f; side < nSides; side += 1.0f)
		{ /* segments loop */

			float u      = (2.0f * PI * side) / nSides;
			float new_u = (2.0f * PI * (side + 1.0f))/ nSides;
			
			for(ring = 0.0f; ring < nRings; ring += 1.0f)
			{ /* slices loop */
				float v        = (2.0f * PI * ring) / nRings;
				float new_v   = (2.0f * PI * (ring + 1.0f))/ nRings;
				
				/* compute sin & cosine */
				
				// bottom two points
				float x1 = (outer_radius + inner_radius*cos(v))*cos(u);
				float y1 = (outer_radius + inner_radius*cos(v))*sin(u);
				float z1 = inner_radius*sin(v);
		
				float x2 = (outer_radius + inner_radius*cos(new_v))*cos(u);
				float y2 = (outer_radius + inner_radius*cos(new_v))*sin(u);
				float z2 = inner_radius*sin(new_v);

				// top two for next phi
				float x3 = (outer_radius + inner_radius*cos(v))*cos(new_u);
				float y3 = (outer_radius + inner_radius*cos(v))*sin(new_u);
				float z3 = inner_radius*sin(v);

				float x4 = (outer_radius + inner_radius*cos(new_v))*cos(new_u);
				float y4 = (outer_radius + inner_radius*cos(new_v))*sin(new_u);
				float z4 = inner_radius*sin(new_v);
				
				// to get normals for each of the points find a point in the center of the tube.
				float pt1_x = sin(u)*outer_radius, pt1_y = cos(u)*outer_radius, pt1_z = 0.0f;
				float pt2_x = sin(u)*outer_radius, pt2_y = cos(u)*outer_radius, pt2_z = 0.0f;
			
				Vector n1(x1 - pt1_x, y1 - pt1_y, z1 - pt1_z);
				Vector n2(x2 - pt2_x, y2 - pt2_y, z2 - pt2_z);
				Vector n3(x3 - pt1_x, y3 - pt1_y, z3 - pt1_z);
				Vector n4(x4 - pt2_x, y4 - pt2_y, z4 - pt2_z);
				n1 = n1.norm();	n2 = n2.norm(); n3 = n3.norm(); n4 = n4.norm();
				
				glNormal3f(n1.x, n1.y, n1.z);
				glVertex3f(x1, y1, z1);

				glNormal3f(n3.x, n3.y, n3.z);
				glVertex3f(x3, y3, z3); 

				glNormal3f(n2.x, n2.y, n2.z);
				glVertex3f(x2, y2, z2);

				glNormal3f(n1.x, n1.y, n1.z);
				glNormal3f(x1, y1, z1);
		
				glNormal3f(n3.x, n3.y, n3.z);
				glVertex3f(x3, y3, z3); 
	
				glNormal3f(n4.x, n4.y, n4.z);
				glVertex3f(x4, y4, z4);

				glNormal3f(n2.x, n2.y, n2.z);
				glVertex3f(x2, y2, z2);
				
			} /* ring loop */
		} /* side loop */
		glEnd();
	}
}

void drawTeapot(float Size){

	/* make sure colour is properly set */
	privateSetColour(IS_A_SURFACE);
	/* draw an appropriate sphere */
	if (wireFrame)	{ /* wireframe version */
		glutWireTeapot(Size);
	}else{
		glutSolidTeapot(Size);
	}
}
