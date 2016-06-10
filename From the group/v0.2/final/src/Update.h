#ifndef UPDATE_H
#define UPDATE_H

#include "document.h"

typedef enum {UP_DOC , UP_MODIF}Type_Update;

typedef enum {inc , mul , rename , set , unset , max , min}Type_UOp;



typedef struct {

	Type_UOp type;
	Liste_Paire* lstpaire;

}Modif;

typedef struct Liste_Modif{

	Modif modif;
	struct Liste_Modif* suivant;

	}Liste_Modif;


typedef struct {
	Type_Update type;
	union {
		Document doc;
		Liste_Modif* lstmodif;
		}parametre;
	}Update;


