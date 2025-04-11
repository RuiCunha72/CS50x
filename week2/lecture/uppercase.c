#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("Before: ");
    printf("After:  ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        /*este bloco é todo desnecessário porque na verdade a função toupper já verifica por nós se é maiuscula ou minuscula portanto nao ha necessidade
         do if else para verificar quais sao as minusculas e apenas converter essas mesmas
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            //change s[i] to uppercase
            //printf("%c", s[i] - ('a' - 'A')); Teríamos de fazer isto caso n existisse a funçao toupper da livraria ctype.h
            printf("%c", toupper(s[i]));
        }
        else
        {
            printf("%c", s[i]);
        }*/
        printf("%c", toupper(s[i]));
    }
    printf("\n");
}
