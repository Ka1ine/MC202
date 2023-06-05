#include <stdlib.h>
#include <stdio.h>

typedef struct arv{
    int info;
    struct arv* esq;
    struct arv* dir;
} arv;

arv * cria(int info, arv* esq, arv* dir){
    arv* a = (arv*)malloc(sizeof(arv));
    a->esq = esq;
    a->dir = dir;
    a->info = info;
    return a;
}

arv* inicializa(void){
    return NULL;
}

void imprimir(arv* a){
    if (a != NULL){
        printf("<");
        printf("%d", a->info);
        imprimir(a->esq);
        imprimir(a->dir);
        printf(">");
    } 
}

arv* busca(arv* a, int valor){
    if (a != NULL){
        if (a->info > valor){
            return busca(a->esq, valor);
        }
        else if (a->info < valor){
            return busca(a->dir, valor);
        }
    }
    return a;
}

arv* remover(arv* a, int valor){
    if (a != NULL){
        if (a->info > valor){
            a->esq = remover(a->esq, valor);
        }
        else if (a->info < valor){
            a->dir = remover(a->dir, valor);
        }
        else{
            if (a->dir == NULL && a->esq == NULL){
                free(a);
                a = NULL;
            }
            else if (a->esq == NULL){
                arv* p = a;
                a = a->dir;
                free(p);
            }
            else if (a->dir == NULL){
                arv* p = a;
                a = a->esq;
                free(p);
            }
            
        }
        return a;
    }
    return a;
}

arv* insere(arv* a, int valor){
    if (a == NULL){
        a = (arv*)malloc(sizeof(arv));
        a->info = valor;
        a->dir = NULL;
        a->esq = NULL;
    }
    else if(a->info < valor){
        a->dir = insere(a->dir, valor);
    }
    else {
        a->esq = insere(a->esq, valor);
    }
    return a;
}
   
int main(){
    // arv* a = cria(6, 
    //                 cria(2,
    //                     cria(1, NULL, NULL),
    //                     cria(4, 
    //                         cria(3, NULL, inicializa()), inicializa())),  
    //                 cria(8,inicializa(), inicializa()));
    // arv* a = cria(6, 
    //             cria(2,NULL, NULL), 
    //             cria(8, NULL, NULL));
    //
    arv* a = NULL;
    a = insere(a, 17);
    a = insere(a, 26);
    a = insere(a, 25);
    a = insere(a, 8);
    a = insere(a, 9);
    imprimir(a);
    printf("\n");
    a = remover(a, 26);
    imprimir(a);
}