#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char *argv[]) {
    int addrt[] = {2,4,1,7,3,5,6};
    int fdi, fdo;
    unsigned long os, p, physar, virtar;

    if(argc != 2) {
        printf("Usage: %s <SEQUENCE_FILE>\n", argv[0]);
        exit(1);
        }
    if((fdi = open(argv[1], O_RDONLY)) == -1) {
        perror("Failed to open sequence file");
        exit(2);
        }
    if((fdo = open("output-part1", O_WRONLY | O_CREAT, 0600)) == -1) {
        perror("Failed to open output file");
        close(fdi);
        exit(2);
        }
    while(read(fdi, &virtar, sizeof(virtar)) > 0) {
        os = virtar & 0x7F;
        p = virtar >> 7;
        p = addrt[p];
        physar = p << 7;
        physar += os;
        if(write(fdo, &physar, sizeof(physar)) == -1) {
            perror("Failed to write to output file");
            exit(3);
            }
    }
    close(fdi);
    close(fdo);

    return 0;
}
