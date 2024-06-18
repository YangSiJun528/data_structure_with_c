//
// Created by sijun yang on 2024. 6. 17..
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hash_map.h"

int DEFAULT_INIT_CAPACITY = 10;
int RESIZE_SCALE = 2;
float LOAD_FACTOR = 0.7f;
unsigned int SEED = 0x45d9f3b;

static inline unsigned int hashcode(KEY key) {
    unsigned int hash = (unsigned int) key;
    // 비트 연산을 사용하여 해시 값 계산
    hash = ((hash >> 16) ^ hash) * SEED;
    hash = ((hash >> 16) ^ hash) * SEED;
    hash = (hash >> 16) ^ hash;
    return hash;
}

static inline Node *create_node(KEY key, VALUE *value) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->key = key;
    new_node->value = value;
    return new_node;
}


static inline int get_index(HashMap *hash_map, unsigned int hash) {
    int index = abs((int) hash % hash_map->slot_capacity); // 이게 맞나? 어차피 뭐 size도 int 제한 있으니까 상관 없을 거 같은데...
    return index;
}

static inline Node *get_bucket(HashMap *hash_map, KEY key) {
    unsigned int hash = hashcode(key);
    int index = get_index(hash_map, hash);
    Node *bucket = hash_map->buckets[index];
    return bucket;
}

// 어려워서 GPT 좀 씀.
static inline void resize(HashMap *hash_map) {
    int old_capacity = hash_map->slot_capacity;
    hash_map->slot_capacity = hash_map->slot_capacity * RESIZE_SCALE;
    //buckets capacity를 증가해서 "새로" 할당. 기존 값은 새 할당을 위해서 남겨놓아야 함.
    Node **new_buckets = (Node **) malloc(hash_map->slot_capacity * sizeof(Node *));
    for (int i = 0; i < hash_map->slot_capacity; i++) {
        new_buckets[i] = NULL;
    }

    for (int i = 0; i < old_capacity; i++) {
        Node *node = hash_map->buckets[i];
        while (node != NULL) {
            Node *next_node = node->next;
            unsigned int hash = hashcode(node->key);
            int new_index = get_index(hash_map, hash);
            node->next = new_buckets[new_index];
            new_buckets[new_index] = node;
            node = next_node;
        }
    }
    free(hash_map->buckets);
    hash_map->buckets = new_buckets;
}

HashMap *hash_map_init() {
    HashMap *hash_map = (HashMap *) malloc(sizeof(HashMap));
    hash_map->slot_capacity = DEFAULT_INIT_CAPACITY;
    hash_map->size = 0;
    Node **buckets = malloc(DEFAULT_INIT_CAPACITY * sizeof(Node));
    for (int i = 0; i < hash_map->slot_capacity; i++) {
        buckets[i] = NULL;
    }
    hash_map->buckets = buckets;
    return hash_map;
}

void hash_map_put(HashMap *hash_map, KEY key, VALUE *value) {
    if (((float) hash_map->size) / ((float) hash_map->slot_capacity) >= LOAD_FACTOR) {
        resize(hash_map);
    }
    // index가 필요해서 get_bucket 함수를 못 씀.
    unsigned int hash = hashcode(key);
    int index = get_index(hash_map, hash);
    Node *bucket = hash_map->buckets[index];
    if (bucket == NULL) { // bucket이 비어있는 경우
        hash_map->buckets[index] = create_node(key, value);
        hash_map->size += 1;
    } else {
        while (true) {
            if (bucket->key == key) { // key가 있는 경우, update
                bucket->value = value;
                return;
            }
            if (bucket->next == NULL) { // 다음 key가 없는 경우, insert
                Node *new_node = create_node(key, value);
                bucket->next = new_node;
                hash_map->size += 1;
                return;
            }
            bucket = bucket->next;
        }
    }
}

VALUE *hash_map_get(HashMap *hash_map, KEY key) {
    Node *bucket = get_bucket(hash_map, key);
    while (bucket != NULL) {
        if (bucket->key == key) {
            return bucket->value;
        }
        bucket = bucket->next;
    }
    return NULL;
}

void hash_map_remove(HashMap *hash_map, KEY key) {
    Node *prev_node = NULL;
    Node *node = get_bucket(hash_map, key);
    while (node != NULL) {
        if (node->key == key) {
            if (prev_node != NULL) { // 요소 중간에 있는 경우
                prev_node->next = node->next;
            } else { // node가 head인 경우
                int index = get_index(hash_map, hashcode(key));
                hash_map->buckets[index] = node->next;
            }
            //free(node->value); value도 포인터 변수인데, 왜 이 코드가 추가되면 중복해서 할당하려 한다고 하는지 모르겠음. 그리고 free(node);만 해도 value까지 할당 해제됨.
            free(node);
            hash_map->size -= 1;
            return;
        }
        prev_node = node;
        node = node->next;
    }
}

bool hash_map_contains(HashMap *hash_map, KEY key) {
    Node *bucket = get_bucket(hash_map, key);
    while (bucket != NULL) {
        if (bucket->key == key) return true;
        bucket = bucket->next;
    }
    return false;
}

int hash_map_size(HashMap *hash_map) {
    return hash_map->size;
}

Entry *hash_map_entries(HashMap *hash_map) {
    if (hash_map->size == 0) return NULL;
    Entry *entries = malloc(hash_map->size * sizeof(Entry));
    int index = 0;
    for (int i = 0; i < hash_map->slot_capacity; i++) { // 버킷 배열 수 만큼 순회
        Node *node = hash_map->buckets[i];
        while (node != NULL) { // 각 버킷의 linked list를 전부 돌면서 조회
            entries[index].key = node->key;
            entries[index].value = node->value;
            index++;
            node = node->next;
        }
    }
    return entries;
}

void hash_map_free(HashMap *hash_map) {
    for (int i = 0; i < hash_map->slot_capacity; i++) {
        Node *bucket = hash_map->buckets[i];
        while (bucket != NULL) {
            Node *next = bucket->next;
            // free(bucket->value); remove 함수와 마찬가지
            free(bucket);
            bucket = next;
        }
    }
    free(hash_map->buckets);
    free(hash_map);
}
