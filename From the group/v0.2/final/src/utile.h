#ifndef UTILE_H
#define UTILE_H
#include <stdlib.h>
typedef enum
{
	false=0,true=1
}boolean;

void copier_chaine(char **destination,char* origine);
void concatener_chaine(char **destination,char* origine);

#define Malloc(type) (type*)malloc(sizeof(type))
#endif
