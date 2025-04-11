#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x = malloc(3 * sizeof(int));
    x[1] = 72;
    x[2] = 73;
    x[3] = 33;

    //este programa tem 2 bugs; feito para correr valgrind ./memory para ver como nos mostra os erros
    //importante olhar para as linhas onde sao identificados erros
    //neste programa nao indexamos o array, começamos na posição x[1] ao invés de x[0]
    //also neste programa nao libertamos a memória de x no final através de free(x) 
}
