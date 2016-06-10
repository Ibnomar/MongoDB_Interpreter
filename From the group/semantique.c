


									/*

									Auteur : Adil AOURCHANE
									Année  : 2012-2013
									Sujet : Analyseur Lexical, Syntaxique, et Sémantique du Langage Zz

									*/




#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "analyseur_syn.h"

#define size 10

//**********************************Declarartions*****************************************
	int initErr=0;
	int initDecl=0;
	int initInst=0;
	int ligneDecl;
	int ligneInst;

	int plus=2;  //une valeur != 0 

	//chaines stockant IDF
	char mavar[10];
	char mavar2[10];
	char mavar3[10];
	char mavar4[10];

	boolean existeDeja=false;
	boolean idfEg=true,idfEgEg=true;
	boolean follow_token=false;
//***************************************************************************************



//******************************Prototypes de Fonctions de l'Analyseur Syntaxique*****************************************
boolean LISTE_DECL_AUX();
boolean LISTE_DECL();
boolean LISTE_INST();
boolean LISTE_INSTAUX();
boolean INST();
boolean IF_INSTAUX();
boolean DECL();
boolean DECL_AUX();
boolean type();
boolean CONST();
boolean Lire_token();
boolean ADDSUB();
boolean ADDSUBAUX();
boolean MULTDIV();
boolean MULTDIVAUX();
boolean AUX();
boolean PROG();
typetoken lire_token();
//***********************************************************************************************************************

//************************************************Prototypes de Fonctions de l'Analyseur Sémantique***********************
void creer_sm_erreur(SemanticErrorType,int,char *);
int nombre_sm_erreurs();
void afficher_sm_erreurs();
void deja_declaree();
void mal_initialisee();
boolean type_const();
boolean non_declaree();
void incompatible_affectation(monType);
void incompatible_comparaison(monType);
void incompatible_operation();
//****************************************************************************************************************************

extern int yylex();
	
	
	
	//************************************** La Fonction Principale main() *******************************************
 main()
 {
	int i;
		token=lire_token();
		if(PROG()) printf("\n0 Erreurs Syntaxiques !\n");
	    else printf("\nErreurs Syntaxiques\n");
		printf("%d Erreurs Sémantiques !\n\n",nombre_sm_erreurs());
		afficher_sm_erreurs();
	
 } 
 //**********************************************************************************************************************
 
 
 //*******************************************Définitions des fonctions ***********************************************


