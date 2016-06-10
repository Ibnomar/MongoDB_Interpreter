#ifndef MONGOV0_2_FINDQUERY_H
#define MONGOV0_2_FINDQUERY_H
#include "mongo.h"

boolean isQueryLogical;

//Types d'opérations logiques
typedef enum {
    _NOR,
    _AND,
    _OR,
} op_log;

//Types d'opérations de comparaison
typedef enum {
    _EXISTS,
    _MOD,
    _IN,
    _NOT,
    _EQ,
    _GT,
    _GTE,
    _LT,
    _LTE,
    _NE
} op_comp;

//Types d'arguments
typedef enum {
    _BOOLEAN,
    _STRING,
    _INT,
    _FLOAT,
    _OBJECT,
    _ARRAY,
    _NULL
} typeArg;

//Liste pour stocker la liste des arguments
typedef struct argg {
    typeArg type;
    char *argument;
    struct argg *next;
} arg;

//Liste pour stocker l'opération et ses arguments
typedef struct opp {
    op_comp opcomp;
    arg *listeArgs;
//    struct fquerry *queries;
    struct opp *next;
} op;

//La liste chainée pour stocker opérations
//typedef struct _op_logical {
//    //Opération logique
//    op_log nom_op_log;
//    //Opérations de comparaison
//    op *ops;
//    struct _op_logical *next;
//} op_logical;

//Liste chainée pour stocker les queries
typedef struct fquerry {
    //le nom de l'attribut en question
    char *attr;
    //La liste des opérations logique ou autre
    op *ops;

    //struct _querry *log_query;
    struct fquerry *next;
} fquery;

typedef struct _querry {
    op_log nom_op_log;
    fquery *queries;
    struct _querry *next;
} Querry;

Querry *createTopQuery(op_log);

fquery *createQuery();

void addQueryToTop(Querry *topQuery, fquery *query);

op *createOp(op_comp);

void addToArgs(op *, typeArg);

void addToOps(fquery *, op *);

void afficherTop(Querry *);

#endif //MONGOV0_2_FINDQUERY_H
