#include <stdlib.h>
#include "utile.h"
#include "document.h"

void ajouterPaire(Document* p_document,Paire paire)
{
	//Création du nouveau noeud:
	Liste_Paire* p_noeud=Malloc(Liste_Paire);
	p_noeud->paire=paire;
	p_noeud->suivant=NULL;
	
	if(*p_document==NULL)//Si le document est vide
	{
		*p_document=p_noeud;
	}else
	{
		Liste_Paire* p_dernier_noeud;
		for(p_dernier_noeud=*p_document;p_dernier_noeud->suivant!=NULL;p_dernier_noeud=p_dernier_noeud->suivant)
		{}
		p_dernier_noeud->suivant=p_noeud;
	}
}

void ajouterValeur(Tableau* p_tableau,Valeur valeur)
{
	//Création du nouveau noeud:
	Liste_Valeur* p_noeud=Malloc(Liste_Valeur);
	p_noeud->valeur=valeur;
	p_noeud->suivant=NULL;
	
	if(*p_tableau==NULL)//Si le tableau est vide
	{
		*p_tableau=p_noeud;
	}else
	{
		Liste_Valeur* p_dernier_noeud;
		for(p_dernier_noeud=*p_tableau;p_dernier_noeud->suivant!=NULL;p_dernier_noeud=p_dernier_noeud->suivant)
		{}
		p_dernier_noeud->suivant=p_noeud;
	}
}

int nbrPaire(Document doc)
{
	int nbr=0;
	while(doc!=NULL)
	{
		nbr++;
		doc=doc->suivant;
	} 
	return nbr;
}

int nbrValeur(Tableau table)
{
	int nbr=0;
	while(table!=NULL)
	{
		nbr++;
		table=table->suivant;
	} 
	return nbr;
}
