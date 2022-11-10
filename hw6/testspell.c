#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check(char* output, char* input) {
	FILE* out_fp = fopen(output, "w");
	FILE* in_fp = fopen(input, "r");
	if(!out_fp || !in_fp) {
		printf("File(s) could not be opened.\n");
        return 0;
	}
/*
But you have a buffer, and if it’s not a separator, store it in the buffer
Then keep putting stuff in that buffer until you hit a separator
And then just parse the word when you hit a separator
*/

    char buffer[101];
    int c;
    int i;
    while((c = fgetc(in_fp)) != EOF){ 
        if((ispunct(c)) || (c == 32)) { //32 ascii value for whitespace
            printf("%s\n", buffer);
            memset(buffer, 0, 101);
            i=0;
        }

        else {
            buffer[i] = c;
            i++;
        }
    }


    fclose(out_fp);
    fclose(in_fp);
    return 1;
}

int main() {
    char testname[101] = "text1.txt";
    printf("Enter the text file name: ");
    //scanf("%s", testname);

    char out_filename[20] = "out_";
	strcat(out_filename, testname);
	printf("Corrected output filename: %s\n", out_filename);

    check(out_filename, testname);
}
