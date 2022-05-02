#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

bool vote(string name);
void print_winner(void);

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate candidates[9];
int numberOfCandidates = 0;

int main(int argc, string argv[])
{
    numberOfCandidates = argc - 1;
    if (numberOfCandidates > 1 && numberOfCandidates < 10)
    {
        for (int i=0; i<numberOfCandidates; i++)
        {
            candidates[i].name = argv[i+1];
            printf("Candidate: %s\n", candidates[i].name);
            candidates[i].votes = 0;
        }

        int voters = get_int("How many voters? \n");
        string voteName;
        for (int j=0; j<voters; j++)
        {
            voteName = get_string("Vote: ");
            vote(voteName);
        }

        for (int l=0; l<numberOfCandidates; l++)
        {
            printf("%s has %i votes\n", candidates[l].name, candidates[l].votes);
        }

        print_winner();

    }
    else
    {
        printf("Usage: ./plurality and name of candidates\n");
    }
}

bool vote(string name)
{
    for (int k=0; k<numberOfCandidates; k++)
            {
                if (strcmp(name, candidates[k].name) == 0)
                {
                    printf("Yes!\n");
                    candidates[k].votes = candidates[k].votes + 1;
                    printf("%i vote for %s\n", candidates[k].votes, candidates[k].name);
                    return true;
                }
                else
                {
                    printf("No!\n");
                }
            }
            return false;
}

void print_winner(void)
{
    int currentVotesNumber = 0;
    for (int i=0; i<numberOfCandidates; i++)
    {
        if (candidates[i].votes > currentVotesNumber)
        {
            currentVotesNumber = candidates[i].votes;
        }
    }
    for (int j=0; j<numberOfCandidates; j++)
    {
        if (candidates[j].votes == currentVotesNumber)
        {
            printf("Winner is %s with votes: %i\n", candidates[j].name, currentVotesNumber);
        }
    }
}