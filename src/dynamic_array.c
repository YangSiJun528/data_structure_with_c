//
// Created by sijun yang on 2024. 5. 26.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dynamic_array.h"

#define INIT_CAPACITY 10
#define RESIZE_SCALE 2

/*
 * 메모
 * 구현 시 예외나 에러를 반환하지 않게 구현됨. 사용자가 잘못된 인덱스에 접근하는 걸 막지 않음.
 * 대신 assert를 사용하여 개발/테스트 환경에서는 실패하도록 구현함.
 * c언어 자체가 예외처리 기능을 잘 제공하지 않는거 같고,
 * 어떤 점을 주의해야 하는지는 assert로 확인할 수 있기 때문.
 */

// inline 사용 이유 -> 성능
static inline void resize(Darr *darr);

Darr darr_create(int element_size) {
    assert(element_size > 0);
    void *prt = malloc(INIT_CAPACITY * element_size);
    Darr darr = {prt, element_size, 0, (INIT_CAPACITY * element_size)};
    return darr;
};

void darr_add(Darr *darr, void *element) {};

void darr_insert(Darr *darr, int index, void *element) {};

void darr_delete(Darr *darr, int index) {};

void *darr_get(Darr *darr, int index) {};

int darr_length(Darr *darr) {};

char* darr_to_string(Darr *darr) {};

void darr_free(Darr *darr) {
    free(darr->data);
    free(darr);
};

static inline void resize(Darr *darr) {};
