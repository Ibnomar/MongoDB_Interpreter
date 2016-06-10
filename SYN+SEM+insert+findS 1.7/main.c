#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include "find.h"
#include "interpreter.h"

typedef enum {
DB_TOKEN, FIND_TOKEN, INSERT_TOKEN, UPDATE_TOKEN,  STRING_TOKEN,NUM_TOKEN,  TRUE_TOKEN,
 FALSE_TOKEN, NULL_TOKEN, ACO_TOKEN, ACF_TOKEN, MO_TOKEN, MF_TOKEN, DEUXP_TOKEN, VIRG_TOKEN, POINT_TOKEN, ERREUR_TOKEN,
 PARO_TOKEN, PARF_TOKEN, IDF_TOKEN, EQ_TOKEN, GTE_TOKEN, GT_TOKEN, LTE_TOKEN, LT_TOKEN, NE_TOKEN, NOT_TOKEN, EXISTS_TOKEN,
 IN_TOKEN, NIN_TOKEN, AND_TOKEN, OR_TOKEN, NOR_TOKEN, FIN_TOKEN , REMOVE_TOKEN, GLL_TOKEN
             } CODES_LEX;



typedef struct Erreur {
    Erreurs CODE_ERR;
    char message[40];
                      }Erreur;

typedef struct Tsym_cour{
              CODES_LEX code;
              char nom[20];
                        }Tsym_cour;

 typedef struct  String{
    char string [20];
    struct String * suivant;
}String;

typedef String* list_String;

Query * qu;
Query_aux * qux;
char car_cour;
Tsym_cour sym_cour;
int test = 0 ;
int ER=0;
FILE *file=NULL;
list_String liste = NULL;
char* collection=NULL;
char * liste_membres=NULL;
//Erreur MES_ERR[200]={{,""}};

int i,a=0,n=1;

list_String ajouter_string(list_String liste, char mot[]){
    String* nv_str = malloc(sizeof(String));
    strcpy(nv_str->string,mot);
    nv_str->suivant=NULL;
   if(liste == NULL) return nv_str;
   else {String* tmp = liste;
   while(tmp->suivant != NULL )
   {
       tmp = tmp ->suivant;
   }
   tmp->suivant = nv_str;
   return liste;
   }
}

int rechercher(list_String liste ,char str[]){
    if(liste == NULL) {return 0;}
    String* tmp = liste;
    while(tmp != NULL){
    if(strcmp(tmp->string,str)== 0 ) return 1;
    else tmp = tmp->suivant;
    }

return 0;
}

CODES_LEX COD_CAR_SPE [100]= {{DB_TOKEN,"db"},{FIND_TOKEN,"find"},{INSERT_TOKEN,"insert"},
{UPDATE_TOKEN,"update"},{STRING_TOKEN,"string"},{FALSE_TOKEN,"false"},
{TRUE_TOKEN,"true"},{NULL_TOKEN,"null"},{ACO_TOKEN,"{"},{ACF_TOKEN,"}"},{MO_TOKEN,"["},{MF_TOKEN,"]"},
{DEUXP_TOKEN,":"},{VIRG_TOKEN,","},{POINT_TOKEN,"."},{PARO_TOKEN,"("},{PARF_TOKEN,")"},{EQ_TOKEN,"="},
{GTE_TOKEN,"$gte"},{GT_TOKEN,"$gt"},{LTE_TOKEN,"$lte"},{LT_TOKEN,"$lt"},{NE_TOKEN,"$ne"},
{NOT_TOKEN,"$not"},{EXISTS_TOKEN,"$exists"},{IN_TOKEN,"$in"},{NIN_TOKEN,"$nin"},{AND_TOKEN,"$and"},
{OR_TOKEN,"$or"},{NOR_TOKEN,"$nor"},{GLL_TOKEN,"\""}
};

