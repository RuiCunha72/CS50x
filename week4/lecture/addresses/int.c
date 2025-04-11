#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n;
    //printf("%p\n", p);
    //printf("%p\n", &n);
    printf("%i\n", *p);

    //& -> this tells me the address of something (like were in the memory is this variable)
    //* -> this tells me hwo to get to something (like having the address and goes there in that location of the memory)
    //%p -> to print pointers
}
