/* 
 * Hayden Johnson ID: 1001878135
 * Updated 2/17/2022 - Alexandra Stefan
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "list.h"

/*
TO DO LIST:
	1. ask user for filename.
	2. read file and export data to an array (A)
	3. run bucket sort on that array
		-CHECK BUCKET SORT STEPS BELOW
	4. Copy from each bucket into original array
		-Result: sorted array

STEPS TO RUN BUCKET SORT
	1. Make an array (B) of buckets with size N (original array size)
		-Each bucket is a linked list
		-Make the buckets by mallocing N node pointers 
		-Set malloced nodes equal to NULL
	2. Iterate through array and place in proper bucket
		-For each elem in A, add elem to list B[floor(elem*n)]
		-Insertion sort as you place in buckets
	3. For each list in B, concatenate it (or copy back into A in this order),
       destroy the list (if needed).
*/

/* 
compile with -g to collect debugging info needed for Valgrind ( -lm links the math library): 
gcc -g bucket_sort.c list.c -lm
(g flag generates debug information to be used by GDB debugger)

run with Valgrind:
valgrind --leak-check=full ./a.out

On some systems, but not all, you can also use the --show-leak-kinds=all flag:
valgrind --leak-check=full --show-leak-kinds=all ./a.out

run without Valgrind:
./a.out
*/

void print_array(int arr[], int N);
void bucket_sort(int arr[], int N);
nodePT insert_sorted(nodePT L, nodePT newP);
int* file_to_array(char filename[], int* size);
void insert_to_array(nodePT* buckets, int arr[], int N);

/* // recommended helper functions:
- function to insert a new node in a sorted list.
nodePT insert_sorted(nodePT L, nodePT newP)
- function to sort an array using bucket sort
void bucket_sort(int arr[], int N)
- function to read file and read the data into an array, edits int size.
int* file_to_array(charfilename[], int* size)
*/

void insert_to_array(nodePT* buckets, int arr[], int N) { //inserts sorted linked lists into array and frees lists.
	int i=0, j=0;
	nodePT current = NULL;
	for(i=0;i<N;i++) {
		current = buckets[i];
		if(current != NULL){
			
			arr[j] = current->data;
			j++;

			while(current->next != NULL) {
				current=current->next;
				arr[j] = current->data;
				j++;
			}
		}
		destroy_list(buckets[i]);
	}
	print_array(arr, N);
}

void bucket_sort(int arr[], int N){
	int i, index, max=0, min=0;
	max = arr[0];
	min = arr[0];
	
	for(i=0; i<N; i++) {
		if(arr[i]>=max) max = arr[i];
		else if(arr[i]<min) min = arr[i];
	}

	nodePT* buckets = malloc(N*sizeof(nodePT));
	for(i=0; i<N; i++) {
		buckets[i] = NULL;
	}

	printf("\nBucketsort: min=%d, max=%d, N=%d buckets\n", min, max, N);

	for(i=0; i<N; i++) {
		index=floor(((arr[i]-(double)min) * N)/ ((1+(double)max) - (double)min ));
		printf("arr[%d]= %6d, idx = %d\n", i, arr[i], index);

		buckets[index] = insert_sorted(buckets[index], new_node(arr[i]));
	}

	for(i=0;i<N;i++){
		printf("------ List at index %d :", i);
		print_list_horiz(buckets[i]);
	}

	insert_to_array(buckets, arr, N);

	//free bucket array
	free(buckets);
}

nodePT insert_sorted(nodePT L, nodePT newP){

	nodePT head = L;
	//nodePT current = L;
	if(head == NULL) { //if bucket is empty
		L = newP;
	}

	else if(newP->data < head->data) { //if new node is less than the head, replace head.
		newP->next = head;
		L = newP;
	}

	
	else {
		while(head->next != NULL && newP->data > head->next->data) {
			head = head->next;
		}
		newP->next = head->next;
		head->next = newP;
	}

	return L;
}

int* file_to_array(char filename[], int* size){
	FILE* fp = fopen(filename, "r");
	if(!fp) {
		printf("File could not be opened.\n");
		return NULL;
	}

	char* token;
	char line[100];
	int i = 0;
	
	//get size of arr from file
	fgets(line, 100, fp);
	strtok(line, "\n"); 
	*size = atoi(line);

	//allocate arr
	int* arr = malloc((*size) * sizeof(int));

	//get next line and first token
	fgets(line,100,fp);
	token = strtok(line, " ");

	//get each token and put in arr
	while(token) {
		arr[i] = atoi(token);
		token = strtok(NULL, " ");
		i++;
	}
	print_array(arr, *size);
	fclose(fp);
	return arr;
}

void print_array(int arr[], int N){
	int j;
	printf("\n array: ");
	for(j= 0; j<N; j++){
		printf("%5d,", arr[j]);
	}
	printf("\n");
}

//-------------------------------------------------------------

void run1(){
	int size, i=0;
	int* size_ptr = &size;
	char filename[50];

	printf("\nEnter the filename: ");
	scanf("%s", filename);
	int* array = file_to_array(filename, size_ptr); //will change int* size value

	bucket_sort(array, size);
	free(array);
}

int main()
{
	printf("This program will read a file name, load data for an array from there and print the sorted array.\n");
	printf("The array is sorted using bucket sort.\n");
	printf("This will be repeated as long as the user wants.\n");
	int option;
	do {
		run1();
		printf("\nDo you want to repeat? Enter 1 to repeat, or 0 to stop) ");
		char ch;
		scanf("%d%c",&option, &ch);  // ch is used to remove the Enter from the input buffer
 	} while (option == 1);

   return 0;
}
