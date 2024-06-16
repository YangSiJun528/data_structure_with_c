//
// Created by sijun yang on 2024. 6. 15.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "heap.h"

/**
 * MAX HEAP이라 어느 노드를 기준으로 해도 자식 노드가 더 작아야 함. (재귀 특성)
 * 노드의 인덱스를 i라고 할 때,
 * 왼쪽 자식 노드의 인덱스: 2*i + 1
 * 오른쪽 자식 노드의 인덱스: 2*i + 2
 * 부모 노드의 인덱스: (i - 1) // 2
 * heap->size - 1 << latest node index 값
 * 0 << root node index 값
 */

int DEFAULT_INIT_CAPACITY = 10;
int RESIZE_SCALE = 2;

static inline TYPE get(Heap *heap, int index);

static inline void set(Heap *heap, int index, TYPE data);

static inline void resize(Heap *heap);

static inline void sift_up(Heap *heap);

static inline void sift_down(Heap *heap);

static inline void add_latest(Heap *heap, TYPE data);

static inline void swap_heap_node(Heap *heap, int index1, int index2);

static inline void swap_root_and_latest(Heap *heap);

static inline void remove_latest(Heap *heap);

static inline int parent(int i);

static inline int left_child(int i);

static inline int right_child(int i);

Heap *heap_init() {
    Heap *heap = (Heap *) malloc(sizeof(Heap));
    heap->data = malloc(DEFAULT_INIT_CAPACITY * sizeof(TYPE));
    heap->capacity = DEFAULT_INIT_CAPACITY;
    heap->size = 0;
    return heap;
}

Heap *heap_init_set_capacity(int init_capacity) {
    Heap *heap = (Heap *) malloc(sizeof(Heap));
    heap->data = malloc(init_capacity * sizeof(TYPE));
    heap->capacity = init_capacity;
    heap->size = 0;
    return heap;
}

void heap_push(Heap *heap, TYPE data) {
    if (heap->size * sizeof(TYPE) == heap->capacity) {
        resize(heap);
    }
    add_latest(heap, data);
    sift_up(heap);
}

TYPE heap_pop(Heap *heap) {
    TYPE popped_data = get(heap, 0);
    swap_root_and_latest(heap);
    remove_latest(heap);
    sift_down(heap);
    return popped_data;
}

int heap_get_size(Heap *heap) {
    return heap->size;
}

bool heap_is_empty(Heap *heap) {
    return heap->size == 0;
}

TYPE heap_peek(Heap *heap) {
    return get(heap, 0);
}

void heap_free(Heap *heap) {
    free(heap->data);
    free(heap);
}

/**
 * Heap 내부 동적 배열의 특정 인덱스 값 가져오기.
 * index out of range 조건 없음 주의. 동적 배열의 길이보다 큰 index 사용 시 런타임 에러 발생.
 */
static inline TYPE get(Heap *heap, int index) {
    return heap->data[index];
}

/**
 * Heap 내부 동적 배열의 특정 인덱스 값 가져오기.
 * index out of range 조건 없음 주의. 동적 배열의 길이보다 큰 index 사용 시 런타임 에러 발생.
 */
static inline void set(Heap *heap, int index, TYPE data) {
    heap->data[index] = data;
}

/**
 * Heap 내부 동적 배열의 크기를 증가.
 */
static inline void resize(Heap *heap) {
    void *ptr = realloc(heap->data, heap->capacity * RESIZE_SCALE * sizeof(TYPE));
    assert(ptr != NULL);
    heap->data = ptr;
    heap->capacity = heap->capacity * RESIZE_SCALE;
    assert(heap->size * sizeof(TYPE) < heap->capacity * sizeof(TYPE));
}

/**
 * latest 노드를 Heap이 유효하도록 특정 위치까지 올림.
 * 추가 시에 유효하지 않은 상태일 수 있으므로 유효한 상태가 될 때까지 올려줘야 함.
 */
static inline void sift_up(Heap *heap) {
    int current_index = heap->size - 1;
    int parent_index = parent(current_index);
    // 현재 노드(시작 시점에 latest 노드)가 부모 노드보다 작거나 같으면 종료.
    while (current_index > 0 && get(heap, current_index) > get(heap, parent_index)) {
        swap_heap_node(heap, current_index, parent_index);
        current_index = parent_index;
        parent_index = parent(current_index);
    }
}

/**
 * root 노드를 Heap이 유효하도록 특정 위치까지 내림. (부모 노드가 자삭 노드보다 작도록(Min Heap 기준))
 * 제거 시에 root와 latest 노드의 위치를 변경하므로 root가 되버린 latest 노드를 내려줘야 함.
 */
static inline void sift_down(Heap *heap) {
    int current_index = 0;
    int left_child_index;
    int right_child_index;
    int larger_child_index;
    // 핸재 노드의 left 자식 노드가 없을 때까지 반복.
    while ((left_child_index = left_child(current_index)) < heap->size) {
        right_child_index = right_child(current_index);

        // 자식 노드 중 더 큰 노드 구하기
        if (right_child_index < heap->size && get(heap, right_child_index) > get(heap, left_child_index)) {
            larger_child_index = right_child_index;
        } else {
            larger_child_index = left_child_index;
        }

        // 현재 노드(시작 시점에 root 노드)가 자식 노드중 가장 큰 노드보다 크거나 같으면 종료.
        if (get(heap, current_index) >= get(heap, larger_child_index)) {
            break;
        };

        swap_heap_node(heap, current_index, larger_child_index);
        current_index = larger_child_index;
    }
}

/**
 * 가장 마지막에 새로운 노드 추가.
 *
 * 완전 이진 트리 특성 상, 결과적으론 (연산이 끝난 이후) 항상 모든 level이 채워있고,
 * 좌축에서 우측으로 채워지는 형태를 가지고 있어야만 한다.
 */
static inline void add_latest(Heap *heap, TYPE data) {
    heap->data[heap->size] = data;
    heap->size = heap->size + 1;
}

/**
 * 가장 마지막 노드 제거.
 */
static inline void remove_latest(Heap *heap) {
    heap->size = heap->size - 1;
}

/**
 * 두 노드의 값을 서로 바꾸기.
 */
static inline void swap_heap_node(Heap *heap, int index1, int index2) {
    TYPE root = get(heap, index1);
    TYPE latest = get(heap, index2);
    set(heap, index1, latest);
    set(heap, index2, root);
}

/**
 * 루트 노드와 마지막 노드의 값을 서로 바꾸기.
 */
static inline void swap_root_and_latest(Heap *heap) {
    swap_heap_node(heap, 0, heap->size - 1);
}

static inline int parent(int i) {
    return (i - 1) / 2;
}

static inline int left_child(int i) {
    return 2 * i + 1;
}

static inline int right_child(int i) {
    return 2 * i + 2;
}
