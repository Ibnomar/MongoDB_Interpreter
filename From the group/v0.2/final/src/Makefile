gen_lexer : analyseur_lexical.l tokens.h
	flex -i analyseur_lexical.l
	mv lex.yy.c analyseur_lexical.c
	gcc -c analyseur_lexical.c

gen_utile : utile.c utile.h
	gcc -c utile.c

gen_document : document.c document.h utile.h
	gcc -c document.c
	
gen_commande : commande.c commande.h document.h utile.h query.h
	gcc -c commande.c

gen_insert : insert.c document.h utile.h
	gcc -c insert.c

gen_find : find.c document.h utile.h query.h
	gcc -c find.c
	
gen_lire : lire.c document.h utile.h
	gcc -c lire.c

gen_interpreteur : interpreteur.c utile.h tokens.h commande.h document.h
	gcc -c interpreteur.c
	
gen_mongoi :  gen_lexer gen_utile gen_document gen_commande gen_insert gen_find gen_interpreteur gen_lire
	gcc -o mongoi analyseur_lexical.o utile.o document.o commande.o insert.o find.o interpreteur.o lire.o

all : gen_mongoi

clean :
	rm *~
	rm *.yy.c
	rm *.exe
	rm zzc zzi
	rm *.o
