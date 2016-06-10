#include <sys/stat.h>
#include "mongo.h"



//query-----------------> { queryAux } | epsilon
//queryAux -------------> string : Q QAux | query_logical : [ list_query] QAux | epsilon
//QAux -----------------> ,queryAux | epsilon
//liste_query ----------> query liste_queryAux
//liste_queryAux -------> ,list-query | epsilon
//Q---------------------> { QAux4 }| valeur***!!!
//QAux4----------------->  QAux2 Qaux5 | Membres | epsilon**
//QAux2 ----------------> query_comparaison : valeur
//                        | $exists : boolean
//                        | $mod : [ divisor, remainder ]
//                        | $in : [ quaux_in ]
//                        | $not : {query-comparaison : valeur}
//quaux_in--------------> valeur QAux3 | {Membres} QAux3
//QAux5----------------->,QAux2 Qaux5 | epsilon
//QAux3 ----------------> ,qaux3virg | epsilon
//qaux3virg ------------> valeur QAux3 | {Membres} QAux3
//query_comparaison ------> $eq
//                        | $gt
//                        | $gte
//                        | $lt
//                        | $lte
//                        | $ne
//
//query_logical ----------> $or
//                        | $and
//                        | $nor
/*
 * Follow (qaux5) = {'}'} **
 *
 * Follow (query) = {',',']'}
 *
 * Follow (queryaux) = {'}'}
 *
 * Follow (QAux) ={'}'}
 *
 * Follow (liste_queryAux) = {']'}
 *
 * Follow (QAux3) = {']'}
 *
 * Follow (QAux4) = {'}'}
 * */

/*
 *
 * Find : DB.IDF.FIND(query)
 *
 * Insert : DB . IDF . INSERT ({Membres})
 *
 * Update :DB.IDF.UPDATE(query,{Membres})
 *
 * Membres : Paire Paire_Aux
 * Paire_Aux : , Membres | epsilon
 *
 * Paire : string : Valeur
 *
 * Tableau : [ ] | [ Elements ]
 *
 * Elements : Valeur Valeur_Aux
 * Valeur_Aux : , Elements | epsilon
 *
 * Valeur : stringM|int|float|tableau|true|false|null
 *
 * Follow (Valeur_Aux)={ ']' }
 *
 * Follow (Paire_Aux) = { '}' }
 *
 * */




typetoken lire_token() {
    if (isConsumed) {
        isConsumed = false;
        return token;
    }
    else
        return (typetoken) yylex();
}

