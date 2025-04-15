#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    string phrase;
    struct node *next;
} node;

int main(void)
{
    node *list = NULL;
    node *n = malloc (sizeof(node));
    if (n == NULL)
    {
        return 1;
    }

    n->phrase = "Hi!";
    n->next = NULL;

    list = n;

    node *m = malloc (sizeof(node));
    if (m == NULL)
    {
        return 1;
    }
    m->phrase = "Hey!";
    m->next = list;

    list = m;

    node *l = malloc (sizeof(node));
    if (l == NULL)
    {
        return 1;
    }
    l->phrase = "Hello!";
    l->next = list;

    list = l;

    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%s\n", ptr->phrase);
    }

    node *ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

}