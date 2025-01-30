#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{



    int ch = 8;
    unsigned char kk;
    unsigned char val = 5;
    while (ch--)
    {
        kk = ((val >> ch & 1)) +'0';
        printf("%c",kk);

    }
}