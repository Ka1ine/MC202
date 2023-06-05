# include <stdlib.h>
# include <stdio.h>
#include <string.h>

typedef struct node {
    struct node *next;
    struct node *prev;
    char data;
} node;

typedef struct list {
    node *head;
    node *tail;
} list;

list* list_new(char c) {
    node *new = malloc(sizeof(node));
    new->next = NULL;
    new->prev = NULL;
    new->data = c;
    list *new_list = malloc(sizeof(list));
    new_list->head = new;
    new_list->tail = new;
    return new_list;
}

void list_insert(list *lista, char c) {
    node *new = malloc(sizeof(node));
    new->data = c;
    new->prev = lista->tail;
    new->next = NULL;
    lista->tail->next = new;
    lista->tail = new;
}

void list_print(list *lista) {
    node *p = lista->head;
    while (p != NULL) {
        printf("%c\n", p->data);
        p = p->next;
    }
}

list * criar_nos(char *letra, list *lista){
    while (*letra != '\0')
    {
        if (lista == NULL) {
            lista = list_new(*letra);
            letra++;
            continue;
        }
        list_insert(lista, *letra);
        letra++;
    }
    // list_print(lista);   
    // printf("-------\n");
    return lista;
}

void mata(node * no){
    node * p = no;
    while (p != NULL){
        node * t = p->next;
        free(p);
        p = t;
    }
    
}

/*-------ARVORE-------*/

typedef struct arv {
    char info;
    struct arv *esq;
    struct arv *dir;
} arv;

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

int busca (arv* a, char *c){
    if (!vazia(a))
        return a->info== *c || busca(a->esq,c) || busca(a->dir,c);
    else
        return 0;
}

node * busca_no(node * no, char v){
    node * p;
    for(p = no; p != NULL; p = p->next){
        if (p -> data == v)
            return p;
    }
    return NULL;
}

list* busca_sla(list* em_ordem, list* direita){
    list* p = direita;
    while (p->head->data != em_ordem->head->data)
    {
        /* code */
    }
    
}


node * dividir(list* em_ordem, char * raiz, arv* a){
    node* direita = em_ordem->head;
    while (direita->data != *raiz){
        direita = direita->next;
    }
    node* q = direita;
    direita = direita->next;
    free(q);
    return direita;
}

arv* montar_arvore(list* em_ordem, list* pre_ordem){
    char* raiz = &pre_ordem->head->data;
    arv* a = cria(raiz, inicializa(), inicializa());
    node * direita = dividir(em_ordem, raiz, a);
    pre_ordem->head = pre_ordem->head->next;
    montar_arvore(em_ordem, pre_ordem);
    
    return a;

}

int main(){
    
    char * letra_pre_ordem = "ABCZEF";
    char * letra_em_ordem = "CBAEZF";
    char * letra = letra_pre_ordem;
    char * letra2 = letra_em_ordem;

    list *pre_ordem = NULL;
    list *em_ordem = NULL;

    pre_ordem = criar_nos(letra, pre_ordem);
    em_ordem = criar_nos(letra2, em_ordem);

    montar_arvore(pre_ordem, em_ordem);

}