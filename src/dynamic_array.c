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

static inline char *get(Darr *darr, int index);

Darr darr_create(int element_size) {
    assert(element_size > 0);
    void *prt = malloc(INIT_CAPACITY * element_size);
    assert(prt != NULL); // 이거는 if문으로 예외 던지는 게 맞을거 같긴 함.
    Darr darr = {prt, element_size, 0, (INIT_CAPACITY * element_size)};
    return darr;
};

void darr_add(Darr *darr, void *element) {
    if (darr->length * darr->element_size == darr->capacity) {
        resize(darr);
    };
    memcpy(get(darr, darr->length), element, darr->element_size);
    darr->length += 1;
};

void darr_insert(Darr *darr, int index, void *element) {
    assert(index < darr->length); // 추가할 인덱스는 현재 할당된 최대 인덱스(darr->length-1)보다 작거나 같아야 한다.
    memmove(get(darr, index + 1), // src와 dest의 메모리 영역이 겹치므로 memmove 사용
            get(darr, index),
            (darr->length - index) * darr->element_size);
    memcpy(get(darr, index), element, darr->element_size); // 메모리 주소가 안겹치므로 더 효율적인 memcpy 사용
    darr->length += 1;
}

void darr_delete(Darr *darr, int index) {
    assert(index < darr->length); // 삭제할 인덱스는 현재 할당된 최대 인덱스(darr->length-1)보다 작거나 같아야 한다.
    memmove(get(darr, index), // 메모리가 덮어씌워지면서 데이터 삭제됨
            get(darr, index+1),
            (darr->length - index) * darr->element_size);
    darr->length -= 1;
};

void *darr_get(Darr *darr, int index) {
    assert(index >= 0 && index < darr->length); // 유효한 인덱스 확인
    return get(darr, index);
};

int darr_length(Darr *darr) {
    return darr->length;
};

void darr_free(Darr *darr) {
    free(darr->data);
    // darr 자체는 동적 할당되지 않았으므로 free 할 필요 없음
};

static inline void resize(Darr *darr) {
    int new_capacity = darr->capacity * RESIZE_SCALE;
    void *new_data = realloc(darr->data, new_capacity);
    assert(new_data != NULL);
    darr->data = new_data;
    darr->capacity = new_capacity;
};

static inline char *get(Darr *darr, int index) {
    // 내부 함수이므로 assert 사용 안함, 하는게 맞나?
    return (char *) darr->data + index * darr->element_size;
};
