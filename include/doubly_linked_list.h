//
// Created by sijun yang on 2024. 6. 5.
//

#ifndef DATA_STRUCTURE_WITH_C_DOUBLY_LINKED_LIST_H
#define DATA_STRUCTURE_WITH_C_DOUBLY_LINKED_LIST_H
#define TYPE int // 자료구조의 요소 타입

typedef struct Node {
    TYPE value;         // 노드가 저장한 값
    struct Node* next;  // 다음 노드를 가리키는 포인터
    struct Node* prev;  // 이전 노드를 가리키는 포인터
} Node;

typedef struct {
    Node* head;     // 처음 노드
    Node* tail;     // 마지막 노드
    int length;     // 배열 길이
} LinkedList;

LinkedList linkedlist_create();
void linkedlist_push(LinkedList * linkedList, TYPE element);
TYPE linkedlist_pop(LinkedList * linkedList);
void linkedlist_pushleft(LinkedList * linkedList, TYPE element);
TYPE linkedlist_popleft(LinkedList * linkedList);
TYPE linkedlist_get(LinkedList * linkedList, int index);
void linkedlist_insert(LinkedList * linkedList, TYPE element);
void linkedlist_update(LinkedList * linkedList, TYPE element);
TYPE linkedlist_delete(LinkedList * linkedList);
int linkedlist_length(LinkedList * linkedList);

#endif //DATA_STRUCTURE_WITH_C_DOUBLY_LINKED_LIST_H
