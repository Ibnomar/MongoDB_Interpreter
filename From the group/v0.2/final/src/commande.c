#include "commande.h"
#include "document.h"
#include "query.h"


extern void insert(char* collection,Document doc);
extern void find(char* collection,Query query);
extern void drop(char* collection);
extern void renamecol(char* collection,char* nom);
extern void getcolnames();

void executer(Commande commande)
{
	switch(commande.type)
	{
		case C_INSERT:
			insert(commande.collection,commande.parametre.p_insert.document);
			break;
		case C_FIND:
			find(commande.collection,commande.parametre.p_find.query);
			break;
		case C_DROP:
			drop(commande.collection);
			break;
		case C_RENAMECOL:
			renamecol(commande.collection,commande.parametre.p_renamecol.nom);
			break;
		case C_GETCOLNAMES:
			getcolnames();
			break;
	}	
}
