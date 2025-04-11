#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float average_per_100_words(int n, int words);
float get_grade(string text);

int main(void)
{
    string text = get_string("Text: ");
    float gradeLevel = get_grade(text);
    if(gradeLevel > 0 && gradeLevel < 16)
    {
        printf("Grade %i\n", (int) round(gradeLevel));
    }
    else
    {
        if(gradeLevel < 1)
        {
            printf("Before Grade 1\n");
        }
        else
        {
            printf("Grade 16+\n");
        }
    }

}

float get_grade(string text)
{
    int count_letters = 0;
    int count_words = 1;
    int count_sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (tolower(text[i]) >= 'a' && tolower(text[i]) <= 'z')
        {
            count_letters++;
        }
        if (text[i] == ' ')
        {
            count_words++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count_sentences++;
        }
    }
    float l = average_per_100_words(count_letters, count_words);
    float s = average_per_100_words(count_sentences, count_words);
    float index = (0.0588 * l) - (0.296 * s) - 15.8;
    return index;
}

float average_per_100_words(int n, int words)
{
    return (float) n / words * 100;
}