void Error(Erreurs COD_ERR){
ER++;
if(ER==1){printf("Ligne: %d - \"%s\"\t",n,sym_cour.nom);
switch(COD_ERR){
    case OPINT_ERR : printf("Erreur : Argument de l'operateur different de int \n");break;
    case DOUBLE_ERR : printf("Erreur : Doublon trouve \n");break;
    case QAUX5_ERR : printf("Erreur : ',' ou '}' manquante \n");break;
    case QAUX3_ERR : printf("Erreur : ',' ou ']' manquante \n");break;
    case Q_ERR : printf("Erreur : Valeur invalide ou '{' manquante \n");break;
    case EXISTS_ERR : printf("Erreur : Expression exist invalide \n");break;
    case MO_ERR : printf("Erreur : ' [ ' non trouve \n");break;
    case QUERY_COMPARAISON_ERR: printf("Erreur : Expression de comparaison invalide \n");break;
    case PAIRE_AUX_ERR : printf("Erreur : Verifier la syntaxe des paires \n");break;
    case TABLEAU_ERR : printf("Erreur : Tableau invalide \n");break;
    case MF_ERR : printf("Erreur : ' ] ' non trouve \n");break;
    case QUERY_LOGICAL_ERR : printf("Erreur : Requete logique invalide \n");break;
    case QAUX3VIRG_ERR : printf("Erreur : Valeur invalide ou '{' manquante \n");break;
    case VALEUR_AUX_ERR : printf("Erreur : Verifier la fin de la requete ' , ou ] ' \n");break;
    case QAUX_IN_ERR : printf("Erreur : Valeur invalide ou } manquante \n");break;
    case QAUX_ERR : printf("Erreur : Verifier la fin de la requete ' , ou } ' \n");break;
    case LISTE_QUERYAUX_ERR : printf("Erreur :  Liste des requetes invalide ! Attention à la virgule\n");break;
    case QUERYAUX_ERR : printf("Erreur : Requete invalide  \n");break;
    case QUERY_ERR : printf("Erreur : Requete invalide\n");break;
    case VALEUR_ERR : printf("Erreur : Valeur invalide \n");break;
    case ACF_ERR : printf("Erreur : ' } ' non trouvé \n");break;
    case STRING_ERR : printf("Erreur : Identifiant non trouve \n");break;
    case DEUXP_ERR : printf("Erreur : ' : ' non trouvé \n");break;
    case VIRG_ERR : printf("Erreur : ' , ' non trouvé \n");break;
    case ACO_ERR : printf("Erreur : ' { ' non trouvé \n");break;
    case PARF_ERR : printf("Erreur : ' ) ' non trouvé \n");break;
    case PARO_ERR : printf("Erreur : ' ( ' non trouvé \n");break;
    case INST_ERR : printf("Erreur : Début d'instruction \n");break;
    case POINT_ERR : printf("Erreur : Point non trouvé \n");break;
    case DB_ERR : printf("Erreur : 'db' non trouvé \n");break;
    case GLL_ERR : printf("Erreur : requete invalide \n");break;
    default : printf("Erreur : ERREUR NON SYNTAXIQUE\n\t\t\t   \n");break;
               }
         }
                          }

void cmp_mot(){
        if ( !strcmp(sym_cour.nom,"db") ){ sym_cour.code=DB_TOKEN;
        }
 else       if ( !strcmp(sym_cour.nom,"find")  ) { sym_cour.code=FIND_TOKEN;
                }
 else       if ( !strcmp(sym_cour.nom,"insert")  ) { sym_cour.code=INSERT_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"update") ) { sym_cour.code=UPDATE_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"remove") ) { sym_cour.code=REMOVE_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"true") ) { sym_cour.code=TRUE_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"false") ) { sym_cour.code=FALSE_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"null") ) { sym_cour.code=NULL_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"{") ) { sym_cour.code=ACO_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"}") ) { sym_cour.code=ACF_TOKEN;
 }
else       if ( !strcmp(sym_cour.nom,"[") ) { sym_cour.code=MO_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"]") ) { sym_cour.code=MF_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,":") ) { sym_cour.code=DEUXP_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,",") ) { sym_cour.code=VIRG_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"(") ) { sym_cour.code=PARO_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,")") ) { sym_cour.code=PARF_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"$eq") ) { sym_cour.code=EQ_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"$gte") ) { sym_cour.code=GTE_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"$gt") ) { sym_cour.code=GT_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"$lte") ) { sym_cour.code=LTE_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"$lt") ) { sym_cour.code=LT_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"$ne") ) { sym_cour.code=NE_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"$not") ) { sym_cour.code=NOT_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"$exists") ) { sym_cour.code=EXISTS_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"$in") ) { sym_cour.code=IN_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"$nin") ) { sym_cour.code=NIN_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"$and") ) { sym_cour.code=AND_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"$or") ) { sym_cour.code=OR_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"$nor") ) { sym_cour.code=NOR_TOKEN;
 }
 else       if ( !strcmp(sym_cour.nom,"\"") ) { sym_cour.code=GLL_TOKEN;
 }
 else {sym_cour.code=STRING_TOKEN;

      }
    }


