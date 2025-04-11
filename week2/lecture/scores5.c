//Averages three numbers using an array, a constant, and a helper function

#include <cs50.h>
#include <stdio.h>

// Constant
const int N = 3;

//Prototype
float average(int length, int array[]);

int main(void)
{
    //Get scores
    int scores[N];
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }

    //print average
    printf("Average: %f\n", average(N, scores));
}

float average(int length, int array[]) //em C quando passamos um array como argumento para uma função ela não sabe qual é o
//tamanho do array portanto temos de passar noutro argumento o tamanho desse mesmo array, tal como está feito aqui
{
    //Calculate average
    int sum = 0;
    for (int i = 0; i < length; i++)
    {

        sum += array[i];
    }
    return sum / (float) length;
}
