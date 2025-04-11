#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    //este exemplo abaixo nao funcionaria pq quando estamos a dizer char *t = s o que estamos a fazer na vdd é dizer para o computador
    //ir buscar o endereço de memoria onde está guardado s, ou seja, t e s vão estar sempre a referir-se aos mesmos caracteres q começam
    //no adreço de memoria de s, que t vai depois buscar, portanto quando mudamos a letra inicial de t para maiuscula vamos estar a alterar
    //a letra maiuscula de s também, pois são a mesma coisa, solução para isto é usar a função malloc (library stdlib necessary)
    /*char *s = get_string("s: ");

    char *t = s;

    t[0] = toupper(t[0]);

    printf("s: %s\n",s);
    printf("t: %s\n",t);*/


    char *s = get_string("s: ");

    char *t = malloc(strlen(s) + 1); //1 byte a mais para o \0
    if ( t == NULL ) //este if é um método de programação defensiva, no caso, se a malloc não conseguir ir buscar a memória necessária
    {                 //para alocar o que precisamos em t, a função malloc vai buscar o ponteiro para 0 que é no caso == NULL
        return 1;       // por isso fazemos este if para na eventualidade de isso acontecer o programa nao correr
    }

    /* Este loop não é necessário, a função strcpy já faz isto por nós
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
    }
    */

    strcpy(t, s);

    if (strlen(t) > 0) //mais um if de programação defensiva, caso o user nao tenha introduzido nada na string s não vamos fazer uppercase de nada
    {
        t[0] = toupper(t[0]);
    }


    printf("s: %s\n",s);
    printf("t: %s\n",t);

    free(t); //libertar a memoria que foi alocada a t
}
