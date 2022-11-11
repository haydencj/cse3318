#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "spell.h"

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MAX_LEN:
Student answer:  Theta(DT*MAX_LEN^2)


Worst case to do an unsuccessful binary search in a dictionary with D words, when 
all dictionary words and the searched word have length MAX_LEN 
Student answer:  Theta(MAX_LEN*lg(D))
*/


/* You can write helper functions here */
int binary_search(char** dict, int size, char* token, int* counter, int printOn) {
	//convert to lowercase for search
	char new_token[strlen(token)];

	for(int i = 0; i<strlen(token); i++){
  		new_token[i] = tolower(token[i]);
	}

	if(printOn) printf("\nBinary search for: %s\n", new_token);
	
	(*counter) = 0;
	int left = 0;
	int right = size-1;

	while(left <= right) {
		int m = (left+right)/2;
		if(strcmp(new_token, dict[m]) == 0) { // match found
			return m; //index of token in dict
		}
		else if(strcmp(new_token, dict[m]) < 0) {// <
			right = m-1;
		}

		else { // >
			left = m+1;
		}
		if(printOn) printf("dict[%d] = %s\n", m, dict[m]);
		(*counter)++; //precedence
	}

	if(printOn) printf("Not found\n");
	return -1; //not found
}

int min_dist(char* string, char** dict, int size) {
	int* min_dist = malloc(size * sizeof(int));
	int counter = 0, j = 0;
	//populate array with all distances
	for(int i = 0; i < size; i++) {
		min_dist[i] = edit_distance(string, dict[i], 0);
	}

	int smallest = min_dist[0];
	//get smallest number in array
	for(int i = 1; i<size; i++) {
		if(smallest > min_dist[i]) {
			smallest = min_dist[i];
		}
	}

	free(min_dist);
	return smallest;
}

int check(char* output, char* input, char** dict, int dict_size, int printOn) {
	FILE* out_fp = fopen(output, "w");
	FILE* in_fp = fopen(input, "r");
	if(!out_fp || !in_fp) {
		printf("File(s) could not be opened.\n");
		return 0;
	}

	char buffer[101] = {'\0'}; //intialize as empty string so no garbage values
    int c = 0, i = 0, j = 0, counter = 0, result = 0, answer = 0;

    while(c != EOF){
		c = fgetc(in_fp);
		//if next character is white space or punc, then we have a word to check
        if(((ispunct(c)) || (c == 32) || (c == -1))) { //32 ascii value for whitespace, -1 for EOF value
            if(buffer[0] != '\0') { //deals with multiple separators
                //do binary search
				result = binary_search(dict, dict_size, buffer, &counter, printOn);
				
				printf("\n---> |%s| (words compared when searching: %d)\n", buffer, counter);
				//if found, write to output file
				if(result >= 0) {
					printf("	- OK\n\n\n");
				}
				//if not found, identify the most similar words in the dictionary and give these options to the user as to what correction to be used for this word in the output file
				else {
					//find minimum distance of all words in dict
					int smallest_dist = min_dist(buffer, dict, dict_size);
					printf("-1 - type correction\n");
					printf(" 0 - leave word as is (do not fix spelling)\n");
					printf("     Minimum distance: %d (computed edit distances: %d)\n", smallest_dist, dict_size);
					//print all dictionary words with smallest dist
					printf("     Words that give minimum distance:\n");
					counter = 0;

					//count number of words with min distance and print them
					for(int i = 0; i < dict_size; i++) {
						if((edit_distance(buffer, dict[i], 0)) == smallest_dist) {
							counter++;
						}
					}

					char* words[counter];
					j=0;
					for(int i = 0; i < dict_size; i++) {
						if((edit_distance(buffer, dict[i], 0)) == smallest_dist) {
							words[j] = dict[i];
							printf(" %d - %s\n", j+1, words[j]);
							j++;
						}
					}

					printf("Enter your choice (from the above options): ");
					scanf("%d", &answer);

					if(answer == 0) {
						//do nothing
					}

					else if(answer == -1) {
						printf("Enter correct word: ");
						scanf("%s", buffer);
					}

					else if(answer > 0) {
						//words with min distance
						strcpy(buffer, words[answer-1]);
					}
				}

				fprintf(out_fp, "%s", buffer);
				if(c != -1) fprintf(out_fp, "%c", c); //if it doesnt have EOF val

                memset(buffer, 0, 101);
                i=0;
            }

			else if(c != -1) { //if character is EOF value, do not print.
				fprintf(out_fp, "%c", c);
			}

        }

        else{
            buffer[i] = c;
            i++;
        }
    }

	fclose(in_fp);
	fclose(out_fp);
	return 1;
}


