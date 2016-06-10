#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>  
#include <string.h>
#include "utile.h"

char* getNomFichier(char* collection)
{
	char* fichier;
	copier_chaine(&fichier,"Database/");
	concatener_chaine(&fichier,collection);
	return fichier;
}

void drop(char* collection)
{
        if(remove(getNomFichier(collection))==0)
        {
            printf("\nsuppression de la collection reussie");
        }else
        {
            printf("\nsuppression de la collection echouee ");
        }
}

void renamecol(char* old,char* new)
{
	char* of=getNomFichier(old);
	char* nf=getNomFichier(new);
	
	if(rename(of,nf)==0)
	{
	    printf("\nrenomination reussie");
        }else
        {
            printf("\nrenomination echouee");
        }
}


 
void getcolnames() 
{ 
   DIR *rep=opendir("Database"); 
   if(rep!=NULL) 
   { 
      struct dirent *lecture; 
      while((lecture=readdir(rep))!=NULL) 
      { 
         if(lecture->d_name!="."||lecture->d_name!="..") 	
 	 	printf("\n%s",lecture->d_name);
      } 
      closedir(rep);
      rep=NULL; 
   }
} 