void lire_car(){
car_cour=fgetc(file);
}

void lire_mot(){
int a=0;
if(car_cour=='$'){
    sym_cour.nom[a]=car_cour;lire_car();
    a++;
}
while(a<20){
if(isalpha(car_cour)||isdigit(car_cour)){
            sym_cour.nom[a]= car_cour;
            lire_car();}
else{
sym_cour.nom[a]='\0';return;
}
a++;
}
i=a;
}

void lire_num(){
int a=0;
while(a<20){
if(isdigit(car_cour)){
            sym_cour.nom[a]= car_cour;
            lire_car();}
else{
sym_cour.nom[a]='\0';return;
}
a++;
}
i=a;
}

void sym_suiv(){

    int c=0;
    while(car_cour==' ' || car_cour=='\t' || car_cour=='\n'){
                if(car_cour=='\n')n++;lire_car();
                                                            }
    while(c<20){sym_cour.nom[c]='\0';c++;}

    if( isalpha(car_cour) || car_cour == '$' ) {
        lire_mot();
        cmp_mot();
        return;
                          }

    else {
       if(isdigit(car_cour)){
        lire_num();
        sym_cour.code=NUM_TOKEN;
        return;
                            }

       else{
    switch(car_cour) {
        case ':': sym_cour.nom[0]=car_cour;sym_cour.nom[1]='\0';sym_cour.code=DEUXP_TOKEN; lire_car();break;
        case '{': sym_cour.nom[0]=car_cour;sym_cour.nom[1]='\0';sym_cour.code=ACO_TOKEN; lire_car();break;
        case '}': sym_cour.nom[0]=car_cour;sym_cour.nom[1]='\0';sym_cour.code=ACF_TOKEN; lire_car();break;
        case '[': sym_cour.nom[0]=car_cour;sym_cour.nom[1]='\0';sym_cour.code=MO_TOKEN; lire_car();break;
        case ']': sym_cour.nom[0]=car_cour;sym_cour.nom[1]='\0';sym_cour.code=MF_TOKEN; lire_car();break;
        case ',':sym_cour.nom[0]=car_cour;sym_cour.nom[1]='\0';sym_cour.code=VIRG_TOKEN; lire_car();break;
        case '.':sym_cour.nom[0]=car_cour;sym_cour.nom[1]='\0';sym_cour.code=POINT_TOKEN; lire_car();break;
        case '(':sym_cour.nom[0]=car_cour;sym_cour.nom[1]='\0';sym_cour.code=PARO_TOKEN; lire_car();break;
        case ')':sym_cour.nom[0]=car_cour;sym_cour.nom[1]='\0';sym_cour.code=PARF_TOKEN; lire_car();break;
        case '"':sym_cour.nom[0]=car_cour;sym_cour.nom[1]='\0';sym_cour.code=GLL_TOKEN; lire_car();break;
        case EOF: sym_cour.code=FIN_TOKEN; lire_car(); break;
        default : sym_cour.nom[0]=car_cour;sym_cour.nom[1]='\0';sym_cour.code=ERREUR_TOKEN;lire_car(); break;
        }
    }
}
}
void open_file(char const* cible){

file=fopen(cible,"r");
if (file==NULL)
 {printf("Erreur : Fichier introuvable!\n");}
else
{a=1;
printf("\n");
  }
  }

void Test_Symbole(CODES_LEX cl, Erreurs CODE_ERR){


if (sym_cour.code == cl)  {
        sym_suiv();
}
else  { Error(CODE_ERR);sym_suiv();}
}
void QUERY(){

    //query-----------------> { queryAux } | epsilon
    // Follow (query) = {',',']'}
    switch (sym_cour.code){
         case ACO_TOKEN : sym_suiv(); QUERYAUX();Test_Symbole(ACF_TOKEN,ACF_ERR);break;
         case VIRG_TOKEN : break;
         case MF_TOKEN : break;
         case PARF_TOKEN : break;
         default : Error(QUERY_ERR);  break;
                          }

            }
