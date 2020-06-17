#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "texturePPM.h"
#include <string>
#define SWAPSHORT 1

texture *loadPPM(char *fileName)
	{ /* loadRaw() */
	/* open the file and make sure it exists */
	FILE *rawFile = fopen(fileName, "r");
	if (rawFile == NULL) return NULL;

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
	texture *newTexture = (texture *) malloc(sizeof(texture));
	
	/* read in the height and width */
	unsigned int sizes[2];
	int shortsRead =2;
	//fgets(buffer,1024,rawFile);
	//printf("%s",buffer);
	std::string str(buffer);//very strange bug directly sscanf on buffer corrupts rawFile
	sscanf(str.c_str(),"%d %d",&sizes[0],&sizes[1]);
	
	fgets(buffer,1024,rawFile);
	
	printf("%s",buffer);
	printf("%20s: Read %d bytes: sizes %d %d. ", fileName, shortsRead*sizeof(unsigned short), sizes[0], sizes[1]);

	/* check for stupid sizes */
	if (sizes[0] < 1) return NULL;
	if (sizes[0] > 16384) return NULL;
	if (sizes[1] < 1) return NULL;
	if (sizes[1] > 16384) return NULL;	
	
	/* store the sizes */
	newTexture->width = sizes[0];
	newTexture->height = sizes[1];
	
	/* allocate the memory for the data */
	newTexture->texBytes = (unsigned char *) malloc(sizeof(unsigned char) * sizes[0] * sizes[1] * 3);
	if (newTexture->texBytes == NULL) return NULL;
	
	int bytesRead = fread(newTexture->texBytes, sizeof(unsigned char), sizes[0] * sizes[1] * 3, rawFile);
	
	printf("Read %d bytes\n", bytesRead);
	
	return newTexture;
	} /* loadRaw() */
	

