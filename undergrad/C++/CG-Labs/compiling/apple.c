#include "apple.h"

void setApples(Apples apples, int num_apples){
	apples.num = num_apples;	
}

int getApples(Apples apples){
	return apples.num;
}

void printApples(Apples apples){
	printf("Number of apples : %d", apples.num);
}