void QUERYAUX(){
//queryAux -------------> string : Q QAux | query_logical : [ list_query] QAux | epsilon
//Follow (queryaux) = {'}'}
             switch (sym_cour.code){
                 case STRING_TOKEN : if(qu==NULL)qu=creer_Query(autres);
                                    char * tst = (char*)malloc(20*sizeof(char));
                                    strcpy(tst,sym_cour.nom);
                                    qux = creerQueryAux(tst);
                                    ajouterQuery(qu,qux);

                                    sym_suiv();Test_Symbole(DEUXP_TOKEN,DEUXP_ERR);Q();QAUX();

                                    break;
                 case OR_TOKEN     :   if(qu==NULL)qu=creer_Query(or_);
                                    QUERY_LOGICAL();
                                     Test_Symbole(DEUXP_TOKEN,DEUXP_ERR);
                                     Test_Symbole(MO_TOKEN,ACO_ERR);
                                     LISTE_QUERY();
                                     Test_Symbole(MF_TOKEN,ACF_ERR);
                                     QAUX();break;
                case AND_TOKEN     : QUERY_LOGICAL();
                                        if(qu==NULL)qu=creer_Query(and_);
                                     Test_Symbole(DEUXP_TOKEN,DEUXP_ERR);
                                     Test_Symbole(MO_TOKEN,ACO_ERR);
                                     LISTE_QUERY();
                                     Test_Symbole(MF_TOKEN,ACF_ERR);
                                     QAUX();break;
                case NOR_TOKEN     : if(qu==NULL)qu=creer_Query(nor_);
                                    QUERY_LOGICAL();
                                     Test_Symbole(DEUXP_TOKEN,DEUXP_ERR);
                                     Test_Symbole(MO_TOKEN,ACO_ERR);
                                     LISTE_QUERY();
                                     Test_Symbole(MF_TOKEN,ACF_ERR);
                                     QAUX();break;
               case ACF_TOKEN      : break;
               default : Error(QUERYAUX_ERR);  break;
                                     }
               }
void QAUX(){
    //QAux -----------------> ,queryAux | epsilon
    //Follow (QAux) ={'}'}
    switch(sym_cour.code){
    case VIRG_TOKEN :  test=1;sym_suiv();QUERYAUX();break;
    case ACF_TOKEN : break;
    default : Error(QAUX_ERR);  break;

                         }
           }
void LISTE_QUERYAUX(){
    //liste_queryAux -------> ,list-query | epsilon
    //Follow (liste_queryAux) = {']'}
    switch (sym_cour.code){
        case VIRG_TOKEN :LISTE_QUERY();break;
        case MF_TOKEN : break;
        default : Error(LISTE_QUERYAUX_ERR);  break;
                          }
                     }
