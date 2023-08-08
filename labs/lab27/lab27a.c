#include <stdlib.h>
#include <stdio.h>

typedef struct {
    unsigned key;
    int priority;
    int timestamp;
} Heap;

typedef struct {
    int capacity;
    int size;
    Heap *heap;
} Min_Heap;

Min_Heap* create_heap(int capacity){
    Min_Heap* heap = (Min_Heap*)malloc(sizeof(Min_Heap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->heap = (Heap*)malloc(capacity * sizeof(Heap));
    return heap;
}

void free_heap(Min_Heap * heap){
    free(heap->heap);
    free(heap);
}

void botton_up(Min_Heap* heap, int i){
    int pai = (i - 1) / 2;
    while (i > 0 && (heap->heap[i].priority < heap->heap[pai].priority ||
                         (heap->heap[i].priority == heap->heap[pai].priority &&
                          heap->heap[i].timestamp < heap->heap[pai].timestamp))) {
        Heap temp = heap->heap[i];
        heap->heap[i] = heap->heap[pai];
        heap->heap[pai] = temp;
        i = pai;
        pai = (i - 1) / 2;
    }
    
}

void top_down(Min_Heap* heap, int i){
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;
    int largest = i;

    if (left < heap->size && (heap->heap[left].priority < heap->heap[largest].priority ||
         (heap->heap[left].priority == heap->heap[largest].priority &&
          heap->heap[left].timestamp < heap->heap[largest].timestamp))) {
        largest = left;
    }

    if (right < heap->size && (heap->heap[right].priority < heap->heap[largest].priority ||
         (heap->heap[right].priority == heap->heap[largest].priority &&
          heap->heap[right].timestamp < heap->heap[largest].timestamp))) {
        largest = right;
    }
    
    if (largest != i) {
        Heap temp = heap->heap[i];
        heap->heap[i] = heap->heap[largest];
        heap->heap[largest] = temp;
        top_down(heap, largest);
    }
}

void insert_heap(Min_Heap* heap, unsigned key, int priority, int timestamp){
    if (heap->size == heap->capacity){
        return;
    }
    Heap p;
    p.key = key;
    p.priority = priority;
    p.timestamp = timestamp;
    heap->heap[heap->size] = p;
    botton_up(heap, heap->size);
    heap->size++;
}

void remove_heap(Min_Heap* heap){
    if (heap->size == 0){
        return;
    }
    heap->heap[0] = heap->heap[heap->size - 1];
    heap->size--;
    top_down(heap, 0);
}

void get_min_heap(Min_Heap* heap) {
    if (heap->size == 0) {
        printf("fila de prioridades vazia\n");
        return;
    }

    printf("prioridade minima %d, chave %u\n", heap->heap[0].priority, heap->heap[0].key);
}

int main() {
    Min_Heap* heap = NULL;
    unsigned key;
    char opcao;
    int priority;
    int timestamp = 0;
    while (scanf(" %c", &opcao) != EOF) {
        if (opcao == 'c') {
            if (heap != NULL) 
                free_heap(heap);
            
            scanf("%d", &priority);
            heap = create_heap(priority);
        }
        
        if (opcao == 'i') {
            scanf("%u %d", &key, &priority);
            insert_heap(heap, key, priority, timestamp);
            timestamp++;
        }

        if (opcao == 'r') 
            remove_heap(heap);
        
        if (opcao == 'm') 
            get_min_heap(heap);

        if (opcao == 't') {
            free_heap(heap);
            return 0;
        }
    }
}
