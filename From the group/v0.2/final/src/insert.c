#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utile.h"
#include "document.h"

void insertDocument(Document doc);
void insertChamp(char *champ);
void insertValeur(Valeur valeur);
void insertTableau(Tableau table);

extern char* getNomFichier(char* collection);

static FILE *fichier;
static int debug=0;

void insert(char* collection,Document doc)
{
	fichier=fopen(getNomFichier(collection),"ab");
	if(fichier==NULL)
		printf("impossible d'ouvrir la collection\n");
	else
	{
		insertDocument(doc);
		fclose(fichier);
	}
}

void insertDocument(Document doc)
{
	int nbrp=nbrPaire(doc);
	if(debug)
		printf("le nombre de paires du document est %d\n",nbrp);
	fwrite(&nbrp,sizeof(int),1,fichier);
	Liste_Paire* noeud=doc;
	while(noeud!=NULL)
	{
		insertChamp(noeud->paire.champ);
		insertValeur(noeud->paire.valeur);
		noeud=noeud->suivant;
	}

}

void insertChamp(char* champ)
{
	int taille=strlen(champ);
	if(debug)
		printf("la taille du champ est %d\n",taille);
	fwrite(&taille,sizeof(int),1,fichier);
	if(debug)
		printf("le champ à insérer est %s\n",champ);
	fwrite(champ,sizeof(char),strlen(champ),fichier);
}


void insertValeur(Valeur valeur)
{
	if(debug)
		printf("le type de la valeur est %d\n",valeur.type);
	fwrite(&(valeur.type),sizeof(Type_Valeur),1,fichier);
	int taille;

	switch(valeur.type)
	{
		case T_ENTIER :
			if(debug)
				printf("l'entier à insérer est %d\n",valeur.parametre.entier);
			fwrite(&(valeur.parametre.entier),sizeof(int),1,fichier);
			break;

		case T_DECIMAL:
			if(debug)
				printf("le décimal à insérer est %lf\n",valeur.parametre.decimal);
			fwrite(&(valeur.parametre.decimal),sizeof(double),1,fichier);
			break;

		case T_CHAINE:
			taille=strlen(valeur.parametre.chaine);
			if(debug)
				printf("la taille de la chaine est %d\n",taille);
			fwrite(&taille,sizeof(int),1,fichier);
			if(debug)
				printf("la chaine à insérer est %s\n",valeur.parametre.chaine);
			fwrite(valeur.parametre.chaine,sizeof(char),strlen(valeur.parametre.chaine),fichier);
			break;

		case T_REGEXP:
			taille=strlen(valeur.parametre.chaine);
			if(debug)
				printf("la taille de la regexp est %d\n",taille);
			fwrite(&taille,sizeof(int),1,fichier);
			if(debug)
				printf("la regexp à insérer est %s\n",valeur.parametre.chaine);
			fwrite(valeur.parametre.chaine,sizeof(char),strlen(valeur.parametre.chaine),fichier);
			break;

		case T_BOOL:
			if(debug)
				printf("le boolean à insérer est %d\n",valeur.parametre.bool);
			fwrite(&(valeur.parametre.bool),sizeof(boolean),1,fichier);
			break;

		case T_DOC:
			insertDocument(valeur.parametre.document);
			break;

		case T_TAB:
			insertTableau(valeur.parametre.tableau);
			break;
	}
}


void insertTableau(Tableau table)
{
	int nbrt=nbrValeur(table);
	if(debug)
		printf("le nombre de valeurs du tableau est %d\n",nbrt);
	fwrite(&nbrt,sizeof(int),1,fichier);
	Liste_Valeur* noeud=table;
	while(noeud!=NULL)
	{
		insertValeur(noeud->valeur);
		noeud=noeud->suivant;
	}
}
