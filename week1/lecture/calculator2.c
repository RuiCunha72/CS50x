#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("x: ");
    int y = get_int("y: ");

    printf("%i\n", x / y); //vai devolver sempre inteiros
    printf("%f\n", (float) x / y); //vai fazer cast do valor inteiro para float e evitar a truncation e portanto vai permitir imprimir em float
    printf("%.3f\n", (float) x / y); //é igual à linha de cima, mas imprime c/ 3 casas decimais
    printf("%.50f\n", (float) x / y); //"erro" de float-point imprecision erro semalhante ao overflow para inteiros; also como os int tem o long os floats tem o double
}
