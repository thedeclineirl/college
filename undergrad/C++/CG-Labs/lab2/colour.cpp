#include "colour.h"

Colour::Colour(){
	// default colour on instansiation is white
	colour[0] = 1.0f; colour[1] = 1.0f; colour[2] = 1.0f, colour[3] = 1.0f;
}

Colour::Colour(GLfloat Red, GLfloat Green, GLfloat Blue){
	colour[0] = Red; colour[1] = Green; colour[2] = Blue; 

	colour[3] = 1.0f;
}

Colour::Colour(GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat Alpha){
	colour[0] = Red; colour[1] = Green; colour[2] = Blue; colour[3] = Alpha;
}

Colour::~Colour(){
}

Colour &Colour::operator= (Colour c){
	for(int i = 0; i < 4; i++)
		colour[i] = c.colour[i];
	return (*this);
}

void Colour::SetPixel(GLfloat Red, GLfloat Green, GLfloat Blue){
	colour[0] = Red; colour[1] = Green; colour[2] = Blue; 

	colour[3] = 1.0f;
}

GLfloat &Colour::operator[](int i){
	switch(i) // depending on the index
	{ // switch on index i
		case 0: return colour[0];   // red is equivalent to index 0
		case 1: return colour[1]; // green is equivalent to index 1
		case 2: return colour[2];  // blue is equivalent to index 2
		case 3: return colour[3];  // alpha is equivalent to index 3
		default:
			cout << "Error: . . . .";
			return colour[3]; // we have to return something
	} // switch on index i
}

ostream &operator<< (ostream & ostr, Colour c){
	ostr << "[" << c[0] << ", " << c[1] << ", " << c[2] << ", " << c[3] << "]";
	return ostr;
}
// C++ print routine

/**
 * Colour Operations
 */

//Can Add, Subtract colour
Colour operator+ (Colour c1, Colour c2){
	return Colour( c1[0] + c2[0], c1[1] + c2[1], c1[2] + c2[2]);
}

Colour operator- (Colour c1, Colour c2){
	return Colour( c1[0] - c2[0], c1[1] - c2[1], c1[2] - c2[2]);
}

// Scalar Multiplication for applying a weighting to a colour
Colour operator* (float s, Colour c){
	return Colour( c[0]*s, c[1]*s, c[2]*s);
}

Colour operator* (Colour c, float s){
	return Colour( c[0]*s, c[1]*s, c[2]*s);
}

