//
// Created by sijun yang on 2024. 6. 2.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "deque.h"

/*
 * Circular Array(원형 배열)을 사용한 구현.
 * Linked List-Based 구현도 있는데, Linked List랑 별반 다를 것도 없어서...
 */

#define INIT_CAPACITY 10
#define RESIZE_SCALE 2

Deque deque_create(int element_size) {
    assert(element_size > 0);
    void *prt = malloc(INIT_CAPACITY * element_size);
    assert(prt != NULL); // 이거는 if문으로 예외 던지는 게 맞을거 같긴 함.
    Deque deque = {prt, element_size, 0,  0, (INIT_CAPACITY * element_size)};
    return deque;
};

void deque_push(Deque *Deque, void *element) {};

void *deque_pop(Deque *Deque) {};

void deque_push_left(Deque *Deque, void *element) {};

void *deque_pop_left(Deque *Deque) {};

void *deque_get(Deque *Deque, int index) {};

int deque_length(Deque *Deque) {
    if (Deque->front < Deque->rear) {
        return Deque->rear - Deque->front;
    }
    return Deque->front-Deque->rear;
};

void deque_free(Deque *Deque) {
    free(Deque->data);
};


