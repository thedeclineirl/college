#include "pear.h"

void setPears(Pears pears, int num_pears){
	pears.num = num_pears;	
}

int getPears(Pears pears){
	return pears.num;
}

void printPears(Pears pears){
	printf("Number of pears : %d", pears.num);
}
