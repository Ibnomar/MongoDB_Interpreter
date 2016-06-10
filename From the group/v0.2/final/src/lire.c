#include <stdio.h>
#include <stdlib.h>
#include "utile.h"
#include "document.h"

static FILE *fichier;

static int debug=0;

static Valeur valeur;

boolean lireDocument(Document *p_document);
boolean lireChamp(Paire* p_paire);
boolean lireValeur();
boolean lireTableau(Tableau* p_tableau);

boolean lire(FILE *fich,Document* p_document)
{
	fichier=fich;
	return lireDocument(p_document);
}

boolean lireDocument(Document* p_document)
{
	int taille;
	if(fread(&taille,sizeof(int),1,fichier)!=1)
		return false;
	if(debug)
	{
		printf("--Lecture: le nombre de paires du document est %d\n",taille);
		printf("--Lecture: {\n");
	}
	int i;
	Paire paire;
	for (i=0;i<taille;i++)
	{
		if(lireChamp(&paire)==false)
			return false;
		if(lireValeur()==false)
			return false;
		paire.valeur=valeur;
		ajouterPaire(p_document,paire);
	}
	if(debug)
		printf("--Lecture: }\n");
	return true;
}	

boolean lireChamp(Paire* p_paire)
{
	int taille;
	if(fread(&taille,sizeof(int),1,fichier)!=1)
		return false;
	if(debug)
		printf("--Lecture: la taille du champ est %d\n",taille);
	p_paire->champ=(char*)malloc(sizeof(char)*taille+1);
	p_paire->champ[taille]='\0';
	if(fread(p_paire->champ,sizeof(char),taille,fichier)!=taille)
		return false;
	if(debug)
		printf("--Lecture: %s:",p_paire->champ);
	return true;
}

boolean lireValeur()
{
	Document* p_document=Malloc(Document);
	*p_document=NULL;
	Tableau* tableau=Malloc(Tableau);
	*p_tableau=NULL;
	if(fread(valeur.type,sizeof(Type_Valeur),1,fichier)!=1)
		return false;
	if(debug)
		printf("--Lecture: le type de la valeur est %d\n",valeur.type);
	switch(valeur.type) 
	{
		case T_ENTIER:
			if(fread(valeur.parametre.entier,sizeof(int),1,fichier)!=1)
				return false;
			if(debug)
				printf("--Lecture: %d\n",valeur.parametre.entier);
			break;
					
		case T_DECIMAL: 
			if(fread(&valeur.parametre.decimal,sizeof(double),1,fichier)!=1)
				return false;
			if(debug)
				printf("--Lecture: %lf\n",valeur.parametre.decimal);
			break;
				
		case T_CHAINE:
			if(fread(&taille,sizeof(int),1,fichier)!=1)
				return false;
			if(debug)
				printf("--Lecture: la taille de la chaine string %d\n",taille);
			valeur.parametre.chaine=(char*)malloc(sizeof(char)*taille+1);
			valeur.parametre.chaine[taille]='\0';
			if(fread(valeur.parametre.chaine,sizeof(char),taille,fichier)!=taille)
				return false;
			if(debug)
				printf("--Lecture: %s\n",valeur.parametre.chaine);
			break;
				
		case T_REGEXP:	
			if(fread(&taille,sizeof(int),1,fichier)!=1)
				return false;
			if(debug)
				printf("--Lecture: la taille de la chaine regexp %d\n",taille);
			valeur.parametre.chaine=(char*)malloc(sizeof(char)*taille+1);
			valeur.parametre.chaine[taille]='\0';
			if(fread(valeur.parametre.chaine,sizeof(char),taille,fichier)!=taille)
				return false;
			if(debug)
				printf("--Lecture: %s\n",valeur.parametre.chaine);
			break;
					
		case T_BOOL: 
			if(fread(&valeur.parametre.bool,sizeof(boolean),1,fichier)!=1)
				return false;
			if(debug)
			{
				if(valeur.parametre.bool==true)
					printf("--Lecture: true\n");
				else
					printf("--Lecture: false\n");
			}
			break;
				
		case T_DOC: 
			if(lireDocument(p_document)==false)
				return false;
			valeur.parametre.document=*p_document;
			break;
			
		case T_TAB: 
			if(lireTableau(p_tableau)==false)
				return false;
			valeur.parametre.tableau=*p_tableau;
			break;		
	}
	return true;	
}

boolean lireTableau(Tableau* p_tableau)
{
	int taille;
	if(fread(&taille,sizeof(int),1,fichier)!=1)
		return false;
	if(debug)
	{
		printf("--Lecture: le nombre des valeurs du tableau est %d\n",taille);
		printf("--Lecture: [");
	}
	int i;
	for (i=0;i<taille;i++)
	{
		if(lireValeur()==false)
			return false;
		ajouterValeur(p_tableau,valeur);
	}
	if(debug)
		printf("--Lecture: ]");
	return true;
}
