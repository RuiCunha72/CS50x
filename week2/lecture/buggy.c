#include <cs50.h>
#include <stdio.h>

void print_column(int height);

int main(void)
{
   /* for (int i = 0; i < 3; i++)
    {
        //printf("i is %i\n", i);//usado para debug
        printf("#\n");
    }*/

    int h = get_int("Height: ");
    print_column(h);
}

void print_column(int height)
{
    for (int i = 0; i <= height; i++)//erro propositado <= feito para estudar o debug através do debug tool --> debug50 ./buggy (ñ é related c/ o cs50)
    {
        printf("#\n");
    }
}
