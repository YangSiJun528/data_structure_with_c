#include <stdio.h>
#include <time.h>
#include "dynamic_array.h"
#include "timer.h"

#define ELEMENT_COUNT 10000000

// 더미 데이터 구조체
typedef struct {
    int id;
    char name[20];
} Data;

void add_data_test(Darr *darr) {
    for (int i = 0; i < ELEMENT_COUNT; i++) {
        Data data = {i, "test"};
        MEASURE_TIME_ARGS_VOID("darr_add", darr_length(darr), darr_add, darr, &data);
    }
}

void access_data_test(Darr *darr) {
    for (int i = 0; i < ELEMENT_COUNT; i++) {
        Data *data;
        MEASURE_TIME_ARGS_RETURN("darr_get", darr_length(darr), data, darr_get, darr, i);
    }
}

void insert_data_test(Darr *darr) {
    for (int i = 0; i < 1000; i++) {
        Data data = {i + ELEMENT_COUNT, "insert"};
        int index = (i % 3 == 0) ? 0 : (i % 3 == 1) ? darr->length / 2 : darr->length - 1;
        MEASURE_TIME_ARGS_VOID("darr_insert", darr_length(darr), darr_insert, darr, index, &data);
    }
}

void delete_data_test(Darr *darr) {
    for (int i = 0; i < 1000; i++) {
        int index = (i % 3 == 0) ? 0 : (i % 3 == 1) ? darr->length / 2 : darr->length - 1;
        MEASURE_TIME_ARGS_VOID("darr_delete", darr_length(darr), darr_delete, darr, index);
    }
}

void  pop_data_test(Darr *darr) {
    for (int i = 0; i < 1000; i++) {
        MEASURE_TIME_ARGS_VOID("darr_pop", darr_length(darr), darr_pop, darr);
    }
}

int main() {
    // 이미 기능 테스트는 완료 되었으므로, 이 테스트에서는 시간 측정만 함.

    // 현재 시간을 가져오기 위한 구조체
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // 결과를 저장할 배열 선언
    char subsystems[100];  // 충분히 큰 크기로 선언

    // 현재 날짜와 시간을 포맷하여 문자열에 추가
    strftime(subsystems, sizeof(subsystems), "test.dynamic_array.%Y-%m-%d_%H-%M-%S", &tm);

    printf("subsystems: %s\n", subsystems);
    os_log_t logger = os_log_create(subsystems, "default");
    // log show --predicate 'subsystem == "test.dynamic_array.2024-05-30_14-15-23"' --info

    init_logger(&logger);

    // 동적 배열 생성
    Darr darr = darr_create(sizeof(Data));

    // 데이터 추가 테스트
    add_data_test(&darr);

    // 데이터 접근 테스트
    access_data_test(&darr);

    // 데이터 삽입 테스트 (앞, 중간, 끝)
    insert_data_test(&darr);

    // 데이터 삭제 테스트 (앞, 중간, 끝)
    delete_data_test(&darr);

    // 데이터 팝 테스트
    pop_data_test(&darr);

    // 동적 배열 해제
    darr_free(&darr);

    return 0;
}
