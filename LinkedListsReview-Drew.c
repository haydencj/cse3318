#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};
typedef struct node* nodePT;

nodePT list_from_array(int N, int A[N]);
void print_list(nodePT head);
nodePT list_from_list(nodePT L);

int main()
{
    int arr[5] = {5,10,15,20,25};
    int size = 5;

    nodePT newList = list_from_array(size,arr);
    print_list(newList);
    nodePT listFromList = list_from_list(newList);

    printf("\n\n");
    print_list(listFromList);


}

nodePT reverse(nodePT L)
{
    nodePT prev = NULL;
    nodePT current = L;
    nodePT next = NULL;

    if(L == NULL)
    {
        return NULL;
    }

    if(L->next == NULL)
    {
        return L;
    }

    while(next != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

void destroy_list(nodePT L)
{
    nodePT current = L;
    nodePT next = NULL;

    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
}

nodePT list_from_list(nodePT L)
{
    nodePT prev = NULL;
    nodePT head = NULL;
    nodePT newNode = NULL;

    if(L == NULL)
    {
        return NULL;
    }

    head = (nodePT) malloc(sizeof(struct node));
    head->data = L->data;
    head->next = NULL;

    L = L->next;
    prev = head;

    while(L != NULL)
    {
        newNode = (nodePT) malloc(sizeof(struct node));
        newNode->data = L->data;
        newNode->next = NULL;

        prev->next = newNode;
        prev = newNode;

        L = L->next;
    }

    return head;
}

nodePT list_from_array(int N, int A[N]){
    
    if(N == 0 || A == NULL)
    {
        return NULL;
    }

    nodePT prev = NULL;
    nodePT newNode = NULL;

    nodePT head = (nodePT) malloc(sizeof(struct node));
    head->data = A[0];
    head->next = NULL;

    prev = head;

    for(int i = 1; i < N; i++)
    {
        newNode = (nodePT) malloc(sizeof(struct node));
        newNode->data = A[i];
        newNode->next = NULL;

        prev->next = newNode;
        prev = newNode;
    }

    return head;


}

void print_list(nodePT head)
{
    nodePT current = head;

    while(current != NULL)
    {
        printf("%d\n",current->data);
        current = current->next;
    }
}