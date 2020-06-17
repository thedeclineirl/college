/***************************************************************************
 *   Copyright (C) 2006 by John Meade   *
 *   john.meade[no spam]ucd[dot]ie   *
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

#ifndef IMAGEWRITE_H
#define IMAGEWRITE_H

#ifndef IMAGEWIDTH
#define IMAGEWIDTH 512 // The width of the image
#endif

#ifndef IMAGEHEIGHT
#define IMAGEHEIGHT 512 // The height of the image
#endif
#include <string>
#include "image.h"
#include "colour.h"

using namespace std;

class ImageIO{
	public:
		ImageIO();
		~ImageIO(){};
		/**
		* Generates a PPM format file.
		* The function writePPM takes as its arguement the file name, fName,
		* the image is to written to and the 3D unsigned char array containing
		* the image data
		*/
		void writePPM(string fName, Colour pixelMatix[IMAGEWIDTH][IMAGEHEIGHT]);
		
		/**
		* Generates a PGM format file.
		* The function writePGM takes as its arguement the file name, fName,
		* the image is to written to and the 3D unsigned char array containing
		* the image data
		*/
		void writePGM(string fName, Colour pixelMatix[IMAGEWIDTH][IMAGEHEIGHT]);
		/**
		 * Reads the ppm image file into the Image structure provided
		 */
		void readPPMRaw(string fName,Image& image);
		
		/**
		 * Reads the pgm image file into the Image structure provided
		 */
		void readPGMRaw(string fName,Image& image);
};
#endif


