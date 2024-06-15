//
// Created by sijun yang on 2024. 6. 15..
//

#ifndef DATA_STRUCTURE_WITH_C_HEAP_TREE_H
#define DATA_STRUCTURE_WITH_C_HEAP_TREE_H

#define TYPE int // < 연산자 사용이 가능한 기본형만 Type으로 설정, 그래서 반환 시 포인터로 반환 안해도 됨.

#include <stdbool.h>

extern int DEFAULT_INIT_CAPACITY;
extern int RESIZE_SCALE;

typedef struct {
    TYPE *root;
    int capacity;
    int size;
} Heap;

Heap heap_init();

Heap heap_init_set_capacity(int init_capacity);

void heap_push(TYPE data);

TYPE heap_pop();

int heap_get_size();

bool heap_is_empty();

TYPE heap_peek();

#endif //DATA_STRUCTURE_WITH_C_HEAP_TREE_H
