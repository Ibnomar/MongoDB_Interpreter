
 typedef struct  String{
    char * string = malloc(40*sizeof(char));
    struct String * suivant;
}String;

typedef String* list_String;

 void PAIRE(){
    //Paire : string : Valeur
    Test_Symbole(STRING_TOKEN,STRING_ERR);
    if(rechercher(list,sym_cour.nom)==0)
    ajouter_string(list,sym_cour.nom);
    else printf("Erreur doublon");
    Test_Symbole(DEUXP_TOKEN,DEUXP_ERR);
    VALEUR();
            }

list_String ajouter_string(list_String liste, char *mot){
    String* nv_str = malloc(sizeof(String));
    strcpy(nv_str->string,mot);
    nv_str->suivant=null;
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

int rechercher(list_String liste ,char * str){
    if(liste == NULL) return 0;
    String* tmp = liste;
    while(tmp->suivant != NULL){
    if(strcmp(tmp->string,str)== 0 ) return 1;
    else tmp = tmp->suivant;
    }

return 0;
}

