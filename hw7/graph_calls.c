#include "graph.h"
#include <stdio.h>

int main() {
    char fname[30];
    Graph graph;

    printf("This program will read, from a file, a list of courses and their prerequisites and will print the list in which to take courses.\n");
    printf("Enter filename: ");
    scanf("%s", fname);

    FILE* fp = fopen(fname, "r");

    if(!fp) {
        printf("Could not open file %s. Exit\n\n", fname);
        printf("Failed to read from file. Program will terminate.\n\n");
        return 0;
    }

    


}