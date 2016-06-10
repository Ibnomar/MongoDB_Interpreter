#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <time.h>
#include "utile.h"

typedef struct Liste_Paire* Document;

typedef struct Liste_Valeur* Tableau;

typedef enum
{
	T_ENTIER  , T_DECIMAL , T_CHAINE , T_REGEXP , T_NULL , T_BOOL , T_MINKEY , T_MAXKEY , T_DOC , T_TAB,
	T_OBJECT_ID,   T_LONG , T_BIN_DATA, T_DATE ,T_TIMESTAMP
}Type_Valeur;

typedef struct Liste_Byte Liste_Byte;

typedef struct Liste_Byte
{
	unsigned char byte;
	Liste_Byte* suivant;
}Liste_Byte;

typedef struct
{
	unsigned char type;
	Liste_Byte* liste_byte;
}Bin_Data;

typedef struct
{
	unsigned int t;
	unsigned int i;
}Timestamp;

typedef struct Valeur
{
	Type_Valeur type;
	union
	{
		int entier;
		double decimal;
		char* chaine;
		boolean bool;
		Document document;
		Tableau tableau;
		unsigned char objectid[12];
		long nlong;
		Bin_Data bindata;
		struct tm date;
		Timestamp timestamp;
	}parametre;

}Valeur;

typedef struct Paire
{
	char* champ;
	Valeur valeur;
}Paire;

typedef struct Liste_Paire
{
	Paire paire;
	struct Liste_Paire* suivant;
}Liste_Paire;

typedef struct Liste_Valeur
{
	Valeur valeur;
	struct Liste_Valeur* suivant;
}Liste_Valeur;

int nbrValeur(Tableau tableau);
int nbrPaire(Document doc);

#endif
