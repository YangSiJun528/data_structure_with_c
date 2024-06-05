//
// Created by sijun yang on 2024. 6. 5..
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "doubly_linked_list.h"

/*
 * node를 기준으로 prev <-> node <-> next 햇갈려서 적음.
 *
 * 메모리 관리 너무 어렵다. 이러니까 버그가 나지.
 * 그냥 단순하게 1차원 메모리 공간을 할당받는다는 생각.
 */

static inline Node *create_node(TYPE value);
static inline void unlink_node(Node* node);

LinkedList linkedlist_create() {
    LinkedList linked_list = {NULL, NULL, 0};
    return linked_list;
}

void linkedlist_push(LinkedList *linked_list, TYPE element) {
    assert(linked_list->length >= 0);
    Node *new_node = create_node(element);
    if (linked_list->length == 0) {
        linked_list->head = new_node;
        linked_list->tail = new_node;
    } else {
        new_node->prev = linked_list->tail;
        linked_list->tail = new_node;
        new_node->prev->next = new_node;
    }
    linked_list->length += 1;
}

TYPE linkedlist_popleft(LinkedList *linked_list) {
    assert(linked_list->length != 0);
    Node *popped_node = linked_list->head;
    TYPE value = popped_node->value;
    if (linked_list->length == 1) {
        linked_list->tail = NULL;
        linked_list->head = NULL;
    } else {
        linked_list->head = popped_node->next;
        linked_list->head->prev = NULL;
    }
    unlink_node(popped_node);
    free(popped_node);
    linked_list->length -= 1;
    assert(linked_list->length >= 0);
    return value;
}

TYPE linkedlist_pop(LinkedList *linked_list) {
    assert(linked_list->length != 0); // 이거는 사용자 문제(예외)
    Node *popped_node = linked_list->tail;
    TYPE value = popped_node->value;
    if (linked_list->length == 1) { // 아니면 tail or head == NULL
        linked_list->tail = NULL;
        linked_list->head = NULL;
    } else {
        linked_list->tail = popped_node->prev;
        linked_list->tail->next = NULL;
    }
    unlink_node(popped_node);
    free(popped_node);
    linked_list->length -= 1;
    assert(linked_list->length >= 0);
    return value;
}

void linkedlist_pushleft(LinkedList *linked_list, TYPE element) {
    assert(linked_list->length >= 0);
    Node *new_node = create_node(element);
    if (linked_list->length == 0) {
        linked_list->head = new_node;
        linked_list->tail = new_node;
    } else {
        new_node->next = linked_list->head;
        linked_list->head = new_node;
        new_node->next->prev = new_node;
    }
    linked_list->length += 1;
}


TYPE linkedlist_get(LinkedList *linked_list, int index) {
    assert(index >= 0 && index < linked_list->length); // 사용자 문제(예외)
    Node* ptr = linked_list->head;
    for (int i = 0; i < index; ++i) {
        ptr += 1;
    }
    return ptr->value;
}

void linkedlist_insert(LinkedList *linked_list, TYPE element) {}

void linkedlist_update(LinkedList *linked_list, TYPE element) {}

TYPE linkedlist_delete(LinkedList *linked_list) {}

int linkedlist_length(LinkedList *linked_list) {
    return linked_list->length;
}


static inline Node *create_node(TYPE value) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    assert(new_node != NULL);
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->value = value;
    return new_node;
};

static inline void unlink_node(Node* node) { // 이거 없어도 될거 같은데, GC가 있는 것도 아니고
    node->next = NULL;
    node->prev = NULL;
};