typetoken lire_token()
{
	
		if (follow_token)
		{
		follow_token = false;
		return token;
		}
		
	else{ 
		return (typetoken) yylex();
	    }
}



 // type
 
 boolean type()
 {
		boolean test;
		if(token==INT) { test=true; tabDeclarations[initDecl].typeVar=Int; }
		else if(token==DOUBLE) test=true;
		else if(token==BOOLEAN) { test=true; tabDeclarations[initDecl].typeVar=Bool; } 
		else test=false;
	return test;
 }
 
 // CONST
 
  boolean CONST()
 {
		boolean test;
		tabDeclarations[initDecl].valInit=(char*) malloc(sizeof(char)*size);
		if(token==INUMBER) {test=true; strcpy(tabDeclarations[initDecl].valInit,"inumber");
							incompatible_comparaison(entier); }
		else if(token==DNUMBER) test=true; 
		else if(token==VRAI) {test=true;strcpy(tabDeclarations[initDecl].valInit,"vrai");
								incompatible_comparaison(trueOrFalse);}
		else if(token==FAUX) {test=true; strcpy(tabDeclarations[initDecl].valInit,"faux");}
		else test=false;
		return test;
 }
 
 
 // DECL_AUX
 
 boolean DECL_AUX()
 {
	boolean test;
	if(CONST())  
				{
				token=lire_token();
				if(token==PVIRG) { test=true; tabDeclarations[initDecl].initOrNot=true;mal_initialisee();}
				
				else test=false;
				}
	else if(token==PVIRG) { test=true; tabDeclarations[initDecl].initOrNot=false; }
	else  test=false;
	return test;
 }
	
 // DECL
 
 boolean DECL()
 {
	boolean test;
	if(token==IDF)
				{
				tabDeclarations[initDecl].nomVar=(char*) malloc(sizeof(char)*5);
				strcpy(tabDeclarations[initDecl].nomVar,mavar);
				
				tabDeclarations[initDecl].line=ligneDecl;
				deja_declaree();
				token=lire_token();
				if(type()) 
						  {
						   token=lire_token();
						   if(DECL_AUX()) test=true;
						   
						   else test=false;
						  }
				else test=false;
				}
	else test=false;
	initDecl++;
	
	
	return test;
 }

  //LISTE_DECL()
 
 boolean LISTE_DECL()
 {
	boolean test;
	if(DECL())
			  {
				token=lire_token();
				if(LISTE_DECL_AUX())  test=true;
				else test=false;
			  }
	else test=false;
	return test;
 }
	
  // LISTE_DECL_AUX()

	boolean LISTE_DECL_AUX()
	{
		boolean test;
		if(token==BEG_IN) {follow_token=true;test=true;}
		
		else if(LISTE_DECL()) {test=true;}
		
		else test=false;
		
		return test;
	}
	
	boolean LISTE_INST()
	{
		boolean test;
						if(INST())
							{
								token = lire_token();
								if(LISTE_INSTAUX()) test = true;
								else test=false;
							}
						else test=false;
					
			
	return test;
	}
	
	boolean LISTE_INSTAUX()
	{
		boolean test;
		if(token==END)
					{
					
					 follow_token=true;
					 test=true;
					}
		else if(token==ENDFOR)
					{
					
					 follow_token=true;
					 test=true;
					}
		else if(token==ENDIF)
					{
					
					 follow_token=true;
					 test=true;
					}	
		else if(token==ELSE)
					{
					
					 follow_token=true;
					 test=true;
					}

		else if(LISTE_INST()) test=true;
		else test=false;
	return test;		
	}
	
	boolean INST()
	{
	  
	  
	 
	  
	  boolean test;
	  
 
 /*if(token==IDF)
					{
					token=lire_token();
					if(token==EGALE)
									{
									token=lire_token();
									if(CONST())
											  {
											  token=lire_token();
											  if(token==PVIRG) test=true;
											  else test=false;
											  }
									else test=false;
									}
					else test=false;
					}
	*/
	// INST : idf = ADDSUB ';' | true ';' | false ';'
	
	if(token==IDF)
					{
					strcpy(mavar2,mavar); // mavar2 sera utilisée dans idf1(=mavar2)=idf2
					
					// voir si IDF est déclaré ou Pas ?
					idfEg=non_declaree();
					token=lire_token();
					if(token==EGALE)
									{
									token=lire_token();
									if(ADDSUB())
											  {
											  token=lire_token();
											  if(token==PVIRG) test=true;
											  else test=false;
											  }
									else if(token==VRAI)
											  {
											  // voir si IDF est de type bool ??
											 incompatible_affectation(trueOrFalse);
											  
											
											  token=lire_token();
											  if(token==PVIRG) test=true;
											  else test=false;
											  }
									else if(token==FAUX)
											  {
											  incompatible_affectation(trueOrFalse);
											  token=lire_token();
											  if(token==PVIRG) test=true;
											  else test=false;
											  }
									else test=false;
									
									}
					else test=false;
					}
											  
	  
	 /* if ‘(‘ idf == CONST ‘)’ then LISTE_INST IF_INSTAUX */
	 
	 else if(token==IF)
					  {
						token=lire_token();
						if(token==PAR_OUVR)
										  {
										    token=lire_token();
											if(token==IDF)
														  {
															// voir si IDF est déclaré ou Pas ?
															strcpy(mavar3,mavar);
															
															idfEgEg=non_declaree();
															
															token=lire_token();
															if(token==EGALEEGALE)
																				{
																				 token=lire_token();
																				 if(CONST())
																							{
																							 token=lire_token();
																							 if(token==PAR_FERM)
																												{
																												token=lire_token();
																												if(token==THEN)
																															  { 
																															    token=lire_token();
																																if(LISTE_INST())
																																			   {
																																			    token=lire_token();
																																				if(IF_INSTAUX())
																																				{
																																					test=true;
																																				}
																																			    else test=false;
																																				}
																																else test=false;
																															   }
																												else test=false;
																												}
																							 else test=false;
																							}
																				 else test=false;
																				 }
			
													else test=false;
															}
											else test=false;																									
											}
						else test=false;
					  } 
					  
		// if ‘(‘ idf == ADDSUB ‘)’ then LISTE_INST IF_INSTAUX
		
		/*else if(token==IF)
					  {
						token=lire_token();
						if(token==PAR_OUVR)
										  {
										    token=lire_token();
											if(token==IDF)
														  {
														    // voir si IDF est déclaré ou Pas ?
															strcpy(mavar3,mavar);
															
															idfEgEg=non_declaree();
															token=lire_token();
															if(token==EGALEEGALE)
																				{
																				 token=lire_token();
																				 if(ADDSUB())
																							{
																							
																							 token=lire_token();
																							 if(token==PAR_FERM)
																												{
																												token=lire_token();
																												if(token==THEN)
																															  { 
																															    token=lire_token();
																																if(LISTE_INST())
																																			   {
																																			    token=lire_token();
																																				if(IF_INSTAUX())
																																				{
																																					test=true;
																																				}
																																			    else test=false;
																																				}
																																else test=false;
																															   }
																												else test=false;
																												}
																							 else test=false;
																							}
																				 else test=false;
																				 }
			
													else test=false;
															}
											else test=false;																									
											}
						else test=false;
					  }*/
		
		
		
		
		
	/*print IDF ';'*/
	
	else if(token==PRINT)
						{
							 token=lire_token();
							 if(token==IDF)
										  {
											 // voir si IDF est déclaré ou Pas ?
											 non_declaree();
											 
											 token=lire_token();
											 if(token==PVIRG)
															{
																test=true;
															}
											 else test=false;
										  }
							 else test=false;
						}
	/*for IDF = inumber to inumber do LISTE_INST endfor*/
	
	 else if(token==FOR)
					  {
						token=lire_token();
						if(token==IDF)
										  {
										    // voir si IDF est déclaré ou Pas ?
											non_declaree();
											
											token=lire_token();
											if(token==EGALE)
														  {
															token=lire_token();
															if(token==INUMBER)
																				{
																				//voir si IDF est de type INT ?
																				
																				incompatible_affectation(inumber); 
																				
																				 token=lire_token();
																				 if(token==TO)
																							{
																							token=lire_token();
																							if(token==INUMBER)
																											 {
																												token=lire_token();
																												if(token==DO)
																															  {
																																token=lire_token();
																																if(LISTE_INST())
																																					{
																																					token=lire_token();
																																					if(token==ENDFOR)
																																									{
																																									test=true;
																																									}
																																					else test=false;
																																					}
																																else test=false;
																																}
																												else test=false;
																												}
																								else test=false;
																							}
																					else test=false;
																				}
															else test=false;
															}
											else test=false;
										   }
						else test=false;
					  }
					
	else test=false;
	
	
		return test;
	}
	
	
	// AUX
	boolean AUX()
	{
	
		boolean test;
		
		
		if(token==INUMBER) { 
							// voir si IDF est de type INT ??                  //affectation
											  incompatible_affectation(entier);
											  	
							test=true;
							}
		else if(token==DNUMBER) test=true;
		else if(token==IDF) {strcpy(mavar4,mavar);
							
							incompatible_affectation(memeType);
								
								//incompatible avec l'opération
						    incompatible_operation();
							
							test=true; 
							
							}
							
		else if(token==PAR_OUVR)
								{
									token=lire_token();
									if(ADDSUB())
												{
													token=lire_token();
													if(token==PAR_FERM) test=true;
													else test=false;
												}
									else test=false;
								}
		else test=false;
	return test;
	}
	
	//  IF_INSTAUX : endif | else LISTE_INST endif
	
	boolean IF_INSTAUX()
	{
		boolean test;
		if(token==ENDIF) test=true;
		else if(token==ELSE)
							{
							
							token=lire_token();
							if(LISTE_INST())
											{
											token=lire_token();
											if(token==ENDIF) test=true;
											else test=false;
											}
							else test=false;
							}
		else test=false;
		return test;
	}
	
	
	boolean ADDSUB()
	{	
		boolean test;
		if(MULTDIV())
					{
					token=lire_token();
					if(ADDSUBAUX()) {test=true;
					 }
					else test=false;
					}
		else test=false;
		
		return test;
	}
	
	boolean ADDSUBAUX()
	{
		boolean test;
		if(token==MOINS)
						{
						token=lire_token();
						if(MULTDIV())
									{
									token=lire_token();
									if(ADDSUBAUX()) test=true;
									else test=false;
									}
						else test=false;
						}
		else if(token==PLUS)
						{
						plus=1;   //test si token==PLUS
						
						token=lire_token();
						if(MULTDIV())
									{
									token=lire_token();
									if(ADDSUBAUX()) test=true;
									else test=false;
									}
						else test=false;
						}
		else if (token==PVIRG || token==PAR_FERM)
										{
										follow_token = true;
										test=true;
										}
		else test=false;
		
		return test;
	}
	
	boolean MULTDIV()
	{
		boolean test;
		if(AUX())
				{
				token=lire_token();
				if(MULTDIVAUX()) test=true;
				else test=false;
				}
		else test=false;
	}
	
	boolean MULTDIVAUX()
	{
		boolean test;
		if(token==PROD)
						{
						token=lire_token();
						if(AUX())
									{
									token=lire_token();
									if(MULTDIVAUX()) test=true;
									else test=false;
									}
						else test=false;
						}
		else if(token==DIV)
						{
						token=lire_token();
						if(AUX())
									{
									token=lire_token();
									if(MULTDIVAUX()) test=true;
									else test=false;
									}
						else test=false;
						}	
		else if (token==PLUS || token==MOINS || token==PVIRG || token==PAR_FERM)
		{
		follow_token = true;
		test=true;
		}
		else test=false;
		
		return test;
	}
	
	boolean PROG()
	{
		boolean test;
		if(LISTE_DECL()) 
				{
				token=lire_token();
				if(token==BEG_IN)
						{
							token=lire_token();
							if(LISTE_INST())
									{
									token=lire_token();
									if(token==END) test=true;
									else test=false;
									}
							else test=false;
						}
				else test=false;
				}
		else test=false; 
																 
		
		return test;
			
	}
		
	
	//**********************************Définitions des Fonctions de l'analyseur Sémantique*********************************
	void creer_sm_erreur(SemanticErrorType et,int line,char *nom)
{
	
	//creation
	smError *erreur;
	erreur = (smError*) malloc(sizeof(smError));
	
	erreur->lineErreur=line;
	erreur->nomSourceErreur=(char *) malloc(sizeof(char)*size);
	strcpy(erreur->nomSourceErreur,nom);
	erreur->typeErreur=et;
	
	//ajout
	tabErreur[initErr].lineErreur=erreur->lineErreur;
	tabErreur[initErr].nomSourceErreur=(char *) malloc(sizeof(char)*size);
	strcpy(tabErreur[initErr].nomSourceErreur,erreur->nomSourceErreur);
	tabErreur[initErr].typeErreur=erreur->typeErreur;
	
	//tabErreur[initErr]=erreur;
	
	initErr++;
}

