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
#include "vector.h"
#include <iostream>
#include <math.h>

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
	Vector a;
	a[0]= (y*v.z)-(z*v.y);
	a[1]= (z*v.x)-(x*v.z);
	a[2]= (x*v.y)-(y*v.x);
	return a;
}

float Vector::dot(Vector v){
	float x1,y1,z1,x2,y2,z2;
	x1=v.x;
	y1=v.y;
	z1=v.z;
		
	x2=x1*x;
	y2=y1*y;
	z2=z1*z;

	return x2,y2,z2;
	
}

float Vector::length(){
	float a,b,t,u,v;
	t=x*x;
	u=y*y;
	v=z*z;
	a=t+u+v;
	b= sqrt(a);
	
	return b;
}

Vector Vector::norm(){
	Vector a;
	float l; 
	l = length();
	a[0]=x/l;
	a[1]=y/l;
	a[2]=z/l;
	
	return a;
}

float & Vector::operator [ ](int i){
	//returns ith element of the vector
	switch(i) // depending on the index
		{ // switch on index i
			case 0: return x; // x is equivalent to index 0
			case 1: return y; // y is equivalent to index 1
			case 2: return z; // z is equivalent to index 2
			default:
				cout << "Error: . . . .";
				return x; // we have to return something
}
}

// C++ print routine
ostream & operator<< (ostream & ostr, Vector v){
	ostr << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return ostr;
}


Vector operator -(Vector v){
	Vector q;
	for(int i = 0; i < 3; i++)
	q[i] = v[i] * -1;
	return q;
}

//Addition
Point operator+ (Point p, Vector v)
{ // operator+
	Point q;
	for(int i = 0; i < 3; i++)
	q[i] = p[i] + v[i];
	return q;
} // operator+

Point operator+ (Vector v, Point p){
	Point q;
	for(int i = 0; i < 3; i++)
	q[i] = p[i] + v[i];
	return q;
	
}

Point operator+ (Vector v, Vector w){
	Point q;
	for(int i = 0; i < 3; i++)
	q[i] = w[i] + v[i];
	return q;
}
// Subtraction
Point operator- (Point p, Vector v){
	Point q;
	for(int i = 0; i < 3; i++)
	q[i] = p[i] - v[i];
	return q;
}

Vector operator- (Point tail, Point head)
{ // operator -
	Vector v;
	for(int i = 0; i < 3; i++)
	v[i] = tail[i] - head[i];
	return v;
} // operator -

Vector operator- (Vector v, Vector w){
	Vector q;
	for(int i = 0; i < 3; i++)
	q[i] = v[i] - w[i];
	return q;
}
// Scalar Multiplication
Vector operator* (float s, Vector v){
	Vector q;
	for(int i = 0; i < 3; i++)
	q[i] = v[i] * s;
	return q;
}
Vector operator* (Vector v, float s){
	Vector q;
	for(int i = 0; i < 3; i++)
	q[i] = v[i] * s;
	return q;
}



