#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
Student answer:  Theta(............)
*/


/* You can write helper functions here */
int calc_dist(char* first, char* second, int i, int j, int** table) {
	if(i == 0 && j == 0) return 0;
	else if(i == 0) return j;
	else if(j == 0) return i;
	else {
		if(first[i-1] == second[j-1]) return table[i-1][j-1];
		else {
			return min(table[i-1][j],table[i][j-1],table[i-1][j-1]);
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
	int dist;

	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			table[i][j] = calc_dist(first_string, second_string, i, j, table);
		}
	}

	if(print_table == 1) {

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
	// Write your code here
}

