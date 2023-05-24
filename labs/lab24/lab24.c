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

int main(){
    
    char * letra_pre_ordem = "ABCZEF";
    char * letra_em_ordem = "CBAEZF";
    char * letra = letra_pre_ordem;
    char * letra2 = letra_em_ordem;

    list *pre_ordem = NULL;
    list *em_ordem = NULL;

    pre_ordem = criar_nos(letra, pre_ordem);
    em_ordem = criar_nos(letra, em_ordem);

    
    
}