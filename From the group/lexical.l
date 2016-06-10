%{
#include<stdio.h>
#include "analyseur_syn.h"

int ligneDecl=1;
int ligneInst=1;
char mavar[10];

%}

%option noyywrap 

IDF [A-Za-z][A-Za-z0-9]*
DIGIT [0-9]

%%

{DIGIT}+             						{return INUMBER;}
"int"                						{return INT;}
"bool"                						{return BOOLEAN;}
"double"                					{return DOUBLE;}
"true"										{return VRAI;}
"false"										{return FAUX;}
"begin"										{return BEG_IN;}
"if"										{return IF;}
"for"										{return FOR;}
"to"                                        {return TO;}
"do"                                        {return DO;}
"endfor"                                    {return ENDFOR;}
")"										    {return PAR_FERM;}
"("										    {return PAR_OUVR;}
"end"										{return END;}
"print"										{return PRINT;}
"endif"										{return ENDIF;}
"else"										{return ELSE;}
"then"										{return THEN;}  

";"                                 		{return PVIRG;}
"="											{return EGALE;}
"-"                						{return MOINS;}
"+"                						{return PLUS;}
"*"                						{return PROD;}
"/"                						{return DIV;}

"=="										{return EGALEEGALE;}

[\n]                                        {ligneDecl++;ligneInst++;}
[\t]+										
" "                                         
{IDF}										{strcpy(mavar,yytext);return IDF;}
												
										    
.											{printf("ERRORLEX(%s)",yytext);}
												
%%

	

