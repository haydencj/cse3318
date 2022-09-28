/*
This program demonstrates two topics that you
will have to implement in your coding assignments as well:
1. reading from files that have a specific format
2. "formatted printing" - printing integers in a way that can produce 
'aligned' rows by reserving 4 spaces for every number printed. See:
printf("%4d|", nums[i]);  

*/

#include <stdio.h>
#include <stdlib.h>

int linear_search(int nums[], int N, int val);
int binary_search (int nums[], int left, int right, int val);

int main(){
	char fname[100];
	int mx_size, N, i, M, val;
	FILE *fp;

	printf("Enter the filename: ");
	scanf("%s", fname);
	fp =fopen(fname, "r");
	if (fp == NULL){
		printf("File could not be opened.\n");
		return 1;
	}
	fscanf(fp, "%d %d", &mx_size, &N);

	int nums1[mx_size];
	//int* nums1 = malloc(mx_size * sizeof(int));

	// read from file and populate array
	for (i = 0; i < N; i++) {
		fscanf(fp, "%d ", &nums1[i]);
		//printf("%4d|", nums1[i]);
	}

	int found = linear_search(nums1, N, 67);
	printf("\nreturned index:%d\n", found);

	// read the second line of numbers from file and search for them in nums1
	fscanf(fp, "%d", &M);
	for(i=0; i<M; i++){
		fscanf(fp, "%d", &val);
		found = linear_search(nums1, N, val);
		printf("\nreturned index:%d\n", found);
	}

	fclose(fp);

	found = binary_search(nums1, 0, N-1, 67);
	printf("returned index:%d\n", found);

	return (EXIT_SUCCESS);
}

// Assumes array nums has N elements.
int linear_search(int nums[], int N, int val){
	int i;
	printf("\n Searching for %d in array ...\n", val);
	for(i=0; i<N; i++) {
		printf("%4d|", nums[i]);  // formatted printing: reserves 4 spaces
		if ( nums[i] == val )
			return i;
	}
	printf("\n");
	return -1;
}

// Assumes left and right are valid indexes in the array nums.
int binary_search (int nums[], int left, int right, int val){
	int i, m;
	printf("\n Searching (BINARY search) for %d in array ...\n", val);
	printf("If the array is not sorted this will not work as expected.\n");
	while(left <= right) {
		//printf("%4d|", nums[i]);
		m = (left+right)/2;
		if ( nums[m] == val )
			return m;
		else if (nums[m]<val) left = m+1;
		else right = m-1;
	}
	printf("\n");
	return -1;
}

