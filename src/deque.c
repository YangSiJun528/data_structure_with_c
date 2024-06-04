//
// Created by sijun yang on 2024. 6. 2.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "deque.h"

/*
 * Circular Array(원형 배열)을 사용한 구현.
 * Linked List-Based 구현 방법도 있는데, Linked List랑 별반 다를 것도 없어서...
 *
 * front, rear는 항상 다음에 추가할 위치를 바라보고 있다.
 *
 * front랑 rear랑 같은 경우, 요소가 하나도 없거나, 하나 빼고 다 차있거나, length를 확인해야 한다.
 */

#define INIT_CAPACITY 10
#define RESIZE_SCALE 2

static inline void *get(Deque *Deque, int index);

static inline void resize(Deque *Deque);

static inline int last_index(Deque *Deque);

Deque deque_create(int element_size) {
    assert(element_size > 0);
    void *ptr = malloc(INIT_CAPACITY * element_size);
    assert(ptr != NULL);
    Deque deque = {ptr, 0, 0, INIT_CAPACITY * element_size, element_size};
    return deque;
}

void deque_push(Deque *Deque, void *element) {
}

void *deque_pop(Deque *Deque) {
};

void deque_push_left(Deque *Deque, void *element) {
};

void *deque_pop_left(Deque *Deque) {
};

void *deque_get(Deque *Deque, int index) {
};

int deque_length(Deque *Deque) {
};

void deque_free(Deque *Deque) {
    free(Deque->data);
};

static inline void *get(Deque *Deque, int index) {
}

static inline int last_index(Deque *Deque) {
}

static inline void resize(Deque *Deque) {
}


