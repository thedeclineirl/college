#include <stdio.h>
#include <stdlib.h>



/* Definition of what an Image should be */
typedef struct
    { /* image */
    int height, width, max;
    int **imageData;
	
    } /* image */
    Image; 


/* Define two global Images, on contains the input Image the other contains the output */
Image *inImage = NULL, *outImage = NULL; 


/* Filters to apply to your images */
void adjustBrightness(int brightness);
void threshold(int lowerLimit, int upperLimit);
void meanFilter(int kernelSize);
void medianFilter(int kernelSize);

/* Image Input and Ouput Functions: we are only Interested in PGM's */
void   writePGM(char *outfile);
Image* loadPGM(char *infile);

/* Initialise Image meta data and memory block */
Image*  initImage(int width, int height, int max);

/* stats operators */
int Median(int *array, int size);

/* compare operators */
int compare (const void * a, const void * b);

/*-------------*/
/*   M A I N   */
/*-------------*/
int main () {

	inImage  = loadPGM("image1.pgm");
	outImage = initImage(inImage->width, inImage->height, inImage->max);
	
// 	adjustBrightness(100);
// 	writePGM("result_brightness.pgm");
// 
// 	threshold(130,179);
// 	writePGM("result_threshold.pgm");
	
	//removing noise
	inImage  = loadPGM("image1.pgm");
 	//meanFilter(1);
 	//writePGM("result_mean.pgm");
 
 	medianFilter(3);
 	writePGM("result_median.pgm");
// 
// 	medianFilter(20);
// 	writePGM("result_median_20.pgm");

	return 0;
}


/*----------------------------*/
/*      ADJUST BRIGHTNESS     */
/*----------------------------*/
void adjustBrightness(int brightness){
	int height = inImage->height;
	int width = inImage->width;
	
	for(int h=0; h<height; h++)	//loop through the height of the image
	{
		for(int w=0; w<width; w++) //loop through the width of the image
		{    
			
			int thisPixel = inImage->imageData[h][w] + brightness;
			if(thisPixel>255){
				thisPixel=255;
			}
			if(thisPixel<0){
				thisPixel=0;
			}
			outImage->imageData[h][w] = thisPixel;	
		}
	}
}

/*------------------------*/
/*        THRESHOLD       */
/*------------------------*/
void threshold(int lowerLimit, int upperLimit){

	int height = inImage->height;
	int width = inImage->width;
	
	for(int h=0; h<height; h++)	//loop through the height of the image
	{
		for(int w=0; w<width; w++) //loop through the width of the image
		{    
			if(inImage->imageData[h][w]>lowerLimit && inImage->imageData[h][w]<upperLimit) 
			{
			int thisPixel = 255;
			outImage->imageData[h][w] = thisPixel;
			}
			else
			{
			int thisPixel = 0;
			outImage->imageData[h][w] = thisPixel;
			}		
		}
	}

}


/*------------------------*/
/*       MEAN FILTER      */
/*------------------------*/
void meanFilter(int kernelSize){

	int height = inImage->height;
	int width = inImage->width;
	int limit = kernelSize + kernelSize + 1;
		
	for(int h=kernelSize; h<height-kernelSize; h++)	//loop through the height of the image
	{
		for(int w=kernelSize; w<width-kernelSize; w++) //loop through the width of the image
		{
		int kernelSum=0;
		int count = 0;
			for(int h2 = h-kernelSize; h2<= h+kernelSize; h2++)	//loop through the height of the kernel
			{
				for(int  w2 = w-kernelSize; w2<= w+kernelSize; w2++) //loop through the width of the kernel
				{	kernelSum += inImage->imageData[h2][w2];
					count++;
					}		
			}
		//setting the pixel
		
		outImage->imageData[h][w] = (int)((float)kernelSum/(float)count);
		}
	}

}



/*------------------------*/
/*      MEDIAN FILTER     */
/*------------------------*/
void medianFilter(int kernelSize){

	int height = inImage->height;
	int width = inImage->width;
	int limit = kernelSize + kernelSize + 1;
		
	for(int h=kernelSize; h<height-kernelSize; h++)	//loop through the height of the image
	{
		for(int w=kernelSize; w<width-kernelSize; w++) //loop through the width of the image
		{
		int kernelSum=0;
		int min = 0;
		int max = 0;
			for(int h2 = h-kernelSize; h2<= h+kernelSize; h2++)	//loop through the height of the kernel
			{
				for(int  w2 = w-kernelSize; w2<= w+kernelSize; w2++) //loop through the width of the kernel
				{	int thisPoint = inImage->imageData[h2][w2];
					if(thisPoint>max)
					{max=thisPoint;}
					if(thisPoint<min)
					{min=thisPoint;}
					}		
			}
		//setting the pixel
		
		outImage->imageData[h][w] = (max-min)/2;
		}
	}
}


/*------------------------*/
/*       WRITE PGM        */
/*------------------------*/
void writePGM(char *outfile){

	int j, k;

	FILE *fout = fopen(outfile, "w");

	fprintf(fout, "P2\n%d %d\n%d\n",outImage->width, outImage->height, outImage->max);

	for( j = 0; j < outImage->height; j++){
		for( k = 0; k < outImage->width; k++){
		
			fprintf(fout, "%d ", outImage->imageData[j][k]);
		}
		fprintf(fout, "\n");
	}
	
	fclose(fout);
}


/*------------------------*/
/*        LOAD PGM        */
/*------------------------*/
Image* loadPGM(char *infile){

	int i, j, temp=0;
	int width, height, max;
	Image* newImage = NULL;

	FILE *fin = fopen(infile, "r");

	if(fin == NULL){
		printf("File doesn't exist\n");
		getchar();
		exit(1);
	}
	else{
		fscanf(fin, "P2\n%d %d\n%d\n", &width, &height, &max);
		
		newImage = initImage(width, height, max);

		printf("%s : Width: %d  Height: %d  Max: %d\n", 
			infile, newImage->width, newImage->height, newImage->max);

		/* scan in the image and store it in the inImage struct */
		for(i = 0; i < height; i++){
			for(j = 0; j < width; j++){
				fscanf(fin, "%d", &temp);
				newImage->imageData[i][j] = temp;
			}
		}

	}

	fclose(fin); /* Done scanning finished return the struct*/
	
	return newImage;
}

/* Initialise Image meta data and memory block */
Image* initImage(int width, int height, int max){

	int *block1 = NULL, **block2 = NULL;
	int i, j;

	Image *image = (Image *) malloc(sizeof(Image)); /* allocate memory for struct */
	image->width  = width;
	image->height = height;
	image->max    = max;
	
	block1 = (int*)malloc(width*height*sizeof(int)); /* allocate mem blks */
	block2 = (int**)malloc(height*sizeof(int*));
	image->imageData = &(block2[0]); /* assign ptr to the struct one */
		
	/* Connect up the blks */ 
	for(i = 0; i < height; i++){ 
		image->imageData[i] = block1 + (i*width); 
	}

	/* Initialize the image to be black  */
	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
			image->imageData[i][j] = 0;

	return image;
}

int Median(int *array, int size)
{ /* Median() */

	/* code here  */

} /* Median() */

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
