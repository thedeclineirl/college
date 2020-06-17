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
#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"
/**
	@author John Meade <john.meade@ucd.ie>
*/
class Matrix
{ // class Matrix
	public: // makes life easier
		float coords[3][3]; // treat each row as a vector
		Matrix(); // default constructor
		~Matrix();
		static Matrix Identity(); // returns identity matrix
		Vector operator[](int i); // returns a row as a vector
		Vector column(int j); // returns a column as vector
}; // class Matrix

ostream &operator<< (ostream & ostr, Matrix m);
// C++ print routine

/**
 * Matrix Operations
 */
Point operator* (Matrix m, Point p);
Vector operator* (Matrix m, Vector v);
Matrix operator* (Matrix m,Matrix w);
Matrix operator+ (Matrix m, Matrix w);
Matrix operator- (Matrix m, Matrix w);
#endif
