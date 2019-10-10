#include <stdio.h>

int add(int a, int b) {
    return a+b;
}

int main() {
    int c = add(3,4);
    if(c > 0)
        c = 1;
    else if(c <0)
        c = -1;
    else
        c = 0;
    return 0;
}
