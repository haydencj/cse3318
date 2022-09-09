#include "hw1_student.h"  // .h extenssion, not .c

// You do not need to change this print_1D function. It is included here for 
// your convenience, in case you need to call it while debugging.
void print_1D(int sz, int * arr){
	for(int k = 0; k< sz; k++){
		printf("%8d", arr[k]);
	}
	printf("\n");
}


/* dynamically allocates an array and populates it with all values from arr 
	that are strictly smaller than thresh. 
	Returns:
		- the pointer to the dynamically allocated array.
		- NULL if all elements of arr are greater or equal to thres. In this case it does not allocate any memory, and sets content of sz_res to 0.
*/
int* get_scores_below(int thresh, int sz_arr, int * arr, int* sz_res){
	int counter = 0;
	for(int i = 0; i < sz_arr; i++) {
		if(arr[i] < thresh) {
			counter++;
		}
	}

	*sz_res = counter; //cant do &counter, bc when the function ends. counter is erased bc of pass by reference.
	int* new_arr = malloc(counter*sizeof(int));
	int k = 0;

	for(int i = 0; i < sz_arr; i++) {
		if(arr[i] < thresh) {
			new_arr[k] = arr[i];
			k++;
		}
	}

	if(counter == 0) {
		free(new_arr);
		return NULL;
	}

	else {
		return new_arr;
	}
}


void update_min_max(int num_rows, int num_cols, int* arr2D[], int* arr_min, int* arr_max){
	int r,c;
	int min=10000;
	int max=0;

	for(r = 0; r<num_rows; r++) {
		for(c = 0; r<num_cols; c++) {
			if(arr2D[r][c] > max) {
				max = arr2D[r][c];
			}
			else if(arr2D[r][c] < min) {
				min = arr2D[r][c];
			}
		}
	}
}


// improve this code to print as required in the homework
void print_2D(int num_rows, int num_cols, int* arr2D[]){	
	int r,c;
	printf("\n");

	printf("%2c", '|');
	for(c=0; c<num_cols; c++){ //columns 5
		printf("%8d|", c);
	}
	printf("\n");

	for(c=0; c<num_cols; c++){ //columns 5
		printf("----------");
	}

	printf("\n");

	for (r = 0; r<num_rows; r++){ //rows 3
		printf("%d|", r);
		for(c=0; c<num_cols; c++){ //columns 5
			printf("%8d|", arr2D[r][c]);
		}
		printf("\n");
	}	
}


