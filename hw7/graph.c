#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int** fill_matrix(int N, char** courses, FILE* fp);
void print_matrix(int** matrix, int N);

int main() {
    char fname[30];

    printf("This program will read, from a file, a list of courses and their prerequisites and will print the list in which to take courses.\n");
    printf("Enter filename: ");
    scanf("%s", fname);

    FILE* fp = fopen(fname, "r");

    if(!fp) {
        printf("Could not open file %s. Exit\n\n", fname);
        printf("Failed to read from file. Program will terminate.\n\n");
        return 0;
    }

    char line[30];
    char* token;
    int N = 0; //number of vertices 
    while(fgets(line, 1000, fp)) {
        N++;
    }
    rewind(fp);

    printf("Number of vertices in built graph: N = %d\n", N);

    //create 2d char array
	char **courses = malloc((N) * sizeof(char*)); //create an array of char pointers, one for each string (char *):
	for (int i = 0; i < N; ++i) {
    	courses[i] = (char*) malloc(30 * sizeof(char)); //allocate space for each string
	}

    int i = 0;
    while(fgets(line, 1000, fp)) {
        token = strtok(line, " \n");
        strcpy(courses[i], token);
        i++;
    }

    printf("Vertex - coursename correspondence\n");
    for(int i = 0; i < N; i++) {
        printf("%d - %s\n", i, courses[i]);
    }

    int** matrix = fill_matrix(N, courses, fp);
    printf("\nAdjacency matrix:\n");
    print_matrix(matrix, N);

    fclose(fp);
}

int** fill_matrix(int N, char** courses, FILE* fp) {
    //create 2d int array
	int** matrix = malloc((N) * sizeof(int*)); //create an array of int pointers
	for (int i = 0; i < N; ++i) {
    	matrix[i] = (int*) malloc(sizeof(int)); //allocate space for each int
	}

    int destination = 0, source = 0;
    char line[30];
    char* token;

    //fill matrix with 0s
    for(int i = 0 ; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = 0;
        }
    }

    rewind(fp);
    for(int i = 0; i < N; i++) {
        fgets(line, 1000, fp);
        token = strtok(line, " \n");

        for(int i = 0; i < N; i++) {
            if(!strcmp(token, courses[i])) {
                destination = i;
                break;
            }
        }

        token = strtok(NULL, " \n");

        while(token != NULL) {
            for(int i = 0; i < N; i++) {
                if(!strcmp(token, courses[i])) {
                    source = i;
                    break;
                }
            }

            matrix[source][destination] = 1;
            token = strtok(NULL, " \n");
        }
    }

    return matrix;
}

void print_matrix(int** matrix, int N){
    printf("    |");
    for(int i = 0 ; i < N; i++) {
        printf("%4d", i);
    }
    printf("\n");
    printf("-----");
    for(int i = 0; i < N; i++) {
        printf("----");
    }
    printf("\n");
    for(int i = 0; i < N; i++){
        printf("%4d|", i);
        for(int j = 0; j < N; j++){
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}