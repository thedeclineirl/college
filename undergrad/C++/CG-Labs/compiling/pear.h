// Macros are important, this one for example
// says that only define one instance of the apple
// otherwise we will get errors when we reach the linking
// stage of compilation

#ifndef _PEAR_H
#define _PEAR_H

#include <stdio.h>
// Structs are like classes in C++ but far less complicated

typedef struct{
	int num;
}Pears;

void setPears(Pears pears, int num_pears);

int getPears(Pears pears);

void printPears(Pears pears);

#endif //_PEAR_H

