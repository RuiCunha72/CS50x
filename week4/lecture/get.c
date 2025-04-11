#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /*int n;
    printf("n: ");
    scanf("%i", &n);
    printf("n: %i\n", n);*/

    char *s = malloc(4); //nao se recomenda dar hardcode no tamanho de memoria a alocar. prof. David recomendou por enquanto continuar a usar get_string da biblioteca cs50
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
    free(s);
}
