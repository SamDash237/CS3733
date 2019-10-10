#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main(){
 printf("L0\n");
 if (fork() != 0) {
printf("L1\n");
if (fork() != 0) {
 printf("L2\n");
 fork();
}
 }
 printf("Bye\n");
}
