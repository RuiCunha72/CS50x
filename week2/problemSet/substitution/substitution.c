#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int is_key_valid(string text);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    int is_valid = is_key_valid(key);

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (is_valid == 0)
    {
        printf("Key must contain alphabetic characters only!\n");
        return 1;
    }
    else
    {
        string text = get_string("plaintext:  ");
        printf("ciphertext: ");
        for (int i=0, n = strlen(text); i < n; i++)
        {
            if (text[i] >= 'a' && text[i] <= 'z')
            {
                int position = text[i] - 'a';
                printf("%c", tolower(key[position]));
            }
            else if (text[i] >= 'A' && text[i] <= 'Z')
            {
                int position = text[i] - 'A';
                printf("%c", toupper(key[position]));
            }
            else
            {
                printf("%c", text[i]);
            }
        }
        printf("\n");
    }
}


int is_key_valid(string text)
{
    int is_valid = 1;
    char letters[25];
    for (int i = 0; i < 26; i++)
    {
        if ((isalpha(text[i])))
        {
            for (int j = 0; j <= i; j++)
            {
                if (letters[j] == tolower(text[i]))
                {
                    is_valid = 0;
                }
            }
            letters[i] = tolower(text[i]);
        }
        else
        {
            is_valid = 0;
        }
    }
    return is_valid;
}
