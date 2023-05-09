#include <stdio.h>
#include <stdlib.h>

struct node{
    int valor;
    struct node * next;  
};

typedef struct node Node;

Node * insere (Node * no, int v){
    Node * new_no = (Node*) malloc(sizeof(Node));
    new_no->valor = v;
    new_no->next = no;
    return new_no;
}

Node * busca(Node * no, int v){
    Node * p;
    for(p = no; p != NULL; p = p->next){
        if (p -> valor == v)
            return p;
    }
    return NULL;
}

Node * retira(Node * no, int v){
    Node * ant = NULL;
    Node * p = no;
    while(p != NULL && p->valor != v){
        ant = p;
        p = p->next;
    }
    if (p == NULL)
        return no;
    if (ant == NULL)
        no = p->next;
    else
        ant->next = ant->next->next;
    free(p);
    return no;
}

void imprime (Node * no){
    Node * p;
    p = no;
    while(p != NULL){
        printf("Valor = %d\n", p->valor);
        p = p->next;
    }
    
}

void movenexttofront(Node* no){
    Node * p = no->next;
    p->next = no;
    no->next = no->next->next;
    no->next->next = NULL;
}

/*Função vazia returna*/
int vazia (Node * no){
    if (no == NULL)
        return 1;
    else
        return 0;
}

void mata(Node * no){
    Node * p = no;
    while (p != NULL){
        Node * t = p->next;
        free(p);
        p = t;
    }
    
}

int minimo (Node * no){
    Node * p = no;
    int num = p->valor;
    for(p = no; p != NULL; p = p->next){
        if (num > p->valor)
            num = p->valor;
    }
    return num;
}

int main(void) {
    Node * no = NULL;
    no = insere(no, 2);
    no = insere(no, 3);
    no = insere(no, 6);
    no = insere(no, 4);
    no = insere(no, 5);
    imprime(no);
    printf("----------\n");
    int a = minimo(no);
    printf("%d", a);

}
