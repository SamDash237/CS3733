#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myio.h"

int main(int argc, char *argv[]) {
    FILE *f1, *f2;
    char *iL, *oL;
    int d1, d2;
    int s;
    char c;
    
    //This loop checks for the correct number of arguments
    if(argc != 3) {
        printf("Correct usage is %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    //This loop opens the files
    f1 = fopen(argv[1], "r");
    if(f1 == NULL) {
        printf("Unable to open input file %s\n", argv[1]);
        return 1;
    }

    f2 = fopen(argv[2], "w");
    if(f2 == NULL) {
        printf("Unable to open output file %s\n", argv[2]);
    }

    while((iL = ReadLineFile(f1)) != NULL) {
        oL = calloc(strlen(iL),sizeof(char));
        d1 = 0;
        d2 = 0;
        s = 0;
        while(!s) {
            c = iL[d1++];
            //copies all non-space characters
            while(c != ' ' && c != '\t') {
                if(c=='\0') {
                    s = 1;
                    break;
                }
                oL[d2++] = c;
                c = iL[d1++];
            }
            if(!s) {
            //puts single space in output
                oL[d2++] = ' ';
                //skips over blank space characters
                while(iL[d1] == ' ' || iL[d1] == '\t')
                    d1++;
                }
            else {
                oL[d2] = '\0';
                fprintf(f2, "%s\n", oL);
            }
        }
    //free space allocated for files
    free(iL);
    free(oL);
    }
    fclose(f1);
    fclose(f2);
    
    printf("Generated output file %s\n", argv[2]);
}