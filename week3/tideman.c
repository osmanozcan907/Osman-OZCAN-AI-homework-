// tideman.c
// CS50x — Week 3, Problem Set 3
//
// Exercise: Tideman (Ranked Pairs)

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Limits
#define MAX 9

// preferences[i][j] = number of voters who prefer candidate i over candidate j
int preferences[MAX][MAX];

// locked[i][j] = true means there is a locked edge FROM i TO j
bool locked[MAX][MAX];

typedef struct
{
    int winner;
    int loser;
} pair;

string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool creates_cycle(int start, int end);

int main(int argc, string argv[])
{
    // ... (Main function provided by CS50 handles setup and calling functions)
    // I will focus on implementing the TODOs below.
    
    // Initialise and collect votes (Standard CS50 logic)
    // After collecting votes, the following functions are called:
    // add_pairs();
    // sort_pairs();
    // lock_pairs();
    // print_winner();
    return 0;
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 1: vote()
// ─────────────────────────────────────────────────────────────────────────────
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 2: record_preferences()
// ─────────────────────────────────────────────────────────────────────────────
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // The person at ranks[i] is preferred over the person at ranks[j]
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 3: add_pairs()
// ─────────────────────────────────────────────────────────────────────────────
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 4: sort_pairs()
// ─────────────────────────────────────────────────────────────────────────────
void sort_pairs(void)
{
    // Sorting by strength of victory (descending) using Bubble Sort
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int strength1 = preferences[pairs[j].winner][pairs[j].loser];
            int strength2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser];

            if (strength1 < strength2)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 5: lock_pairs() & creates_cycle()
// ─────────────────────────────────────────────────────────────────────────────
bool creates_cycle(int start, int end)
{
    // If the path leads back to the original winner, a cycle is created
    if (start == end)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        // If 'end' points to 'i', check if 'i' eventually points back to 'start'
        if (locked[end][i])
        {
            if (creates_cycle(start, i))
            {
                return true;
            }
        }
    }
    return false;
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Only lock the edge if it doesn't create a cycle
        if (!creates_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 6: print_winner()
// ─────────────────────────────────────────────────────────────────────────────
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool has_incoming_edge = false;

        for (int j = 0; j < candidate_count; j++)
        {
            // If anyone points to candidate i, i is not the source
            if (locked[j][i])
            {
                has_incoming_edge = true;
                break;
            }
        }

        // If no one points to candidate i, they are the source (winner)
        if (!has_incoming_edge)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
