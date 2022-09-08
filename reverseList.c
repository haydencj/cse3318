#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head);
struct ListNode* buildList(int* arr, int size);
void printList(struct ListNode* curr);

int main(int argc, char** argv) {
    int arr[] = {1,2,3,4,5};
    int size = (int) sizeof(arr)/sizeof(int);
    struct ListNode* head = buildList(arr, size);
    printList(head);
    printList(reverseList(head));
}

void printList(struct ListNode* curr) {
    while(curr != NULL) {
        printf("%d ", curr->val);
        curr = curr->next;
    }
    printf("\n");
}

struct ListNode* buildList(int* arr, int size) {
    struct ListNode* head = malloc(sizeof(struct ListNode));
    struct ListNode* curr = head;
    head->val = arr[0];
    head->next = NULL;
    
    for(int i = 1; i<size; i++) {
        struct ListNode* newNode = malloc(sizeof(struct ListNode));
        curr->next = newNode;
        newNode->val = arr[i];
        newNode->next = NULL;
        curr = newNode;
    }

    return head;
}

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* curr = head;
    struct ListNode* prev = NULL;
    struct ListNode* next;

    while(curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    return prev;
}