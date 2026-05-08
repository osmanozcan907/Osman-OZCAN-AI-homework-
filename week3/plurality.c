// plurality.c
// CS50x — Week 3, Problem Set 3
//
// Exercise: Plurality Vote
// ─────────────────────────
// Simulate a first-past-the-post election.

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h> // For strcasecmp on some systems

// Maximum number of candidates allowed
#define MAX 9

// Data structure
typedef struct
{
    string name;
    int    votes;
} candidate;

// Global array of candidates and the count of candidates
candidate candidates[MAX];
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Require at least one candidate name as a command-line argument
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate the array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name  = argv[i + 1];
        candidates[i].votes = 0;
    }

    // Collect votes
    int voter_count = get_int("Number of voters: ");
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Announce result
    print_winner();
}

// ---------------------------------------------------------------------------
// Implementation of vote()
// ---------------------------------------------------------------------------
bool vote(string name)
{
    // Loop through candidates to find a match
    for (int i = 0; i < candidate_count; i++)
    {
        // Use strcasecmp for case-insensitive comparison
        if (strcasecmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    // If no match is found after checking the whole list
    return false;
}

// ---------------------------------------------------------------------------
// Implementation of print_winner()
// ---------------------------------------------------------------------------
void print_winner(void)
{
    // Step 1 — find the maximum vote count
    int max_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    // Step 2 — print every candidate who achieved max_votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
