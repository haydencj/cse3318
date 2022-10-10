//Hayden Johnson
#include <stdlib.h>
#include <stdio.h>

#include "heap.h"  

#define DEBUG 1


struct heap_struct make_heap_empty(int cap){
    struct heap_struct heap;
    heap.items = (int*) calloc(cap, sizeof(int));
    heap.capacity = cap;
    heap.N = 0;

    return heap;
}

struct heap_struct make_heap(int N, int * arr){
    struct heap_struct heap;
    heap.items = arr;
    heap.N = N;
    heap.capacity = N;

    printf("in function make_heap, in DEBUG MODE, printing array BEFORE it gets turned into a heap :\n");
    print_heap(heap);

    int i;
    for(i = (heap.N-1)/2; i>=0; i--) sink_down(i, heap.N, heap.items);

    printf("in function make_heap, in DEBUG MODE, printing array after sink_down at index 0.\n");
    print_heap(heap);

    return heap;
}


void destroy(struct heap_struct * heapP){
    //int i;
    //for(i=0; i<heapP->N; i++) free(heapP->items[i]);
    free(heapP->items);
}

/*
Heap:  size: 3, capacity : 3
indexes:           0,      1,      2,
values:           43,     20,     10,
*/

void print_heap(struct heap_struct heapS){
    int i;
    printf("Heap:  size: %d, capacity: %d\n", heapS.N, heapS.capacity);

    printf("indexes:");
    for(i=0; i<heapS.N; i++) printf("%6d,", i);
    printf("\n");

    printf("values: ");
    for(i=0; i<heapS.N; i++) printf("%6d,", heapS.items[i]);
    printf("\n\n");
}

int idxOfMaxValue(int* arr, int i, int left, int right, int N) {
    int imv = i;

    if( (left<=N) && (arr[left]>arr[imv])) {
        imv = left;
    }

    if( (right<=N) && (arr[right]>arr[imv])) {
        imv = right;
    }

    return imv;
}

//index 0: left child is 2i+1, right child is 2i+2, parent is (i-1)/2
void swim_up(int idx, int * arr){
    int swap;
    int idx_actual = idx-1; //bc starting at index 0

    while( (idx_actual>0) && (arr[idx_actual]>arr[idx_actual/2]) ) {
        swap = arr[idx_actual]; 
        arr[idx_actual] = arr[idx_actual/2];
        arr[idx_actual/2] = swap;
        idx_actual = idx_actual/2;
    }
}

void sink_down(int i, int N, int * arr){
    int left = (2*i)+1; //left child of i
    int right = (2*i)+2; //right child of i
    int imv = idxOfMaxValue(arr, i, left, right, N);
    int swap;

    while(imv!=i) {
        swap = arr[imv];
        arr[imv] = arr[i];
        arr[i] = swap;
        left = (2*i)+1;
        right = (2*i)+2;
        imv = idxOfMaxValue(arr, i, left, right, N);
    }
}

void add(struct heap_struct * heapP, int new_item){
    heapP->N = heapP->N + 1;
    int idx = heapP->N - 1;
    heapP->items[idx] = new_item;
    swim_up(idx, heapP->items);
}

int peek(struct heap_struct heapS){
    return heapS.items[0];
}


int poll(struct heap_struct * heapP){
    int max = heapP->items[0];
    heapP->items[0] = heapP->items[heapP->N - 1];
    heapP->N = heapP->N - 1;
    sink_down(0, heapP->N, heapP->items);
    return max;
}

