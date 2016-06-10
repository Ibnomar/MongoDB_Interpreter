%{
#include "mongo.h"
%}

%option noyywrap
%option yylineno
%option outfile="mongo_an.c" header-file="mongo_an.h"

IDF [A-Za-z][A-Za-z0-9]*

INSERT "insert"
UPDATE "update"
FIND "find"

POINT "."

DB "db"

MOD "\"\$mod\""

EQ "\"\$eq\""

GTE  "\"\$gte\""

GT  "\"\$gt\""

LTE  "\"\$lte\""

LT  "\"\$lt\""

NE  "\"\$ne\""

NOT  "\"\$not\""

EXISTS  "\"\$exists\""

IN  "\"\$in\""

NIN  "\"\$nin\""

AND  "\"\$and\""

OR  "\"\$or\""

NOR  "\"\$nor\""

STRING \"[^\$][^\n\\\"]*\"

STRINGM \"[^\n\\\"]*\"

INT "-"?[0-9]+

FLOAT {INT}"."[0-9]+

TRUE "true"

FALSE "false"

NULL "null"

ACO "{"

ACF "}"

MO "["

MF "]"

PARO "("

PARF ")"

DEUXP ":"

VIRG ","

%%

{STRING} {return STRING;}

{EXISTS} {return EXISTS;}

{MOD} {return MOD;}

{EQ} {return EQ;}

{GTE} {return GTE;}

{GT} {return GT;}

{LTE} {return LTE;}

{LT} {return LT;}

{NE} {return NE;}

{NOT} {return NOT;}

{IN} {return IN;}

{NIN} {return NIN;}

{AND} {return AND;}

{OR} {return OR;}

{NOR} {return NOR;}

{DB} {return DB;}

{INSERT} {return INSERT;}

{UPDATE} {return UPDATE;}

{FIND} {return FIND;}

{TRUE} {return TRUE;}

{FALSE} {return FALSE;}

{NULL} {return NULL_;}

{IDF} {return IDF;}

{POINT} {return POINT;}

{STRINGM} {return STRINGM;}

{FLOAT} {return FLOAT;}

{INT} {return INT;}

{ACO} {return ACO;}

{ACF} {return ACF;}

{MO} {return MO;}

{MF} {return MF;}

{PARO} {return PARO;}

{PARF} {return PARF;}

{DEUXP} {return DEUXP;}

{VIRG} {return VIRG;}

[ \t\n]+ {}

. {return ERROR;}

%%