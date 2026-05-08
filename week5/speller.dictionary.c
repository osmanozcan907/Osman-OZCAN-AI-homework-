// Implements a dictionary's functionality using a hash table

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
} node;

// Choose number of buckets in hash table
// Using a larger N (like 10007) would make it even faster by reducing collisions
const unsigned int N = 26;

// Hash table array
node *table[N];

// Global word counter initialized to 0
unsigned int word_count = 0;

// TODO 1: hash()
// Hashes word to a number in range [0, N-1]
unsigned int hash(const char *word)
{
    // A simple hash function that uses the first character
    // We use tolower to make it case-insensitive
    return tolower(word[0]) - 'a';
}

// TODO 2: load()
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Read strings from file one at a time until EOF
    while (fscanf(file, "%45s", word) != EOF)
    {
        // Allocate memory for a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy word into node using strcpy
        strcpy(n->word, word);

        // Get hash index for the word
        unsigned int index = hash(word);

        // Prepend node to the linked list in the bucket
        n->next = table[index];
        table[index] = n;

        // Increment the global word counter
        word_count++;
    }

    // Close dictionary file
    fclose(file);
    return true;
}

// TODO 3: check()
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Obtain hash index for the word
    unsigned int index = hash(word);

    // Set cursor to point to the head of the linked list in the bucket
    node *cursor = table[index];

    // Walk through the linked list
    while (cursor != NULL)
    {
        // Use strcasecmp for case-insensitive comparison
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // Move to next node
        cursor = cursor->next;
    }

    return false;
}

// TODO 4: size()
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Simply return the global counter incremented during load()
    return word_count;
}

// TODO 5: unload()
// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop over each bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        // Set cursor to the start of the bucket's linked list
        node *cursor = table[i];

        while (cursor != NULL)
        {
            // Save pointer to next node BEFORE freeing current node
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
