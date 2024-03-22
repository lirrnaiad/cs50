#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    // Loop through each candidate and add to the 2D preferences array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    // Loop through each voter on the outer loop,
    // loop through each candidate on the inner loop

    // If voter 1's first preference is Alice, and Alice is candidates[0]
    // then preferences[i][j] will be 0
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if candidate is eliminated
            // If yes, move to the next preference of voter
            while (candidates[preferences[i][j]].eliminated == true)
            {
                j++;
            }

            candidates[preferences[i][j]].votes++;
            break;
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    // Check highest number of votes
    int highest_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > highest_votes)
        {
            highest_votes = candidates[i].votes;
        }
    }

    // Get the half of voter count to indicate majority
    int majority_vote = voter_count / 2;

    // After getting highest number, check how many candidates have the same number of votes
    int potential_winners = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == highest_votes)
        {
            potential_winners++;
        }
    }

    // If only one candidate, check if candidate has the majority vote
    // If candidate does indeed have the majority, we have a winner!
    if (potential_winners == 1)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes == highest_votes && candidates[i].votes > majority_vote)
            {
                printf("%s\n", candidates[i].name);
                return true;
            }
        }
    }

    // Otherwise, return false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int smallest_votes = candidates[0].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        // If the candidate is eliminated, skip
        if (candidates[i].eliminated == true)
        {
            i++;
            continue;
        }

        if (candidates[i].votes < smallest_votes)
        {
            smallest_votes = candidates[i].votes;
        }
    }

    return smallest_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    // Iterate through the candidates array and check if each one of them are the same
    // Check to see if they are eliminated as well
    int ties = 0;
    int eliminated_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            ties++;
        }

        if (candidates[i].eliminated == true)
        {
            eliminated_count++;
        }
    }

    // If they're all tied, minus those that are eliminated, return true
    if (ties == candidate_count - eliminated_count)
    {
        return true;
    }

    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    // Find the candidate(s) with the least amount of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
