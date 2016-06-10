#include <stdio.h>
#include <stdlib.h>
#include "utile.h"
#include "document.h"
#include "query.h"

boolean lire(FILE *fich,Document* p_document);

extern char* getNomFichier(char* collection);

void find(char* collection,Query query)
{
	FILE *fichier;
	fichier=fopen(getNomFichier(collection),"rb");
	if(fichier==NULL)
		printf("impossible d'ouvrir la collection\n");
	else
	{ 
		Document* p_document=Malloc(Document);
		p_document=NULL;
		while(lireDocument(p_document)==true)
		{
			if(query==NULL)
				afficherDocument(p_document);
		}
		fclose(fichier);
	}
}


