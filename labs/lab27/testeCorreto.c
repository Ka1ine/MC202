#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned chave;
    int prioridade;
    int timestamp;
} Par;

typedef struct {
    int capacidade;
    int tamanho;
    Par *heap;
} HeapMin;

HeapMin* criarHeap(int capacidade) {
    HeapMin* heap = (HeapMin*)malloc(sizeof(HeapMin));
    heap->capacidade = capacidade;
    heap->tamanho = 0;
    heap->heap = (Par*)malloc(capacidade * sizeof(Par));
    return heap;
}

void trocar(Par* a, Par* b) {
    Par temp = *a;
    *a = *b;
    *b = temp;
}

void subir(HeapMin* heap, int indice) {
    int pai = (indice - 1) / 2;
    while (indice > 0 && (heap->heap[indice].prioridade < heap->heap[pai].prioridade ||
                         (heap->heap[indice].prioridade == heap->heap[pai].prioridade &&
                          heap->heap[indice].timestamp < heap->heap[pai].timestamp))) {
        trocar(&heap->heap[indice], &heap->heap[pai]);
        indice = pai;
        pai = (indice - 1) / 2;
    }
}

void descer(HeapMin* heap, int indice) {
    int filhoEsquerda = 2 * indice + 1;
    int filhoDireita = 2 * indice + 2;
    int menor = indice;

    if (filhoEsquerda < heap->tamanho &&
        (heap->heap[filhoEsquerda].prioridade < heap->heap[menor].prioridade ||
         (heap->heap[filhoEsquerda].prioridade == heap->heap[menor].prioridade &&
          heap->heap[filhoEsquerda].timestamp < heap->heap[menor].timestamp))) {
        menor = filhoEsquerda;
    }

    if (filhoDireita < heap->tamanho &&
        (heap->heap[filhoDireita].prioridade < heap->heap[menor].prioridade ||
         (heap->heap[filhoDireita].prioridade == heap->heap[menor].prioridade &&
          heap->heap[filhoDireita].timestamp < heap->heap[menor].timestamp))) {
        menor = filhoDireita;
    }

    if (menor != indice) {
        trocar(&heap->heap[indice], &heap->heap[menor]);
        descer(heap, menor);
    }
}

void inserir(HeapMin* heap, unsigned chave, int prioridade, int timestamp) {
    if (heap->tamanho == heap->capacidade) {
        printf("Erro: Heap cheio\n");
        return;
    }

    Par novoPar;
    novoPar.chave = chave;
    novoPar.prioridade = prioridade;
    novoPar.timestamp = timestamp;

    heap->heap[heap->tamanho] = novoPar;
    subir(heap, heap->tamanho);
    heap->tamanho++;
}

void removerMinimo(HeapMin* heap) {
    if (heap->tamanho == 0) {
        return;
    }

    heap->heap[0] = heap->heap[heap->tamanho - 1];
    heap->tamanho--;
    descer(heap, 0);
}

void obterMinimo(HeapMin* heap) {
    if (heap->tamanho == 0) {
        printf("fila de prioridades vazia\n");
        return;
    }

    printf("prioridade minima %d, chave %u\n", heap->heap[0].prioridade, heap->heap[0].chave);
}

void liberarHeap(HeapMin* heap) {
    free(heap->heap);
    free(heap);
}

int main() {
    HeapMin* heap = NULL;

    char comando;
    unsigned chave;
    int prioridade;
    int timestamp = 0;

    while (scanf("%c", &comando) != EOF) {
        switch (comando) {
            case 'c':
                if (heap != NULL) {
                    liberarHeap(heap);
                }
                scanf("%d", &prioridade);
                heap = criarHeap(prioridade);
                break;

            case 'i':
                scanf("%u %d", &chave, &prioridade);
                inserir(heap, chave, prioridade, timestamp);
                timestamp++;
                break;

            case 'r':
                removerMinimo(heap);
                break;

            case 'm':
                obterMinimo(heap);
                break;

            case 't':
                liberarHeap(heap);
                return 0;
        }
    }

    return 0;
}
