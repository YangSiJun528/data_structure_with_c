#include <stdio.h>
#include <time.h>
#include "doubly_linked_list.h"
#include "timer.h"
#include "log_write_to_file.h"

#define ELEMENT_COUNT 200000 // 짝수여야 함
#define OPERATION_COUNT 20000

void add_data_test(LinkedList *linked_list) {
    for (int i = 0; i < ELEMENT_COUNT/2; i++) {
        Complex *data = (Complex *)malloc(sizeof(Complex));
        data->value = i;
        strcpy(data->name, "test");
        MEASURE_TIME_ARGS_VOID("linkedlist_push", linkedlist_length(linked_list), linkedlist_push, linked_list, data);
    }
}

void add_data_left_test(LinkedList *linked_list) {
    for (int i = 0; i < ELEMENT_COUNT/2; i++) {
        Complex *data = (Complex *)malloc(sizeof(Complex));
        data->value = i;
        strcpy(data->name, "test");
        MEASURE_TIME_ARGS_VOID("linkedlist_pushleft", linkedlist_length(linked_list), linkedlist_pushleft, linked_list, data);
    }
}

void access_data_test(LinkedList *linked_list) {
    for (int i = 0; i < ELEMENT_COUNT; i++) {
        Complex *data;
        MEASURE_TIME_ARGS_RETURN("linkedlist_get", linkedlist_length(linked_list), data, linkedlist_get, linked_list, i);
    }
}

void insert_data_test(LinkedList *linked_list) {
    for (int i = 0; i < OPERATION_COUNT; i++) {
        Complex *data = (Complex *)malloc(sizeof(Complex));
        data->value = i + ELEMENT_COUNT;
        strcpy(data->name, "insert");
        int index = (i % 3 == 0) ? 0 : (i % 3 == 1) ? linkedlist_length(linked_list) / 2 : linkedlist_length(linked_list) - 1;
        MEASURE_TIME_ARGS_VOID("linkedlist_insert", linkedlist_length(linked_list), linkedlist_insert, linked_list, index, data);
    }
}

void delete_data_test(LinkedList *linked_list) {
    for (int i = 0; i < OPERATION_COUNT; i++) {
        int index = (i % 3 == 0) ? 0 : (i % 3 == 1) ? linkedlist_length(linked_list) / 2 : linkedlist_length(linked_list) - 1;
        MEASURE_TIME_ARGS_VOID("linkedlist_delete", linkedlist_length(linked_list), linkedlist_delete, linked_list, index);
    }
}

void pop_data_test(LinkedList *linked_list) {
    for (int i = 0; i < OPERATION_COUNT; i++) {
        MEASURE_TIME_ARGS_VOID("linkedlist_pop", linkedlist_length(linked_list), linkedlist_pop, linked_list);
    }
}

void popleft_data_test(LinkedList *linked_list) {
    for (int i = 0; i < OPERATION_COUNT; i++) {
        MEASURE_TIME_ARGS_VOID("linkedlist_popleft", linkedlist_length(linked_list), linkedlist_popleft, linked_list);
    }
}

int main() {
    // 현재 시간을 가져오기 위한 구조체
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // 결과를 저장할 배열 선언
    char subsystems[100];  // 충분히 큰 크기로 선언

    // 현재 날짜와 시간을 포맷하여 문자열에 추가
    strftime(subsystems, sizeof(subsystems), "test.doubly_linked_list.%Y-%m-%d_%H-%M-%S", &tm);

    printf("subsystems: %s\n", subsystems);
    os_log_t logger = os_log_create(subsystems, "default");

    init_logger(&logger);

    // 연결 리스트 생성
    LinkedList linked_list = linkedlist_create();

    // 데이터 추가 테스트
    add_data_test(&linked_list);

    // 왼쪽에 데이터 추가 테스트
    add_data_left_test(&linked_list);

    // 데이터 접근 테스트
    access_data_test(&linked_list);

    // 데이터 삽입 테스트 (앞, 중간, 끝)
    insert_data_test(&linked_list);

    // 데이터 삭제 테스트 (앞, 중간, 끝)
    delete_data_test(&linked_list);

    // 데이터 팝 테스트
    pop_data_test(&linked_list);

    // 데이터 팝레프트 테스트
    popleft_data_test(&linked_list);

    // 측정한 수행 시간 로그를 파일로 저장
    save_log(subsystems);

    return 0;
}
