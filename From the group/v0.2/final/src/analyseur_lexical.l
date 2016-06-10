%{

#include "tokens.h"
static int debug=1;
%}
%option noyywrap
%option yylineno
chaineGui	[\"]([^"]|([\\][\"]))*[\"]
chaineAp	[']([^']|([\][']))*[']
%%

";" 			{if (debug) printf (";");return PVIRG;}
"." 			{if (debug) printf (".");return POINT;}
"{" 			{if (debug) printf ("{");return ACOOPEN;}
"}" 			{if (debug) printf ("}");return ACOCLOSE;}
"[" 			{if (debug) printf ("[");return CROOPEN;}
"]" 			{if (debug) printf ("]");return CROCLOSE;}
":" 			{if (debug) printf (":");return DPOINTS;}
"," 			{if (debug) printf (",");return VIRG;}
"("			{if (debug) printf ("(");return POPEN;}
")"			{if (debug) printf (")");return PCLOSE;}
"db"			{if (debug) printf ("db");return DB;}
"insert"		{if (debug) printf ("insert");return INSERT;}
"find"			{if (debug) printf ("find");return FIND;}
"getCollectionNames"	{if (debug) printf ("getCollectionNames");return GETCOLNAMES;}
"renameCollection"	{if (debug) printf ("renameCollection");return RENAMECOL;}
"drop"			{if (debug) printf ("drop");return DROP;}
"null"			{if (debug) printf ("null");return NUL;}
"true"			{if (debug) printf ("true");return TRUE;}
"false"			{if (debug) printf ("false");return FALSE;}
"MinKey"		{if (debug) printf ("MinKey");return MINKEY;}
"MaxKey"		{if (debug) printf ("MaxKey");return MAXKEY;}
"$or"			{if (debug) printf ("$or");return OR;}
"$and"			{if (debug) printf ("$and");return AND;}
"$eq"			{if (debug) printf ("$eq");return EQ;}
"$gt"			{if (debug) printf ("$gt");return GT;}
"$gte"			{if (debug) printf ("$gte");return GTE;}
"$lt"			{if (debug) printf ("$lt");return LT;}
"$lte"			{if (debug) printf ("$lte");return LTE;}
"$ne"			{if (debug) printf ("$ne");return NE;}
"$in"			{if (debug) printf ("$in");return IN;}
"$nin"			{if (debug) printf ("$nin");return NIN;}
[a-zA-Z_][a-zA-Z0-9_]*  {if (debug) printf ("IDF(%s)",yytext); return IDF;}
[-]?[0-9]+[.][0-9]+	{if (debug) printf ("DECIMAL(%s)\n",yytext);return DECIMAL;}
[-]?[0-9]+		{if (debug) printf ("ENTIER(%s)\n",yytext);return ENTIER;}
{chaineGui}|{chaineAp}	{if (debug) printf ("CHAINE(%s)\n",yytext);return CHAINE;}
[/]({chaineGui}|{chaineAp})[/][gi]	{if (debug) printf ("REGEXP(%s)",yytext); return REGEXP;}			
[\t]			{if (debug) printf ("\t");}
[\n]			{if (debug) printf ("\n");}
[ ]			{if (debug) printf (" ");}
.			{printf	("ERRORLEX(%s)\n",yytext);return -1;}
%%

