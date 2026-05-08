// runoff.c
// CS50x — Week 3, Problem Set 3
//
// Exercise: Instant Runoff Voting
// ─────────────────────────────────

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Limits
#define MAX_VOTERS     100
#define MAX_CANDIDATES   9

// preferences[i][j] = the index of voter i's j-th ranked choice
int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    string name;
    int    votes;
    bool   eliminated;
} candidate;

candidate candidates[MAX_CANDIDATES];

int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int  find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // ... (Main function provided by CS50 remains the same)
    // It handles the runoff rounds, calling the functions below in order.
    // (I am skipping the full main body to focus on your TODOs)
    
    // Note: Use the provided main() from your distribution code.
    // The implementation below completes your required tasks.
    return 0; 
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 1: vote(voter, rank, name)
// ─────────────────────────────────────────────────────────────────────────────
bool vote(int voter, int rank, string name)
{
    // Search for a candidate matching the given name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(candidates[i].name, name) == 0)
        {
            // Record the candidate's index in the preferences array
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 2: tabulate()
// ─────────────────────────────────────────────────────────────────────────────
void tabulate(void)
{
    // Iterate over each voter
    for (int i = 0; i < voter_count; i++)
    {
        // For each voter, look through their ranked choices (from 0 to count)
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];

            // If the candidate at this preference rank is still in the race
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                // Stop here: we only count the highest-ranked valid choice
                break;
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 3: print_winner()
// ─────────────────────────────────────────────────────────────────────────────
bool print_winner(void)
{
    // A winner needs strictly more than half the votes
    float majority = voter_count / 2.0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 4: find_min()
// ─────────────────────────────────────────────────────────────────────────────
int find_min(void)
{
    int min = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        // Only consider candidates who are NOT eliminated
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 5: is_tie(min)
// ─────────────────────────────────────────────────────────────────────────────
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // If a candidate is still in the race but has more than min votes, it's not a tie
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    // All remaining candidates have exactly 'min' votes
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 6: eliminate(min)
// ─────────────────────────────────────────────────────────────────────────────
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Eliminate anyone currently in the race with the minimum number of votes
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
