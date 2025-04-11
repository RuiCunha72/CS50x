#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Missing command-line argument\n");
        return 1;
    }
    printf("hello, %s\n", argv[1]);
    return 0;

    //quando corremos o programa depois podemos executar o comando echo $? e ver o valor que retornou, usado no mundo de automação de testes
}
