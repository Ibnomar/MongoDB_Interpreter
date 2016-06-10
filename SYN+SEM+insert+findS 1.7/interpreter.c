#include <string.h>
#include <stdio.h>
#include "find.h"

void interpreter_find(char * chemin,Query * qu){
	FILE*fichier=fopen(chemin,"r");
	char ligne[1024];
	while(fgets(ligne,sizeof(ligne),fichier)!=NULL){
            if(fonction_monstre(ligne,qu)==1)
                printf("%s",ligne);
	//char * tst = ligne;
	//if(fonction_monstre(tst,Query)==1)concat(liste_affiche,tst);
	}

}

/*
void interpreter_remove(){
FILE*fichier=fopen(chemin,"r");
FILE*fichier2=fopen(chemin2,"a");
//
while(ligne!=EOF){
	char * tst = ligne;
	if(fonction_monstre(tst,Query)==0)copier tst f fichier2;
}
remove(fichier);
rename(fichier2,fichier1);
}

void interpreter_update(){
FILE*fichier=fopen(chemin,"r");
FILE*fichier2=fopen(chemin2,"a");
//
while(ligne!=EOF){
	char * tst = ligne;
	if(fonction_monstre(tst,Query)==1){
		fonction_kamla()
	}
}
remove(fichier);
rename(fichier2,fichier1);
}
*/
int fonction_monstre(char *tst,Query * qu){
	if(qu==NULL)return 1 ;
	else{
	switch(qu->type){
		case or_ : {
		    Query_aux * tmpe = qu->qAux;
            while(tmpe){
                if(minimonstre(tst,tmpe)==1)return 1 ;
                tmpe=tmpe->suivant;
            }
            return 0;
                } break;
		case nor_ :{
            Query_aux * tmpe = qu->qAux;
            while(tmpe){
                if(minimonstre(tst,tmpe)==0)return 0 ;
                tmpe=tmpe->suivant;
            }
            return 1;
		} break;
		case and_ : {
            Query_aux * tmpe = qu->qAux;
            while(tmpe){
                if(minimonstre(tst,tmpe)==1)return 0 ;
                tmpe=tmpe->suivant;
            }
            return 1;
            } break;
		default : {
            Query_aux * tmpe = qu->qAux;
            while(tmpe){
                if(minimonstre(tst,tmpe)==0)return 0 ;
                tmpe=tmpe->suivant;
            }
            return 1;
		}break;
	}}
	return 0 ;
}

int minimonstre(char * tst,Query_aux* tmpe){
    if(tmpe==NULL)return 1 ;
    else{
        switch (tmpe->Op->tOpComp) {
            case eq: break;
            case gt: {
                    if(tmpe->Op->argList->tArg==int_){
                        char *chst = (char*)malloc(strlen(tst)*sizeof(char));
                        char *best = NULL;
                        strcpy(chst,tmpe->nom);
                        strcat(chst,":");
                        int indi = strlen(chst);
                        char * sueno = strdup(tst);
                        if(strstr(sueno,chst)==NULL)return 0 ;
                        else {
                        best = strstr(sueno,chst);
                        strcat(chst,tmpe->Op->argList->argValue);
                        if(best[indi]<'0'|| best[indi]>'9' )return 0;
                        best[strlen(chst)+1]='\0';char c = best[strlen(chst)];
                        if(c>='0'&& c<='9')return 1;
                        else{
                            best[strlen(chst)]='\0';
                            if(strcmp(best,chst)==1)return 1 ;
                        }
                        }
                    }
                    else Error(OPINT_ERR);
                    }break;
            case gte:{
                    if(tmpe->Op->argList->tArg==int_){
                        char *chst = (char*)malloc(strlen(tst)*sizeof(char));
                        char *best = NULL;
                        strcpy(chst,tmpe->nom);
                        strcat(chst,":");
                        int indi = strlen(chst);
                        char * sueno = strdup(tst);
                        if(strstr(sueno,chst)==NULL)return 0 ;
                        else {
                        best = strstr(sueno,chst);
                        strcat(chst,tmpe->Op->argList->argValue);
                        if(best[indi]<'0'|| best[indi]>'9' )return 0;
                        best[strlen(chst)+1]='\0';char c = best[strlen(chst)];
                        if(c>='0'&& c<='9')return 1;
                        else{
                            best[strlen(chst)]='\0';
                            if(strcmp(best,chst)==1||strcmp(best,chst)==0)return 1 ;
                        }
                        }
                    }
                    else Error(OPINT_ERR);
                    } break;
            case lt: {
                    if(tmpe->Op->argList->tArg==int_){
                        char *chst = (char*)malloc(strlen(tst)*sizeof(char));
                        char *best = NULL;
                        strcpy(chst,tmpe->nom);
                        strcat(chst,":");
                        int indi = strlen(chst);
                        char * sueno = strdup(tst);
                        if(strstr(sueno,chst)==NULL)return 0 ;
                        else {
                        best = strstr(sueno,chst);
                        strcat(chst,tmpe->Op->argList->argValue);
                        if(best[indi]<'0'|| best[indi]>'9' )return 0;
                        best[strlen(chst)+1]='\0';char c = best[strlen(chst)];
                        if(c>='0'&& c<='9')return 0;
                        else{
                            best[strlen(chst)]='\0';
                            if(strcmp(best,chst)==-1)return 1 ;
                        }
                        }
                    }
                    else Error(OPINT_ERR);
                    } break;
            case lte: {
                    if(tmpe->Op->argList->tArg==int_){
                        char *chst = (char*)malloc(strlen(tst)*sizeof(char));
                        char *best = NULL;
                        strcpy(chst,tmpe->nom);
                        strcat(chst,":");
                        int indi = strlen(chst);
                        char * sueno = strdup(tst);
                        if(strstr(sueno,chst)==NULL)return 0 ;
                        else {
                        best = strstr(sueno,chst);
                        strcat(chst,tmpe->Op->argList->argValue);
                        if(best[indi]<'0'|| best[indi]>'9' )return 0;
                        best[strlen(chst)+1]='\0';char c = best[strlen(chst)];
                        if(c>='0'&& c<='9')return 0;
                        else{
                            best[strlen(chst)]='\0';
                            if(strcmp(best,chst)==-1||strcmp(best,chst)==0)return 1 ;
                        }
                        }
                    }
                    else Error(OPINT_ERR);
                    } break;
            default: {
                char * tests = (char*)malloc(strlen(tst)*sizeof(char));
                strcpy(tests,tmpe->nom);
                strcat(tests,":");
                if(tmpe->Op->argList->tArg==string_)strcat(tests,"\"");
                strcat(tests,tmpe->Op->argList->argValue);
                if(tmpe->Op->argList->tArg==string_)strcat(tests,"\"");
                if(strstr(tst,tests))return 1;
            } break;
        }
    }
return 0;
}
