#include "banana.h"

void setBananas(Bananas bananas, int num_bananas){
	bananas.num = num_bananas;	
}

int getBananas(Bananas bananas){
	return bananas.num;
}

void printBananas(Bananas bananas){
	printf("Number of bananas : %d", bananas.num);
}

