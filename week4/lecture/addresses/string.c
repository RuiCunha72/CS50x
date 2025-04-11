//#include <cs50.h> //adicionado para lidar c strings
#include <stdio.h>

int main(void)
{
    /*string s = "Hi!\n"; //string nao existe em C
    printf("%s\n", s);*/
    //printf vai ao address do primeiro caracter e da print do array (sim string é um array de caracteres) até ao \0 (NUL caracter)


    char *s = "Hi!";
    /*printf("%s\n", s);
    printf("%p\n", s);
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);*/


    /*printf("%c\n", *s);
    printf("%c\n", *(s + 1));
    printf("%c\n", *(s + 2));*/


    printf("%s\n", s + 1);
}
