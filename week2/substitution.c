// substitution.c
// CS50x - Week 2, Problem Set 2
//
// Exercise: Substitution Cipher
// ------------------------------
// Encrypt a message using a 26-character substitution key.

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function prototypes
bool is_valid_key(string key);

int main(int argc, string argv[])
{
    // ---------------------------------------------------------------------------
    // STEP 1: Validate command-line arguments
    // ---------------------------------------------------------------------------
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (!is_valid_key(argv[1]))
    {
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    string key = argv[1];

    // ---------------------------------------------------------------------------
    // STEP 2: Get the plaintext from the user
    // ---------------------------------------------------------------------------
    string plaintext = get_string("plaintext:  ");

    // ---------------------------------------------------------------------------
    // STEP 3: Encrypt and print ciphertext
    // ---------------------------------------------------------------------------
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];

        if (isupper(c))
        {
            // Find alphabet position (0-25) and use the key's character
            int index = c - 'A';
            printf("%c", toupper(key[index]));
        }
        else if (islower(c))
        {
            // Find alphabet position (0-25) and use the key's character
            int index = c - 'a';
            printf("%c", tolower(key[index]));
        }
        else
        {
            // Non-letter characters stay the same
            printf("%c", c);
        }
    }

    printf("\n");
    return 0;
}

// ---------------------------------------------------------------------------
// Implementation of is_valid_key
// ---------------------------------------------------------------------------
bool is_valid_key(string key)
{
    // Check length is 26
    if (strlen(key) != 26)
    {
        return false;
    }

    bool seen[26] = {false};

    for (int i = 0; i < 26; i++)
    {
        // Check if alphabetic
        if (!isalpha(key[i]))
        {
            return false;
        }

        // Check for duplicates (case-insensitive)
        int index = tolower(key[i]) - 'a';
        if (seen[index])
        {
            return false;
        }
        seen[index] = true;
    }

    return true;
}
