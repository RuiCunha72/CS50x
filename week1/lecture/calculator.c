#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long dollars = 1; //long é uma versão mais longa de inteiros, inteiros só tem 32 bits para serem representados, long tem até 64 bits
    while (true)
    {
        char c = get_char("Here's $%li. Double it and give it to the next person? ", dollars);
        if (c == 'y')
        {
            dollars *=2;
        }
        else
        {
            break;
        }
    }
    printf("Here's $%li.\n", dollars);
}
