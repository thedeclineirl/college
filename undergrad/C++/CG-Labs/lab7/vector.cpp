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


Vector::Vector():x(0),y(0),z(0){
	
}

Vector::Vector(float X,float Y, float Z){
	x=X;
	y=Y;
	z=Z;
}

Vector::~Vector()
{
}

Vector Vector::cross(Vector v){
	Vector result;
	result.x = y*v.z - z*v.y;
	result.y = z*v.x - x*v.z;
	result.z = x*v.y - y*v.x;
	return result;
}

float Vector::dot(Vector v){
	return (x*v.x + y*v.y + z*v.z);
}

float Vector::length(){
	return sqrtf(x*x + y*y + z*z);
}

Vector Vector::norm(){
	Vector unit;
	float l = sqrtf(x*x + y*y + z*z);
	unit.x = x/l;
	unit.y = y/l;
	unit.z = z/l;
	return unit;
}

float & Vector::operator [ ](int i){
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

Point operator+ (Vector v, Vector w){
	Point q;
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
Vector operator* (float s, Vector v){
	Vector u;
	for (int i = 0; i < 3; i++)
	u[i] = s*v[i];
	return u;
}
Vector operator* (Vector v, float s){
	Vector u;
	for (int i = 0; i < 3; i++)
	u[i] = v[i]*s;
	return u;
}



