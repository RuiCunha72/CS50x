// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1378;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    for (node *ptr = table[hash(word)]; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word,word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (strlen(word) < 2)
    {
        return toupper(word[0]) - 'A';
    }
    
    int hash_value1 = toupper(word[0]) - 'A';
    int hash_value2 = toupper(word[1]) - 'A';

    int hash_value = ((hash_value1 + 26) * 26) + (hash_value2); //26 + 26 * 26 + 26 = 1378

    return hash_value;
}

int words = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{ 
    // TODO
    /*open dictionary file
    read strings from file one at a time
    create a new node for each word
    hash word to obtain a hash value
    inster node into hash table at that location
    */

    //Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) == 1)
    {
        if (strcmp(word, "EOF") == 0)
        {
            break;
        }

        node *new_word = malloc(sizeof(node));
        if (new_word == NULL)
        {
            printf("Error in memory\n");
            return false;
        }

        strcpy(new_word->word, word);
        new_word->next = table[hash(word)];
        table[hash(word)] = new_word;
        words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (words != 0)
    {
        return words;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }

    return true;
}
