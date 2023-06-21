#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arv{
    int num;
    char nome[100];
    float pont;
    struct arv * esq;
    struct arv * dir;
};typedef struct arv arv;

void liberar(arv* a){
    if(a != NULL){
        liberar(a->esq);
        liberar(a->dir);
        free(a);
    }
}

arv* criar(arv* a){
    liberar(a);
    return NULL;
}

arv* inserir(arv* a, int num, char nome[100], float pont){
    if (a == NULL){
        arv* new_a = (arv*)malloc(sizeof(arv));
        new_a->num = num;
        strcpy(new_a->nome, nome);
        new_a->pont = pont;
        new_a->dir = NULL;
        new_a->esq = NULL;
        a = new_a;
    }
    else if(a->num < num){
        a->dir = inserir(a->dir, num, nome, pont);
    }
    else if(a->num > num){
        a->esq = inserir(a->esq, num, nome, pont);
    }
    return a;
}

void imprimir(arv* a){
    if (a != NULL){
        imprimir(a->esq);
        printf("%s (%d) ", a->nome, a->num);
        imprimir(a->dir);
    }
}

arv* minimo(arv* a){
    if (a == NULL) return NULL;

    if (a->esq == NULL) {
        return a;
    } else {
        return minimo(a->esq);
    }
}

arv* maximo(arv* a){
    if (a == NULL) return NULL;

    if (a->dir == NULL) {
        return a;
    } else {
        return maximo(a->dir);
    }
}

arv* buscar(arv* a, int num){
    if (a != NULL){
        if(a->num == num){
            return a;
        }
        else if(a->num < num){
           return buscar(a->dir,num);
        }
        else if(num < a->num){
            return buscar(a->esq,num);
        }        
    }
    return NULL;
}

arv* sucessor(arv* a, int num) {
    if (a == NULL) {
        printf("arvore vazia\n");
        return NULL;
    }

    arv* buscado = buscar(a, num);

    if (buscado == NULL) {
        printf("nao ha cliente %d\n", num);
        return NULL;
    }

    if (buscado->dir != NULL) {
        arv* min = minimo(buscado->dir);
        printf("sucessor de %d: %d\n", num, min->num);
        return min;
    }

    arv* sucessor = NULL;
    arv* atual = a;

    while (atual != NULL) {
        if (atual->num > num) {
            sucessor = atual;
            atual = atual->esq;
        } else if (atual->num < num) {
            atual = atual->dir;
        } else {
            break;
        }
    }

    if (sucessor == NULL) {
        printf("sucessor de %d: não ha\n", num);
    } else {
        printf("sucessor de %d: %d\n", num, sucessor->num);
    }

    return sucessor;
}

arv* predecessor(arv* a, int num) {
    if (a == NULL) {
        printf("arvore vazia\n");
        return NULL;
    }

    arv* buscado = buscar(a, num);
    if (buscado == NULL) {
        printf("nao ha cliente %d\n", num);
        return NULL;
    }

    if (buscado->esq != NULL) {
        arv* max = maximo(buscado->esq);
        printf("predecessor de %d: %d\n", num, max->num);
        return max;
    }

    arv* predecessor = NULL;
    arv* atual = a;

    while (atual != NULL) {
        if (atual->num < num) {
            predecessor = atual;
            atual = atual->dir;
        } else if (atual->num > num) {
            atual = atual->esq;
        } else {
            break;
        }
    }

    if (predecessor == NULL) {
        printf("predecessor de %d: nao ha\n", num);
    } else {
        printf("predecessor de %d: %d\n", num, predecessor->num);
    }

    return predecessor;
}

arv* remover(arv* a, int num){
    if (a != NULL){
        if (a->num > num){
            a->esq = remover(a->esq, num);
        }
        else if (a->num < num){
            a->dir = remover(a->dir, num);
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
            else {
                arv* successor = minimo(a->dir);
                a->num = successor->num;
                strcpy(a->nome, successor->nome);
                a->pont = successor->pont;
                a->dir = remover(a->dir, successor->num);
            }
        }
    }
    return a;
}

void buscar_intervalo(arv* a, int x, int y) {
    if (a == NULL) {
        return;
    }
    if (a->num > x) {
        buscar_intervalo(a->esq, x, y);
    }
    if (a->num >= x && a->num <= y) {
        printf("%d ", a->num);
    }
    if (a->num < y) {
        buscar_intervalo(a->dir, x, y);
    }
}

int main(){
    arv* a = NULL;
    int sla = 0;
    while(sla == 0){
        char ordem[10];
        scanf(" %s", ordem);
        if (!strcmp(ordem, "criar")){
            arv* a = criar(a);
        }
        if (!strcmp(ordem, "inserir")) {
            int num;
            char nome[100];
            float pont;
            scanf(" %d, %[^,]", &num, nome);
            scanf(", %f", &pont);
            a = inserir(a, num, nome, pont);
        }
        
        if (!strcmp(ordem, "buscar")) {
            int numero;
            scanf("%d", &numero);
            arv* buscado = buscar(a, numero);
            if (buscado == NULL){
                printf("nao ha cliente %d\n", numero);
            }else{
                printf("cliente %d: %s, %.2f pontos\n", buscado->num, buscado->nome, buscado->pont); 
            }
        }

        if (!strcmp(ordem, "imprimir")){
            if (a != NULL){
                printf("clientes: ");
                imprimir(a);
                printf("\n");
            }else{
                printf("arvore vazia\n");
            }
        }
        
        if (!strcmp(ordem, "terminar")){
            liberar(a);
            sla = 1;
        }

        if (!strcmp(ordem, "minimo")){
            arv* min = minimo(a);
            printf("minimo: %d\n", min->num);
        }

        if (!strcmp(ordem, "maximo")){
            arv* max = maximo(a);
            printf("maximo: %d\n", max->num);
        }

        if (!strcmp(ordem, "sucessor")) {
            int numero;
            scanf("%d", &numero);
            arv* suc = sucessor(a, numero);
        }

        if (!strcmp(ordem, "predecessor")) {
            int numero;
            scanf("%d", &numero);
            arv* pred = predecessor(a, numero);
        }
   
        if (!strcmp(ordem, "remover")) {
            int numero;
            scanf("%d", &numero);
            a = remover(a, numero);
        }

        if (!strcmp(ordem, "buscar-intervalo")) {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("clientes no intervalo [%d,%d]: ", x, y);
            buscar_intervalo(a, x, y);
            printf("\n");
        }
    }
}
