// Macros are important, this one for example
// says that only define one instance of the apple
// otherwise we will get errors when we reach the linking
// stage of compilation

#ifndef _APPLE_H
#define _APPLE_H

#include <stdio.h>
// Structs are like classes in C++ but far less complicated

typedef struct{
	int num;
}Apples;

void setApples(Apples apples, int num_apples);

int getApples(Apples apples);

void printApples(Apples apples);

#endif //_APPLE_H
