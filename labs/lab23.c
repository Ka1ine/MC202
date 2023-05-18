#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista* next;
} lista;

lista * comecar(int info) {
    lista * new_lista = (lista*)malloc(sizeof(lista));
    new_lista->info = info;
    new_lista->next = NULL;
    return new_lista;
}

void imprimir(lista* head) {
    lista * atual = head;
    printf("A: { ");
    while (atual != NULL) {
        printf("%d", atual->info);
        atual = atual->next;
        if (atual != NULL)
            printf(", ");
    }
    printf(" }\n");
}

void matar(lista * head) {
    while (head != NULL) {
        lista * p = head;
        head = head->next;
        free(p);
    }
}

lista* inverte_lista(lista * q) {
    lista * anterior = NULL;
    lista* atual = q;
    lista * proximo = NULL;

    while (atual != NULL) {
        proximo = atual->next;
        atual->next = anterior;
        anterior = atual;
        atual = proximo;
    }

    return anterior;
}

lista * sublista(lista * head, int start, int end){
    int index = 0;
    int verificar = 0;
    if (start > end){
        int x = start;
        int y = end;
        start = y;
        end = x;
        verificar = 1;
    }
    lista * lista_atual = head;
    while (index < start){
        index += 1;
        lista_atual = lista_atual->next;
    }
    lista * lista_nova = comecar(lista_atual->info);

    if (end == start) {
        return lista_nova;
    }

    lista * lista_nova_atual = lista_nova;
    /*Pulando proximo index*/
    index += 1;
    lista_atual = lista_atual->next;
    while (index <= end){
        lista_nova_atual->next = comecar(lista_atual->info);
        lista_nova_atual = lista_nova_atual->next;
        lista_atual = lista_atual->next;
        index += 1;
    }
    if (verificar == 1){
        lista_nova = inverte_lista(lista_nova);
    }
    return lista_nova;
}

lista * adicionar(lista * extraida, lista * antigo , int posicao){
    lista * final = extraida;
    lista * inicio = extraida;
    while (extraida->next != NULL){
        extraida = extraida->next;
        final = extraida;
    }
    lista * q = antigo;

    if (posicao == 0)
    {
        final->next = antigo;
        return inicio;
    }
    
    int index = 0;
    while (index < posicao - 1){
        index += 1;
        q = q->next;
    }
    final->next = q->next;
    q->next = inicio;
    return antigo;
}

int main() {
    int info;
    lista * head = NULL;
    scanf("A = { %d", &info);
    lista * new_lista = comecar(info);
    head = new_lista;
    while (scanf(", %d", &info) == 1) {
        lista * atual = head;
        while (atual->next != NULL)
            atual = atual->next;

        lista * new_lista = comecar(info);
        atual->next = new_lista;
    }
    char ordem;
    int start, end, posicao;

    while (scanf(" %c", &ordem) == 1) {
        if (ordem == 's') {
            scanf(" A[%d..%d]", &start, &end);
            new_lista = sublista(new_lista, start, end);
            imprimir(new_lista);
        }
        if (ordem == '+') {
            scanf(" A[%d..%d] %d", &start, &end, &posicao);
            lista * lista_extraida = sublista(new_lista, start, end);
            new_lista = adicionar(lista_extraida, new_lista, posicao);
            imprimir(new_lista);
        }
        if (ordem == 'f')
        {
            break;
        }
    }   
    return 0;
}
