#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"

void print_list(LinkedList *linked_list) {
    Node *current = linked_list->head;
    while (current != NULL) {
        printf("%s.%d - ",(*current->value).name , (*current->value).value);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    LinkedList list = linkedlist_create();

    // 동적 할당 및 초기화
    Complex* data1 = (Complex*)malloc(sizeof(Complex));
    Complex* data2 = (Complex*)malloc(sizeof(Complex));
    Complex* data3 = (Complex*)malloc(sizeof(Complex));
    Complex* data4 = (Complex*)malloc(sizeof(Complex));
    Complex* data5 = (Complex*)malloc(sizeof(Complex));

    if (data1 == NULL || data2 == NULL || data3 == NULL || data4 == NULL || data5 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // 데이터 초기화
    data1->value = 1;
    strcpy(data1->name, "1aaa");

    data2->value = 2;
    strcpy(data2->name, "2aaa");

    data3->value = 3;
    strcpy(data3->name, "3aaa");

    data4->value = 4;
    strcpy(data4->name, "4aaa");

    data5->value = 5;
    strcpy(data5->name, "5aaa");

    // 데이터 출력
    printf("Data1: %d, %s\n", data1->value, data1->name);
    printf("Data2: %d, %s\n", data2->value, data2->name);
    printf("Data3: %d, %s\n", data3->value, data3->name);
    printf("Data4: %d, %s\n", data4->value, data4->name);
    printf("Data5: %d, %s\n", data5->value, data5->name);

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
    Complex* getData = linkedlist_get(&list, 2);
    printf("Get element at index 2: %d\n", getData->value);

    // length 테스트
    int length = linkedlist_length(&list);
    printf("Length of list: %d\n", length);

    // insert 테스트
    Complex* data6 = (Complex*)malloc(sizeof(Complex));
    data6->value = 6;
    strcpy(data6->name, "6aaa");
    linkedlist_insert(&list, 2, data6);
    printf("After inserting element \"6aaa.6\" at index 2:\n");
    print_list(&list);

    // update 테스트
    Complex* data7 = (Complex*)malloc(sizeof(Complex));
    data7->value = 7;
    strcpy(data7->name, "7aaa");
    linkedlist_update(&list, 2, data7);
    printf("After updating element at index 2:\n");
    print_list(&list);

    // delete 테스트
    Complex* deletedData = linkedlist_delete(&list, 2);
    printf("Deleted element: %d, %s\n", deletedData->value, deletedData->name);
    printf("After deleting element at index 2:\n");
    print_list(&list);

    // pop 테스트
    Complex* popData = linkedlist_pop(&list);
    printf("Popped element: %d\n", (*popData).value);
    printf("After pop:\n");
    print_list(&list);

    // popleft 테스트
    Complex* popLeftData = linkedlist_popleft(&list);
    printf("Popped left element: %d\n", (*popLeftData).value);
    printf("After popleft:\n");
    print_list(&list);

    // 동적 할당된 메모리 해제
    free(data1);
    free(data2);
    free(data3);
    free(data4);
    free(data5);

    return 0;
}
