//
// Created by othmane on 11/23/15.
//

#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include "findQuery.h"
#include "mongo_an.h"

Querry *createTopQuery(op_log opLogical) {
    Querry *qu = (Querry *) malloc(sizeof(Querry));
    qu->nom_op_log = opLogical;
    return qu;
}

void addQueryToTop(Querry *topQuery, fquery *query) {
    if (topQuery->queries == NULL)
        topQuery->queries = query;
    else {
        query->next = topQuery->queries;
        topQuery->queries = query;
    }
}

fquery *createQuery() {
    fquery *qu = (fquery *) malloc(sizeof(fquery));
    qu->next = NULL;
    qu->attr = strdup(yyget_text());
    return qu;
}

op *createOp(op_comp opComp) {
    op *opp = (op *) malloc(sizeof(op));
    opp->opcomp = opComp;
    opp->listeArgs = NULL;
    opp->next = NULL;
    return opp;
}

void addToArgs(op *opp, typeArg type) {
    arg *argument = (arg *) malloc(sizeof(arg));
    if (type == _OBJECT || type==_ARRAY)
        argument->argument = strdup(currentDocument);
    else
        argument->argument = strdup(yyget_text());
    argument->type = type;
    argument->next = NULL;
    if (opp->listeArgs == NULL) {
        opp->listeArgs = argument;
    }
    else {
        argument->next = opp->listeArgs;
        opp->listeArgs = argument;
    }
}

void addToOps(fquery *query, op *opp) {
    if (query->ops == NULL) {
        query->ops = opp;
        opp->next = NULL;
    }
    else {
        opp->next = query->ops;
        query->ops = opp;
    }
}

void afficherTop(Querry *query) {
    printf("%d\n", query->nom_op_log);
    while (query->queries) {
        printf("%s\n", query->queries->attr);
        while (query->queries->ops) {
            printf("%d\n", query->queries->ops->opcomp);
            query->queries->ops = query->queries->ops->next;
        }
        query->queries = query->queries->next;
    }
}