// Macros are important, this one for example
// says that only define one instance of the apple
// otherwise we will get errors when we reach the linking
// stage of compilation

#ifndef _BANANA_H
#define _BANANA_H

#include <stdio.h>
// Structs are like classes in C++ but far less complicated

typedef struct{
	int num;
}Bananas;

void setBananas(Bananas bananas, int num_bananas);

int getBananas(Bananas bananas);

void printBananas(Bananas bananas);

#endif //_BANANA_H

