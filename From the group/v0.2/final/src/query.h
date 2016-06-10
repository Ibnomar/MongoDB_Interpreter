#ifndef QUERY_H
#define QUERY_H

#include "document.h" 

typedef enum
{
	EXP_SIMPLE,EXP_COMPLEXE 
}Type_Exp;

typedef enum 
{
	OP_OR,OP_AND 
}Type_LOp;

typedef enum 
{
	OP_GT,OP_LT,OP_GTE,OP_LTE,OP_EQ,OP_NE,OP_IN,OP_NIN
}Type_Op;

typedef struct Expression* Query;

struct Expression;

typedef struct Liste_Exp
{
	struct Expression* exp;
	struct Liste_Exp* suivant;
}Liste_Exp;

typedef struct 
{	
	char* champ;
	Type_Op op;
	union
	{
		Valeur valeur;
		Tableau tableau;
	}critere;
}Expression_Simple;

typedef struct 
{	
	Type_LOp lop;
	Liste_Exp* liste_exp;
}Expression_Complexe;
 
typedef struct Expression
{
	Type_Exp type_exp; 
	union
  	{
  		Expression_Simple expsim;
  		Expression_Complexe expcom;
	}noeud;
}Expression; 

#endif
