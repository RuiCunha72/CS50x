#include <stdio.h>

int main(void)
{
    printf("Hello, world!\n");
}
//usado para explicar o clang --> clang -o hello hello.c
//se usarmos uma third-party library como a <cs50.h> temos de introduzir mais um
//argumento no comando q comila através do clang --> clang -o hello hello.c -lcs50
