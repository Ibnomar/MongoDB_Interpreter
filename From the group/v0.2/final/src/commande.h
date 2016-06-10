#ifndef COMMANDE_H
#define COMMANDE_H

#include "document.h"
#include "query.h"

typedef enum 
{
	C_INSERT,C_FIND,C_DROP,C_RENAMECOL,C_GETCOLNAMES
}Type_Commande;

typedef struct Commande 
{
	Type_Commande type;
	char* collection;
	union 
	{
		struct
		{
			Document document;
		}p_insert;
		struct
		{
			Query query;
		}p_find;
		struct
		{
			char* nom;
		}p_renamecol;
	}parametre;
}Commande;

void executer(Commande commande);

#endif



