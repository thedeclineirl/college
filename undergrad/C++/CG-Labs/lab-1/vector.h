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
#include <ostream>
using namespace std;
/**
	@author John Meade <john.meade@ucd.ie>
*/
class Vector
{ // class Vector
	public: // makes life easier
		float x, y, z; // the coordinates
		~Vector();
		Vector(); // default constructor
		Vector(float X, float Y, float Z); // initializing constructor
		
		float &operator[](int i);
		float length();
		Vector norm();
		float dot(Vector v);
		Vector cross(Vector v);
		
}; // class Vector

ostream &operator<< (ostream & ostr, Vector v);
// C++ print routine

/**
 * Vector/Point Operations
 */
//unary Minuse
Vector operator- (Vector v);

//Addition
Point operator+ (Point p, Vector v);
Point operator+ (Vector v, Point p);
Point operator+ (Vector v, Vector v);
// Subtraction
Point operator- (Point p, Vector v);
Vector operator- (Point tail, Point head);
Vector operator- (Vector v, Vector w);
// Scalar Multiplication
Vector operator* (float s, Vector v);
Vector operator* (Vector v, float s);

#endif
