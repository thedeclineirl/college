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
#include "point.h"
#include "vector.h"
#include <iostream>

using namespace std;

Point::Point(){ // default constructor
	x = 0.0f; y = 0.0f; z = 0.0f; // set to predictable values
} // default constructor

Point::Point(GLfloat X, GLfloat Y, GLfloat Z){// initializing constructor
 // initializing constructor
	x = X; y = Y; z = Z; // copy the input values
} // initializing constructor

Point::~Point(){
	
}

GLfloat &Point::operator[](int i) // index operator
{ // operator[]
	switch(i) // depending on the index
	{ // switch on index i
		case 0: return x; // x is equivalent to index 0
		case 1: return y; // y is equivalent to index 1
		case 2: return z; // z is equivalent to index 2
		default:
			cout << "Error: . . . .";
			return x; // we have to return something
	} // switch on index i
} // operator[]

Point &Point::operator= (Point q)
{ // assignment
	x = q.x;
	y = q.y;
	z = q.z;
	return *this;
} // assignment

// C++ print routine
ostream &operator<< (ostream & ostr, Point p){ // print routine
	ostr << "(" << p.x << ", " << p.y << ", " << p.z << ")";
	return ostr;
} // print routine

/* take an array of three points and sort them in ascending order by their x-coord */
Point* Sort(Point *p){ 
/* sort arbitrary array of points by their x component */
	Point temp;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			
			if(p[i].x < p[j].x){
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}	
	return p;
}
