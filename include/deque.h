//
// Created by sijun yang on 2024. 5. 26.
//

#include "dynamic_array.h"

#ifndef DEQUE_H
#define DEQUE_H

extern int INIT_CAPACITY;
extern int RESIZE_SCALE;

typedef struct {
    void *data;     // 정적 배열 포인터
    int front;      // 원형 큐의 front가 되는 정적 배열의 인덱스
    int rear;       // 원형 큐의 rear거 되는 정적 배열의 인덱스
    int capacity;   // 현재 할당된 요소의 개수
    int element_size;   // 요소 한 개의 크기
} Deque;

Deque deque_create(int element_size);
void deque_push(Deque *Deque, void *element);
void* deque_pop(Deque *Deque);
void deque_push_left(Deque *Deque, void *element);
void* deque_pop_left(Deque *Deque);
void* deque_get(Deque *Deque, int index);
int deque_length(Deque *Deque);
void deque_free(Deque *Deque);

#endif //DEQUE_H
