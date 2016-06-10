typedef enum { STRING , QUERYL}TypeQUERYAUX;
 typedef enum { find , update, insert }type_inst;
  typedef enum {string, num , tableau }type;
  typedef enum { val , membres}typeQUAUX_IN;
  typedef enum { qaux4, valeur}type_q;
 typedef enum { qaux2, membre , in , no }TypeQAUX4;
 struct INST;
 struct INSTS;
 struct INSTSAUX;
 struct LISTE_QUERY;
 struct UPDATE;
 struct ELEMENTS;
 struct PAIRE;
 struct MEMBRES;
 struct INSERT;
struct VALEUR;
struct QAUX2;
struct QUAUX_IN;
struct VALEUR_AUX;
struct PAIRE_AUX;
struct TABLEAU;
struct QAUX3;
struct QAUX5;
struct Q;
struct QAUX4;
struct LISTE_QUERYAUX;
struct QAUX;
struct QUERYAUX;
struct QUERY;

 typedef struct INST{
//inst : db . string . FIND(QUERY)
//inst : db . string . UPDATE(UPDATE)
//inst : db . string . INSERT(INSERT)
     int rangvar;
     type_inst typeinst;
union {
  struct {
      struct QUERY first;
         }findnode;
 struct {
       struct UPDATE first;
        }updatenode;
 struct {
     struct INSERT first
        }insertnode;
      }node;

 }instValueType;
 typedef struct INSTS{
  //insts : inst instsaux
  struct INST first;
  struct INSTSAUX next;

}instsValueType;
typedef struct INSTSAUX{
//instsaux : insts | epsilon
struct INSTS first;
}instsauxValueType;
typedef struct LISTE_QUERY{
     //liste_query ----------> query liste_queryAux
     struct QUERY first;
     struct LISTE_QUERYAUX next;
                          }listeqValueType;
typedef struct UPDATE {
 //Update :query,{Membres}
 struct QUERY first;
 struct MEMBRES next;
                      }updateValueType;
 typedef struct ELEMENTS{
      //Elements : Valeur Valeur_Aux
 struct VALEUR first;
 struct VALEUR_AUX next;
 }elementsValueType;
 typedef struct PAIRE{
     //Paire : string : Valeur
   int rangvar;
   int right;
 }paireValueType;
typedef struct MEMBRES{
 //Membres : Paire Paire_Aux
struct PAIRE first;
struct PAIRE_AUX NEXT;
}membresValueType;
typedef struct INSERT{
 //Insert : {Membres}
 struct MEMBRES first;
}insertValueType;
 typedef struct VALEUR{
 // Valeur : string|num|tableau|true|false|null
 type typename;
 int valinit;
 }valeurValueType;
typedef struct QAUX2 {
  //QAux2 ----------------> query_comparaison : valeur
 struct VALEUR first;
 }qaux2ValueType;
typedef struct QUAUX_IN {

 //quaux_in--------------> valeur QAux3 | {Membres} QAux3
typeQUAUX_IN typequauxin;

union {

    struct {
        struct VALEUR first;
        struct QAUX3 next;
           }valnode;

    struct {
       struct MEMBRES first;
       struct QAUX3 next;
           }membnode;
      } node;


}quaux_inValueType;
typedef struct VALEUR_AUX {
       //Valeur_Aux : , Elements | epsilon
       struct ELEMENTS first;

                           }valeurauxValueType;
typedef struct PAIRE_AUX{
//  Paire_Aux : , Membres | epsilon
    struct MEMBRES first;
                       }paire_auxValueType;
typedef struct TABLEAU {
 //Tableau : [ ] | [ Elements ]
 struct ELEMENTS first;
                       }tableauValueType;
typedef struct QAUX3 {
     //QAux3 ----------------> ,qaux_in| epsilon
     struct QAUX_IN first;
                    }qaux3ValueType;
typedef struct QAUX5{
         //QAux5----------------->,QAux2 Qaux5 | epsilon
         struct QAUX2 first;
         struct QAUX5 next;
                    }qaux5ValueType;
typedef struct Q {
 //Q---------------------> { QAux4 }| valeur
type_q typeq;
union{
    struct {
        struct QAUX4 first;
           }qaux4node;
        struct {
            struct VALEUR first;
               }vnode;
    }node;
                 }qValueType;
 typedef struct QAUX4 {
       //QAux4----------------->  QAux2 Qaux5
 //                       | Membres
//                         | epsilon

//                        | $exists : true | false
//                        | $in : [ qaux_in ]
//                        | $not : {query-comparaison : valeur}

       TypeQAUX4 typeqaux4;
       union {
        struct{
            struct QAUX2 first;
            struct QAUX5 next;
              }qaux2node;
          struct{
              struct MEMBRES first;
              }membresnode;

               struct{
                   struct QAUX_IN first;
              }innode;
               struct{
                   struct   VALEUR first;
              }nonode;
             }node;


                     }qaux4ValueType;
typedef struct LISTE_QUERYAUX {
          //liste_queryAux -------> ,list-query | epsilon
          struct LISTE_QUERY   first ;
                           }listeqauxValueType;
typedef struct QAUX {
//QAux -----------------> ,queryAux | epsilon
struct QUERYAUX first ;
                    }qauxValueType;
typedef struct QUERYAUX {
//queryAux -------------> string : Q QAux | query_logical : [ list_query] QAux | epsilon
TypeQUERYAUX typequeryaux;
union {
    struct {
        int rangvar;
        struct Q first;
        struct QAUX next;
           }stringnode;
    struct {

        struct LISTE_QUERY first;
        struct QAUX next;
           }querylnode;

      }node;

}queryauxValueType;
typedef struct QUERY{
    //query-----------------> { queryAux } | epsilon
    struct QUERYAUX first;
}queryValueType;

typedef union {
      queryValueType queryattribute;
      queryauxValueType queryauxattribute;
      qauxValueType   qauxattribute;
      listeqauxValueType  listeqauxattribute;
      qaux4ValueType  qaux4attribute;
      qValueType qattribute;
      qaux5ValueType qaux5attribute;
      qaux3ValueType qaux3attribute;
      tableauValueType tableauattribute;
      paire_auxValueType paire_auxattribute;
      valeurauxValueType valeurauxattribute;
      quaux_inValueType quaux_inattribute;
    valeurValueType valeurattribute;
    membresValueType membresattribute;
    paireValueType paireattribute;
    elementsValueType elementsattribute;
    updateValueType updateattribute;
    listeqValueType listeqattribute;
    instsValueType instsattribute;
    instValueType instattribute;
    instsauxValueType  instsauxattribute;
    insertValueType insertattribute;
              }ValueType;