boolean find() {
    boolean result = false;
    if (token == DB) {
        token = lire_token();
        if (token == POINT) {
            token = lire_token();
            if (token == IDF) {
                token = lire_token();
                if (token == POINT) {
                    token = lire_token();
                    if (token == FIND) {
                        token = lire_token();
                        if (token == PARO) {
                            token = lire_token();
                            if (query()) {
                                token = lire_token();
                                if (token == PARF) {
                                    result = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

boolean query_logical() {
    boolean result = false;
    if (token == OR)
    {
        result = true;
    }
    else if (token == AND)
    {
        result = true;
    }
    else if (token == NOR)
    {
        result = true;
    }
    return result;
}

boolean query_comparaison() {
    boolean result = false;
    if (token == EQ) {
        result = true;
        
    }
    else if (token == GT) {
        result = true;
        
    } else if (token == GTE) {
        result = true;
        
    } else if (token == LT) {
        result = true;
        
    } else if (token == LTE) {
        result = true;
        
    } else if (token == NE) {
        result = true;
        }
    


    return result;
}

boolean qaux3() {
    boolean result = false;
    if (token == MF) {
        isConsumed = true;
        result = true;
    }
    else if (token == VIRG) {
        token = lire_token();
        if (qaux3virg())
            result = true;
    }
    return result;
}

boolean qaux3virg() {
    boolean result = false;
    if (valeur()) {
        token = lire_token();
        if (qaux3())
            result = true;
    }
    else if (token == ACO) {
        token = lire_token();
        if (membres()) {
            token = lire_token();
            if (token == ACF) {
                token = lire_token();
                if (qaux3())
                    result = true;
            }
        }
    }
    return result;
}

boolean qaux2() {
    boolean result = false;
    if (query_comparaison()) {
        token = lire_token();
        if (token == DEUXP) {
            token = lire_token();
            if (valeur())
                result = true;
        }
    }
    else if (token == EXISTS) {
        if (token == DEUXP) {
            token = lire_token();
            if (token == TRUE || token == FALSE){
                result = true;
            }
            }
    }
    else if (token == MOD) {
            token = lire_token();
            if (token == DEUXP) {
                token = lire_token();
                if (token == MO) {
                    token = lire_token();
                    if (token == INT) {
                        token = lire_token();
                        if (token == VIRG) {
                            token = lire_token();
                            if (token == INT) {
                                token = lire_token();
                                if (token == MF)
                                    result = true;
                            }
                        }
                    }
                }
            }
    }
    else if (token == IN) {
        token = lire_token();
        if (token == DEUXP) {
            token = lire_token();
            if (token == MO) {
                token = lire_token();
                if (qaux_in()) {
                    token = lire_token();
                    if (token == MF)
                        result = true;
                }
            }
        }
    }
    else if (token == NOT) {
        token = lire_token();
        if (token == ACO) {
            token = lire_token();
            if (token == DEUXP) {
                token = lire_token();
                if (query_comparaison()) {
                    token = lire_token();
                    if (token == DEUXP) {
                        token = lire_token();
                        if (valeur()) {
                            token = lire_token();
                            if (token == ACF)
                                result = true;
                        }
                    }
                }
            }
        }
    }
    return result;
}

boolean qaux_in() {
    boolean result = false;
    if (valeur()) {
        token = lire_token();
        if (qaux3())
            result = true;
    }
    else if (token == ACO) {
        token = lire_token();
        if (membres()) {
            token = lire_token();
            if (token == ACF) {
                token = lire_token();
                if (qaux3())
                    result = true;
            }
        }
    }
    return result;
}

boolean q() {
    boolean result = false;
    if (token == ACO) {
        token = lire_token();
        if (qaux4()) {
            token = lire_token();
            if (token == ACF)
                result = true;
        }
    }
    else 
    {
        if (valeur()){ result = true; }
    } 
    return result;
}

boolean qaux4() {
    boolean result = false;
    if (token == ACF) {
        isConsumed = true;
        result = true;
    }
    else if (qaux2()) {
        token = lire_token();
        if (qaux5())
            result = true;
    }
    else if (membres())
        result = true;

    return result;
}

boolean liste_queryaux() {
    boolean result = false;

    if (token == MF) {
        isConsumed = true;
        result = true;
    }
    else if (token == VIRG) {
        token = lire_token();
        if (liste_query())
            result = true;
    }
    return result;
}

boolean liste_query() {
    boolean result = false;
    if (query()) {
        token = lire_token();
        if (liste_queryaux())
            result = true;
    }
    return result;
}

boolean qaux() {
    boolean result = false;
    if (token == ACF) {
        isConsumed = true;
        result = true;
    }
    else if (token == VIRG) {
        token = lire_token();
        if (queryaux())
            result = true;
    }
    return result;
}

boolean queryaux() {
    boolean result = false;
         
    if (token == ACF) {
        isConsumed = true;
        result = true;
    }
    else if (token == STRING) {
        token = lire_token();
        if (token == DEUXP) {
            token = lire_token();
            if (q()) {
                token = lire_token();
                if (qaux())
                    result = true;
            }
        }
    }
    else if (query_logical()) {
        token = lire_token();
        if (token == DEUXP) {
            token = lire_token();
            if (token == MO) {
                token = lire_token();
                if (liste_query()) {
                    token = lire_token();
                    if (token == MF) {
                        token = lire_token();
                        if (qaux())
                            result = true;
                    }
                }
            }
        }
    }
    return result;
}

boolean query() {
    boolean result = false;
    if (token == VIRG) {
        isConsumed = true;
        result = true;
    }
    else if (token == MF) {
        isConsumed = true;
        result = true;
    }
    else if (token == ACO) {
        token = lire_token();
        if (queryaux()) {
            token = lire_token();
            if (token == ACF)
                result = true;
        }
    }
    return result;
}

boolean valeur() {
    boolean result = false;
    if (token == STRINGM) {
        result = true;
    }
    else if (token == STRING) {
    }
    else if (token == INT) {
        result = true;
    }
    else if (token == FLOAT) {
        result = true;
    }
    else if (tableau())
        result = true;
    else if (token == TRUE || token == FALSE) {
        result = true;
    }
    else if (isReserved()) {
        result = true;
    }
    else if (token == NULL_) {
        result = true;
    }
    

    return result;
}

boolean elements() {
    boolean result = false;
    if (valeur()) {
        token = lire_token();
        if (valeur_aux())
            result = true;
    }
    return result;
}

boolean valeur_aux() {
    boolean result = false;
    if (token == MF) {
        isConsumed = true;
        result = true;
    }
    else if (token == VIRG) {
        token = lire_token();
        if (elements()) {
            result = true;
        }
    }
    return result;
}

boolean tableau() {
    boolean result = false;
    if (token == MO) {      
        token = lire_token();
        if (token == MF) {
            result = true;
        }
        else if (elements()) {
            token = lire_token();
            if (token == MF) {
                result = true;
            }
        }
    }
    return result;
}

boolean paire() {
    boolean result = false;
    if (token == STRING) {
        token = lire_token();
        if (token == DEUXP) {
            token = lire_token();
            if (valeur()) {
                result = true;
            }
        }
    }
    return result;
}

boolean paire_aux() {
    boolean result = false;
    if (token == ACF) {
        isConsumed = true;

    }
    else if (token == VIRG) {
        token = lire_token();
        if (membres())
            result = true;
    }
    return result;
}

boolean membres() {
    boolean result = false;
    if (paire()) {
        token = lire_token();
        if (paire_aux())
            result = true;
    }
    return result;
}

boolean insert() {
    boolean result = false;
    if (token == DB) {
        token = lire_token();
        if (token == POINT) {
            token = lire_token();
            if (token == IDF) {
                token = lire_token();
                if (token == POINT) {
                    token = lire_token();
                    if (token == INSERT) {
                        token = lire_token();
                        if (token == PARO) {
                            token = lire_token();
                            if (token == ACO) {
                                token = lire_token();
                                if (membres()) {
                                    token = lire_token();
                                    if (token == ACF) {
                                        token = lire_token();
                                        if (token == PARF) {
                                            result = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

boolean qaux5() {
    boolean result = false;
    if (token == ACF) {
        isConsumed = true;
        result = true;
    }
    else if (token == VIRG) {
        token = lire_token();
        if (qaux2()) {
            token = lire_token();
            if (qaux5())
                result = true;
        }
    }
    return result;
}

boolean isReserved() {
    switch (token) {

        case EQ:
        case GTE:
        case GT:
        case LTE:
        case LT:
        case NE:
        case NOT:
        case EXISTS:
        case IN:
        case NIN:
        case AND:
        case OR:
        case NOR:
        case MOD:
            return true;
    }
    return false;
}

boolean update() {
    boolean result = false;
    if (token == DB) {
        token = lire_token();
        if (token == POINT) {
            token = lire_token();
            if (token == IDF) { ;
                token = lire_token();
                if (token == POINT) {
                    token = lire_token();
                    if (token == UPDATE) {
                        token = lire_token();
                        if (token == PARO) {
                            token = lire_token();
                            if (query()) {
                                token = lire_token();
                                if (token == VIRG) {
                                    token = lire_token();
                                    if (token == ACO) {
                                        token = lire_token();
                                        if (membres()) {
                                            token = lire_token();
                                            if (token == ACF) {
                                                token = lire_token();
                                                if (token == PARF) {
                                                    result = true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}
