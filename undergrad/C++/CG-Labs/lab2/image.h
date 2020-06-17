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

#ifndef IMAGE_H
#define IMAGE_H

class Image{
	public:
		Image();
		~Image();
		int getHeight(){return m_iHeight;};
		void setHeight(int height){m_iHeight=height;};
		
		int getWidth(){return m_iWidth;};
		void setWidth(int width){m_iWidth=width;};
		
		unsigned int getImageName(){return m_imageName;};
		void setImageName(unsigned int imageName){m_imageName=imageName;};

		unsigned char* getImageBytes(){return m_imageBytes;};
		void setImageBytes(unsigned char* imageBytes){m_imageBytes=imageBytes;};
	private:
		int m_iHeight;
		int m_iWidth;
		unsigned int m_imageName;
		unsigned char* m_imageBytes;

};
#endif