void QAUX4(){
    //QAux4----------------->  QAux2 Qaux5 | Membres | epsilon

//                        | $exists : true | false
//                        | $in : [ quaux_in ]
//                        | $not : {query-comparaison : valeur}
//Follow (QAux4) = {'}'}
switch (sym_cour.code){
    case  NOT_TOKEN : sym_suiv(); Test_Symbole(DEUXP_TOKEN,DEUXP_ERR);
                    Test_Symbole(ACO_TOKEN,ACO_ERR);QUERY_COMPARAISON();
                    Test_Symbole(DEUXP_TOKEN,DEUXP_ERR);
                    VALEUR();
                    Test_Symbole(ACF_TOKEN,ACF_ERR);break;
    case IN_TOKEN : sym_suiv(); Test_Symbole(DEUXP_TOKEN,DEUXP_ERR);Test_Symbole(MO_TOKEN,MO_ERR); QAUX_IN();
                     Test_Symbole(MF_TOKEN,MF_ERR);break;
    case EXISTS_TOKEN : sym_suiv(); Test_Symbole(DEUXP_TOKEN,DEUXP_ERR);sym_suiv();
         switch (sym_cour.code){
             case TRUE_TOKEN : break;
             case FALSE_TOKEN : break;
             default : Error(EXISTS_ERR);
                               }

    case ACF_TOKEN : break; // QAux2 Qaux5 | Membres | epsilon
    case EQ_TOKEN : QAUX2();QAUX5();break;
    case GT_TOKEN : QAUX2();QAUX5();break;
    case GTE_TOKEN : QAUX2();QAUX5();break;
    case LT_TOKEN : QAUX2();QAUX5();break;
    case LTE_TOKEN : QAUX2();QAUX5();break;
    case NE_TOKEN : QAUX2();QAUX5();break;
    case STRING_TOKEN : MEMBRES();

                      }

}
void Q(){
    //Q---------------------> { QAux4 }| valeur
    switch (sym_cour.code){
          case ACO_TOKEN : sym_suiv(); QAUX4(); Test_Symbole(ACF_TOKEN,ACF_ERR);break;
          case GLL_TOKEN : {sym_suiv();
                                if(qu!=NULL){
                                    qu->qAux->Op=(Operation*)malloc(sizeof(Operation));
                                    qu->qAux->Op->argList=(Argument*)malloc(sizeof(Argument));
                                    qu->qAux->Op->tOpComp=autr;
                                    qu->qAux->Op->suivant=NULL;
                                    qu->qAux->Op->argList->suivant=NULL;
                                    qu->qAux->Op->argList->tArg=string_;
                                    qu->qAux->Op->argList->argValue=strdup(sym_cour.nom);
                                }
                                Test_Symbole(STRING_TOKEN,STRING_ERR);
                                Test_Symbole(GLL_TOKEN,GLL_ERR);
                                }  break;
          case NUM_TOKEN :{
                                if(qu!=NULL){
                                    qu->qAux->Op=(Operation*)malloc(sizeof(Operation));
                                    qu->qAux->Op->argList=(Argument*)malloc(sizeof(Argument));
                                    qu->qAux->Op->tOpComp=autr;
                                    qu->qAux->Op->suivant=NULL;
                                    qu->qAux->Op->argList->suivant=NULL;
                                    qu->qAux->Op->argList->tArg=int_;
                                    qu->qAux->Op->argList->argValue=strdup(sym_cour.nom);
                                }
                                } sym_suiv(); break;
          case MO_TOKEN : sym_suiv(); break;
          case TRUE_TOKEN : {
                                if(qu!=NULL){
                                    qu->qAux->Op=(Operation*)malloc(sizeof(Operation));
                                    qu->qAux->Op->argList=(Argument*)malloc(sizeof(Argument));
                                    qu->qAux->Op->tOpComp=autr;
                                    qu->qAux->Op->suivant=NULL;
                                    qu->qAux->Op->argList->suivant=NULL;
                                    qu->qAux->Op->argList->tArg=true_;
                                    qu->qAux->Op->argList->argValue=strdup(sym_cour.nom);
                                }
                                }  sym_suiv(); break;
          case FALSE_TOKEN : {
                                if(qu!=NULL){
                                    qu->qAux->Op=(Operation*)malloc(sizeof(Operation));
                                    qu->qAux->Op->argList=(Argument*)malloc(sizeof(Argument));
                                    qu->qAux->Op->tOpComp=autr;
                                    qu->qAux->Op->suivant=NULL;
                                    qu->qAux->Op->argList->suivant=NULL;
                                    qu->qAux->Op->argList->tArg=false_;
                                    qu->qAux->Op->argList->argValue=strdup(sym_cour.nom);
                                }
                                }  sym_suiv(); break;
          case NULL_TOKEN : {
                                if(qu!=NULL){
                                    qu->qAux->Op=(Operation*)malloc(sizeof(Operation));
                                    qu->qAux->Op->argList=(Argument*)malloc(sizeof(Argument));
                                    qu->qAux->Op->tOpComp=autr;
                                    qu->qAux->Op->suivant=NULL;
                                    qu->qAux->Op->argList->suivant=NULL;
                                    qu->qAux->Op->argList->tArg=null;
                                    qu->qAux->Op->argList->argValue=strdup(sym_cour.nom);
                                }
                                } sym_suiv(); break;
          default : Error(Q_ERR);
                          }
        }
void QAUX5(){
    //QAux5----------------->,QAux2 Qaux5 | epsilon
    //Follow (qaux5) = {'}'}
    switch (sym_cour.code){
        case VIRG_TOKEN: QAUX2();QAUX5();break;
        case ACF_TOKEN : break;
        default : Error(QAUX5_ERR);
                          }
            }
