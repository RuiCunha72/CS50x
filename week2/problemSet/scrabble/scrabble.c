#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int get_score(string word);
int get_points(char letter);

int main(void)
{
    string word1 = get_string("Player1: ");
    string word2 = get_string("Player2: ");
    int score1 = get_score(word1);
    int score2 = get_score(word2);
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int get_score(string word)
{
    int sum = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        int points = get_points(tolower(word[i]));
        sum += points;
    }
    return sum;
}

int get_points(char letter)
{
    if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'l' || letter == 'n' ||
        letter == 'o' || letter == 'r' || letter == 's' || letter == 't' || letter == 'u')
    {
        return 1;
    }
    else if (letter == 'd' || letter == 'g')
    {
        return 2;
    }
    else if (letter == 'b' || letter == 'c' || letter == 'm' || letter == 'p')
    {
        return 3;
    }
    else if (letter == 'f' || letter == 'h' || letter == 'v' || letter == 'w' || letter == 'y')
    {
        return 4;
    }
    else if (letter == 'k')
    {
        return 5;
    }
    else if (letter == 'j' || letter == 'x')
    {
        return 8;
    }
    else if (letter == 'q' || letter == 'z')
    {
        return 10;
    }
    else
    {
        return 0;
    }
}
