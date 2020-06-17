#include <GL/glut.h>

/* a struct is the C equivalent of a class */
/* all its variables are public and it has */
/* no methods.                             */

typedef struct
	{ /* texture */
	long height, width;
	unsigned char *texBytes;
	GLuint texName;
	} /* texture */
	texture;

/* attempts to load a texture from file    */
/* returns a valid pointer to a texture if */
/* the load works, a NULL pointer if it    */
/* doesn't.  MAKE SURE you check!!         */

texture *loadPPM(char *fileName);
