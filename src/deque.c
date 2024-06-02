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
 * rear는 항상 다음에 추가할 위치를 바라보고 있다.
 * front는 항상(길이 0 제외) 현재 가장 앞의 데이터를 바라보고 있다.
 *
 * front랑 rear랑 같은 경우, 요소가 하나도 없거나, 다 차있거나, 확실하게 확인하기 위해선 length를 확인해야 한다.
 */

#define INIT_CAPACITY 10
#define RESIZE_SCALE 2

static inline void *get(Deque *Deque, int index);

static inline void resize(Deque *Deque);

static inline int last_index(Deque *Deque);

Deque deque_create(int element_size) {
    assert(element_size > 0);
    void *prt = malloc(INIT_CAPACITY * element_size);
    assert(prt != NULL);
    Deque deque = {prt, 0, 0, (INIT_CAPACITY * element_size), element_size};
    return deque;
};

void deque_push(Deque *Deque, void *element) {
    if ((deque_length(Deque)+1) * Deque->element_size == Deque->capacity) { // length + 1 을 사용하기 때문에, (가능한 최대 크기 - 한 요소의 크기) 인 상태에서 resize, 코드 구현이 어려워서 일단 이렇게 했는데, 나중에 수정해야 할 듯?
        resize(Deque);
    }
    memcpy(get(Deque, Deque->rear), element, Deque->element_size);
    if (Deque->rear == last_index(Deque)) { // 끝 위치인 경우
        Deque->rear = 0;
    } else {
        Deque->rear += 1;
    }
};

void *deque_pop(Deque *Deque) {
    // 길이 0 이하면 assert
    // rear 하나 빼기
    // 결과 반환
};

void deque_push_left(Deque *Deque, void *element) {

};

void *deque_pop_left(Deque *Deque) {
    // 길이 0 이하면 assert
    // front 하나 빼기
    // 결과 반환
};

void *deque_get(Deque *Deque, int index) {
    assert(0 >= index || deque_length(Deque) > index);
    return get(Deque, index);
};

int deque_length(Deque *Deque) {
    if (Deque->front <= Deque->rear) {
        return Deque->rear - Deque->front;
    }
    return last_index(Deque) - Deque->front + Deque->rear + 1;
};

void deque_free(Deque *Deque) {
    free(Deque->data);
};

static inline void *get(Deque *Deque, int index) {
    if (Deque->front + index > last_index(Deque)) {
        return (char *) Deque->data + (Deque->front - last_index(Deque) + index) * Deque->element_size;
    } else {
        return (char *) Deque->data + (Deque->front + index) * Deque->element_size;
    }
}

static inline int last_index(Deque *Deque) {
    return (Deque->capacity / Deque->element_size) - 1;
}

static inline void resize(Deque *Deque) {
    int new_capacity = Deque->capacity * RESIZE_SCALE;
    void *new_data = realloc(Deque->data, new_capacity);
    assert(new_data != NULL);
    Deque->data = new_data;
    Deque->capacity = new_capacity;
};


