#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// Function to print the heap array
void print_heap(Heap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

// 하드코딩된 1이상 29이하 (총 30개)의 랜덤한 숫자를 가지는 배열
int random_numbers[] = {
        3, 14, 27, 8, 22, 5, 19, 1, 12, 30, 6, 17, 23, 9, 2, 25,
        11, 21, 7, 13, 26, 4, 20, 16, 24, 10, 18, 29, 15, 28
};

int main() {
    // Initialize heap with default capacity
    Heap *heap = heap_init();

    // Test adding elements to the heap
    for (int i = 0; i < 30; i++) {
        heap_push(heap, random_numbers[i]);
    }
    printf("Heap after adding elements: ");
    print_heap(heap);

    // Test peeking at the top element
    printf("Top element (peek): %d\n", heap_peek(heap));

    // Test popping elements from the heap
    printf("Popping elements from heap to check min-heap order: ");
    for (int i = 30; i >= 1; i--) {
        int popped = heap_pop(heap);
        printf("%d ", popped);
        if (popped != i) {
            printf("\nError: expected %d but got %d\n", i, popped);
            exit(1);
        }
    }
    printf("\n");

    // Check if heap is empty
    printf("Is heap empty? %s\n", heap_is_empty(heap) ? "Yes" : "No");

    // Initialize heap with custom capacity
    Heap *custom_heap = heap_init_set_capacity(20);

    // Test adding elements to the custom capacity heap
    for (int i = 1; i <= 15; i++) {
        heap_push(custom_heap, random_numbers[i]);
    }
    printf("Custom heap after adding elements: ");
    print_heap(custom_heap);

    // Test size of the heap
    printf("Size of the custom heap: %d\n", heap_get_size(custom_heap));

    // Free the heaps
    heap_free(heap);
    heap_free(custom_heap);

    return 0;
}
