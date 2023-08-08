#include <stdlib.h>
#include <stdio.h>

typedef struct stuff {
    
} stuff;

typedef struct no {
    int info;
    struct stuff* data;
    struct no* next;
} no;

typedef struct list {
    no* head;
} list;

int retornar_algo(list* A, int k, int offset){
    if (A == NULL){
        return 0;
    }
    
    no* atual = A->head;
    no* anterior = NULL;
    int posicao = 1;
    while (atual != NULL && atual->info != k){
        anterior = atual;
        atual = atual->next;
        posicao++;
    }
    
    anterior->next = anterior->next->next;

    no* p = A->head;

    int sla = posicao - offset - 2;
    if (sla <= 0){
        p->next = A->head;
        A->head = p;
    }else
    {
        for (int i = 0; i < posicao - offset - 2; i++){
            p = p->next;
        }
        atual->next = p->next;
        p->next = atual;
    }

    return 1;
}

// typedef struct no{
//     int info;\
//     struct no* next;
// } no;

no* inserir_comeco(no* node, int info){
    no* new_node = (no*)malloc(sizeof(no));
    new_node->info = info;
    new_node->next = node;
    return new_node;
}

int vazio(no* node){
    if (node == NULL)
        return 1;

    return 0;
}

no* inserir(no* node, int info){
    if (vazio(node)){
        no* new_node = (no*)malloc(sizeof(no));
        new_node->info = info;
        new_node->next = NULL;
        return new_node;
    }

    no* p;
    p = node;

    while (p->next != NULL){
        p = p->next;
    }

    no* new_node = (no*)malloc(sizeof(no));
    new_node->info = info;
    new_node->next = NULL;
    p->next = new_node;
    return node;
}

void imprimir(no* node){
    if (vazio(node)){
        printf("Lista vazia\n");
        return;
    }

    no* p;
    p = node;

    while (p != NULL){
        printf("%d ", p->info);
        p = p->next;
    }
    printf("\n");
    
}

void buscar(no* node, int info){
    if (vazio(node))
        return;

    no* p;
    p = node;

    while (p != NULL){
        if (p->info == info){
            printf("MDS eu achei esse número: %d\n", p->info);
            return;
        }
        
        p = p->next;
    }
    printf("F voce é incapaz de achar um número\n");

}

no* remover(no* node, int info){
    if (vazio(node))
        return node;

    no* p;
    p = node;

    if (p->info == info){
        no* h = p;
        node = p->next;
        free(h);
        return node;
    }
    

    while (p->next != NULL && p->next->info != info ){
        p = p->next;
    }
    if (p->next != NULL){
        no* q = p->next;
        p->next = p->next->next;
        free(q);
    }
    return node;
    
}

no* remover_tudo(no* node, int info){
    if (vazio(node))
        return node;

    no* p;
    p = node;

    if (p->info == info){
        no* h = p;
        node = p->next;
        free(h);
        node = remover_tudo(node, info);
        return node;
    }
    

    while (p->next != NULL && p->next->info != info ){
        p = p->next;
    }
    if (p->next != NULL){
        no* q = p->next;
        p->next = p->next->next;
        free(q);
        node = remover_tudo(node, info);
    }
    return node;
    
}

no* mover(no* node, int info){
    if (vazio(node))
        return node;

    no* p;
    p = node;

    if (p->info == info){
        return node;
    }
    
    while (p->next != NULL && p->next->info != info){
        p = p->next;
    }
    if (p->next != NULL){
        no* q = p->next;
        p->next = p->next->next;
        q->next = node;
        node = q;
    }
    else{
        printf("Nao tem esse valor :)\n");
    }
    return node;
}

no* minimo(no* node){
    if (vazio(node))
        return node;

    no* p;
    p = node;
    int minimo = p->info;
    while (p != NULL){
        if (p->info < minimo){
            minimo = p->info;
        }
        
        p = p->next;
    }
    node = remover(node, minimo);
    return node;
}

no* copiar(no* node){
    if (vazio(node))
        return node;
    no* new_node = NULL;
    no* p = node;
    while (p != NULL){
        new_node = inserir(new_node, p->info);
        p = p->next;
    }
    
    return new_node;
}

void verificar(no* node, no* new_node){
    if (vazio(node) && vazio(new_node))
        return;
    
    no* p = node;
    no* q = new_node;

    while (p != NULL && q != NULL){
        if (p->info == q->info){
            q = q->next;
            p = p->next; 
        }
        else{
            printf("Nao é igual\n");
            return;
        }
    }
    if (p == NULL && q == NULL){
        printf("É igual");
        return;
    }
    else {
        printf("Naooo igual");
    }
    
}

double* criar_vetor(double* A, no* node){
    if (vazio(node))
        return A;

    int i = 0;
    no* p = node;

    while (p != NULL){
        A = (double*)realloc(A, (i + 2) * sizeof(double));
        A[i] = p->info;
        p = p->next;
        i++;
    }
    return A;
}

void verificar_zuada(no* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }

    no* slow = head;
    no* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            no* p = head;
            while (p->next != fast) {
                p = p->next;
            }

            p->next = NULL;
            printf("Lista zuada\n");
        }
    }
    printf("Tudo certo\n");
}



int main(){
    list A;
    no* node = NULL;
    node = inserir_comeco(node, 6);
    node = inserir_comeco(node, 5);
    node = inserir_comeco(node, 4);
    node = inserir_comeco(node, 3);
    node = inserir_comeco(node, 2);
    node = inserir_comeco(node, 1);
    A.head = node;
    // node = inserir(node, 7);
    // node = remover(node, 4);
    // node = remover(node, 1);
    // buscar(node, 2);
    // node = mover(node, 15);
    // node = mover(node, 7);
    imprimir(node);
    // node = remover_tudo(node, 5);
    // imprimir(node);
    // node = minimo(node);
    // imprimir(node);
    // no* new_node = copiar(node);
    // printf("Novo nó: ");
    // imprimir(new_node); 
    // verificar(node, new_node);
    
    // double* A = (double*)malloc(sizeof(double));
    // A = criar_vetor(A, node);
    // printf("%2.f",A[1]);

    


    // // Criação dos nós
    // no* head = (no*)malloc(sizeof(no));
    // no* node1 = (no*)malloc(sizeof(no));
    // no* node2 = (no*)malloc(sizeof(no));
    // no* node3 = (no*)malloc(sizeof(no));
    // no* node4 = (no*)malloc(sizeof(no));
    

    // head->info = 1;
    // head->next = node1;

    // node1->info = 2;
    // node1->next = node2;

    // node2->info = 3;
    // node2->next = node3;

    // node3->info = 4;
    // node3->next = node4;

    // node4->info = 5;
    // node4->next = node3; 

    // verificar_zuada(head);
    // verificar_zuada(node);

    retornar_algo(&A, 5, 2);
    imprimir(node);
}