//
// Created by sijun yang on 2024. 6. 15. .
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "heap.h"

Heap heap_init() {};

Heap heap_init_set_capacity(int init_capacity) {};

void heap_push(Heap heap, TYPE data) {};

TYPE heap_pop(Heap heap) {};

int heap_get_size(Heap heap) {};

bool heap_is_empty(Heap heap) {};

TYPE heap_peek(Heap heap) {};

void heap_free(Heap heap) {};
