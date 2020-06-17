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
/**
  * note this code uses low level io code as its more efficient in writing
  * formated strings.
*/
#include "imageio.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
ImageIO::ImageIO(){
}

void ImageIO::writePPM(std::string fName, Colour pixelMatrix[IMAGEWIDTH][IMAGEHEIGHT]){
	FILE* output =(FILE*)fopen(fName.c_str(),"w");//open output Stream

	if(!output){
		printf("Error opening '%s' for writing\n",fName.c_str());
		exit(EXIT_FAILURE);
	}

	fprintf(output,"P3\n");//specify file type Image PLAIN
	fprintf(output,"%d %d\n",IMAGEWIDTH,IMAGEHEIGHT); //specify width and height
	fprintf(output,"255\n");//colour depth standard RGB 256
	
	// grab each of the colour components and store them locally converting to integers
	int red, green, blue;
	//begin rastering
	for(int i=0;i<IMAGEHEIGHT;i++){
		for(int j=0;j<IMAGEWIDTH;j++){

			red   = (int)(pixelMatrix[i][j].colour[0]*255);
			green = (int)(pixelMatrix[i][j].colour[1]*255);
			blue  = (int)(pixelMatrix[i][j].colour[2]*255);

			fprintf(output,"%d %d %d\t",red, green, blue);//write pixel triplet i.e. RGB
		}
		fprintf(output,"\n");//End raster line
	}
	//finished rastering

	fclose(output);//close Stream
}

void ImageIO::writePGM(std::string fName, Colour pixelMatrix[IMAGEWIDTH][IMAGEHEIGHT]){
	FILE* output =(FILE*)fopen(fName.c_str(),"w");//open output Stream

	if(!output){
		printf("Error opening '%s' for writing\n",fName.c_str());
		exit(EXIT_FAILURE);
	}

	fprintf(output,"P2\n");//specify file type Image, GrayScale
	fprintf(output,"%d %d\n",IMAGEWIDTH,IMAGEHEIGHT); //specify width and height
	fprintf(output,"255\n");//colour depth standard 256
	
	//begin rastering
	for(int i=0;i<IMAGEHEIGHT;i++){
		for(int j=0;j<IMAGEWIDTH;j++){
			fprintf(output,"%d\t", (int)(pixelMatrix[i][j].colour[0]*255));//write pixel i.e. GRAYSCALE value
		}
		fprintf(output,"\n");//End raster line
	}
	//finished rastering

	fclose(output);//close Stream
}

void ImageIO::readPPMRaw(std::string fName,Image& image){
	FILE *rawFile = fopen(fName.c_str(), "r");
	image.setImageBytes(NULL);
	if (rawFile == NULL) return ;

	//skip to width and height assumes gimp standard
	char buffer[1024];
	
	fgets(buffer,1024,rawFile);
	printf("%s",buffer);

	
	fgets(buffer,1024,rawFile);
	printf("%s",buffer);
	while(buffer[0]=='#'){
		fgets(buffer,1024,rawFile);
		printf("%s",buffer);
	}
	/* generate a texture structure */
	//texture *newTexture = (texture *) malloc(sizeof(texture));
	
	/* read in the height and width */
	unsigned short sizes[2];
	int shortsRead =2;
	//fgets(buffer,1024,rawFile);
	//printf("%s",buffer);
	stringstream ss(stringstream::in|stringstream::out);
	ss<<buffer;
	ss>>sizes[0];
	ss>>sizes[1];
	
	fgets(buffer,1024,rawFile);
	printf("%s\n",buffer);
	printf("%s: Read %d bytes: sizes %d %d. \n", fName.c_str(), shortsRead*sizeof(unsigned short), sizes[0], sizes[1]);

	/* check for stupid sizes */
	if (sizes[0] < 1) {
		image.setImageBytes(NULL);
		return ;
	}
	if (sizes[0] > 16384){
		image.setImageBytes(NULL);
		return ;
	}
	if (sizes[1] < 1){
		image.setImageBytes(NULL);
		return ;
	}
	if (sizes[1] > 16384) {
		image.setImageBytes(NULL);
		return ;
	}
	
	/* store the sizes */
	image.setWidth(sizes[0]);
	image.setHeight(sizes[1]);
	
	/* allocate the memory for the data */
	image.setImageBytes((unsigned char *) malloc(sizeof(unsigned char) * sizes[0] * sizes[1] * 3));
	if (image.getImageBytes() == NULL){
		image.setImageBytes(NULL);
		return ;
	}
	
	int bytesRead = fread(image.getImageBytes(), sizeof(unsigned char), sizes[0] * sizes[1] * 3, rawFile);
	
	printf("Read %d bytes\n", bytesRead);
	fclose(rawFile);
	
}

void ImageIO::readPGMRaw(std::string fName,Image& image){
	FILE *rawFile = fopen(fName.c_str(), "r");
	image.setImageBytes(NULL);
	if (rawFile == NULL) return ;

	//skip to width and height assumes gimp standard
	char buffer[1024];
	
	fgets(buffer,1024,rawFile);
	printf("%s",buffer);

	
	fgets(buffer,1024,rawFile);
	printf("%s",buffer);
	while(buffer[0]=='#'){
		fgets(buffer,1024,rawFile);
		printf("%s",buffer);
	}
	/* generate a texture structure */
	//texture *newTexture = (texture *) malloc(sizeof(texture));
	
	/* read in the height and width */
	unsigned short sizes[2];
	int shortsRead =2;
	//fgets(buffer,1024,rawFile);
	//printf("%s",buffer);
	stringstream ss(stringstream::in|stringstream::out);
	ss<<buffer;
	ss>>sizes[0];
	ss>>sizes[1];
	
	fgets(buffer,1024,rawFile);
	printf("%s",buffer);
	printf("%20s: Read %d bytes: sizes %d %d. ", fName.c_str(), shortsRead*sizeof(unsigned short), sizes[0], sizes[1]);

	/* check for stupid sizes */
	if (sizes[0] < 1){
		image.setImageBytes(NULL);
		return ;
	}
	if (sizes[0] > 16384) {
		image.setImageBytes(NULL);
		return ;
	}
	if (sizes[1] < 1) {
		image.setImageBytes(NULL);
		return ;
	}
	if (sizes[1] > 16384){
		image.setImageBytes(NULL);
		return ;
	}
	
	/* store the sizes */
	image.setWidth(sizes[0]);
	image.setHeight(sizes[1]);
	
	/* allocate the memory for the data */
	image.setImageBytes((unsigned char *) malloc(sizeof(unsigned char) * sizes[0] * sizes[1] * 1));
	if (image.getImageBytes() == NULL){
		image.setImageBytes(NULL);
		return ;
	}
	
	int bytesRead = fread(image.getImageBytes(), sizeof(unsigned char), sizes[0] * sizes[1] * 1, rawFile);
	
	printf("Read %d bytes\n", bytesRead);
	fclose(rawFile);
	
}

