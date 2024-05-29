//
// Created by sijun yang on 2024. 5. 26.
//

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

extern int INIT_CAPACITY;
extern int RESIZE_SCALE;

typedef struct {
    void *data;         // 데이터 포인터
    int element_size;   // 요소의 크기
    int length;         // 현재 크기
    int capacity;       // 용량
} Darr;

Darr darr_create(int element_size);
void darr_add(Darr *darr, void *element);
void darr_insert(Darr *darr, int index, void *element);
void darr_pop(Darr *darr);
void darr_delete(Darr *darr, int index);
void* darr_get(Darr *darr, int index);
int darr_length(Darr *darr);
void darr_free(Darr *darr);

#endif //DYNAMIC_ARRAY_H
