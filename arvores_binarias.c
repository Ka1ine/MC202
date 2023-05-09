# include <stdlib.h>
# include <stdio.h>

struct arv{
    char info;
    struct arv * esq;
    struct arv * dir;
};typedef struct arv arv;

arv* inicializa(void){
    return NULL;
}

arv* cria(char * info, arv* esq, arv* dir){
    arv* arvore = (arv*)malloc(sizeof(arv));
    arvore->info = *info;
    arvore->esq = esq;
    arvore->dir = dir;
    return arvore;
}

int vazia(arv* arvore){
    return arvore == NULL;
}

void imprime(arv* arvore){
    if(!vazia(arvore)){
        printf("<");
        printf("%c", arvore->info);
        imprime(arvore->esq);
        imprime(arvore->dir);
        printf(">");
    }else{
        printf("<>");
    }
} 

int altura(arv* arvore){
    if(!vazia(arvore)){
        int x = altura(arvore->esq);
        int y = altura(arvore->dir);
        x += 1;
        y += 1;

        if (x > y){
            return x;
        }else{
            return y;
        } 
    }else{
        return -1;
    }
}

int busca (arv* a, char *c){
    if (!vazia(a))
        return a->info== *c || busca(a->esq,c) || busca(a->dir,c);
    else
        return 0;
}

arv* libera(arv* arvore){
    if(!vazia(arvore)){
        libera(arvore->esq);
        libera(arvore->dir);
        free(arvore);
    }
    return NULL;
}

int main(){
    arv* a = cria("a", 
                    cria("b", 
                            NULL,
                            cria("d", inicializa(), inicializa())), 
                    cria("c", 
                            cria("e", inicializa(), inicializa()),
                            cria("f", inicializa(), inicializa())));

    // imprime(a);
    // a->esq->esq = cria("x",
    //                     cria("y", inicializa(), inicializa()),
    //                     cria("z", inicializa(), inicializa()));

    // printf("\n-------------\n");
    // imprime(a);
    // a->esq->esq->dir = libera(a->esq->esq->dir);

    // printf("\n-------------\n");
    // imprime(a);

    // int b = altura(a);
    // printf("%d", b);

    printf("%d", busca(a, "e"));
}