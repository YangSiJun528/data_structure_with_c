//
// Created by sijun yang on 2024. 6. 2.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "deque.h"

/*
 * Circular Array(원형 배열)을 사용한 구현.
 * Linked List-Based 구현 방법도 있는데, Linked List랑 별반 다를 것도 없어서...
 *
 * rear는 항상 추가하고 이동한다. front는 이동하고 추가한다.
 *
 * front랑 rear랑 같은 경우, 요소가 하나도 없거나, 하나 빼고 다 차있거나, length를 확인해야 한다.
 */

#define INIT_CAPACITY 10
#define RESIZE_SCALE 2

static inline void *get(Deque *Deque, int index);

static inline bool is_full(Deque *deque);

static inline void resize(Deque *Deque);

Deque deque_create(int element_size) {
    assert(element_size > 0);
    void *ptr = malloc(INIT_CAPACITY * element_size);
    assert(ptr != NULL);
    Deque deque = {ptr, 0, 0, INIT_CAPACITY, element_size};
    return deque;
}

void deque_push(Deque *Deque, void *element) {
    if (is_full(Deque)) {
        resize(Deque);
    }
    assert(deque_length(Deque) == 0 || Deque->front != Deque->rear);
    memcpy(get(Deque, Deque->rear), element, Deque->element_size);
    Deque->rear = (Deque->rear + 1) % Deque->capacity;
}

void *deque_pop(Deque *Deque) {
    assert(deque_length(Deque) > 0);
    int popped_index = Deque->rear - 1;
    Deque->rear = Deque->rear == 0 ? Deque->capacity - 1 : Deque->rear - 1;
    return get(Deque, popped_index);
}

void deque_push_left(Deque *Deque, void *element) {
    if (is_full(Deque)) {
        resize(Deque);
    }
    assert(deque_length(Deque) == 0 || Deque->front != Deque->rear);
    Deque->front = Deque->front == 0 ? Deque->capacity - 1 : Deque->front - 1;
    memcpy(get(Deque, Deque->front), element, Deque->element_size);
}

void *deque_pop_left(Deque *Deque) {
    assert(deque_length(Deque) > 0);
    int popped_index = Deque->front;
    Deque->front = Deque->front == 0 ? Deque->capacity - 1 : Deque->front + 1;
    return get(Deque, popped_index);;
}

void *deque_get(Deque *Deque, int index) {
    assert(0 >= index || deque_length(Deque) > index);
    int actual_index = (Deque->front + index) % Deque->capacity;
    return get(Deque, actual_index);
}

int deque_length(Deque *Deque) {
    if (Deque->front <= Deque->rear) { // front가 앞에 위치하거나 같으면
        return Deque->rear - Deque->front;
    }
    return Deque->capacity - Deque->front + Deque->rear;
}

void deque_free(Deque *Deque) {
    free(Deque->data);
}

// 내부 배열 기준 index로 접근
static inline void *get(Deque *Deque, int index) {
    assert(index < Deque->capacity);
    return (char *) Deque->data + index * Deque->element_size;
}

static inline bool is_full(Deque *Deque) {
    return (deque_length(Deque) == Deque->capacity - 1) ? true : false;
}

static inline void resize(Deque *Deque) {
    int old_capacity = Deque->capacity;
    int new_capacity = old_capacity * RESIZE_SCALE;
    void *new_data = realloc(Deque->data, new_capacity * Deque->element_size);
    assert(new_data != NULL);
    Deque->data = new_data;
    Deque->capacity = new_capacity;

    if (Deque->front > Deque->rear) { // 조건이 아닌 경우 front가 rear보다 앞에 있으므로 메모리 이동이 필요없음.
        int elements_after_front = old_capacity - Deque->front;
        void *dest = get(Deque, old_capacity + Deque->front);
        void *src = get(Deque, Deque->front);
        memmove(dest, src, elements_after_front * Deque->element_size);
        Deque->front = old_capacity + 1;
    }
}