#ifndef ANALYSEUR_ZZ_H
#define ANALYSEUR_ZZ_H


#define declMax 100
#define instMax 100
#define erreurMax 100

  

typedef enum {true=1,false=0} boolean;

typedef enum{INUMBER,DNUMBER,INT,BOOLEAN,DOUBLE,PVERG,IDF,VRAI,FAUX,BEG_IN,PVIRG,MULT,EGALE,END,ENDIF,ELSE,IF,PAR_FERM,PAR_OUVR,EGALEEGALE,THEN,PRINT,FOR,TO,DO,ENDFOR,MOINS,PLUS,PROD,DIV} typetoken;

typedef enum {Int,Bool} TYPE;

typedef enum {entier,trueOrFalse,inumber,memeType} monType;

typedef struct 
	{
	char *nomVar;
	int nombreDecl;
	TYPE typeVar;
	boolean initOrNot;
	char *valInit;
	int line;
	} varvalueType;
	
	
	
typedef struct
	{
	char *nomVar;
	int line;
	}varvalueInst;
	
	
	
typedef enum 
	{
	dejaDeclaree,
	malInitialisee,
	incompatibleAffectation,
	incompatibleComparaison,
	nonDeclaree,
	incompatibleOperation
	} SemanticErrorType;
	
typedef struct 
	{
	int lineErreur;
	char *nomSourceErreur;
	SemanticErrorType typeErreur;
	} smError;



smError tabErreur[declMax];             //tableau d'erreur 
varvalueType tabDeclarations[declMax];  //taleau de declarations
varvalueInst tabInstructions[instMax];  //tableau d'instructions
typetoken token;


#endif


	
