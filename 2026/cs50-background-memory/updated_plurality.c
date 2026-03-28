#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Candidates have name, vote count, eliminated status
typedef struct
{
    char *name;
    int votes;
} candidate;

// Array of candidates
candidate *candidates;

// Number of candidates
int candidate_count;

bool vote(char *name);
void print_winner(void);
candidate create_struct(char *name);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    // allocate memory for candidates
    size_t candidates_size = (sizeof(candidate) * candidate_count);
    candidates = malloc(candidates_size);

    if (candidates == NULL)
    {
        printf("Memory error.\n");
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidate new = create_struct(argv[i + 1]);
        if (new.name == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(candidates[j].name);
            }
            free(candidates);
            return 3;
        }
        candidates[i] = new;
    }

    // sanity check
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].name != NULL)
        {
            printf("%s\n", candidates[i].name);
        }

    }

    // Run election
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char *name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();

    // Free Candidates List
    for (int i = 0; i < candidate_count; i++)
    {
        free(candidates[i].name);
    }
    free(candidates);

    return 0;
}

bool vote(char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

void print_winner(void)
{
    int top_votes = -1;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > top_votes){
            top_votes = candidates[i].votes;
        }
    }

    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == top_votes) {
            printf("%s\n", candidates[j].name);
        }
    }
}

candidate create_struct(char *name)
{
    candidate new_candidate;
    new_candidate.name = malloc(strlen(name) + 1);
    if (new_candidate.name == NULL){
        printf("Memory error copying name: %s\n", name);
        return new_candidate;
    }
    strcpy(new_candidate.name, name);
    new_candidate.votes = 0;
    return new_candidate;
}