void QAUX3(){
    //QAux3 ----------------> ,qaux3virg | epsilon
    // Follow (QAux3) = {']'}
switch(sym_cour.code){
    case VIRG_TOKEN : QAUX3VIRG(); break;
    case MF_TOKEN : break;
    default : Error(QAUX3_ERR);
                     }
}
void QUERY_COMPARAISON(){
//query_comparaison ------> $eq| $gt| $gte| $lt| $lte| $ne

                                   // qu->qAux->Op->argList->tArg=string_;
                                  //  qu->qAux->Op->argList->argValue=strdup(sym_cour.nom);
switch (sym_cour.code){
    case EQ_TOKEN : if(qu!=NULL){
                                    qu->qAux->Op=(Operation*)malloc(sizeof(Operation));
                                    qu->qAux->Op->argList=(Argument*)malloc(sizeof(Argument));
                                    qu->qAux->Op->tOpComp=eq;
                                    qu->qAux->Op->suivant=NULL;
                                    qu->qAux->Op->argList->suivant=NULL;
                                }sym_suiv();break;
    case GT_TOKEN : if(qu!=NULL){
                                    qu->qAux->Op=(Operation*)malloc(sizeof(Operation));
                                    qu->qAux->Op->argList=(Argument*)malloc(sizeof(Argument));
                                    qu->qAux->Op->tOpComp=gt;
                                    qu->qAux->Op->suivant=NULL;
                                    qu->qAux->Op->argList->suivant=NULL;
                                }sym_suiv();break;
    case GTE_TOKEN : if(qu!=NULL){
                                    qu->qAux->Op=(Operation*)malloc(sizeof(Operation));
                                    qu->qAux->Op->argList=(Argument*)malloc(sizeof(Argument));
                                    qu->qAux->Op->tOpComp=gte;
                                    qu->qAux->Op->suivant=NULL;
                                    qu->qAux->Op->argList->suivant=NULL;
                                }sym_suiv();break;
    case LT_TOKEN :if(qu!=NULL){
                                    qu->qAux->Op=(Operation*)malloc(sizeof(Operation));
                                    qu->qAux->Op->argList=(Argument*)malloc(sizeof(Argument));
                                    qu->qAux->Op->tOpComp=lt;
                                    qu->qAux->Op->suivant=NULL;
                                    qu->qAux->Op->argList->suivant=NULL;
                                } sym_suiv(); break;
    case LTE_TOKEN :if(qu!=NULL){
                                    qu->qAux->Op=(Operation*)malloc(sizeof(Operation));
                                    qu->qAux->Op->argList=(Argument*)malloc(sizeof(Argument));
                                    qu->qAux->Op->tOpComp=lte;
                                    qu->qAux->Op->suivant=NULL;
                                    qu->qAux->Op->argList->suivant=NULL;
                                } sym_suiv();break;
    case NE_TOKEN : if(qu!=NULL){
                                    qu->qAux->Op=(Operation*)malloc(sizeof(Operation));
                                    qu->qAux->Op->argList=(Argument*)malloc(sizeof(Argument));
                                    qu->qAux->Op->tOpComp=ne;
                                    qu->qAux->Op->suivant=NULL;
                                    qu->qAux->Op->argList->suivant=NULL;
                                }sym_suiv();break;
    default : Error(QUERY_COMPARAISON_ERR);
                      }
                        }
void TABLEAU(){
    switch(sym_cour.code){
        //Tableau : [ ] | [ Elements ]
        case MO_TOKEN: sym_suiv();
                switch(sym_cour.code){
                    case MF_TOKEN: if(liste_membres!=NULL)strcat(liste_membres,sym_cour.nom);sym_suiv();break ;
                    case GLL_TOKEN :   ELEMENTS();if(liste_membres!=NULL)strcat(liste_membres,sym_cour.nom);Test_Symbole(MF_TOKEN,MF_ERR);break;
                    case NUM_TOKEN : ELEMENTS();if(liste_membres!=NULL)strcat(liste_membres,sym_cour.nom);Test_Symbole(MF_TOKEN,MF_ERR);break;
                    case MO_TOKEN :  ELEMENTS();if(liste_membres!=NULL)strcat(liste_membres,sym_cour.nom);Test_Symbole(MF_TOKEN,MF_ERR);break;
                    case TRUE_TOKEN :  ELEMENTS();if(liste_membres!=NULL)strcat(liste_membres,sym_cour.nom);Test_Symbole(MF_TOKEN,MF_ERR);break;
                    case FALSE_TOKEN :  ELEMENTS();if(liste_membres!=NULL)strcat(liste_membres,sym_cour.nom);Test_Symbole(MF_TOKEN,MF_ERR);break;
                    case NULL_TOKEN :  ELEMENTS();if(liste_membres!=NULL)strcat(liste_membres,sym_cour.nom);Test_Symbole(MF_TOKEN,MF_ERR);break;
                    default : Error(TABLEAU_ERR);
                                     }break;
        default : Error(TABLEAU_ERR);
                         }
              }
