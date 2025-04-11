#include <cs50.h>
#include <stdio.h>

string userInput(void);

int main(void)
{
    string userName = userInput();
    printf("hello, %s\n", userName);
}

string userInput(void)
{
    string name = get_string("Name: ");
    return name;
}
