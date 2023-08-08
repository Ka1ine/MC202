#include <stdio.h>
#include <stdlib.h>

typedef struct arv{
    char info;
    struct arv* dir;
    struct arv* esq;
} arv;

arv* cria(char * info, arv* esq, arv* dir){
    arv* a = (arv*)malloc(sizeof(arv));
    a->dir = dir;
    a->esq = esq;
    a->info = *info;
    return a;
}

void imprime(arv* arvore){
    if(arvore != NULL){
        printf("<");
        printf("%c", arvore->info);
        imprime(arvore->esq);
        imprime(arvore->dir);
        printf(">");
    }else{
        printf("<>");
    }
} 

int main(){
    arv* a = cria("a", 
                cria("b", 
                        NULL,
                        cria("d", NULL, NULL)), 
                cria("c", 
                        cria("e", NULL, NULL),
                        cria("f", NULL, NULL)));

    imprime(a);
    return 1;
}