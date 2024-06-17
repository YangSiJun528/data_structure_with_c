//
// Created by sijun yang on 2024. 6. 17..
//

#ifndef DATA_STRUCTURE_WITH_C_HASH_MAP_H
#define DATA_STRUCTURE_WITH_C_HASH_MAP_H

// 내부 구현 상, 타입이 고정됨.
#define KEY int // hash 함수 값으로 주소 값을 받으면, Java의 equals 같은 함수가 필요해지기 때문에, Key는 int 형으로 사용
#define VALUE Data // Value는 구조체면 다 상관 없는데, 미리 정의한 Data를 사용함.

#include <stdbool.h>

typedef struct {
    int data;
} Data;

typedef struct {
    VALUE **bucket;
    int capacity;
    int size;
} HashMap;

HashMap *hash_map_init();

void hash_map_put(HashMap *hash_map, KEY key, VALUE value);

VALUE hash_map_get(HashMap *hash_map, KEY key);

void hash_map_remove(HashMap *hash_map, KEY key);

bool hash_map_contains(HashMap *hash_map, KEY key);

int hash_map_size(HashMap *hash_map);

// keys/values 도 있어야 하는데, 구현 비슷하고, 귀찮으니까... 생략
int hash_map_entries(HashMap *hash_map);

void hash_map_free(HashMap *hash_map);

#endif //DATA_STRUCTURE_WITH_C_HASH_MAP_H
