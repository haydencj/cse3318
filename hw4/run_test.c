//Hayden Johnson
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "heap.h"  

int main() {
	int N, P;
	char fname[501];
	struct heap_struct heap;
    printf("This program will create a max-heap and perform operations on it based on data from a file.\n");

    printf("Enter the filename: ");
    scanf("%s", fname);

    FILE* fp = fopen(fname, "r");

	char* token;
	char line[100];
	int i = 0;
	
	//get size of arr from file
	fgets(line, 100, fp);
	strtok(line, "\n"); 
	N = atoi(line);

	//allocate arr
	int* arr = calloc(N, sizeof(int));

	//get next line and first token
	fgets(line,100,fp);
	token = strtok(line, " ");

	//get each token and put in arr
	while(token) {
		arr[i] = atoi(token);
		token = strtok(NULL, " ");
		i++;
	}

    //gets number of operations
    fgets(line, 100, fp);
	strtok(line, "\n"); 
	P = atoi(line);

    heap = make_heap(N, arr);
    print_heap(heap);

    fgets(line,100,fp);
	token = strtok(line, " ");

    for(i=0; i<P;i++) {
        printf("Operation number %d, string: %s\n", i+1, token);

        if(atoi(token)) {
            printf("add:     %6d\n", atoi(token));	
            add(&heap, atoi(token));
            print_heap(heap);
        }

        else if(token[0] == '*') {
            if(heap.N==0){
                printf("Empty heap. No removed performed.\n");
                print_heap(heap);
            }
            else{
                printf("removed: %6d\n", poll(&heap) );	
                print_heap(heap);
            }
        }

        else if(!strcasecmp(token, "P")) {
            printf("peek:    %6d\n", peek(heap) );
            print_heap(heap);
        }

        token = strtok(NULL, " ");
    }
    destroy(&heap);
    fclose(fp);
}





