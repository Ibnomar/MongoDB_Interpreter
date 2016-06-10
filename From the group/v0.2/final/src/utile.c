#include <stdlib.h>
#include <string.h>

void copier_chaine(char **destination,char* origine)
{
	//free(*destination);
	*destination=(char*)malloc(sizeof(char)*(strlen(origine)+1));
	strcpy(*destination,origine);
}

void concatener_chaine(char **destination,char* origine)
{
	int taille;
	taille=strlen(*destination)+strlen(origine)+1;
	*destination=(char*)realloc(*destination,taille);
	strcat(*destination,origine);
}
