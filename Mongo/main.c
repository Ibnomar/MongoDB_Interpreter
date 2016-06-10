#include <stdio.h>
#include "mongo.h"
int main(int argc, char * argv[]){

    token=lire_token();
    if(membres())

        printf("YEP");
    else
        printf("NOPE");

    return 0;
}