#include <stdio.h>
#include <time.h>
#include "heap.h"
#include "timer.h"
#include "log_write_to_file.h"

#define ELEMENT_COUNT 50000000
#define OPERATION_COUNT 200000

void add_data_test(Heap *heap) {
    for (int i = 0; i < ELEMENT_COUNT; i++) {
        int random_value = rand();
        heap_push(heap, random_value);
    }

    for (int i = 0; i < OPERATION_COUNT; i++) {
        int random_value = rand();
        MEASURE_TIME_ARGS_VOID("heap_push", heap_get_size(heap), heap_push, heap, random_value);
    }
}

void access_data_test(Heap *heap) {
    for (int i = 0; i < OPERATION_COUNT; i++) {
        MEASURE_TIME_ARGS_VOID("heap_peek", heap_get_size(heap), heap_peek, heap);
    }
}

void delete_data_test(Heap *heap) {
    for (int i = 0; i < OPERATION_COUNT; i++) {
        MEASURE_TIME_ARGS_VOID("heap_pop", heap_get_size(heap), heap_pop, heap);
    }
}

int main() {
    // 현재 시간을 가져오기 위한 구조체
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // 결과를 저장할 배열 선언
    char subsystems[100];  // 충분히 큰 크기로 선언

    // 현재 날짜와 시간을 포맷하여 문자열에 추가
    strftime(subsystems, sizeof(subsystems), "test.heap.%Y-%m-%d_%H-%M-%S", &tm);

    printf("subsystems: %s\n", subsystems);
    os_log_t logger = os_log_create(subsystems, "default");

    init_logger(&logger);

    // 힙 생성
    Heap *heap = heap_init();

    // 데이터 추가 테스트
    add_data_test(heap);

    // 데이터 접근 테스트
    access_data_test(heap);

    // 데이터 삭제 테스트
    delete_data_test(heap);

    // 힙 메모리 해제
    heap_free(heap);

    // 측정한 수행 시간 로그를 파일로 저장
    save_log(subsystems);

    return 0;
}
