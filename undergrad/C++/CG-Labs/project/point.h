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
#ifndef POINT_H
#define POINT_H
#include <iostream>
using namespace std;
/**
	@author John Meade <john.meade@ucd.ie>
*/
class Point{ // class Point
	public: // makes life easier
		float x, y, z; // the coordinates
		Point(); // default constructor
		Point(float X, float Y, float Z); // initializing constructor
		~Point();
		float &operator[](int i);
		Point &operator= (Point q);
}; // class Point

ostream &operator<< (ostream & ostr, Point p);
// C++ print routine

#endif
