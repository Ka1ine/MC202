#include <stdio.h>
#define max_size 20

void heap_max(int A[], int size, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left < size && A[left] > A[largest])
        largest = left;

    if (right < size && A[right] > A[largest])
        largest = right;

    if (largest != i) {
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;

        heap_max(A, size, largest);
    }
}

void heap_build(int A[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heap_max(A, size, i);
}

void heap_remove(int A[], int* size) {
    if (*size <= 0)
        return;

    A[0] = A[*size - 1];
    (*size)--;
    heap_build(A, *size);
}

void heap_insert(int A[], int* size, int element) {
    if (*size >= max_size) {
        return;
    }

    A[*size] = element;
    (*size)++;
    heap_build(A, *size);
}

int main() {
    int A[] = {17, 5, 56, 13, 12, 33, 5, 17, 39, 1};
    int size = sizeof(A) / sizeof(A[0]);

    heap_build(A, size);

    for (int i = 0; i < size; ++i)
        printf("%d ", A[i]);

    printf("\n");
    heap_remove(A, &size);

    for (int i = 0; i < size; ++i)
        printf("%d ", A[i]);

    printf("\n");

    heap_insert(A, &size, 14);

    for (int i = 0; i < size; ++i)
        printf("%d ", A[i]);

    return 0;
}
