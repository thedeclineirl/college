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
#include "matrix.h"

Matrix::Matrix(){
	
}

Matrix::~Matrix()
{
}

Matrix Matrix::Identity(){
	Matrix q;
	for (int i = 0; i < 3; i++){
	for (int j = 0; j < 3; j++){
		if(i==j){
			q[i][j]=1;
		}else{
			q[i][j]=0;	
		}
	}
	}
	return q;
}

Vector Matrix::operator[](int i)
{ // operator[]
	return Vector(coords[i][0], coords[i][1], coords[i][2]);
} // operator[]

Vector Matrix::column(int j) // returns a column as vector
{ // column()
	return Vector(coords[0][j], coords[1][j], coords[2][j]);
} // column()

ostream &operator<< (ostream & ostr, Matrix m)
{ // print operator
	for (int i = 0; i < 3; i++){
		ostr << m[i] << endl;
	}
	return ostr;
} // print operator


Point operator* (Matrix m, Point p)
{ // operator*
	Point q(0,0,0);
	for (int i = 0; i < 3; i++){
	for (int j = 0; j < 3; j++){
	q[i] += m[i][j]* p[j];
	}
	}
	return q;
} // operator*

Vector operator* (Matrix m, Vector v)
{ // operator*
	Vector w(0,0,0);
	for (int i = 0; i < 3; i++)
	w[i] = m[i].dot(v);
} // operator*

Matrix operator* (Matrix m, Matrix w){
	Matrix q;
	for (int i = 0; i < 3; i++){
	for (int j = 0; j < 3; j++){
	q[i][j] = (m[0][j]*w[0][j])+(m[1][j]*w[1][j])+(m[2][j]*w[2][j]);
	}
	}
	return q;
}

Matrix operator+(Matrix m, Matrix w){
	Matrix q;
	for (int i = 0; i < 3; i++){
	for (int j = 0; j < 3; j++){
	q[i][j] = m[i][j] + w[i][j];
	}
	}
	return q;
}

Matrix operator-(Matrix m, Matrix w){
	Matrix q;
	for (int i = 0; i < 3; i++){
	for (int j = 0; j < 3; j++){
	q[i][j] = m[i][j] - w[i][j];
	}
	}
	return q;
}



