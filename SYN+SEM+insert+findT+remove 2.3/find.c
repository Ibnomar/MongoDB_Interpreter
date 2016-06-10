#include "find.h"
#include <string.h>

Query *creer_Query(typeOpLogique opLog) {
    Query *qu = (Query *) malloc(sizeof(Query));
    qu->type = opLog;
    qu->qAux = NULL;
    qu->suivant=NULL;
    return qu;
}

void ajouterQuery(Query *topQuery, Query_aux *query) {
    if (topQuery->qAux == NULL)
        topQuery->qAux = query;
    else {
        query->suivant = topQuery->qAux;
        topQuery->qAux = query;
    }
}

void ajouterPetiteQuery(Query *topQuery, Query_aux *query) {
    if (topQuery->qAux == NULL)
        topQuery->qAux = query;
    else {
        query->suivant = topQuery->qAux;
        topQuery->qAux = query;
    }
}

Query_aux *creerQueryAux(char *nom) {
    Query_aux *qu = (Query_aux *) malloc(sizeof(Query_aux));
    qu->suivant = NULL;
    qu->nom = strdup(nom);
    return qu;
}

Operation *creerOp(typeOpComparaison tOpComp) {
    Operation *opp = (Operation *) malloc(sizeof(Operation));
    opp->tOpComp = tOpComp;
    opp->argList = NULL;
    opp->suivant = NULL;
    return opp;
}

void ajouterArg(Operation *opp, typeArgument tArg,char *nom) {
    Argument *argument = (Argument *) malloc(sizeof(Argument));
    if (tArg==tableau)printf("lol");
        // probleme argument->argValue = strdup(table);
    else
        argument->argValue = strdup(nom);
    argument->tArg = tArg;
    argument->suivant = NULL;
    if (opp->argList == NULL) {
        opp->argList = argument;
    }
    else {
        argument->suivant = opp->argList;
        opp->argList = argument;
    }
}

void ajouterOp(Query_aux *query, Operation *opp) {
    if (query->Op == NULL) {
        query->Op = opp;
        opp->suivant = NULL;
    }
    else {
        opp->suivant = query->Op;
        query->Op = opp;
    }
}

void afficherTop(Query *query) {
    if(query!=NULL){
   printf("%d\n", query->type);
    while (query->qAux!=NULL) {
        puts(query->qAux->nom);

        while (query->qAux->Op->argList) {
            puts(query->qAux->Op->argList->argValue);
            query->qAux->Op->argList = query->qAux->Op->argList->suivant;
        }

    query->qAux = query->qAux->suivant; }}
}