char** dict_to_array(char * filename, int* size) {
	FILE* fp = fopen(filename, "r");
	if(!fp) {
		printf("Dictionary could not be opened.\n");
		return NULL;
	}

	char line[101]; //100+1 for null terminator
	int i;
	
	//get size of dict from file
	fgets(line, 101, fp);
	strtok(line, "\n"); 
	*size = atoi(line);

	//create 2d arr
	char **dict_arr = malloc((*size) * sizeof(char*)); //create an array of char pointers, one for each string (char *):
	for (i = 0; i < *size; ++i) {
    	dict_arr[i] = (char*) malloc(101 * sizeof(char)); //allocate space for each string
	}

	i=0;

	//get each token and put in arr
	while (fgets(line, 101, fp)) {
		strtok(line, "\n");
		strcpy(dict_arr[i], line); //copy data from line (on stack) to arr (on heap)
		i++;
	}

	fclose(fp);
	return dict_arr;
}

int cmpstr(const void* str1, const void* str2)
{
    const char* str1_p = *(const char**)str1;
    const char* str2_p = *(const char**)str2;
    return strcmp(str1_p, str2_p);
}

int min(int a, int b, int c){
	int min;
	if( (a<b) && (a<c) )
	{
		min = a;
	}
	else if(b<c)
	{
		min = b;
	}
	else
	{
		min = c;
	}
	return min;
}

int calc_dist(char* first, char* second, int i, int j, int rows, int cols, int table[][cols]) {
	if(i == 0 && j == 0) return 0;
	else if(i == 0) return j;
	else if(j == 0) return i;
	else {
		if(first[i-1] == second[j-1]) return table[i-1][j-1];
		else {
			return min(table[i-1][j]+1,table[i][j-1]+1,table[i-1][j-1]+1);
		}
	}
}

/*
Parameters:
first_string - pointer to the first string (displayed vertical in the table)
second_string - pointer to the second string (displayed horizontal in the table)
print_table - If 1, the table with the calculations for the edit distance will be printed.
              If 0 (or any value other than 1)it will not print the table
(See sample run)
Return:  the value of the edit distance (e.g. 3)
*/
int edit_distance(char * first_string, char * second_string, int print_table){
	int rows = strlen(first_string) + 1;
	int cols = strlen(second_string) + 1;
	int i, j;
	int table[rows][cols];
	
	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			table[i][j] = calc_dist(first_string, second_string, i, j, rows, cols, table);
		}
	}

	if(print_table == 1) {
		for (i = 0; i < rows; i++) {
			printf("%c ", first_string[i]);
        	for (j = 0; j < cols; j++) {
            	printf("%d ", table[i][j]);
        	}
        	printf("\n");
    	}
	}

	return table[rows-1][cols-1];  // final edit distance, bottom right of table
}
	  

/*
Parameters:
testname - string containing the name of the file with the paragraph to spell check, includes .txt e.g. "text1.txt" 
dictname - name of file with dictionary words. Includes .txt, e.g. "dsmall.txt"
printOn - If 1 it will print EXTRA debugging/tracing information (in addition to what it prints when 0):
			 dictionary as read from the file	
			 dictionary AFTER sorting in lexicographical order
			 for every word searched in the dictionary using BINARY SEARCH shows all the "probe" words and their indices indices
			 See sample run.
	      If 0 (or anything other than 1) does not print the above information, but still prints the number of probes.
		     See sample run.
*/
void spell_check(char * testname, char * dictname, int printOn){
	int dict_size = 0;
	int* dict_ptr = &dict_size;

	char out_filename[20] = "out_";
	strcat(out_filename, testname);
	printf("Corrected output filename: %s\n", out_filename);
	
	printf("\nLoading the dictionary file: %s\n", dictname);
	char** dict_arr = dict_to_array(dictname, dict_ptr);
	printf("\nDictionary has size: %d", dict_size);

	if(printOn == 1) {
		int i;

		printf(" Original dictionary:\n");
		//dict print unsorted
		for(i = 0; i<dict_size; i++) {
			printf("%d. %s\n", i, dict_arr[i]);
		}

		//sort dict
		qsort(dict_arr, dict_size, sizeof(*dict_arr), cmpstr);

		printf("\n Sorted dictionary (alphabetical order):\n");
		//dict print sorted
		for(i = 0; i<dict_size; i++) {
			printf("%d. %s\n", i, dict_arr[i]);
		}

		check(out_filename, testname, dict_arr, dict_size, 1);
	}

	else {
		//sort dict
		qsort(dict_arr, dict_size, sizeof(*dict_arr), cmpstr);
		check(out_filename, testname, dict_arr, dict_size, 0);
	}

	//free dict_arr
	for(int i = 0; i < dict_size; i++) free(dict_arr[i]);
	free(dict_arr);
}

