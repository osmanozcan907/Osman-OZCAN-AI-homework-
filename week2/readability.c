// readability.c
// CS50x - Week 2, Problem Set 2
//
// Exercise: Readability
// ----------------------
// Compute the Coleman-Liau readability index of a text sample
// and print the corresponding U.S. grade level.

#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Function prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count letters, words, and sentences using helper functions
    int letters   = count_letters(text);
    int words     = count_words(text);
    int sentences = count_sentences(text);

    // Compute L and S (averages per 100 words)
    // We use 100.0 to force float division
    float L = 100.0 * letters / words;
    float S = 100.0 * sentences / words;

    // Apply the Coleman-Liau formula and round to nearest integer
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print the grade level based on the index result
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// ---------------------------------------------------------------------------
// Implementation of count_letters
// ---------------------------------------------------------------------------
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Increment count if the character is a letter (a-z or A-Z)
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

// ---------------------------------------------------------------------------
// Implementation of count_words
// ---------------------------------------------------------------------------
int count_words(string text)
{
    // We assume at least one word exists, so we count spaces and add 1
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isspace(text[i]))
        {
            count++;
        }
    }
    return count + 1;
}

// ---------------------------------------------------------------------------
// Implementation of count_sentences
// ---------------------------------------------------------------------------
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // Check for common sentence-ending punctuation
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
