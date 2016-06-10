
#ifndef MONGO_JSON_H
#define MONGO_JSON_H

typedef enum {
    FIND,
    UPDATE,
    STRINGM,
    STRING,
    INT,
    FLOAT,
    TRUE,
    FALSE,
    NULL_,
    ACO,
    ACF,
    MO,
    MF,
    DEUXP,
    VIRG,
    ERROR,
    INSERT,
    DB,
    POINT,
    IDF,
    PARO,
    PARF,
    EQ,
    GTE,
    GT,
    LTE,
    LT,
    NE,
    NOT,
    EXISTS,
    IN,
    NIN,
    AND,
    OR,
    NOR,
    MOD
} typetoken;

typedef enum {
    false, true
} boolean;

char currentDataFile[1024];

char currentDocument[1024];

boolean isConsumed;

typetoken token;

typetoken lire_token();

boolean query_logical();

boolean query_comparaison();

boolean qaux3();

boolean qaux2();

boolean qaux4();

boolean qaux_in();

boolean qaux3virg();

boolean q();

boolean liste_queryaux();

boolean liste_query();

boolean qaux();

boolean queryaux();

boolean query();

boolean valeur();

boolean valeur();

boolean valeur_aux();

boolean elements();

boolean tableau();

boolean paire();

boolean paire_aux();

boolean membres();

boolean json();

boolean insert();

boolean find();

boolean qaux5();
boolean update();
boolean isReserved();
#endif //MONGO_JSON_H
