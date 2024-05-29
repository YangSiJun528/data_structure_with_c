#include <stdio.h>
#include "dynamic_array.h"

// Helper function to print the array
void print_array(Darr *darr, void (*print_element)(void *)) {
    for (int i = 0; i < darr_length(darr); i++) {
        print_element(darr_get(darr, i));
    }
    printf("\n");
}

// Function to print integer elements
void print_int(void *element) {
    printf("%d ", *(int *)element);
}

int main() {
    // Create a dynamic array for integers
    Darr darr = darr_create(sizeof(int));

    // Test adding elements
    for (int i = 0; i < 15; i++) {
        darr_add(&darr, &i);
    }
    printf("Array after adding elements: ");
    print_array(&darr, print_int);

    // Test inserting an element
    int value = 9999;
    darr_insert(&darr, 5, &value);
    printf("Array after inserting 99 at index 5: ");
    print_array(&darr, print_int);

    // Test deleting an element
    darr_delete(&darr, 5);
    printf("Array after deleting element at index 5: ");
    print_array(&darr, print_int);

    // Test popping an element
    darr_pop(&darr);
    printf("Array after popping: ");
    print_array(&darr, print_int);

    // Test getting elements
    printf("Element at index 0: %d\n", *(int *)darr_get(&darr, 0));
    printf("Element at index 10: %d\n", *(int *)darr_get(&darr, 10));

    // Test length of the array
    printf("Length of the array: %d\n", darr_length(&darr));

    // Free the dynamic array
    darr_free(&darr);

    return 0;
}
