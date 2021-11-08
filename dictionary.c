// Implements a dictionary's functionality
 #include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <strings.h>
#include <string.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// Number of buckets in hash table
const unsigned int N = 200000;

// Hash table
node *table[N];
// Counter for hash table
int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //TODO
    char new_word[strlen(word) + 1];
    for (int i = 0; i < strlen(word) + 1; i++)
    {
        new_word[i] = tolower(word[i]);
    }
    unsigned int index = hash(new_word);

    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, new_word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
           unsigned int hash = 5381;
    int c = 0;

    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % N;


}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    for (int i = 0; i < 200000; i++)
    {
        table[i] = NULL;
    }

    FILE *file = fopen(dictionary, "r");
    if(file == NULL){
    return false;
    }

    char arr[LENGTH];

    while (fscanf(file,"%s",arr) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if(new_node == NULL){
            return false;
        }
        counter++;

        strcpy(new_node->word, arr),
        new_node->next = NULL;

        unsigned int index = hash(new_node->word);
        if (table[index] == NULL)
        {
            table[index] = new_node;
        }
       else
       {
        new_node->next = table[index];
        table[index] = new_node;
       }

    }


    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {

        while (table[i] != NULL)
        {
            node *mirage = table[i]->next;
            free(table[i]);
            table[i] = mirage;

        }
    }

    return true;
}