void PAIRE_AUX(){
  //  Paire_Aux : , Membres | epsilon
    //Follow (Paire_Aux) = { '}' }
    switch(sym_cour.code){
        case VIRG_TOKEN: sym_suiv();if(liste_membres!=NULL)strcat(liste_membres,",");MEMBRES();break;
        case ACF_TOKEN: break;
        default: Error(PAIRE_AUX_ERR);break;
                         }
                }
void QUERY_LOGICAL(){
    //query_logical ----------> $or | $and | $nor
    switch(sym_cour.code){
        case OR_TOKEN : sym_suiv();break;
        case AND_TOKEN : sym_suiv();break;
        case NOR_TOKEN : sym_suiv();break;
        default : Error(QUERY_LOGICAL_ERR);
                         }
                    }
void QAUX3VIRG(){
    //qaux3virg ------------> valeur QAux3 | {Membres} QAux3
    switch(sym_cour.code){
                case STRING_TOKEN :  sym_suiv();VALEUR();QAUX3();break;
                case NUM_TOKEN :  sym_suiv();VALEUR();QAUX3();break;
                case MO_TOKEN :  TABLEAU();VALEUR();QAUX3();break;
                case TRUE_TOKEN :  sym_suiv();VALEUR();QAUX3();break;
                case FALSE_TOKEN :  sym_suiv();VALEUR();QAUX3();break;
                case NULL_TOKEN :  sym_suiv();VALEUR();QAUX3();break;
                case ACO_TOKEN : sym_suiv(); MEMBRES();
                 Test_Symbole(ACF_TOKEN,ACF_ERR); QAUX3();break;
                default:  Error(QAUX3VIRG_ERR)  ;break;
                         }
                 }
void VALEUR_AUX(){
      //Valeur_Aux : , Elements | epsilon
    // Follow (Valeur_Aux)={ ']' }
    switch (sym_cour.code){
        case VIRG_TOKEN : if(liste_membres!=NULL)strcat(liste_membres,sym_cour.nom); sym_suiv(); ELEMENTS(); break;
        case MF_TOKEN : break;
        default : Error(VALEUR_AUX_ERR);
                          }
                 }
void QAUX_IN(){
    //quaux_in--------------> valeur QAux3 | {Membres} QAux3
    switch(sym_cour.code){
                case STRING_TOKEN : sym_suiv(); VALEUR();QAUX3();break;
                case NUM_TOKEN : sym_suiv(); VALEUR();QAUX3();break;
                case MO_TOKEN : sym_suiv(); VALEUR();QAUX3();break;
                case TRUE_TOKEN : sym_suiv(); VALEUR();QAUX3();break;
                case FALSE_TOKEN : sym_suiv(); VALEUR();QAUX3();break;
                case NULL_TOKEN : sym_suiv();VALEUR();QAUX3();break;
                case ACF_TOKEN : sym_suiv();MEMBRES(); Test_Symbole(ACO_TOKEN,ACO_ERR);QAUX3();break;
                default : Error(QAUX_IN_ERR);
                         }
              }
void QAUX2(){
//QAux2 ----------------> query_comparaison : valeur
QUERY_COMPARAISON();
Test_Symbole(DEUXP_TOKEN,DEUXP_ERR);
VALEUR();
            }
void VALEUR(){
    // Valeur : string|num|tableau|true|false|null
    if(liste_membres!=NULL)strcat(liste_membres,sym_cour.nom);
switch   (sym_cour.code) {
                case GLL_TOKEN :   sym_suiv();if(qu!=NULL){qu->qAux->Op->argList->tArg=string_;
                                   qu->qAux->Op->argList->argValue=strdup(sym_cour.nom);}
                                   if(liste_membres!=NULL)strcat(liste_membres,sym_cour.nom);Test_Symbole(STRING_TOKEN,STRING_ERR);
                                    if(liste_membres!=NULL)strcat(liste_membres,sym_cour.nom); Test_Symbole(GLL_TOKEN,GLL_ERR);
                                   break;
                case NUM_TOKEN : if(qu!=NULL){qu->qAux->Op->argList->tArg=int_;
                                   qu->qAux->Op->argList->argValue=strdup(sym_cour.nom);} sym_suiv();break;
                case MO_TOKEN :  TABLEAU();break;
                case TRUE_TOKEN :  sym_suiv();break;
                case FALSE_TOKEN : if(qu!=NULL){qu->qAux->Op->argList->tArg=false_;
                                   qu->qAux->Op->argList->argValue=strdup(sym_cour.nom);} sym_suiv();break;
                case NULL_TOKEN :  if(qu!=NULL){qu->qAux->Op->argList->tArg=null;
                                   qu->qAux->Op->argList->argValue=strdup(sym_cour.nom);}sym_suiv();break;
                default:  Error(VALEUR_ERR) ; break;     }
             }
