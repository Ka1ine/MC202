#include <stdlib.h>
#include <stdio.h>

typedef struct stuff {
    
} stuff;

typedef struct node {
    int key;
    struct stuff* data;
    struct node* next;
} node;

typedef struct list {
    node* head;
} list;

int retornar_algo(list* A, int k, int offset){
    if (A == NULL){
        return 0;
    }
    
    node* atual = A->head;
    node* anterior = NULL;
    int posicao = 1;
    while (atual != NULL && atual->key != k){
        anterior = atual;
        atual = atual->next;
        posicao++;
    }
    
    anterior->next = anterior->next->next;

    node* p = A->head;

    int sla = posicao - offset - 2;
    if (sla <= 0){
        p->next = A->head;
        A->head = p;
    }else
    {
        for (int i = 0; i < posicao - offset - 2; i++){
            p = p->next;
        }
        atual->next = p->next->next;
        p->next = atual;
    }

    return 1;
}


int main(){
    printf("aaaa");
}