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
#include <math.h>
#include <iostream>
#include "vector.h"


Vector::Vector(){
	x = 0.0f; y = 0.0f, z = 0.0f;
}

Vector::Vector(GLfloat X, GLfloat Y, GLfloat Z){
	x = X; y = Y; z = Z;
}

Vector::~Vector()
{
}

Vector &Vector::operator= (Vector v){
	x = v.x;
	y = v.y;
	z = v.z;
	return (*this);
}

Vector Vector::cross(Vector v){
	Vector result;
	result.x = y*v.z - z*v.y;
	result.y = z*v.x - x*v.z;
	result.z = x*v.y - y*v.x;
	return result;
}

GLfloat Vector::dot(Vector v){
	return (x*v.x + y*v.y + z*v.z);
}

GLfloat Vector::length(){
	return sqrtf(x*x + y*y + z*z);
}

Vector Vector::norm(){
	Vector unit;
	GLfloat l = sqrtf(x*x + y*y + z*z);
	unit.x = x/l;
	unit.y = y/l;
	unit.z = z/l;
	return unit;
}

/* trick for rastering in 2D get the normal to a vector in 2D by flipping coordinates */
Vector Vector::Normal2D(){
	
	Vector result( 0.0f, 0.0f, 1.0f );
	
	result[0] = y; //giving result an x co-ordinate, the y co-ordinate of the main vector
	result[1] = x; //giving result an y co-ordinate, the x co-ordinate of the main vector
	result[2] = z; //giving result an z co-ordinate, the z co-ordinate of the main vector
	/** TO DO : make sure this code is right **/
	return result;
}

GLfloat & Vector::operator [ ](int i){
	switch(i) // depending on the index
	{ // switch on index i
		case 0: return x; // x is equivalent to index 0
		case 1: return y; // y is equivalent to index 1
		case 2: return z; // z is equivalent to index 2
		default:
			cout << "Error: . . . .";
			return x; // we have to return something
	} // switch on index i
}

// C++ print routine
ostream & operator<< (ostream & ostr, Vector v){
	ostr << "[" << v.x << ", " << v.y << ", " << v.z << "]";
	return ostr;
}


Vector Vector::operator -(Vector v){
	return Vector(-v.x, -v.y, -v.z);
}

//Addition
Point operator+ (Point p, Vector v)
{ // operator+
	Point q;
	for (int i = 0; i < 3; i++)
		q[i] = p[i] + v[i];
	return q;
} // operator+

Point operator+ (Vector v, Point p){
	Point q;
	for (int i = 0; i < 3; i++)
		q[i] = v[i] + p[i];
	return q;
}

Vector operator+ (Vector v, Vector w){
	Vector q;
	for (int i = 0; i < 3; i++)
		q[i] = v[i] + w[i];
	return q;
}
// Subtraction
Point operator- (Point p, Vector v){
	Point q;
	for (int i = 0; i < 3; i++)
		q[i] = p[i] + v[i];
	return q;
}

Vector operator- (Point tail, Point head)
{ // operator -
	Vector v;
	for (int i = 0; i < 3; i++)
		v[i] = tail[i] - head[i];
	return v;
} // operator -

Vector operator- (Vector v, Vector w){
	Vector u;
	for (int i = 0; i < 3; i++)
		u[i] = v[i] - w[i];
	return u;
}
// Scalar Multiplication
Vector operator* (GLfloat s, Vector v){
	Vector u;
	for (int i = 0; i < 3; i++)
		u[i] = s*v[i];
	return u;
}

Vector operator* (Vector v, GLfloat s){
	Vector u;
	for (int i = 0; i < 3; i++)
		u[i] = v[i]*s;
	return u;
}

GLfloat Distance(Point line_1, Point line_2, Point p){
	
	GLfloat distance = 0.0f;
	Vector x = line_2-line_1;
	Vector y = x.Normal2D(); //normal vector of x
	Vector v = line_1-p;
	distance = (y.dot(v))/y.length(); // divide the product of the normal & the remainder of c subtracted from the point, 
							// by the norm of the normal vector
							
	return distance;
}


