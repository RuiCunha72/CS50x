#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //isto é um bad design, para cada novo score estamos a criar individualmente uma variável
    /*int score1 = 72;
    int score2 = 73;
    int score3 = 33;
    // Print average
    printf("Average: %f\n", (score1 + score2 + score3) / (float) 3);*/ //nesta última linha tivemos de dar cast do 3 para float para a expressão matemática considerar o resultado final como um float

    //esta opção já é melhor
    /*int scores[3];
    scores[0] = 72;
    scores[1] = 73;
    scores[2] = 33;
    printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / (float) 3);*/

    //opção melhor mas ñ perfeita
    /*int scores[3];
    for (int i = 0; i < 3; i++)
    {
        scores[i] = get_int("Score: ");
    }
    printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / (float) 3);*/

    //melhor opção ainda
    const int N = 3; //geralmente o nome da constante fica em CAPS por forma de sobressair no código e alertar o leitor q isto é uma constante
    int scores[N];
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }
    printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / (float) N);

    //MELHOR OPÇÃO CONSTRUÍDA NO FICHEIRO SCORES5.C
}
