#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

void print_array(Deque *deque) {
    for (int i = 0; i < deque_length(deque); i++) {
        printf("%d ", *(int *) deque_get(deque, i));
    }
    printf("\n");
}

Deque init_deque() {
    Deque deque = deque_create(sizeof(int));
    for (int i = 0; i < 100; ++i) {
        deque_push(&deque, &i);
    }
    return deque;
};

Deque init_deque_left_push() {
    Deque deque = deque_create(sizeof(int));
    for (int i = 0; i < 100; ++i) {
        deque_push_left(&deque, &i);
        print_array(&deque);
    }
    return deque;
};

void finally_deque(Deque deque) {
    deque_free(&deque);
}

int main() {
    // create & push 테스트
    Deque deque1 = init_deque();
    print_array(&deque1);

    // length 테스트
    int length = deque_length(&deque1);
    if (length != 100) {
        printf("length is not 100");
        exit(1);
    }
    printf("%d ", length);

    // get 테스트
    for (int i = 0; i < length; ++i) {
        if (*(int*) deque_get(&deque1, i) != i) {
            exit(1);
        };
    }

    Deque deque2 = init_deque_left_push();
    print_array(&deque2);

    deque_free(&deque1);
    deque_free(&deque2);
    return 0;
}