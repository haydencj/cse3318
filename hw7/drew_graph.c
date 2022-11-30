#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int** fill_matrix(int N, char** classes, FILE* fp);
void print_matrix(int** matrix, int N);
void DFS_visit(int** matrix, int* result, int* idx, int N, int j, char* color, char** classes);
void DFS(int** matrix, int* result, int* idx, int N, char** classes);
void reverse(int* result, int N);
void free_mem(int** matrix, int* result, char* color, char** classes, int N);

int main() {
    char fname[30];

    printf("This program will read, from a file, a list of classes and their prerequisites and will print the list in which to take classes.\n");
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
	char **classes = malloc((N) * sizeof(char*)); //create an array of char pointers, one for each string (char *):
	for (int i = 0; i < N; ++i) {
    	classes[i] = (char*) malloc(30 * sizeof(char)); //allocate space for each string
	}

    int i = 0;
    while(fgets(line, 1000, fp)) {
        token = strtok(line, " \n");
        strcpy(classes[i], token);
        i++;
    }

    printf("Vertex - coursename correspondence\n");
    for(int i = 0; i < N; i++) {
        printf("%d - %s\n", i, classes[i]);
    }

    int** matrix = fill_matrix(N, classes, fp);
    printf("\nAdjacency matrix:\n");
    print_matrix(matrix, N);

    int idx = 0;
    int* result = malloc(sizeof(int) * N);
    DFS(matrix, result, &idx, N, classes);
    reverse(result, N);

    printf("Order in which to take classes:\n");
    for(int i = 0; i < N; i++) {
        printf("%d. - %s (corresponds to graph vertex %d)\n", i+1, classes[result[i]], result[i]);
    }

    //free memory
    for(int i = 0; i < N; i++) {
        free(classes[i]);
    }
    free(classes);
    free(result);

    for(int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int** fill_matrix(int N, char** classes, FILE* fp) {
    //create 2d int array
	int** matrix = (int**) malloc(sizeof(int*) * N); //create an array of int pointers
	for (int i = 0; i < N; ++i) {
    	matrix[i] = (int*) malloc(sizeof(int) * N); //allocate space for each int
	}

    //fill matrix with 0s
    for(int i = 0 ; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = 0;
        }
    }

    int d = 0, s = 0;
    char line[30];
    char* token;

    rewind(fp);
    for(int i = 0; i < N; i++) {
        fgets(line, 1000, fp);
        token = strtok(line, " \n");

        for(int i = 0; i < N; i++) {
            if(!strcmp(token, classes[i])) {
                d = i;
                break;
            }
        }

        token = strtok(NULL, " \n");

        while(token != NULL) {
            for(int i = 0; i < N; i++) {
                if(!strcmp(token, classes[i])) {
                    s = i;
                    break;
                }
            }

            matrix[s][d] = 1;
            token = strtok(NULL, " \n");
        }
    }
    fclose(fp);
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

void DFS_visit(int** matrix, int* result, int* idx, int N, int j, char* color, char** classes) {
    color[j] = 'G'; 
    for(int i = 0; i < N; i++) {
        if((color[i] == 'W') && (matrix[j][i] == 1)) { 
            DFS_visit(matrix, result, idx, N, i, color, classes);
        }

        if((color[i] == 'G') && (i != j) && (matrix[j][i] != 0)) { 
            printf("There was at least one cycle. There is no possible ordering of the classes.\n");
            free_mem(matrix, result, color, classes, N);
            exit(0);
        }
    }

    color[j] = 'B'; 
    result[*idx] = j;
    *idx+=1;
}

void DFS(int** matrix, int* result, int* idx, int N, char** classes) {
    char* color = malloc((N) * sizeof(char)); //create an array of char pointers, one for each char

    for(int i = 0; i < N; i++) {
        color[i] = 'W'; 
    }

    for(int i = 0; i < N; i++) {
        if(color[i] == 'W') { 
            DFS_visit(matrix, result, idx, N, i, color, classes);
        }
    }
    free(color);
}

void reverse(int* result, int N) {
    int* aux = malloc(sizeof(int) * N);

    for (int i = 0; i < N; i++) {
            aux[N - 1 - i] = result[i];
    }
    
    for (int i = 0; i < N; i++) {
            result[i] = aux[i];
    }

    free(aux);
}

void free_mem(int** matrix, int* result, char* color, char** classes, int N) {
    free(result);
    free(color);

    for(int i = 0; i < N; i++) {
        free(classes[i]);
    }
    free(classes);

    for(int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}