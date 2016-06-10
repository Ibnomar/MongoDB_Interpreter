typedef enum {
	or_ , and_ , nor_ , autres
} typeOpLogique;

typedef enum {
	exists , in , not_ , eq , gt , gte , lt , lte , ne
} typeOpComparaison;

typedef enum {
	string_ , false_ , true_ , int_ , tableau , null
} typeArgument;

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
