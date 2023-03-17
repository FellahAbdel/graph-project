#include <stdio.h>
#include <stdlib.h>

void init(int **ptr)
{
    *ptr = (int *)malloc(sizeof(int));
}

int main()
{
    int *r;
    init(&r);
    printf("%p\n", r); // should print the address of the memory location pointed to by r
    free(r);
    return 0;
}