// renvoie le nombre d'erreurs

int nombre_sm_erreurs()
{
	return initErr;
}

//afficher les erreurs

void afficher_sm_erreurs()
{
	int i; 
	for(i=0;i<initErr;i++)
						{
						printf("Ligne %d : %s ",tabErreur[i].lineErreur,tabErreur[i].nomSourceErreur); 
						switch(tabErreur[i].typeErreur)
									{
									case dejaDeclaree:printf("variable déja déclarée !\n");break;
									case malInitialisee:printf("variable mal initialisée !\n");break;
									case incompatibleAffectation:printf("incompatible avec la valeur d'affectation!\n");break;
									case incompatibleComparaison:printf("incompatible avec la valeur de comparaison!\n");break;
									case nonDeclaree:printf("variable non déclarée !\n");break;
									case incompatibleOperation:printf("incompatible avec l'opération!\n");break;
									default: printf("Type d'erreur different !\n");
									}
						}
}

	




void deja_declaree()
{ int i=0,j;
	
  tabDeclarations[0].nombreDecl=1;
  
  for(i=initDecl-1;i>=0;i--)
  //for(i=0;i<=initDecl-1;i++)  
    {
		existeDeja=false;
		if( strcmp(tabDeclarations[initDecl].nomVar,tabDeclarations[i].nomVar)==0 ) 
		{
		    existeDeja=true;  //printf("déja déclarée"); 
			j=i;
			
			
			if(existeDeja)  {creer_sm_erreur(dejaDeclaree,tabDeclarations[initDecl].line,tabDeclarations[initDecl].nomVar);
							tabDeclarations[initDecl].nombreDecl=1+tabDeclarations[j].nombreDecl;
						 
						
					        }
			
		}
		if(!existeDeja) tabDeclarations[initDecl].nombreDecl=1;
		if(existeDeja) break;  // une fois trouvee sort,n'imprimer pas les autres "var déja déclaree"
		
    }
		
		 
}


