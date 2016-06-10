#include <stdio.h>
#include "utile.h"
#include "tokens.h"
#include "commande.h"
#include "document.h"

//Les règles de la grammaire:
boolean _PROG();
boolean _LIST_COM();
boolean _COM();
boolean _COM_DB();
boolean _COM_COL();
boolean _PARAM_INSERT(Document* p_document);

boolean _DOC(Document* p_document);
boolean _LIST_PAIR(Document* p_document);
boolean _LIST_PAIR_AUX(Document* p_document);
boolean _LIST_PAIR_AUX_AUX(Document* p_document);
boolean _PAIR(Paire *paire);
boolean _VALEUR();
boolean _TAB(Tableau* p_tableau);
boolean _LIST_VAL(Tableau* p_tableau);
boolean _LIST_VAL_AUX(Tableau* p_tableau);
boolean _LIST_VAL_AUX_AUX(Tableau* p_tableau);

boolean _FIND_AUX();
boolean _PARAM_RENAME();

boolean _QUERY(Query* p_query);
boolean _EXP(Expression** pp_expression);
boolean _EXP_AUX(Expression** pp_expression);
boolean _TAB_EXP(Liste_Exp** pp_liste_exp);
boolean _LIST_EXP(Liste_Exp** pp_liste_exp);
boolean _LIST_EXP_AUX(Liste_Exp** pp_liste_exp);
boolean _LIST_EXP_AUX_AUX(Liste_Exp** pp_liste_exp);
boolean _EXP_ELEM();
boolean _EXP_ELEM_AUX();
boolean _OP_VAL();
boolean _OP_TAB();

//La dernière commande qu'on a lue:
static Commande commande;
//La dernière valeur qu'on a lue:
static Valeur valeur;


static typetoken token;
static boolean follow_token=false;


extern int yylex();
extern char* yytext;

typetoken _lire_token()
{
	if(follow_token==true)
	{
		follow_token=false;
		return token;
	}
	else
	{
		return (typetoken) yylex();
	}
}

char* _get_token()
{
	return yytext;
}

int main(int argc, char * argv)
{
	token = _lire_token();
	if (_PROG() == true) 
	{
		printf("\npas d'erreurs lexicales\n");
		printf("\npas d'erreurs syntaxiques\n");
	}
	else 
	{
		if(token==-1)
			printf("\nerreur lexicale\n");
		else
			printf("\nerreur syntaxique\n");
	}
	
	return 0;
}

// PROG : LIST_COM
boolean _PROG()
{
	boolean result;
	if(_LIST_COM())
	{
		result=true;
	}else
	{
		result=false;
	}
	return result;
}

