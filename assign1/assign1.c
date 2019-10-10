#include <stdio.h>
#include <stdlib.h>
#include "pslibrary.h"

int main(int argc, char *argv[]) {
    int i1, i2, i3, i4, i5, i6, i7;
    char *heading;
    int n;
    char *s1, *s2;

    if(argc != 8) {
        printf("Improper format! Usage is %s int 1 int 2... int 3\n", argv[0]);
        exit(1);
    }

    i1 = atoi(argv[1]);
    i2 = atoi(argv[2]);
    i3 = atoi(argv[3]);
    i4 = atoi(argv[4]);
    i5 = atoi(argv[5]);
    i6 = atoi(argv[6]);
    i7 = atoi(argv[7]);

    printf("Assignment 1 was written by Sam Dash\n");
    printf("inputs: %d %d %d %d %d %d %d\n", i1, i2, i3, i4, i5, i6, i7);

    n = i2+i3+i4+i5+i6+i7;

    if((s1 = malloc(n)) == NULL || (s2 = malloc(n)) == NULL) {
        printf("Insufficient memory\n");
        exit(2);
    }

    heading = "Part 0\n";

    fcfsa(s1, s2, i2, i3, i4, i5, i6, i7);
    display(heading, s1, s2);

    return 0;

}
