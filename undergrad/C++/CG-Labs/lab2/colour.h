#ifndef COLOUR_H
#define COLOUR_H

#include <iostream>
#include <GL/glut.h>

using namespace std;

class Colour{

	public:
		GLfloat colour[4]; // the coordinates
		~Colour();
		Colour(); // default constructor
		Colour(GLfloat Red, GLfloat Green, GLfloat Blue); // initializing constructor no alpha
		Colour(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha); // initializing constructor

		Colour &operator= (Colour c);
		void SetPixel(GLfloat Red, GLfloat Green, GLfloat Blue);
		GLfloat &operator[](int i);
		
}; // class Vector

ostream &operator<< (ostream & ostr, Colour c);
// C++ print routine

/**
 * Colour Operations
 */

//Can Add, Subtract colour
Colour operator+ (Colour c1, Colour c2);
Colour operator- (Colour c1, Colour c2);

// Scalar Multiplication
Colour operator* (float s, Colour c);
Colour operator* (Colour, float s);

#endif  //COLOUR_H
