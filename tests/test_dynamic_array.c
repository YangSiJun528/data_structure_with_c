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
        MEASURE_TIME_ARGS_VOID("darr_add", sizeof(Data), darr_add, darr, &data);
    }
}

int access_data_test(Darr *darr) {
    for (int i = 0; i < ELEMENT_COUNT; i++) {
        Data *data;
        MEASURE_TIME_ARGS_RETURN("darr_get", sizeof(Data), data, darr_get, darr, i);
        if (data->id != i) {
            printf("데이터 불일치: %d != %d\n", data->id, i);
            return 0;
        }
    }
    return 1;
}

int insert_data_test(Darr *darr) {
    for (int i = 0; i < 1000; i++) {
        Data data = {i + ELEMENT_COUNT, "insert"};
        int index = (i % 3 == 0) ? 0 : (i % 3 == 1) ? darr->length / 2 : darr->length - 1;
        MEASURE_TIME_ARGS_VOID("darr_insert", sizeof(Data), darr_insert, darr, index, &data);
    }
    return 1;
}

int verify_insert_data(Darr *darr) {
    int original_length = ELEMENT_COUNT;
    int inserted_count = 0;
    for (int i = 0; i < 1000; i++) {
        int expected_id = i + ELEMENT_COUNT;
        int index;
        if (i % 3 == 0) {
            index = i;
        } else if (i % 3 == 1) {
            index = original_length / 2 + (inserted_count / 2);
        } else {
            index = original_length + inserted_count - 1;
        }
        Data *data = (Data *)darr_get(darr, index);
        if (data->id != expected_id) {
            printf("데이터 삽입 후 불일치: index %d, expected %d, got %d\n", index, expected_id, data->id);
            return 0;
        }
        inserted_count++;
    }
    return 1;
}

int delete_data_test(Darr *darr) {
    for (int i = 0; i < 1000; i++) {
        int index = (i % 3 == 0) ? 0 : (i % 3 == 1) ? darr->length / 2 : darr->length - 1;
        MEASURE_TIME_ARGS_VOID("darr_delete", sizeof(Data), darr_delete, darr, index);
    }
    return 1;
}

int verify_delete_data(Darr *darr) {
    for (int i = 0; i < ELEMENT_COUNT; i++) {
        Data *data = (Data *)darr_get(darr, i);
        if (data->id != i) {
            printf("데이터 불일치: %d != %d\n", data->id, i);
            return 0;
        }
    }
    return 1;
}

int pop_data_test(Darr *darr) {
    for (int i = 0; i < 1000; i++) {
        MEASURE_TIME_ARGS_VOID("darr_pop", sizeof(Data), darr_pop, darr);
    }
    return 1;
}

int verify_pop_data(Darr *darr) {
    if (darr->length != ELEMENT_COUNT - 1000) {
        printf("데이터 불일치 %d != %d\n", darr->length, ELEMENT_COUNT - 1000);
        return 0;
    }
    return 1;
}

int main() {
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
    if (!access_data_test(&darr)) return 0;

    // 데이터 삽입 테스트 (앞, 중간, 끝)
    if (!insert_data_test(&darr)) return 0;

    // 데이터 삽입 후 검증
    if (!verify_insert_data(&darr)) return 0;

    // 데이터 삭제 테스트 (앞, 중간, 끝)
    if (!delete_data_test(&darr)) return 0;

    // 데이터 삭제 후 접근 검증 (삽입 연산의 데이터를 제거하므로 전체 데이터 접근을 통한 검증 수행)
    if (!verify_delete_data(&darr)) return 0;

    // 데이터 팝 테스트
    if (!pop_data_test(&darr)) return 0;

    // 데이터 팝 후 검증
    if (!verify_pop_data(&darr)) return 0;

    // 동적 배열 해제
    darr_free(&darr);

    return 1;
}
