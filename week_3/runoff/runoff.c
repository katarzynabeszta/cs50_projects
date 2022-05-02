#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool vote (int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
bool is_tie (int min);
int find_min(void);
void eliminate (int min);

#define MAX_CANDIDATES 9
#define MAX_VOTERS 7

int voter_count;
int candidate_count;
bool winner_found = false;

typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES];
int preferences [MAX_VOTERS][MAX_CANDIDATES];

int main (int argc, string argv[])
{
    if (argc>1 && argc <=MAX_CANDIDATES)
    {
        candidate_count = argc - 1;
        for (int a=0; a<candidate_count; a++)
        {
            candidates[a].name = argv[a+1];
            candidates[a].votes = 0;
            candidates[a].eliminated = false;
            printf("Name of %i candidate: %s\n", a+1, candidates[a].name);
        }

        voter_count = get_int("How many voters?\n");
        if (voter_count>0 && voter_count<=MAX_VOTERS)
        {
            for (int i=0; i<voter_count; i++)
            {
                printf("Voter %i\n", i+1);
                for(int j=0; j<candidate_count; j++)
                {
                    string preference_name = get_string("Rank %i: \n", j+1);
                    bool vote_status = vote (i, j, preference_name);
                    if (vote_status == false)
                    {
                        return 1;
                    }
                }
            }
            while (winner_found == false)
            {
                tabulate();
                winner_found = print_winner();

                for (int x=0; x<candidate_count; x++)
                {
                    printf("Candidate %s have %i votes\n", candidates[x].name, candidates[x].votes);
                }

                if (winner_found == false)
                {
                    int fewest_votes_candidate = find_min();
                    printf("Fewest votes is: %i\n", fewest_votes_candidate);
                    is_tie (fewest_votes_candidate);
                    bool tie = is_tie(fewest_votes_candidate);
                    printf("Tie status: %d\n", tie);
                    eliminate (fewest_votes_candidate);
                }
            }
        }
        else
        {
            printf("Minium number of voters is 1 and maximum is %i.\n", MAX_VOTERS);
        }
    }
    else
    {
        printf("Usage: ./runoff and names of candidates\n");
    }
}


bool vote (int voter, int rank, string name)
{
    for (int l=0; l<candidate_count; l++)
    {
        if (strcmp(candidates[l].name, name) == 0)
        {
            printf("Found %s\n", name);
            int rank_index = l;
            preferences[voter][rank] = rank_index;
            return true;
        }
    }
    printf("Incorrect candidate name! Election have to be rerun.\n");
    return false;
}


void tabulate(void)
{
    for (int k=0; k<candidate_count; k++)
    {
        candidates[k].votes = 0;
    }
    int voted_candidate_index;
    for (int i=0; i<voter_count; i++)
    {
        for (int j=0; j<candidate_count; j++)
        {
            voted_candidate_index = preferences[i][j];
            if (candidates[voted_candidate_index].eliminated == false)
            {
                break;
            }
        }
        candidates[voted_candidate_index].votes = candidates[voted_candidate_index].votes + 1;
        printf("Total votes for %s: %i\n", candidates[voted_candidate_index].name, candidates[voted_candidate_index].votes);
    }
}


bool print_winner(void)
{
    int min_votes_to_win = (voter_count/2)+1;
    for (int i=0; i<candidate_count; i++)
    {
        if (candidates[i].votes >= min_votes_to_win)
        {
            printf("Winner is: %s\n", candidates[i].name);
            return true;
        }
    }
    printf("Winner not found yet!\n");
    return false;
}


int find_min (void)
{
    int fewest_votes_candidate = voter_count;
    string candidate_fewest_name;

    for (int b=0; b<candidate_count; b++)
    {
        if (candidates[b].eliminated == false && candidates[b].votes < fewest_votes_candidate)
        {
            fewest_votes_candidate = candidates[b].votes;
            candidate_fewest_name = candidates[b].name;
        }
    }
    return fewest_votes_candidate;
}


bool is_tie (int min)
{
    for (int l=0; l<candidate_count ; l++)
    {
        if (candidates[l].eliminated == false && candidates[l].votes != min)
        {
            return false;
        }
    }
    return true;
}


void eliminate (int min)
{
    for (int n=0; n<candidate_count ; n++)
    {
        if (candidates[n].votes == min)
        {
            candidates[n].eliminated = true;
            printf("Wyeliminowany %s\n", candidates[n].name);
        }
    }
}