// LIST_COM : COM ';' LIST_COM | EPSILON
boolean _LIST_COM()
{
	boolean result;
	if(token==0)
	{	
		result=true;
	}else if(_COM())
	{
		token=_lire_token();
		if(token==PVIRG)
		{
			executer(commande);
			token=_lire_token();
			if(_LIST_COM())
			{
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result;
}

// COM : 'db' '.' COM_DB
boolean _COM()
{
	boolean result;
     	if(token==DB)
	{
		token=_lire_token();
		if(token==POINT)
		{
			token=_lire_token();
			if(_COM_DB())
			{
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else
	{
		result = false;
	}
	return result;
}


// COM_DB :  idf '.' COM_COL | 'getCollectionNames' '(' ')'
boolean _COM_DB()
{
	boolean result;
	if(token==IDF)
	{
		copier_chaine(&(commande.collection),_get_token());
		token=_lire_token();
		if(token==POINT)
		{
			token=_lire_token();
			if(_COM_COL())
			{
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else if(token==GETCOLNAMES)
	{
		commande.type=C_GETCOLNAMES;
		token=_lire_token();
		if(token==POPEN)
		{
			token=_lire_token();
			if(token==PCLOSE)
			{
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result;
}


// COM_COL : 'insert' '(' PARAM_INSERT ')' | 'find' '(' FIND_AUX | 'renameCollection' '(' PARAM_RENAME ')' | 'drop' '(' ')'
boolean _COM_COL()
{
	boolean result;
	if(token==INSERT)
	{
		commande.type=C_INSERT;
		
		//Création du document paramètre de la commande:
		Document* p_document=Malloc(Document);
		*p_document=NULL;
		
		token=_lire_token();	
		if(token==POPEN)
		{
			token=_lire_token();
			if(_PARAM_INSERT(p_document))
			{
				token=_lire_token();
				if(token==PCLOSE)
				{
					commande.parametre.p_insert.document=*p_document;
					result=true;
				}else
				{
					result=false;
				}
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else if(token==FIND)
	{
		commande.type=C_FIND;
		
		token=_lire_token();
		if(token==POPEN)
		{
			token=_lire_token();
			if(_FIND_AUX())
			{
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else if(token==RENAMECOL)
	{
		commande.type=C_RENAMECOL;
		
		token=_lire_token();	
		if(token==POPEN)
		{
			token=_lire_token();
			if(_PARAM_RENAME())
			{
				token=_lire_token();
				if(token==PCLOSE)
				{
					result=true;
				}else
				{
					result=false;
				}
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else if(token==DROP)
	{
		commande.type=C_DROP;
		
		token=_lire_token();
		if(token==POPEN)
		{
			token=_lire_token();
			if(token=PCLOSE)
			{
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result;
}

// PARAM_INSERT : DOC
boolean _PARAM_INSERT(Document* p_document)
{
	boolean result;
	if(_DOC(p_document))
	{
		result=true;
	}else
	{
		result=false;
	}
	return result;
}

// FIND_AUX : ')' | QUERY ')'
boolean _FIND_AUX()
{
	//Création du query paramètre de la commande:
	Query* p_query=Malloc(Query);
	*p_query=NULL;
		
	boolean result;
	if(token==PCLOSE)
	{
		commande.parametre.p_find.query=NULL;
		result=true;
	}else if(_QUERY(p_query))
	{
		commande.parametre.p_find.query=*p_query;
		token=_lire_token();
		if(token==PCLOSE)
		{
			result=true;
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result;
}

// PARAM_RENAME : idf
boolean _PARAM_RENAME()
{
	boolean result;
	if(token==IDF)
	{
		result=true;
	}else
	{
		result=false;
	}
	return result;
}

// DOC : '{' LIST_PAIR '}'
boolean _DOC(Document* p_document)
{
	boolean result;
	if(token==ACOOPEN)
	{
		token=_lire_token();
		if(_LIST_PAIR(p_document))
		{
			token=_lire_token();
			if(token==ACOCLOSE)
			{
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result; 
}

// LIST_PAIR: LIST_PAIR_AUX | EPSILON
boolean _LIST_PAIR(Document* p_document)
{
	boolean result;
	if(token==ACOCLOSE)
	{
		follow_token=true;
		result=true;
	}else if(_LIST_PAIR_AUX(p_document))
	{
		result=true;
	}else
	{
		result=false;
	}
	return result;
}

// LIST_PAIR_AUX: PAIR LIST_PAIR_AUX_AUX
boolean _LIST_PAIR_AUX(Document* p_document)
{
	boolean result;
	Paire *paire=Malloc(Paire);
	if(_PAIR(paire))
	{
		//Ajout de la paire au document courant:
		ajouterPaire(p_document,*paire);
		
		token=_lire_token();
		if(_LIST_PAIR_AUX_AUX(p_document))
		{
			result=true;
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result;
}

// LIST_PAIR_AUX_AUX: ',' LIST_PAIR_AUX | EPSILON
boolean _LIST_PAIR_AUX_AUX(Document* p_document)
{
	boolean result;
	if(token==ACOCLOSE)
	{
		follow_token=true;
		result=true;
	}else if(token==VIRG)
	{
		token=_lire_token();
		if(_LIST_PAIR_AUX(p_document))
		{
			result=true;
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result; 
}

// PAIR: idf ':' VALEUR
boolean _PAIR(Paire *paire)
{
	boolean result;
	if(token==IDF)
	{
		copier_chaine(&(paire->champ),_get_token());
		token=_lire_token();
		if(token==DPOINTS)
		{
			token=_lire_token();
			if(_VALEUR())
			{
				paire->valeur=valeur;
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result; 
}

// VALEUR: entier | decimal | chaine | regexp | 'null' | 'true'	| 'false' | 'MinKey' | 'MaxKey'	| DOC | TAB
boolean _VALEUR()
{
	//Création du document et du tableau qui peuvent être des valeurs:
	Document* p_document=Malloc(Document);
	*p_document=NULL;
	Tableau* p_tableau=Malloc(Tableau);
	*p_tableau=NULL;

	boolean result;
	if(token==ENTIER)
	{
		valeur.type=T_ENTIER;
		valeur.parametre.entier=atoi(_get_token());
		result=true;
	}else if(token==DECIMAL)
	{
		valeur.type=T_DECIMAL;
		valeur.parametre.decimal=(double)atof(_get_token());
		result=true;
	}else if(token==CHAINE)
	{
		valeur.type=T_CHAINE;
		copier_chaine(&(valeur.parametre.chaine),_get_token());
		result=true;
	}else if(token==REGEXP)
	{
		valeur.type=T_REGEXP;
		copier_chaine(&(valeur.parametre.chaine),_get_token());
		result=true;
	}else if(token==NUL)
	{
		valeur.type=T_NULL;
		result=true;
	}else if(token==TRUE)
	{
		valeur.type=T_BOOL;
		valeur.parametre.bool=true;
		result=true;
	}else if(token==FALSE)
	{
		valeur.type=T_BOOL;
		valeur.parametre.bool=false;
		result=true;
	}else if(token==MINKEY)
	{
		valeur.type=T_MINKEY;
		result=true;
	}else if(token==MAXKEY)
	{
		valeur.type=T_MAXKEY;
		result=true;
	}else if(_DOC(p_document))
	{
		valeur.type=T_DOC;
		valeur.parametre.document=*p_document;
		result=true;
	}else if(_TAB(p_tableau))
	{
		valeur.type=T_TAB;
		valeur.parametre.tableau=*p_tableau;
		result=true;
	}else
	{
		result=false;
	}
	return result; 
}

	

// TAB : '[' LIST_VAL ']'
boolean _TAB(Tableau* p_tableau)
{
	boolean result;
	if(token==CROOPEN)
	{
		token=_lire_token();
		if(_LIST_VAL(p_tableau))
		{
			token=_lire_token();
			if(token==CROCLOSE)
			{
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result; 	
}

// LIST_VAL: LIST_VAL_AUX | EPSILON
boolean _LIST_VAL(Tableau* p_tableau)
{
	boolean result;
	if(token==CROCLOSE)
	{
		follow_token=true;
		result=true;
	}else if(_LIST_VAL_AUX(p_tableau))
	{
		result=true;
	}else
	{
		result=false;
	}
	return result; 
}

// LIST_VAL_AUX: VALEUR LIST_VAL_AUX_AUX
boolean _LIST_VAL_AUX(Tableau* p_tableau)
{
	boolean result;
	if(_VALEUR())
	{
		//Ajout de la valeur au tableau courant:
		ajouterValeur(p_tableau,valeur);
		
		token=_lire_token();
		if(_LIST_VAL_AUX_AUX(p_tableau))
		{
			result=true;
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result; 
}

// LIST_VAL_AUX_AUX: ',' LIST_VAL_AUX | EPSILON
boolean _LIST_VAL_AUX_AUX(Tableau* p_tableau)
{
	boolean result;
	if(token==CROCLOSE)
	{
		follow_token=true;
		result=true;
	}else if(token==VIRG)
	{
		token=_lire_token();
		if(_LIST_VAL_AUX(p_tableau))
		{
			result=true;
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result; 
}

// QUERY : EXP
boolean _QUERY(Query* p_query)
{
	Expression** pp_expression=(Expression**)p_query;
	boolean result;
	if(_EXP(pp_expression))
	{
		result=true;
	}else
	{
		result=false;
	}
	return result;
}

// EXP : '{' EXP_AUX '}'
boolean _EXP(Expression** pp_expression)
{
	boolean result;
	if(token==ACOOPEN)
	{
		token=_lire_token();
		if(_EXP_AUX(pp_expression))
		{
			token=_lire_token();
			if(token==ACOCLOSE)
			{
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result; 
}

// EXP_AUX : '$or' ':' TAB_EXP | '$and' ':' TAB_EXP | EXP_ELEM
boolean _EXP_AUX(Expression** pp_expression)
{
	Liste_Exp** pp_liste_exp=Malloc(Liste_Exp*);
	*pp_liste_exp=NULL;
	
	boolean result;
	if(token==OR)
	{
		token=_lire_token();
		if(token==DPOINTS)
		{
			token=_lire_token();
			if(_TAB_EXP(pp_liste_exp))
			{
				ajouterExpressionComplexe(OP_OR,*pp_liste_exp);
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else if(token==AND)
	{
		token=_lire_token();
		if(token==DPOINTS)
		{
			token=_lire_token();
			if(_TAB_EXP(pp_liste_exp))
			{
				ajouterExpressionComplexe(OP_AND,*pp_liste_exp);
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else if(_EXP_ELEM())
	{
		result=true;
	}else
	{
		result=false;
	}
	return result; 	
}
	
// TAB_EXP : '[' LIST_EXP ']'
boolean _TAB_EXP(Liste_Exp** pp_liste_exp)
{
	boolean result;
	if(token==CROOPEN)
	{
		token=_lire_token();
		if(_LIST_EXP(pp_liste_exp))
		{
			token=_lire_token();
			if(token==CROCLOSE)
			{
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result; 	
}

// LIST_EXP : LIST_EXP_AUX | EPSILON
boolean _LIST_EXP(Liste_Exp** pp_liste_exp)
{
	boolean result;
	if(token==CROCLOSE)
	{
		follow_token=true;
		result=true;
	}else if(_LIST_EXP_AUX(pp_liste_exp))
	{
		result=true;
	}else
	{
		result=false;
	}
	return result; 
}

// LIST_EXP_AUX: EXP LIST_EXP_AUX_AUX
boolean _LIST_EXP_AUX(Liste_Exp** pp_liste_exp)
{
	boolean result;
	if(_EXP())
	{	
		token=_lire_token();
		if(_LIST_EXP_AUX_AUX(pp_liste_exp))
		{
			result=true;
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result; 
}

// LIST_EXP_AUX_AUX: ',' LIST_EXP_AUX | EPSILON
boolean _LIST_EXP_AUX_AUX(Liste_Exp** pp_liste_exp)
{
	boolean result;
	if(token==CROCLOSE)
	{
		follow_token=true;
		result=true;
	}else if(token==VIRG)
	{
		token=_lire_token();
		if(_LIST_EXP_AUX(pp_liste_exp))
		{
			result=true;
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result; 
}

// EXP_ELEM : idf ':' '{' EXP_ELEM_AUX '}'
boolean _EXP_ELEM()
{
	boolean result;
	if(token==IDF)
	{	
		token=_lire_token();
		if(token==DPOINTS)
		{
			token=_lire_token();
			if(token==ACOOPEN)
			{
				token=_lire_token();
				if(_EXP_ELEM_AUX())
				{
					token=_lire_token();
					if(token==ACOCLOSE)
					{
						result=true;
					}else
					{
						result=false;
					}
				}else
				{
					result=false;
				}
			}else
			{
				result=false;
			}	
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result;
}

// EXP_ELEM_AUX : OP_VAL ':' VALEUR | OP_TAB ':' TAB
boolean _EXP_ELEM_AUX()
{
	boolean result;
	if(_OP_VAL())
	{
		token=_lire_token();
		if(token==DPOINTS)
		{
			token=_lire_token();
			if(_VALEUR())
			{
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else if(_OP_TAB())
	{
		token=_lire_token();
		if(token==DPOINTS)
		{
			token=_lire_token();
			if(_TAB())
			{
				result=true;
			}else
			{
				result=false;
			}
		}else
		{
			result=false;
		}
	}else
	{
		result=false;
	}
	return result; 		
}

// OP_VAL : '$eq' | '$gt' | '$gte' | '$lt' | '$lte' | '$ne'
boolean _OP_VAL()
{
	boolean result;
	if(token==EQ)
	{
		result=true;
	}else if(token==GT)
	{
		result=true;
	}else if(token==GTE)
	{
		result=true;
	}else if(token==LT)
	{
		result=true;
	}else if(token==LTE)
	{
		result=true;
	}else if(token==NE)
	{
		result=true;
	}else
	{
		result=false;
	}
	return result; 	
}

// OP_TAB : '$in' | '$nin'
boolean _OP_TAB()
{
	boolean result;
	if(token==IN)
	{
		result=true;
	}else if(token==NIN)
	{
		result=true;
	}else
	{
		result=false;
	}
	return result; 	
}
