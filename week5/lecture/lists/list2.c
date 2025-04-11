#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *list = malloc (3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    //Time pass

    int *tmp = realloc(list, 4 * sizeof(int));
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    tmp[3] = 4;

    free(list);

    list = tmp;

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    free(list); //we could use free(tmp) tmp and list points to the same chunk of memory because of line 34 so it would work just fine as well
    return 0;
}
