/* 
 * Updated 2/17/2022 - Alexandra Stefan
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "list.h"

/*
TO DO LIST:
	1. ask user for filename, ask again if bad filename.
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

/* // recommended helper functions:
- function to insert a new node in a sorted list.
nodePT insert_sorted(nodePT L, nodePT newP);
- function to sort an array using bucket sort
void bucket_sort(int arr[], int N)
- function to read file and read the data into an array, edits int size.
*/
void bucket_sort(int arr[], int N){

}

nodePT insert_sorted(nodePT L, nodePT newP){
	return NULL;
}

int* file_to_array(char filename[], int* size){
	FILE* fp = fopen(filename, "r");
	if(!fp) return NULL;
	
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
	char filename[50];

	int size;
	int* size_ptr = &size;
	int* array = file_to_array("data1.txt", size_ptr); //will change int* size value
	print_array(array, size);
	free(array);
	printf("\n-------run1 - this is a place holder. You need to edit this function.------ \n");
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
