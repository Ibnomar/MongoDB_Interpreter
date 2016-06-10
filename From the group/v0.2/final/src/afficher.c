#include <stdlib.h>
#include <stdio.h>
#include "document.h"

static int nbrTab=0;

void afficherDocument(Document doc);
void afficherValeur(Valeur valeur);
void afficherTableau(Tableau table);

void afficherTab()
{
	int i;
	printf("\n");
	for(i=0;i<nbrTab;i++)
		printf("\t");
}

void afficherDocument(Document doc) 
{
	Liste_Paire* noeud=doc;
	printf("{");
	nbrTab++;
	while(noeud!=NULL) 
	{
		afficherTab();
		printf("%s:",noeud->paire.champ);	
		afficherValeur(noeud->paire.valeur);
		noeud=noeud->suivant;
		if(noeud!=NULL)
			printf(",");
	}
	nbrTab--;
	afficherTab();
	printf("}");
}



void afficherValeur(Valeur valeur) 
{
	switch(valeur.type) 
	{
		case T_ENTIER :
			printf("%d",valeur.parametre.entier);
			break;
	
		case T_DECIMAL:
			printf("%lf",valeur.parametre.decimal);
			break;
	
		case T_CHAINE:  
			printf("%s",valeur.parametre.chaine);
			break;
	
		case T_REGEXP:  
			printf("%s\n",valeur.parametre.chaine);
			break;
	
		case T_BOOL:
			if(valeur.parametre.bool==true)	
				printf("true");
			else
				printf("false");
			break;
	
		case T_DOC: 
			afficherDoument(valeur.parametre.document);
			break;
	
		case T_TAB: 
			afficherTableau(valeur.parametre.tableau);
			break;
	}
}


void afficherTableau(Tableau table)
{
	Liste_Valeur* noeud=table;
	printf("[");
	nbrTab++;
	while(noeud!=NULL) 
	{
		afficherValeur(noeud->valeur);
		noeud=noeud->suivant;
		if(noeud!=NULL)
			printf(",");
	}
	nbrTab--;
	afficherTab();
	printf("]");
}
