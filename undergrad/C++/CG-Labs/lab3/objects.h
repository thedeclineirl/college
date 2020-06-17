#include <GL/glut.h>

/*	toggle for whether to render wireframe or surface shaded	*/
extern int wireFrame;

/*	utility for setting the colour of an object					*/
void setColour(GLfloat *theColour);

/****************************/
/*	Regular Platonic solids */
/****************************/

/*	draws a tetrahedron of size 1 centred at origin 			*/
void drawTetrahedron();

/*	draws a cube of size 1 centred at origin 					*/
void drawCube();

/*	draws an octahedron of size 1 centred at origin 			*/
void drawOctahedron();

/*	draws a dodecahedron of size 1 centred at origin 			*/
void drawDodecahedron();

/*	draws an icosahedron of size 1 centred at the origin			*/
void drawIcosahedron();

/***********************************/
/*	More complex solids        */
/***********************************/

/*	draws a cylinder of height 1, radius 1						*/
void drawCylinder(int nSegments); //Fridays lab

/*	draws a cone of height 1, radius 1							*/
void drawCone(int nSegments);//Fridays lab

/*	draws a sphere of size 1 centred at origin 					*/
void drawSphere(int nSegments, int nSlices);//Fridays lab

/*	draws a torus centred at the origin     */
void drawTorus(float inner_radius, float outer_radius, int nSides, int nRings);

/*	draw teapot	*/
void drawTeapot(float Size);
