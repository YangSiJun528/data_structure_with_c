//
// Created by sijun yang on 2024. 6. 5..
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "doubly_linked_list.h"

static inline Node *create_node();

LinkedList linkedlist_create() {}

void linkedlist_push(LinkedList *linked_list, TYPE element) {}

TYPE linkedlist_pop(LinkedList *linked_list) {}

void linkedlist_pushleft(LinkedList *linked_list, TYPE element) {}

TYPE linkedlist_popleft(LinkedList *linked_list) {}

TYPE linkedlist_get(LinkedList *linked_list, int index) {}

void linkedlist_insert(LinkedList *linked_list, TYPE element) {}

void linkedlist_update(LinkedList *linked_list, TYPE element) {}

TYPE linkedlist_delete(LinkedList *linked_list) {}

int linkedlist_length(LinkedList *linked_list) {}


static inline Node *create_node() {};