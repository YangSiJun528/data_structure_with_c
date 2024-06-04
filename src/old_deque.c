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
    if (deque_length(Deque) + 1 == Deque->capacity / Deque->element_size) {
        resize(Deque);
    }
    Deque->rear = (Deque->rear + 1) % last_index(Deque);
    memcpy(get(Deque, Deque->rear), element, Deque->element_size);
    //assert(Deque->front != Deque->rear);
}

void *deque_pop(Deque *Deque) {
    // 길이 0 이하면 assert
    // rear 하나 빼기
    // 결과 반환
};

void deque_push_left(Deque *Deque, void *element) {
    if (deque_length(Deque) + 1 == Deque->capacity / Deque->element_size) {
        resize(Deque);
    }
    Deque->front = (Deque->front - 1) % last_index(Deque);
    memcpy(get(Deque, Deque->front), element, Deque->element_size);
    //assert(Deque->front != Deque->rear);
};

void *deque_pop_left(Deque *Deque) {
    // 길이 0 이하면 assert
    // front 하나 빼기
    // 결과 반환
};

void *deque_get(Deque *Deque, int index) {
    assert(0 >= index || deque_length(Deque) > index);
    int actual_index = (Deque->front + index) % last_index(Deque);
    return get(Deque, actual_index);
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
    assert(index < last_index(Deque));
    return (char *) Deque->data + index * Deque->element_size;
}

static inline int last_index(Deque *Deque) {
    return (Deque->capacity / Deque->element_size) - 1;
}

static inline void resize(Deque *Deque) {
    int old_last_index = last_index(Deque);
    int new_capacity = Deque->capacity * RESIZE_SCALE;
    void *new_data = realloc(Deque->data, new_capacity);
    assert(new_data != NULL);
    Deque->data = new_data;
    Deque->capacity = new_capacity;

    if (Deque->front < Deque->rear) {
        // skip. 이 경우 항상 front가 0이고 rear가 last index임을 보장함.
    } else {
        // front ~ old last index 까지를 갱신된 인덱스의 우측 끝으로 이동시킴
        // get 함수를 사용하여 인덱스를 계산할 필요 없이 직접 계산
        void *dest = get(Deque, Deque->front + old_last_index);

        void *src = get(Deque, Deque->front);
        memmove(dest, src, (old_last_index - Deque->front) * Deque->element_size);
        Deque->front = Deque->front + old_last_index;
    }
}


//    r f
//0 1 2 3 4 5 6 7 8 9


