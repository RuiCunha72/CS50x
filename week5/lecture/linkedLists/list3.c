#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(void)
{
    node *list = NULL;
    
    for (int i = 0; i < 3; i++)
    {
        node *n = malloc (sizeof(node)); //novo chunck de memoria, queria um novo nó, q tem por sua vez um int e um next node
        if (n == NULL)
        {
            /*aqui devemos ter o cuidado de perceber que ele pode nao falhar na primeira nem na segunda iteração e falhar por exemplo
            apenas na terceira portanto antes de retornar e fechar o programa deviamos considerar a possiblidade de haver ja memoria 
            alocada e portanto libertar | Isto é, imagine-se q so entra no if para i=2 (terceira iteração), antes de fechar o programa
            deviamos dar free da memoria alocada na iteração i=0 e i=1*/
            return 1;
        }
        n->number = get_int("Number: "); //aloca ao slot int do node o numero introduzido pelo user
        n->next = NULL; //aloca se ao slot next node do co a ser criado memoria ainda vazia

        if (list == NULL) //se o ponteiro list ainda estiver vazio é fácil, apontamos este ponteiro list para o node criado 
        {
            list = n;
        }
        else //caso contrario
        { /*criamos um loop for que cria num ponteiro novo q aponta para o primeiro ponteiro list, este loop vai ser corrido até
            ao ultimo node criado, iterando sempre de ponteiro em ponteiro*/
            for (node *ptr = list; ptr != NULL; ptr = ptr->next) 
            {
                if (ptr->next == NULL) //se chegarmos a um ponteiro em que o proximo é null sabemos que chegamos ao final da lista
                {
                    ptr->next = n; //é entao aí que queremos adicionar o novo ponteiro
                    break;
                }
            }
        }
    }

    //Time passes

    /*loop que aponta para o inicio da lista e da print do inicio e itera sempre para o proximo ponteiro ate ao final da lista*/
    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }

    //Time passes

    node *ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    

    return 0;
}
