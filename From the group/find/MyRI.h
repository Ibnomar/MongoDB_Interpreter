typedef enum {
	or , and , nor 
} typeOpLogique;

typedef enum {
	exists , in , not , eq , gt , gte , lt , lte , ne
} typeOpComparaison;

typedef enum {
	string , false_ , true_ , int_ , tableau , null
} typeArgument;


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