void mal_initialisee()
{
	boolean test;
  if(!type_const())
  creer_sm_erreur(malInitialisee,tabDeclarations[initDecl].line,tabDeclarations[initDecl].nomVar);  //printf("mal initialisée");
}

boolean type_const()
{ boolean test;
	//si(type==INT) Const=INUMBER
	//si(type==boolean) Const=Vrai||Faux;
	
	if(tabDeclarations[initDecl].initOrNot) 
	{
	//tabDeclarations[initDecl].valInit=(char*) malloc(sizeof(char)*size);
	if(tabDeclarations[initDecl].typeVar == Int && strcmp(tabDeclarations[initDecl].valInit,"inumber")==0) test=true;
	else if(tabDeclarations[initDecl].typeVar == Bool && ( strcmp(tabDeclarations[initDecl].valInit,"vrai")==0 ||  strcmp(tabDeclarations[initDecl].valInit,"faux")==0 ) ) test=true;
	else test=false;
	
	return test;
	}
}
	
	boolean non_declaree()
	{
	boolean existePas=true;
	int i;
	
	tabInstructions[initInst].nomVar=(char*) malloc(sizeof(char)*size);
					strcpy(tabInstructions[initInst].nomVar,mavar);
					tabInstructions[initInst].line=ligneInst;
					
					
					for(i=0;i<initDecl;i++) 
					if(strcmp(mavar,tabDeclarations[i].nomVar)==0) existePas=false;//si IDF n'existe pad dans la table de declarations créer une erreur
					if(existePas) creer_sm_erreur(nonDeclaree,tabInstructions[initInst].line,mavar);
					return existePas;
	}
	
	
	
	void incompatible_affectation(monType choix)
	{
	int i,k,j,jj;
	switch(choix)
	{
	case inumber : for(i=0;i<initDecl;i++) if(strcmp(mavar,tabDeclarations[i].nomVar)==0) {k=i;i=100;}//=break
																				 
																				if(tabDeclarations[k].typeVar!=Int ) 
																				//creer une erreur
																				creer_sm_erreur(incompatibleAffectation,tabInstructions[initInst].line,mavar);
			break;
	case trueOrFalse :  if(!idfEg) // si IDF est declaré
											  {
											  for(i=0;i<initDecl;i++) if(strcmp(mavar,tabDeclarations[i].nomVar)==0) {k=i;i=100;}//=break
																				if(tabDeclarations[k].typeVar!=Bool) 
																				//creer une erreur
																				creer_sm_erreur(incompatibleAffectation,tabInstructions[initInst].line,mavar);
																				idfEg=true;
											  }
			break;
	
	
	case entier : if(!idfEg) // si IDF est declaré
											  {
											  for(i=0;i<initDecl;i++) if(strcmp(mavar2,tabDeclarations[i].nomVar)==0) {k=i;i=100;}//=break
																				if(tabDeclarations[k].typeVar!=Int) 
																				//creer une erreur
																				creer_sm_erreur(incompatibleAffectation,tabInstructions[initInst].line,mavar);
																				idfEg=true;
											  }
				break;
	
	case memeType : if(!non_declaree() && !idfEg) // si IDF2 est déclaré ET IDF1 est déclaré ou Pas ?
								{ 
									for(i=0;i<initDecl;i++) 
													{
														if( strcmp(mavar,tabDeclarations[i].nomVar)==0 ) j=i;
														if( strcmp(mavar2,tabDeclarations[i].nomVar)==0 ) jj=i;
							
													}
							if(tabDeclarations[j].typeVar!=tabDeclarations[jj].typeVar)
							creer_sm_erreur(incompatibleAffectation,tabInstructions[initInst].line,mavar);
							idfEg=true;
								}
			break;
	

	
	}
	}
	
	
									
	void incompatible_comparaison(monType choix)
	{ int i,k;
		switch(choix)
					{
					case entier : if(!idfEgEg) // si IDF est declaré
											    {
											    for(i=0;i<initDecl;i++) if(strcmp(mavar3,tabDeclarations[i].nomVar)==0) {k=i;i=100;}//=break
																				if(tabDeclarations[k].typeVar!=Int) 
																				//creer une erreur
																				creer_sm_erreur(incompatibleComparaison,tabInstructions[initInst].line,mavar);
																				idfEgEg=true;
												}break;
					case  trueOrFalse: if(!idfEgEg) // si IDF est declaré
											  {
											  for(i=0;i<initDecl;i++) if(strcmp(mavar3,tabDeclarations[i].nomVar)==0) {k=i;i=100;}//=break
																				if(tabDeclarations[k].typeVar!=Bool) 
																				//creer une erreur
																				creer_sm_erreur(incompatibleComparaison,tabInstructions[initInst].line,mavar);
																				idfEgEg=true;
		
		
		
		
		
		
							} break;
					}
	}
	
	void incompatible_operation()
	{
	int i,m;
	boolean t=false;
		for(i=0;i<initDecl;i++) 
						if(strcmp(mavar4,tabDeclarations[i].nomVar)==0) t=true; 
						
					    
								//incompatible avec l'opération
						if(plus==1 && t) {plus=0;t=false;for(i=0;i<initDecl;i++) if(strcmp(mavar4,tabDeclarations[i].nomVar)==0) {m=i;i=100;}
					    if(tabDeclarations[m].typeVar==Bool) creer_sm_erreur(incompatibleOperation,tabInstructions[initInst].line,tabDeclarations[m].nomVar);}
		
				
		
		
	}
	
	//***************************************************************************************************************************

 
 
 

 
 
 
 
 
 
 
	
	
	
	
	
 
 
