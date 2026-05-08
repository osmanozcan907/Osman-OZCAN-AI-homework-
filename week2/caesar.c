// caesar.c
// CS50x - Week 2, Problem Set 2
//
// Exercise: Caesar Cipher
// ------------------------
// Encrypt a message by rotating each letter forward in the alphabet
// by a numeric key given as a command-line argument.

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // ---------------------------------------------------------------------------
    // STEP 1: Validate command-line arguments
    // ---------------------------------------------------------------------------
    // Check that there is exactly one command-line argument and it is numeric
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // ---------------------------------------------------------------------------
    // STEP 2: Convert the key from string to int
    // ---------------------------------------------------------------------------
    int key = atoi(argv[1]);

    // ---------------------------------------------------------------------------
    // STEP 3: Get the plaintext from the user
    // ---------------------------------------------------------------------------
    string plaintext = get_string("plaintext:  ");

    // ---------------------------------------------------------------------------
    // STEP 4: Encrypt and print the ciphertext
    // ---------------------------------------------------------------------------
    printf("ciphertext: ");

    // Loop through each character of plaintext and rotate it
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        char c = rotate(plaintext[i], key);
        printf("%c", c);
    }

    // Print a newline after the full ciphertext
    printf("\n");
    return 0;
}

// ---------------------------------------------------------------------------
// Implementation of only_digits
// ---------------------------------------------------------------------------
bool only_digits(string s)
{
    // Loop through each character to ensure it is a digit
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// Implementation of rotate
// ---------------------------------------------------------------------------
char rotate(char c, int n)
{
    // If character is uppercase, shift within A-Z
    if (isupper(c))
    {
        return (c - 'A' + n) % 26 + 'A';
    }
    // If character is lowercase, shift within a-z
    else if (islower(c))
    {
        return (c - 'a' + n) % 26 + 'a';
    }
    // If character is not a letter, return it as is
    else
    {
        return c;
    }
}
