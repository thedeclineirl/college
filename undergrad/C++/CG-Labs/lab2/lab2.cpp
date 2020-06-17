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
#include "raster.h"
#include "colour.h"

using namespace std;

int main(int argc, char *argv[]){
	
	cout << "initializing " << endl;
	/* Images can be represented as 2D arrays */
	Colour Image[IMAGEHEIGHT][IMAGEWIDTH];

	/* set up a rastering object and an image writer object */
	ImageIO writer;
	Raster raster;
	/* These points define a line segment, although we have learned that lines can be
	 * defined/described in several different ways, we'll stick with this representation 
	 */
	Point startPoint;
	startPoint.x=0; startPoint.y=1;	
	Point endPoint;
	endPoint.x=30; endPoint.y=50;
	
	/* call the explicit line function and write the resulting image stored in memory */
	raster.lineExplicit(startPoint, endPoint, Image);
	writer.writePPM("lineExplicit.pgm", Image);

	cout << "Done........." << endl;

	return EXIT_SUCCESS;
}
