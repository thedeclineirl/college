#include <GL/glut.h>

/*	toggle for whether to render wireframe or surface shaded	*/
extern int wireFrame;

/*	utility for setting the colour of an object					*/
void setColour(GLfloat *theColour);

/****************************/
/*	0-D, 1-D, & 2-D objects */
/****************************/

/*	draws a point at the origin 								*/
void drawPoint();

/*	draws a line of length 1 along the x axis 					*/
void drawLine();

/*	draws a line of length 1 along the x axis 					*/
void drawLineBetween(GLfloat *from, GLfloat *to);

/*	draws a a panel for use a sign								*/
void drawPanel();

/*	draws a square of size 1 perpendicular to the y axis 		*/
void drawSquare();

/*	draws a circle of radius 1 perpendicular to the y axis 		*/
void drawCircle(int nSegments);

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

/*	draws an icosahedron of size 1 centred at origin 			*/
void drawIcosahedron();

/****************************/
/*	More complex solids 	*/
/****************************/

/*	draws a cylinder of height 1, radius 1						*/
void drawCylinder(int nSegments);

/*	draws a vertical cylinder of given height and radius 		*/
void drawVertCylinder(int nSegments, float height, float radius);

/*	draws a cone of height 1, radius 1							*/
void drawCone(int nSegments);

/*	draws a sphere of size 1 centred at origin 					*/
void drawSphere(int nSegments, int nSlices);

/*	draws a torus centred at origin 							*/
void drawTorus(int ratioRadii, int nSegments, int nSlices);

/*	draws a teapot centred at origin 							*/
void drawTeapot();

/*	draws a standard set of x, y, z axes						*/
void drawAxes();
