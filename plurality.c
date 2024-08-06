#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    char* name;
    int votes;
} 
candidate;

// Array of candidates
candidate candidates[MAX];
 
// Number of candidates
int candidate_count;

// Function prototypes
int vote(char* name);
void print_winner(void);

int main(int argc, char* argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count;  
    printf("How many votes were there? \n");
    scanf("%i", &voter_count);

    // Loop over all voters
    char name[100]; 
    for (int i = 0; i < voter_count; i++)
    {
        printf("Vote: ");
        fgets(name, sizeof(name), stdin); 
        name[strcspn(name, "\n")] = '\0';
         // Check for invalid vote
        if (vote(name) == 0) 
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
int vote(char* name) // False == 0 & True == 1
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return 1;
        }
    }
    return 0;
}

// Print the winner (or winners) of the election 
void print_winner(void)
{
    int min_index;
    printf("The candidate/s with the most votes is/are: \n");
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int max_index = i;
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (candidates[j].votes > candidates[max_index].votes)
            {
                max_index = j;
            }
        }
        if (max_index != i)
        {
            candidate temp = candidates[i];
            candidates[i] = candidates[max_index];
            candidates[max_index] = temp;
        }
    }
    int counter = 0;
    while (candidates[counter].votes == candidates[candidate_count].votes && counter < candidate_count)
    {
        printf("%s\n", candidates[counter].name); 
        counter++; 
    }
    return;
}