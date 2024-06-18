#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash_map.h"
#include "timer.h"
#include "log_write_to_file.h"

#define ELEMENT_COUNT 50000000 // 성능 테스트 전 미리 생성할 데이터 개수
#define OPERATION_COUNT 200000

void add_data_test(HashMap *hash_map) {
    srand(time(NULL));
    for (int i = 0; i < ELEMENT_COUNT; i++) {
        Data *random_data = malloc(sizeof(Data)); // 임의의 데이터 생성
        random_data->data = rand(); // 데이터 값 설정
        hash_map_put(hash_map, i, random_data);
    }

    for (int i = 0; i < OPERATION_COUNT; i++) {
        KEY random_key = rand(); // 임의의 키 생성
        MEASURE_TIME_ARGS_VOID("hash_map_put", hash_map_size(hash_map), hash_map_put, hash_map, random_key, NULL);
    }
}

void access_data_test(HashMap *hash_map) {
    srand(time(NULL));
    for (int i = 0; i < OPERATION_COUNT; i++) {
        KEY random_key = rand(); // 임의의 키 생성
        MEASURE_TIME_ARGS_VOID("hash_map_get", hash_map_size(hash_map), hash_map_get, hash_map, random_key);
    }
}

void delete_data_test(HashMap *hash_map) {
    srand(time(NULL));
    for (int i = 0; i < OPERATION_COUNT; i++) {
        KEY random_key = rand(); // 임의의 키 생성
        MEASURE_TIME_ARGS_VOID("hash_map_remove", hash_map_size(hash_map), hash_map_remove, hash_map, random_key);
    }
}

int main() {
    // 현재 시간을 가져오기 위한 구조체
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // 결과를 저장할 배열 선언
    char subsystems[100];  // 충분히 큰 크기로 선언

    // 현재 날짜와 시간을 포맷하여 문자열에 추가
    strftime(subsystems, sizeof(subsystems), "test.hash_map.%Y-%m-%d_%H-%M-%S", &tm);

    printf("subsystems: %s\n", subsystems);
    os_log_t logger = os_log_create(subsystems, "default");

    init_logger(&logger);

    // 해시 맵 생성
    HashMap *hash_map = hash_map_init();

    // 데이터 추가 테스트
    add_data_test(hash_map);

    // 데이터 접근 테스트
    access_data_test(hash_map);

    // 데이터 삭제 테스트
    delete_data_test(hash_map);

    // 해시 맵 메모리 해제
    hash_map_free(hash_map);

    // 측정한 수행 시간 로그를 파일로 저장
    save_log(subsystems);

    return 0;
}
