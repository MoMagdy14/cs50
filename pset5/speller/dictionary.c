// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65536;

// Hash table
node *table[N];

int wordcount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int length = strlen(word);
    char copy[length + 1]; // take a byte extra for NTC
    copy[length] = '\0'; // necessary to add the ntc after allocating space to it

// not converting gave errors to :) handles min length (1-char) words
//:) handles max length (45-char) words
//:) handles words with apostrophes properly
//:) spell-checking is case-insensitive

    for (int i = 0; i < length; i++) // we take the word and LC and save that into copy
    {
        copy[i] = tolower(word[i]);
    }
    // hash
    int hashcode = hash(copy); // get a hashcode for that copy
    node *tmp = table[hashcode]; // take a pointer tmp to point at what that array of hashcode is pointing
    if (tmp == NULL) // if tmp points to null return
    {
        return false;
    }
    // why always me don't check for temp
    while (tmp != NULL) // do it until the ll ends
    {
        if (strcasecmp(tmp->word, copy) == 0) // check case insesnitive for word in node to our word(copy)
        {
            return true; // if found
        }

        tmp = tmp->next; // else move to next node, traverse the ll
    }

    return false; // if not found copy until end
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned long hash = 5381;
    // just word
    int c = *word;
    // just loop
    while (c == *word++)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    // check if successfuly oppended
    if (dict == NULL)
    {
        return false;
    }
    // reading words
    while (true)
    {
        // word length + 1
        char wordd[LENGTH + 1];
        // scan for a single word
        if (fscanf(dict, "%s", wordd) == EOF)
        {
            break;
        }
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // copy word
        strcpy(n->word, wordd);
        n->next = NULL;
        unsigned int target = hash(wordd);
        n->next = table[target];
        table[target] = n;
        wordcount++;
    }
    fclose(dict);
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        // tmp follows cursor
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
