#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv){

    union{
        short s;
        char  c[sizeof(short)];
    } un;

    un.s = 0x0102;
    if (sizeof(short) == 2 ) {
        if (un.c[0] == 1 && un.c[1] == 2)
            printf("big-endian\n");
        else if (un.c[0] == 2 && un.c[1] == 1)
            printf("little-endian\n");
        else
            printf("unkown\n");
    } 
    else
        printf("sizeof(short) = %lu\n", sizeof(short));

    return 0;
}
