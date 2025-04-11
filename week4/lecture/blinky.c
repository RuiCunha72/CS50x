#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x;
    int *y;

    x = malloc(sizeof(int));

    *x = 42;
    //*y = 13; //não vai funcionar pq n há memória alocada para o ponteiro, ou seja, o ponteiro criado em cima (int y) não está apontado a lado nenhum

    y = x; //põe o ponteiro y a apontar para a mesma memória alocada em x

    *y = 13; //agora já vai funcionar, mas vai fazer com o valor do ponteiro de x seja substituido de 42 por 13, uma vez q estao a apontar para a mesma memoria
}
