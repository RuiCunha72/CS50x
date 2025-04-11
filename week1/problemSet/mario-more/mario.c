#include <cs50.h>
#include <stdio.h>

int getHeight(void);
void print_pyramid(int n);

int main(void)
{
    int n = getHeight();
    print_pyramid(n);
}

int getHeight(void)
{
    int height = get_int("How tall is the pyramid? ");
    while (height <1 || height >8)
    {
        height = get_int("How tall is the pyramid? ");
    }
    return height;
}

void print_pyramid(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n - 1; j++)
        {
            printf(" ");
        }

        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("  ");
        
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}