void MEMBRES (){
    //Membres : Paire Paire_Aux
    PAIRE();
    PAIRE_AUX();
               }
void PAIRE(){
    //Paire : string : Valeur
    if(liste_membres!=NULL){
    strcat(liste_membres,sym_cour.nom);
    strcat(liste_membres,":");}
    if(rechercher(liste,sym_cour.nom)==0){
    liste = ajouter_string(liste,sym_cour.nom);}
    else Error(DOUBLE_ERR);
    Test_Symbole(STRING_TOKEN,STRING_ERR);
    Test_Symbole(DEUXP_TOKEN,DEUXP_ERR);
    VALEUR();
            }
void ELEMENTS(){
     //Elements : Valeur Valeur_Aux
              VALEUR();
              VALEUR_AUX();
               }
void UPDATE(){

//Update :DB.string.UPDATE(query,{Membres})

QUERY();
Test_Symbole(VIRG_TOKEN,VIRG_ERR);
Test_Symbole(ACO_TOKEN,ACO_ERR);
liste = NULL;
MEMBRES();
Test_Symbole(ACF_TOKEN,ACF_ERR);
}

void REMOVE(){
//remove : DB . string . REMOVE (query)
    QUERY();
}
void LISTE_QUERY(){
    //liste_query ----------> query liste_queryAux
    QUERY();
    LISTE_QUERYAUX();
                  }
//insts : inst instsaux
void insts (){
inst();
instaux();
}

//instsaux : insts | epsilon
void instaux(){
    switch(sym_cour.code){
        case DB_TOKEN : insts(); break;
        case FIN_TOKEN : sym_suiv(); break;
    default : Error(INST_ERR) ; break;

    }
}
//inst : db . string . instaux
void FIND(){
char * chemin = (char*)malloc(1024*sizeof(char));
strcpy(chemin,"C://db/");
strcat(chemin,collection);
QUERY();
//afficherTop(qu);
interpreter_find(chemin,qu);
afficherTop(qu);
}

void inst(){
collection=(char*)malloc(1024*sizeof(char));
Test_Symbole(DB_TOKEN,DB_ERR);
Test_Symbole(POINT_TOKEN,POINT_ERR);
strcpy(collection,sym_cour.nom);
strcat(collection,".txt");
Test_Symbole(STRING_TOKEN,STRING_ERR);
Test_Symbole(POINT_TOKEN,POINT_ERR);
    switch(sym_cour.code){
        case FIND_TOKEN : sym_suiv(); Test_Symbole(PARO_TOKEN,PARO_ERR);FIND();break;
        case UPDATE_TOKEN : sym_suiv(); Test_Symbole(PARO_TOKEN,PARO_ERR);UPDATE();break;
        case INSERT_TOKEN :sym_suiv(); Test_Symbole(PARO_TOKEN,PARO_ERR);INSERT();break;
        case REMOVE_TOKEN :sym_suiv(); Test_Symbole(PARO_TOKEN,PARO_ERR);REMOVE();break;
        default :  Error(INST_ERR) ; break;
    }
Test_Symbole(PARF_TOKEN,PARF_ERR);
}


void interpreter_insert(){
    if(ER==0){
char * chemin = (char*)malloc(1024*sizeof(char));
strcpy(chemin,"C://db/");
strcat(chemin,collection);
FILE* fichier = fopen(chemin,"a");
fwrite(liste_membres,sizeof(char),strlen(liste_membres),fichier);
close(fichier);}
}

void INSERT(){
 //Insert : DB . string . INSERT ({Membres})
Test_Symbole(ACO_TOKEN,ACO_ERR);
liste = NULL;
liste_membres = (char*)malloc(1024*sizeof(char));
strcpy(liste_membres,"{");
MEMBRES();
String* tmp = liste;
strcat(liste_membres,"}\n");
Test_Symbole(ACF_TOKEN,ACF_ERR);
interpreter_insert();
             }


int main(int argc,char** argv){
open_file("Test.txt");
car_cour=getc(file);
sym_suiv();
insts();
    return 0;
}


