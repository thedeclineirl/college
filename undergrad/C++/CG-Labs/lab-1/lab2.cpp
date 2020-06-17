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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>
#include "vector.h"
#include "matrix.h"
#include "point.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	Vector v;
	v.x=0;v.y=3;v.z=6;
	float length = v.length();
	printf("|v| =  %f\n",length);
	
	Vector normV = v.norm();
	printf("normalised v = (%f,%f,%f)\n",normV[0],normV[1],normV[2]);
	cout<<"Normalised v = "<<normV<<endl;

	Point p; p.x=12;p.y=-7;p.z=1;
	Point q; q.x=1;q.y=0;q.z=2;
	Vector w = p-q;
	Vector cross = v.cross(w);
	cout<<"v cross w = "<<cross<<endl;

	Point r = p - v;
	cout<<"p - v = "<< r <<endl;
	
	Vector scalar = v*0.2;
	cout<<"scalar : v*0.2 = "<<scalar<<endl;
	
	Matrix m;
	m.coords[0][0] = 1;
	m.coords[0][1] = -3;
	m.coords[0][2] = 10;
	m.coords[1][0] = -1;
	m.coords[1][1] = 0;
	m.coords[1][2] = 3;
	m.coords[2][0] = 6;
	m.coords[2][1] = -9;
	m.coords[2][2] = 0;

	Vector vecMat = m*v;
	cout<<"m*v = "<<vecMat<<endl;
		
	Matrix s;
	s.coords[0][0] = -1;
	s.coords[0][1] = 0;
	s.coords[0][2] = 2;
	s.coords[1][0] = 0;
	s.coords[1][1] = 3;
	s.coords[1][2] = 8;
	s.coords[2][0] = -4;
	s.coords[2][1] = 9;
	s.coords[2][2] = 1;
	
	Matrix f = s*m;
  cout <<"s*m  = \n" << f << endl;

  return EXIT_SUCCESS;
}