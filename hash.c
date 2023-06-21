#include <stdio.h>
#include <stdlib.h>

#define N 13

typedef struct numero {
    int data;
    int mat;
    struct numero* next;
} numero;

int hash(int mat) {
    return mat % 11;
}

int hash2(int mat){
    return N - 2 - mat % (N - 2);
}

void insere_soldagem(numero** vetor, int mat, int data) {
    int h = hash(mat);
    while (vetor[h] != NULL) {
        if (vetor[h]->mat == mat) {
            break;
        }
        h = (h + 1) % 11;
    }
    
    vetor[h] = (numero*)malloc(sizeof(numero));
    vetor[h]->mat = mat;
    vetor[h]->data = data;
}

int busca_soldagem(numero** vetor, int mat){
    int h = hash(mat);
    while (vetor[h] != NULL) {
        if (vetor[h]->mat == mat) {
            printf("%d\n", vetor[h]->data);
            return 1; 
        }
        h = (h + 1) % 11;
    }
    return 0;
}

numero* busca_encadeado(numero ** vetor, int mat){
    int h = hash(mat);
    numero* a = vetor[h];
    while (a != NULL){
        if (a->mat == mat){
            return a;
        }
        a = a->next;
    }
    return NULL;
}

numero* insere_encadeamento(numero** vetor, int mat, int data){
    int h = hash(mat);
    numero* p = NULL;
    numero* a = vetor[h];
    while (a != NULL){
        if (a->mat == mat){
            break;
        }
        p = a;
        a = a->next;
    }
    a = (numero*)malloc(sizeof(numero));
    a->mat = mat;
    a->data = data;
    if(p == NULL)
        vetor[h] = a;
    else
        p->next = a;
    return a;
}

int main() {
    numero* vetor[13] = { 0 };

    insere_soldagem(vetor, 1200, 32);
    insere_soldagem(vetor, 1201, 44);
    insere_soldagem(vetor, 1202, 73);
    insere_soldagem(vetor, 1203, 58);
    insere_soldagem(vetor, 1303, 57);

    
    for (int i = 0; i < 13; i++) {
        if (vetor[i] != NULL) {
            printf("Matricula: %d, Dado: %d\n", vetor[i]->mat, vetor[i]->data);
        }
    }
    
    busca_soldagem(vetor, 1202);

    // ----------------------------------------------------------------------
    numero* vetor2[13] = { 0 };

    insere_encadeamento(vetor2, 1200, 32);
    insere_encadeamento(vetor2, 1203, 58);
    insere_encadeamento(vetor2, 1303, 57);
    insere_encadeamento(vetor2, 1503, 59);
    insere_encadeamento(vetor2, 1201, 44);
    insere_encadeamento(vetor2, 1202, 73);
    

    
    for (int i = 0; i < 13; i++) {
        if (vetor2[i] != NULL) {
            printf("Matricula: %d, Dado: %d\n", vetor2[i]->mat, vetor2[i]->data);
        }
    }
    
    busca_encadeado(vetor2, 1202);

    return 0;
}