#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

void print_list(LinkedList *linked_list) {
    Node *current = linked_list->head;
    while (current != NULL) {
        printf("%s.%d - ",current->value.name , current->value.value);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    LinkedList list = linkedlist_create();

//    // Data 생성
//    Data data1 = {1};
//    Data data2 = {2};
//    Data data3 = {3};
//    Data data4 = {4};
//    Data data5 = {5};

    // Data 생성
    Complex data1 = {1, "1aaa"};
    Complex data2 = {2, "2aaa"};
    Complex data3 = {3, "3aaa"};
    Complex data4 = {4, "4aaa"};
    Complex data5 = {5, "5aaa"};

    // push 테스트
    linkedlist_push(&list, data1);
    linkedlist_push(&list, data2);
    linkedlist_push(&list, data3);

    printf("After pushing 3 elements:\n");
    print_list(&list);

    // pushleft 테스트
    linkedlist_pushleft(&list, data4);
    linkedlist_pushleft(&list, data5);

    printf("After pushleft 2 elements:\n");
    print_list(&list);

    // get 테스트
    Complex getData = linkedlist_get(&list, 2);
    printf("Get element at index 2: %d\n", getData.value);

    // length 테스트
    int length = linkedlist_length(&list);
    printf("Length of list: %d\n", length);

    // pop 테스트
    Complex popData = linkedlist_pop(&list);
    printf("Popped element: %d\n", popData.value);
    printf("After pop:\n");
    print_list(&list);

    // popleft 테스트
    Complex popLeftData = linkedlist_popleft(&list);
    printf("Popped left element: %d\n", popLeftData.value);
    printf("After popleft:\n");
    print_list(&list);

    return 0;
}
