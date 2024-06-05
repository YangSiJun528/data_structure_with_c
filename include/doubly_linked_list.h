//
// Created by sijun yang on 2024. 6. 5.
//

#ifndef DATA_STRUCTURE_WITH_C_DOUBLY_LINKED_LIST_H
#define DATA_STRUCTURE_WITH_C_DOUBLY_LINKED_LIST_H
#define TYPE Complex // 자료구조의 요소 타입, 구조체나 배열만 가능. 포인터를 사용하는 방식으로 일관성있게 처리할거라 그럼. void* 도 가능하긴 한데, 그럼 포인터 다루기 까다로워서...

typedef struct {
    int value;
} Data;

typedef struct {
    int value;
    char name[10];
} Complex;

typedef struct Node {
    TYPE *value;         // 노드가 저장한 값
    struct Node *next;  // 다음 노드를 가리키는 포인터
    struct Node *prev;  // 이전 노드를 가리키는 포인터
} Node;

typedef struct {
    Node *head;     // 처음 노드
    Node *tail;     // 마지막 노드
    int length;     // 배열 길이
} LinkedList;

LinkedList linkedlist_create();

void linkedlist_push(LinkedList *linked_list, TYPE *element);

TYPE *linkedlist_pop(LinkedList *linked_list);

void linkedlist_pushleft(LinkedList *linked_list, TYPE *element);

TYPE *linkedlist_popleft(LinkedList *linked_list);

TYPE *linkedlist_get(LinkedList *linked_list, int index);

void linkedlist_insert(LinkedList *linked_list, int index, TYPE *element);

void linkedlist_update(LinkedList *linked_list, int index, TYPE *element);

void linkedlist_delete(LinkedList *linked_list, int index);

int linkedlist_length(LinkedList *linked_list);

#endif //DATA_STRUCTURE_WITH_C_DOUBLY_LINKED_LIST_H