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
    }
    return deque;
};

int main() {
    // 구현 불완전함. pop 반환 타입이 배열 주소라서 pop -> push 하면 결과 뒤집어씌워짐. 자세한 설명은 깃헙에 따로 정리한 설명 참고.

    // create & push 테스트
    Deque deque1 = init_deque();
    print_array(&deque1);

    Deque deque2 = init_deque_left_push();
    print_array(&deque2);

    // get 테스트
    for (int i = 0; i < 100; ++i) {
        if (*(int *) deque_get(&deque1, i) != i) {
            printf("deque1's get() is not valid work - i: %d get(): %d", i, *(int *) deque_get(&deque1, i));
            exit(1);
        };
    }

    // get 테스트
    for (int i = 0; i < 100; ++i) {
        if (*(int *) deque_get(&deque2, i) != 99 - i) {
            printf("deque2's get() is not valid work - i: %d get(): %d", i, *(int *) deque_get(&deque2, i));
            exit(1);
        };
    }

    for (int i = 0; i < 100; ++i) {
        if (*(int *) deque_get(&deque2, i) != 99 - i) {
            printf("deque2's get() is not valid work - %d", *(int *) deque_get(&deque2, i));
            exit(1);
        };
    }

    // length 테스트
    if (deque_length(&deque1) != 100) {
        printf("deque1's length is not 100 - %d", deque_length(&deque1));
        exit(1);
    }
    if (deque_length(&deque2) != 100) {
        printf("deque2's length is not 100 - %d", deque_length(&deque2));
        exit(1);
    }

    // pop 테스트
    for (int i = 0; i < 100; ++i) {
        int *element = (int *) deque_pop(&deque1);
        if (*element != 99 - i) {
            printf("deque1's pop() is not valid work - expected: %d, got: %d\n", 99 - i, *element);
            exit(1);
        }
    }

    if (deque_length(&deque1) != 0) {
        printf("deque1's length is not 0 after pop - %d\n", deque_length(&deque1));
        exit(1);
    }

    // pop_left 테스트
    for (int i = 0; i < 100; ++i) {
        int *element = (int *) deque_pop_left(&deque2);
        if (*element != 99 - i) {
            printf("deque2's pop_left() is not valid work - expected: %d, got: %d\n", 99 - i, *element);
            exit(1);
        }
    }

    if (deque_length(&deque2) != 0) {
        printf("deque2's length is not 0 after pop_left - %d\n", deque_length(&deque2));
        exit(1);
    }

    deque_free(&deque1);
    deque_free(&deque2);
    return 0;
}