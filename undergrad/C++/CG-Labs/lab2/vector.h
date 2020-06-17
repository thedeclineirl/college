/***************************************************************************
 *   Copyright (C) 2007 by John Meade   *
 *   john.meade@ucd.ie   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef VECTOR_H
#define VECTOR_H
#include "point.h"
#include <GL/glut.h>
#include <iostream>

using namespace std;
/**
	@author John Meade <john.meade@ucd.ie>
*/
class Vector
{ // class Vector
	public: // makes life easier
		GLfloat x, y, z; // the coordinates

		Vector(); // default constructor
		Vector(GLfloat X, GLfloat Y, GLfloat Z); // initializing constructor
		~Vector();

		GLfloat &operator[](int i);
		Vector  &operator=(Vector v);

		GLfloat length();
		Vector  norm();
		GLfloat dot(Vector v);
		Vector  cross(Vector v);

		// extra stuff for doing implicit lines
		Vector  Normal2D();

		//unary Minuse
		Vector operator- (Vector v);
		
}; // class Vector

ostream &operator<< (ostream & ostr, Vector v);
// C++ print routine

/**
 * Vector/Point Operations
 */

//Addition
Point  operator+ (Point p, Vector v);
Point  operator+ (Vector v, Point p);
Vector operator+ (Vector v, Vector v);
// Subtraction
Point  operator- (Point p, Vector v);
Vector operator- (Point tail, Point head);
Vector operator- (Vector v, Vector w);
// Scalar Multiplication
Vector operator* (GLfloat s, Vector v);
Vector operator* (Vector v, GLfloat s);

GLfloat Distance(Point line_1, Point line_2, Point p);

#endif
