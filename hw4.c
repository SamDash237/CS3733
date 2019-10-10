#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
int fd;
char buf[5] = "WXYZ";
fd = open ("mydatafile.txt", O_RDONLY);
fork();
read(fd, buf, 1);
read(fd, buf+1, 1);
printf ("%c%c\n", buf[0], buf[1]);
return 0;
}