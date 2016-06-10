typedef enum {
	or_ , and_ , nor_ , autres
} typeOpLogique;

typedef enum {
	exists , in , not_ , eq , gt , gte , lt , lte , ne , autr
} typeOpComparaison;

typedef enum {
	string_ , false_ , true_ , int_ , tableau , null
} typeArgument;

typedef enum {
DB_ERR, POINT_ERR,FIND_ERR ,PARO_ERR, PARF_ERR, ACO_ERR, ACF_ERR, INSERT_ERR, UPDATE_ERR, VIRG_ERR, DEUXP_ERR, STRING_ERR,
VALEUR_ERR, QUERY_ERR, QUERYAUX_ERR, LISTE_QUERYAUX_ERR, QAUX_ERR, QAUX_IN_ERR, VALEUR_AUX_ERR, QAUX3VIRG_ERR, QUERY_LOGICAL_ERR,
MF_ERR, TABLEAU_ERR, PAIRE_AUX_ERR, QUERY_COMPARAISON_ERR,MO_ERR, BOOLEAN_ERR, EXISTS_ERR, Q_ERR, QAUX3_ERR,INST_ERR
,QAUX5_ERR , DOUBLE_ERR , REMOVE_ERR, GLL_ERR,OPINT_ERR, USE_ERR , DROP_ERR, SHOW_ERR , DBS_ERR , COLLECTIONS_ERR
             }Erreurs;
/*
typedef struct tabQuery{
typeArgument type;
union{
    int val_int;
    char * val_char;

}node;
}*/

typedef struct Argument {
	typeArgument tArg;
	char * argValue;
	struct Argument * suivant;
}Argument;

typedef struct Operation{
	typeOpComparaison tOpComp;
	Argument * argList;
	struct Operation * suivant;
}Operation;

typedef struct Query_aux{
	char * nom;
	Operation * Op;
	struct Query_aux * suivant;

} Query_aux;

typedef struct Query {
	typeOpLogique  type;
	Query_aux * qAux;
	struct  Query * suivant;
} Query;

Query *creer_Query(typeOpLogique opLog);
void ajouterQuery(Query *topQuery, Query_aux *query);
Query_aux *creerQueryAux(char *nom);
Operation *creerOp(typeOpComparaison tOpComp);
void ajouterArg(Operation *opp, typeArgument tArg,char *nom) ;
void ajouterOp(Query_aux *query, Operation *opp) ;
void afficherTop(Query *query) ;
void interpreter_find(char * chemin,Query * qu,int err);
int fonction_monstre(char *tst,Query * qu);
int minimonstre(char * tst,Query_aux* tmpe);
void interpreter_remove(char * chemin,Query * qu,int err);
void interpreter_update(char * chemin,Query * qu,int err);
